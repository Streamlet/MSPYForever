//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlWinHttp.h
//    Author:      Streamlet
//    Create Time: 2013-05-15
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLWINHTTP_H_AABABE1B_FA77_496D_AE29_1FE0DDDF7436_INCLUDED__
#define __XLWINHTTP_H_AABABE1B_FA77_496D_AE29_1FE0DDDF7436_INCLUDED__


#include <xl/Meta/xlUtility.h>
#include <Windows.h>
#include <WinHttp.h>
#include <tchar.h>

namespace xl
{
    template <bool bManaged = true>
    class WinHttpHandleT : public NonCopyable
    {
    public:
        WinHttpHandleT(HINTERNET hInternet = nullptr) :
            m_hInternet(hInternet)
        {
        
        }
        
        ~WinHttpHandleT()
        {
            if (bManaged)
            {
                Close();
            }
            else
            {
                Detach();
            }
        }

    public:
        HINTERNET Attach(HINTERNET hInternet)
        {
            HINTERNET hPrevious = m_hInternet;
            m_hInternet = hInternet;
            return hPrevious;
        }

        HINTERNET Detach()
        {
            return Attach(nullptr);
        }

        bool Close()
        {
            if (m_hInternet == nullptr)
            {
                return true;
            }

            if (!WinHttpCloseHandle(m_hInternet))
            {
                return false;
            }

            return true;
        }

    public:
        bool SetOption(DWORD dwOption, LPCVOID lpBuffer, DWORD dwBufferLength)
        {
            if (!WinHttpSetOption(m_hInternet, dwOption, lpBuffer, dwBufferLength))
            {
                return false;
            }

            return true;
        }

        WINHTTP_STATUS_CALLBACK SetStatusCallback(WINHTTP_STATUS_CALLBACK lpfnInternetCallback, DWORD dwNotificationFlags)
        {
            return WinHttpSetStatusCallback(m_hInternet, lpfnInternetCallback, dwNotificationFlags, 0);
        }

        bool QueryOption(DWORD dwOption, LPVOID lpBuffer, LPDWORD lpdwBufferLength)
        {
            if (!WinHttpQueryOption(m_hInternet, dwOption, lpBuffer, lpdwBufferLength))
            {
                return false;
            }

            return true;
        }

    public:
        operator HINTERNET() const
        {
            return m_hInternet;
        }

    protected:
        HINTERNET m_hInternet;
    };

    typedef WinHttpHandleT<> WinHttpHandle;

    class WinHttpSession : public WinHttpHandle
    {
    public:
        WinHttpSession()
        {

        }

        ~WinHttpSession()
        {

        }

    public:
        bool Initialize(LPCWSTR lpUserAgent = L"",
                        DWORD dwAccessType = WINHTTP_ACCESS_TYPE_NO_PROXY,
                        LPCWSTR lpszProxyName = WINHTTP_NO_PROXY_NAME,
                        LPCWSTR lpszProxyBypass = WINHTTP_NO_PROXY_BYPASS)
        {
            m_hInternet = WinHttpOpen(lpUserAgent, dwAccessType, lpszProxyName, lpszProxyBypass, WINHTTP_FLAG_ASYNC);

            if (m_hInternet == nullptr)
            {
                return false;
            }
        
            return true;
        }
    };

    class WinHttpConnection : public WinHttpHandle
    {
    public:
        WinHttpConnection() :
            m_bSsl(false)
        {

        }

        ~WinHttpConnection()
        {

        }

    public:
        bool Initialize(const WinHttpSession &session, LPCWSTR lpszServerName, INTERNET_PORT nServerPort = INTERNET_DEFAULT_PORT, bool bSsl = false)
        {
            m_hInternet = WinHttpConnect(session, lpszServerName, nServerPort, 0);

            if (m_hInternet == nullptr)
            {
                return false;
            }

            m_bSsl = bSsl;
        
            return true;
        }

        bool IsSsl() const
        {
            return m_bSsl;
        }

    protected:
        bool m_bSsl;
    };

    template <typename T>
    class WinHttpRequest : public WinHttpHandle
    {
    public:
        WinHttpRequest()
        {

        }

        ~WinHttpRequest()
        {

        }

