//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlHttpIO.h
//    Author:      Streamlet
//    Create Time: 2013-05-16
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLHTTPIO_H_460379E8_2E79_435E_BFD9_C6B5E2F28A66_INCLUDED__
#define __XLHTTPIO_H_460379E8_2E79_435E_BFD9_C6B5E2F28A66_INCLUDED__


#include "../../Common/Containers/xlArray.h"
#include "../../Common/Memory/xlSmartPtr.h"
#include "../../Common/Meta/xlFunction.h"
#include "../../Common/Meta/xlScopeExit.h"
#include "../../Common/String/xlString.h"
#include "../Threads/xlEvent.h"
#include "xlWinHttp.h"
#include <stdio.h>

namespace xl
{
    namespace Windows
    {
        typedef xl::Function<bool(xl::Array<BYTE> *pArrayOut)> HttpIOLocalReader;
        typedef xl::Function<bool(LPCVOID lpBuffer, DWORD cbSize)> HttpIOLocalWriter;
        typedef xl::Function<bool(ULONGLONG qwTotalSize, ULONGLONG qwSolvedSize)> HttpIONotifier;

        class HttpIO : public WinHttpRequest
        {
        public:
            HttpIO() :
                m_dwBytesAvailable(0), m_dwBytesRead(0), m_dwBytesWritten(0)
            {
                m_eventReady.Create(nullptr, FALSE, FALSE, nullptr);
                m_eventFailed.Create(nullptr, FALSE, FALSE, nullptr);
            }

            ~HttpIO()
            {

            }

        public:
            bool SendRequest(LPCWSTR lpExtraHeader,
                HANDLE  hEventCancel,
                DWORD   dwCbDataSize = 0,
                HttpIOLocalReader fnRead = nullptr,
                HttpIONotifier    fnUploadNotifier = nullptr)
            {
                xl::ScopeGuard sgCancelRequest = xl::MakeGuard(xl::Bind(this, &HttpIO::Close));

                if (!WinHttpRequest::SendRequest(lpExtraHeader,
                    -1,
                    WINHTTP_NO_REQUEST_DATA,
                    0,
                    dwCbDataSize))
                {
                    return false;
                }

                enum
                {
                    EVENT_READY = 0,
                    EVENT_FAILED,
                    EVENT_CANCEL,
                    EVENT_COUNT
                };

                DWORD dwEvents = hEventCancel == nullptr ? EVENT_COUNT - 1 : EVENT_COUNT;
                HANDLE lpHandles[] = { m_eventReady, m_eventFailed, hEventCancel };
                DWORD dwWaitResult = WaitForMultipleObjects(dwEvents, lpHandles, FALSE, INFINITE);

                if (dwWaitResult != EVENT_READY)
                {
                    return false;
                }

                DWORD dwCbDataRemain = dwCbDataSize;

                if (fnRead != nullptr)
                {
                    if (fnUploadNotifier != nullptr)
                    {
                        if (!fnUploadNotifier(dwCbDataSize, dwCbDataSize - dwCbDataRemain))
                        {
                            return false;
                        }
                    }
                }

                while (dwCbDataRemain > 0)
                {
                    if (fnRead == nullptr)
                    {
                        return false;
                    }

                    xl::Array<BYTE> arrBuffer;

                    if (!fnRead(&arrBuffer))
                    {
                        return false;
                    }

                    DWORD dwSize = (DWORD)arrBuffer.Size();

                    if (dwSize > dwCbDataRemain)
                    {
                        return false;
                    }

                    DWORD dwRemain = dwSize;

                    while (dwRemain > 0)
                    {
                        LPCVOID lpBuffer = &arrBuffer[0] + dwSize - dwRemain;
                        DWORD dwToWrite = dwRemain;

                        if (!WriteData(lpBuffer, dwToWrite, nullptr))
                        {
                            return false;
                        }

                        DWORD dwWaitResult = WaitForMultipleObjects(dwEvents, lpHandles, FALSE, INFINITE);

                        if (dwWaitResult != EVENT_READY)
                        {
                            return false;
                        }

                        dwRemain -= m_dwBytesWritten;
                    }

                    dwCbDataRemain -= dwSize;

                    if (fnUploadNotifier != nullptr)
                    {
                        if (!fnUploadNotifier(dwCbDataSize, dwCbDataSize - dwCbDataRemain))
                        {
                            return false;
                        }
                    }
                }

                if (!ReceiveResponse())
                {
                    return false;
                }

                dwWaitResult = WaitForMultipleObjects(dwEvents, lpHandles, FALSE, INFINITE);

                if (dwWaitResult != EVENT_READY)
                {
                    return false;
                }

                sgCancelRequest.Dismiss();

                return true;
            }

            xl::String QueryHeader(DWORD dwInfoLevel)
            {
                DWORD dwSize = 0;

                if (QueryHeaders(dwInfoLevel, WINHTTP_HEADER_NAME_BY_INDEX, WINHTTP_NO_OUTPUT_BUFFER, &dwSize, WINHTTP_NO_HEADER_INDEX))
                {
                    return false;
                }

                DWORD dwError = GetLastError();

                if (dwError != ERROR_INSUFFICIENT_BUFFER)
                {
                    return false;
                }

                xl::SharedArray<wchar_t> spBuffer(new wchar_t[dwSize]);

                if (!QueryHeaders(dwInfoLevel, WINHTTP_HEADER_NAME_BY_INDEX, spBuffer.RawPointer(), &dwSize, WINHTTP_NO_HEADER_INDEX))
                {
                    return false;
                }

                return spBuffer.RawPointer();
            }

            bool ReceiveRespionse(HANDLE hEventCancel,
                HttpIOLocalWriter fnWrite = nullptr,
                HttpIONotifier    fnDownloadNotifier = nullptr)
            {
                ULONGLONG qwContentLength = 0;
                xl::String strContentLength = QueryHeader(WINHTTP_QUERY_CONTENT_LENGTH);

                if (!strContentLength.Empty())
                {
                    swscanf_s(strContentLength, L"%llu", &qwContentLength);
                }

                if (fnWrite == nullptr)
                {
                    return true;
                }

                enum
                {
                    EVENT_READY = 0,
                    EVENT_FAILED,
                    EVENT_CANCEL,
                    EVENT_COUNT
                };

                DWORD dwEvents = hEventCancel == nullptr ? EVENT_COUNT - 1 : EVENT_COUNT;
                HANDLE lpHandles[] = { m_eventReady, m_eventFailed, hEventCancel };
                DWORD dwWaitResult = 0;

                ULONGLONG qwDownloaded = 0;
                const DWORD BUFFER_SIZE = 4096;
                BYTE BUFFER[BUFFER_SIZE];

                if (fnDownloadNotifier != nullptr)
                {
                    if (!fnDownloadNotifier(qwContentLength, qwDownloaded))
                    {
                        return false;
                    }
                }

                while (qwContentLength == 0 || qwDownloaded < qwContentLength)
                {
                    if (!QueryDataAvailable(nullptr))
                    {
                        return false;
                    }

                    dwWaitResult = WaitForMultipleObjects(dwEvents, lpHandles, FALSE, INFINITE);

                    if (dwWaitResult != EVENT_READY)
                    {
                        return false;
                    }

                    if (m_dwBytesAvailable == 0)
                    {
                        break;
                    }

                    while (m_dwBytesAvailable > 0)
                    {
                        DWORD dwBytesToRead = (m_dwBytesAvailable < BUFFER_SIZE ? m_dwBytesAvailable : BUFFER_SIZE);

                        if (!ReadData(BUFFER, dwBytesToRead, nullptr))
                        {
                            return false;
                        }

                        dwWaitResult = WaitForMultipleObjects(dwEvents, lpHandles, FALSE, INFINITE);

                        if (dwWaitResult != EVENT_READY)
                        {
                            return false;
                        }

                        if (!fnWrite(BUFFER, m_dwBytesRead))
                        {
                            return false;
                        }

                        m_dwBytesAvailable -= m_dwBytesRead;
                        qwDownloaded += m_dwBytesRead;
                    }

                    if (fnDownloadNotifier != nullptr)
                    {
                        if (!fnDownloadNotifier(qwContentLength, qwDownloaded))
                        {
                            return false;
                        }
                    }
                }

                return true;
            }

        protected:
            virtual void OnSendRequestComplete()
            {
                m_eventReady.Set();
            }

            virtual void OnHeadersAvaiable()
            {
                m_eventReady.Set();
            }

            virtual void OnDataAvailable(DWORD cbSize)
            {
                m_dwBytesAvailable = cbSize;
                m_eventReady.Set();
            }

            virtual void OnReadComplete(DWORD cbSizeRead)
            {
                m_dwBytesRead = cbSizeRead;
                m_eventReady.Set();
            }

            virtual void OnWriteComplete(DWORD cbWritten)
            {
                m_dwBytesWritten = cbWritten;
                m_eventReady.Set();
            }

            virtual void OnRequestError(const WINHTTP_ASYNC_RESULT &result)
            {
                m_eventFailed.Set();
            }

        private:
            Event m_eventReady;
            Event m_eventFailed;
            DWORD m_dwBytesAvailable;
            DWORD m_dwBytesRead;
            DWORD m_dwBytesWritten;
        };