    public:
        bool Initialize(const WinHttpConnection &connection,
                        LPCWSTR lpszVerb,
                        LPCWSTR lpszObjectName,
                        LPCWSTR lpszVersion = nullptr,
                        LPCWSTR lpszReferrer = nullptr,
                        LPCWSTR *ppwszAcceptTypes = WINHTTP_DEFAULT_ACCEPT_TYPES,
                        DWORD dwFlags = 0)
        {
            if (connection.IsSsl())
            {
                dwFlags |= WINHTTP_FLAG_SECURE;
            }

            m_hInternet = WinHttpOpenRequest(connection,
                                             lpszVerb,
                                             lpszObjectName,
                                             lpszVersion,
                                             lpszReferrer,
                                             ppwszAcceptTypes,
                                             dwFlags);

            if (m_hInternet == nullptr)
            {
                return false;
            }

            SetStatusCallback(StaticWinHttpStatusCallback, WINHTTP_CALLBACK_FLAG_ALL_COMPLETIONS);
        
            return true;
        }

    public:
        bool AddRequestHeaders(LPCWSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwModifiers)
        {
            if (!WinHttpAddRequestHeaders(m_hInternet, lpszHeaders, dwHeadersLength, dwModifiers))
            {
                return false;
            }

            return true;
        }

        bool QueryAuthSchemes(LPDWORD lpdwSupportedSchemes, LPDWORD lpdwFirstScheme, LPDWORD pdwAuthTarget)
        {
            if (!WinHttpQueryAuthSchemes(m_hInternet, lpdwSupportedSchemes, lpdwFirstScheme, pdwAuthTarget))
            {
                return false;
            }

            return true;
        }

        bool QueryDataAvailable(LPDWORD lpdwNumberOfBytesAvailable)
        {
            if (!WinHttpQueryDataAvailable(m_hInternet, lpdwNumberOfBytesAvailable))
            {
                return false;
            }

            return true;
        }

        bool QueryHeaders(DWORD dwInfoLevel, LPCWSTR lpszName, LPVOID lpBuffer, LPDWORD lpdwBufferLength, LPDWORD lpdwIndex)
        {
            if (!WinHttpQueryHeaders(m_hInternet,
                                     dwInfoLevel,
                                     lpszName,
                                     lpBuffer,
                                     lpdwBufferLength,
                                     lpdwIndex))
            {
                return false;
            }

            return true;
        }
        
        bool ReadData(LPVOID lpBuffer, DWORD dwNumberOfBytesToRead, LPDWORD lpdwNumberOfBytesRead)
        {
            if (!WinHttpReadData(m_hInternet,
                                 lpBuffer,
                                 dwNumberOfBytesToRead,
                                 lpdwNumberOfBytesRead))
            {
                return false;
            }

            return true;
        }

        bool ReceiveResponse()
        {
            if (!WinHttpReceiveResponse(m_hInternet, nullptr))
            {
                return false;
            }

            return true;
        }

        bool SendRequest(LPCWSTR lpszHeaders, DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength, DWORD dwTotalLength)
        {
            if (!WinHttpSendRequest(m_hInternet,
                                    lpszHeaders,
                                    dwHeadersLength,
                                    lpOptional,
                                    dwOptionalLength,
                                    dwTotalLength,
                                    static_cast<T *>(this)))
            {
                return false;
            }

            return true;
        }

        bool SetCredentials(DWORD dwAuthTargets,
                            DWORD dwAuthScheme,
                            LPCWSTR lpszUserName,
                            LPCWSTR lpszPassword,
                            LPVOID pAuthParams)
        {
            if (!WinHttpSetCredentials(m_hInternet, dwAuthTargets, dwAuthScheme, lpszUserName, lpszPassword, pAuthParams))
            {
                return false;
            }

            return true;
        }

        bool WriteData(LPCVOID lpBuffer, DWORD dwNumberOfBytesToWrite, LPDWORD lpdwNumberOfBytesWritten)
        {
            if (!WinHttpWriteData(m_hInternet, lpBuffer, dwNumberOfBytesToWrite, lpdwNumberOfBytesWritten))
            {
                return false;
            }

            return true;
        }

    private:
        static void CALLBACK StaticWinHttpStatusCallback(HINTERNET hInternet,
                                                         DWORD_PTR dwContext,
                                                         DWORD dwInternetStatus,
                                                         LPVOID lpvStatusInformation,
                                                         DWORD dwStatusInformationLength)
        {
            T *pT = reinterpret_cast<T *>(dwContext);

            if (hInternet == pT->m_hInternet)
            {
                pT->OnCallback(dwInternetStatus,
                               lpvStatusInformation,
                               dwStatusInformationLength);
            }
        }
    };

} // namespace xl

#endif // #ifndef __XLWINHTTP_H_AABABE1B_FA77_496D_AE29_1FE0DDDF7436_INCLUDED__