        class HttpRestIO : public HttpIO
        {
        public:
            HttpRestIO()
            {

            }

            ~HttpRestIO()
            {

            }

        public:
            bool SendRequest(LPCWSTR lpHeaders,
                LPVOID lpData,
                DWORD dwDataSize,
                HANDLE hEventCancel,
                xl::Array<BYTE> *pContent)
            {
                if (!HttpIO::SendRequest(lpHeaders,
                    hEventCancel,
                    dwDataSize,
                    xl::Bind(this, &HttpRestIO::HttpIOCallback, lpData, dwDataSize, xl::_1)))
                {
                    return false;
                }

                if (!ReceiveRespionse(hEventCancel,
                    xl::Bind(this, &HttpRestIO::HttpIOCallback, xl::_1, xl::_2, pContent)))
                {
                    return false;
                }

                return true;
            }

        protected:
            bool HttpIOCallback(LPCVOID lpBuffer, DWORD cbSize, xl::Array<BYTE> *pArrayOut)
            {
                if (pArrayOut == nullptr)
                {
                    return false;
                }

                pArrayOut->Insert(pArrayOut->Size(), (const BYTE *)lpBuffer, cbSize);

                return true;
            }
        };

        typedef xl::Function<bool(ULONGLONG qwTotalSize, ULONGLONG qwSolvedSize)> HttpProgressNotifier;

        class HttpUploader : public HttpIO
        {
        public:
            HttpUploader()
            {

            }

            ~HttpUploader()
            {

            }

        public:
            bool SendRequest(LPCWSTR lpHeaders,
                LPCTSTR lpLocalFile,
                HANDLE hEventCancel,
                xl::Array<BYTE> *pResponse,
                HttpProgressNotifier fnProgressNotifier = nullptr)
            {
                HANDLE hFile = CreateFile(lpLocalFile, GENERIC_READ, 0, nullptr, OPEN_EXISTING, 0, nullptr);

                if (hFile == INVALID_HANDLE_VALUE)
                {
                    return false;
                }

                LARGE_INTEGER li = {};

                if (!GetFileSizeEx(hFile, &li))
                {
                    return false;
                }

                if (li.HighPart > 0)
                {
                    return false;
                }

                XL_ON_BLOCK_EXIT(CloseHandle, hFile);

                if (!HttpIO::SendRequest(lpHeaders,
                    hEventCancel,
                    li.LowPart,
                    xl::Bind(this, &HttpUploader::HttpIOReader, hFile, xl::_1),
                    fnProgressNotifier))
                {
                    return false;
                }

                if (!ReceiveRespionse(hEventCancel,
                    xl::Bind(this, &HttpUploader::HttpIOWriter, xl::_1, xl::_2, pResponse),
                    nullptr))
                {
                    return false;
                }

                return true;
            }

        protected:
            bool HttpIOReader(HANDLE hFile, xl::Array<BYTE> *pArrayOut)
            {
                if (hFile == nullptr)
                {
                    return false;
                }

                const DWORD BUFFER_SIZE = 4096;
                pArrayOut->Resize(BUFFER_SIZE);
                DWORD dwRead = 0;

                if (!ReadFile(hFile, &(*pArrayOut)[0], BUFFER_SIZE, &dwRead, nullptr))
                {
                    return false;
                }

                if (dwRead != BUFFER_SIZE)
                {
                    pArrayOut->Delete(dwRead, BUFFER_SIZE - dwRead);
                }

                return true;
            }

            bool HttpIOWriter(LPCVOID lpBuffer, DWORD cbSize, xl::Array<BYTE> *pArrayOut)
            {
                if (pArrayOut == nullptr)
                {
                    return true;
                }

                pArrayOut->Insert(pArrayOut->Size(), (const BYTE *)lpBuffer, cbSize);

                return true;
            }
        };

        class HttpDownloader : public HttpIO
        {
        public:
            HttpDownloader()
            {

            }

            ~HttpDownloader()
            {

            }

        public:
            bool SendRequest(LPCWSTR lpHeaders,
                LPVOID lpData,
                DWORD dwDataSize,
                HANDLE hEventCancel,
                LPCTSTR lpLocalFile,
                HttpProgressNotifier fnProgressNotifier = nullptr)
            {
                HANDLE hFile = CreateFile(lpLocalFile, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);

                if (hFile == INVALID_HANDLE_VALUE)
                {
                    return false;
                }

                XL_ON_BLOCK_EXIT(CloseHandle, hFile);

                if (!HttpIO::SendRequest(lpHeaders,
                    hEventCancel,
                    dwDataSize,
                    xl::Bind(this, &HttpDownloader::HttpIOReader, lpData, dwDataSize, xl::_1),
                    nullptr))
                {
                    return false;
                }

                if (!ReceiveRespionse(hEventCancel,
                    xl::Bind(this, &HttpDownloader::HttpIOWriter, xl::_1, xl::_2, hFile),
                    fnProgressNotifier))
                {
                    return false;
                }

                return true;
            }

        protected:
            bool HttpIOReader(LPCVOID lpBuffer, DWORD cbSize, xl::Array<BYTE> *pArrayOut)
            {
                if (pArrayOut == nullptr)
                {
                    return false;
                }

                pArrayOut->Insert(pArrayOut->Size(), (const BYTE *)lpBuffer, cbSize);

                return true;
            }

            bool HttpIOWriter(LPCVOID lpBuffer, DWORD cbSize, HANDLE hFile)
            {
                if (hFile == nullptr)
                {
                    return false;
                }

                DWORD dwWrittern = 0;

                if (!WriteFile(hFile, lpBuffer, cbSize, &dwWrittern, nullptr) || dwWrittern != cbSize)
                {
                    return false;
                }

                return true;
            }
        };

        inline bool SimpleHttpRestIO(LPCWSTR lpVerb,
            LPCWSTR lpUrl,
            LPCWSTR lpHeaders,
            LPVOID lpData,
            DWORD dwDataSize,
            HANDLE hEventCancel,
            xl::Array<BYTE> *pContent)
        {
            String strHostName, strUrlPath;
            bool bSecure = false;

            if (!WinHttpUtils::CrackUrl(lpUrl, &strHostName, &strUrlPath, &bSecure))
            {
                return false;
            }

            WinHttpSession session;

            if (!session.Initialize(L"SimpleHttpRestIO"))
            {
                return false;
            }

            WinHttpConnection connection;

            if (!connection.Initialize(session,
                strHostName,
                bSecure ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT,
                bSecure))
            {
                return false;
            }

            HttpRestIO request;

            if (!request.Initialize(connection,
                lpVerb,
                strUrlPath))
            {
                return false;
            }

            if (!request.SendRequest(lpHeaders, lpData, dwDataSize, hEventCancel, pContent))
            {
                return false;
            }

            return true;
        }

        inline bool SimpleHttpUpload(LPCWSTR lpVerb,
            LPCWSTR lpUrl,
            LPCWSTR lpHeaders,
            LPCWSTR lpLocalFile,
            HANDLE hEventCancel,
            xl::Array<BYTE> *pResponse,
            HttpProgressNotifier fnProgressNotifier = nullptr)
        {
            String strHostName, strUrlPath;
            bool bSecure = false;

            if (!WinHttpUtils::CrackUrl(lpUrl, &strHostName, &strUrlPath, &bSecure))
            {
                return false;
            }

            WinHttpSession session;

            if (!session.Initialize(L"SimpleHttpUpload"))
            {
                return false;
            }

            WinHttpConnection connection;

            if (!connection.Initialize(session,
                strHostName,
                bSecure ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT,
                bSecure))
            {
                return false;
            }

            HttpUploader request;

            if (!request.Initialize(connection,
                lpVerb,
                strUrlPath))
            {
                return false;
            }

            if (!request.SendRequest(lpHeaders, lpLocalFile, hEventCancel, pResponse, fnProgressNotifier))
            {
                return false;
            }

            return true;
        }

        inline bool SimpleHttpDownload(LPCTSTR lpVerb,
            LPCTSTR lpUrl,
            LPCTSTR lpHeaders,
            LPVOID lpData,
            DWORD dwDataSize,
            HANDLE hEventCancel,
            LPCTSTR lpLocalFile,
            HttpProgressNotifier fnProgressNotifier = nullptr)
        {
            String strHostName, strUrlPath;
            bool bSecure = false;

            if (!WinHttpUtils::CrackUrl(lpUrl, &strHostName, &strUrlPath, &bSecure))
            {
                return false;
            }

            WinHttpSession session;

            if (!session.Initialize(L"SimpleHttpDownload"))
            {
                return false;
            }

            WinHttpConnection connection;

            if (!connection.Initialize(session,
                strHostName,
                bSecure ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT,
                bSecure))
            {
                return false;
            }

            HttpDownloader request;

            if (!request.Initialize(connection,
                lpVerb,
                strUrlPath))
            {
                return false;
            }

            if (!request.SendRequest(lpHeaders, lpData, dwDataSize, hEventCancel, lpLocalFile, fnProgressNotifier))
            {
                return false;
            }

            return true;
        }

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLHTTPIO_H_460379E8_2E79_435E_BFD9_C6B5E2F28A66_INCLUDED__
