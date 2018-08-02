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


#include "../../Common/Meta/xlNonInstantiable.h"
#include "../../Common/Meta/xlNonCopyable.h"
#include "../../Common/String/xlString.h"
#include "../xlWin32Ver.h"
#include <WinHttp.h>
#pragma comment(lib, "WinHttp.lib")

namespace xl
{
    namespace Windows
    {
        class WinHttpUtils : public NonInstantiable
        {
        public:
            static bool CheckPlatform()
            {
                if (!WinHttpCheckPlatform())
                {
                    return false;
                }

                return true;
            }

            static bool CrackUrl(LPCWSTR lpszUrl, DWORD dwUrlLength, DWORD dwFlags, LPURL_COMPONENTS lpUrlComponents)
            {
                if (!WinHttpCrackUrl(lpszUrl, dwUrlLength, dwFlags, lpUrlComponents))
                {
                    return false;
                }

                return true;
            }

            static bool CrackUrl(const String &strUrl, String *pHostName, String *pUrlPath, String *pExtroInfo, bool *pSecure = nullptr)
            {
                URL_COMPONENTS urlComp = { sizeof(URL_COMPONENTS) };

                urlComp.dwHostNameLength = (DWORD)-1;
                urlComp.dwUrlPathLength = (DWORD)-1;
                urlComp.dwExtraInfoLength = (DWORD)-1;

                if (!CrackUrl(strUrl, 0, 0, &urlComp))
                {
                    return false;
                }

                if (pHostName != nullptr)
                {
                    *pHostName = String(urlComp.lpszHostName, urlComp.dwHostNameLength);
                }

                if (pUrlPath != nullptr)
                {
                    *pUrlPath = String(urlComp.lpszUrlPath, urlComp.dwUrlPathLength);
                }

                if (pExtroInfo != nullptr)
                {
                    *pExtroInfo = String(urlComp.lpszExtraInfo, urlComp.dwExtraInfoLength);
                }

                if (pSecure != nullptr)
                {
                    *pSecure = (urlComp.nScheme == INTERNET_SCHEME_HTTPS);
                }

                return true;
            }

            static bool CrackUrl(const String &strUrl, String *pHostName, String *pUrlPath, bool *pSecure = nullptr)
            {
                String strUrlPath, strExtraInfo;

                if (!CrackUrl(strUrl, pHostName, &strUrlPath, &strExtraInfo, pSecure))
                {
                    return false;
                }

                if (pUrlPath != nullptr)
                {
                    *pUrlPath = strUrlPath + strExtraInfo;
                }

                return true;
            }

            static bool CreateUrl(LPURL_COMPONENTS lpUrlComponents, DWORD dwFlags, LPWSTR lpszUrl, LPDWORD lpdwUrlLength)
            {
                if (!WinHttpCreateUrl(lpUrlComponents, dwFlags, lpszUrl, lpdwUrlLength))
                {
                    return false;
                }

                return true;
            }

            static bool DetectAutoProxyConfigUrl(DWORD dwAutoDetectFlags, LPWSTR *ppwszAutoConfigUrl)
            {
                if (!WinHttpDetectAutoProxyConfigUrl(dwAutoDetectFlags, ppwszAutoConfigUrl))
                {
                    return false;
                }

                return true;
            }

            static bool GetDefaultProxyConfiguration(WINHTTP_PROXY_INFO *pProxyInfo)
            {
                if (!WinHttpGetDefaultProxyConfiguration(pProxyInfo))
                {
                    return false;
                }

                return true;
            }

            static bool GetIEProxyConfigForCurrentUser(WINHTTP_CURRENT_USER_IE_PROXY_CONFIG *pProxyConfig)
            {
                if (WinHttpGetIEProxyConfigForCurrentUser(pProxyConfig))
                {
                    return false;
                }

                return true;
            }

            static bool SetDefaultProxyConfiguration(WINHTTP_PROXY_INFO *pProxyInfo)
            {
                if (!WinHttpSetDefaultProxyConfiguration(pProxyInfo))
                {
                    return false;
                }

                return true;
            }

            static bool HttpTimeFromSystemTime(const SYSTEMTIME *pst, LPWSTR lpszTime)
            {
                if (!WinHttpTimeFromSystemTime(pst, lpszTime))
                {
                    return false;
                }

                return true;
            }

            static bool HttpTimeToSystemTime(LPCWSTR lpszTime, SYSTEMTIME *pst)
            {
                if (!WinHttpTimeToSystemTime(lpszTime, pst))
                {
                    return false;
                }

                return true;
            }
        };

        template <typename T, bool bManaged = true>
        class WinHttpHandleT : public NonCopyable,
            public T
        {
        public:
            WinHttpHandleT(HINTERNET hInternet = nullptr) :
                m_hInternet(nullptr)
            {
                Attach(hInternet);
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

                m_hInternet = nullptr;

                return true;
            }

        public:
            bool QueryOption(DWORD dwOption, LPVOID lpBuffer, LPDWORD lpdwBufferLength)
            {
                if (!WinHttpQueryOption(m_hInternet, dwOption, lpBuffer, lpdwBufferLength))
                {
                    return false;
                }

                return true;
            }

            bool SetOption(DWORD dwOption, LPCVOID lpBuffer, DWORD dwBufferLength)
            {
                if (!WinHttpSetOption(m_hInternet, dwOption, lpBuffer, dwBufferLength))
                {
                    return false;
                }

                return true;
            }

            WINHTTP_STATUS_CALLBACK SetStatusCallback(DWORD dwNotificationFlags)
            {
                return WinHttpSetStatusCallback(m_hInternet, &WinHttpHandleT::StatusCallback, dwNotificationFlags, 0);
            }

            bool SetTimeouts(int dwResolveTimeout, int dwConnectTimeout, int dwSendTimeout, int dwReceiveTimeout)
            {
                if (!WinHttpSetTimeouts(m_hInternet,
                    dwResolveTimeout,
                    dwConnectTimeout,
                    dwSendTimeout,
                    dwReceiveTimeout))
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
            static void CALLBACK StatusCallback(HINTERNET hInternet,
                DWORD_PTR dwContext,
                DWORD dwInternetStatus,
                LPVOID lpvStatusInformation,
                DWORD dwStatusInformationLength)
            {
                T *pT = reinterpret_cast<T *>(dwContext);
                WinHttpHandleT<T> *pHandle = dynamic_cast<WinHttpHandleT<T> *>(pT);

                if (pHandle != nullptr && hInternet == pHandle->m_hInternet)
                {
                    pHandle->OnCallback(dwInternetStatus,
                        lpvStatusInformation,
                        dwStatusInformationLength);
                }
            }

        protected:
            HINTERNET m_hInternet;
        };

        template <typename T>
        class WinHttpSessionT : public WinHttpHandleT<T>
        {
        public:
            WinHttpSessionT()
            {

            }

            ~WinHttpSessionT()
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

        public:
            bool GetProxyForUrl(LPCWSTR lpszUrl, WINHTTP_AUTOPROXY_OPTIONS *pAutoProxyOptions, WINHTTP_PROXY_INFO *pProxyInfo)
            {
                if (!WinHttpGetProxyForUrl(m_hInternet, lpszUrl, pAutoProxyOptions, pProxyInfo))
                {
                    return false;
                }

                return true;
            }

            DWORD ResetAutoProxy(DWORD dwFlags)
            {
                if (!WinHttpResetAutoProxy(m_hInternet, dwFlags))
                {
                    return false;
                }

                return true;
            }
        };

#if (WINVER >= 0x0602)
        class WinHttpProxyResult : public WINHTTP_PROXY_RESULT
        {
        public:
            WinHttpProxyResult()
            {
                cEntries = 0;
                pEntries = nullptr;
            }

            ~WinHttpProxyResult()
            {
                WinHttpFreeProxyResult(this);
            }
        };
#endif

        template <typename T>
        class WinHttpProxyResolverT : public WinHttpHandleT<T>
        {
        public:
            WinHttpProxyResolverT()
            {

            }

            ~WinHttpProxyResolverT()
            {

            }

        public:
            template <typename U>
            bool Initialize(const WinHttpSessionT<U> &session)
            {
                if (WinHttpCreateProxyResolver(session, &m_hInternet) != ERROR_SUCCESS)
                {
                    return false;
                }

                SetStatusCallback(WINHTTP_CALLBACK_FLAG_ALL_NOTIFICATIONS);

                return true;
            }

        public:
            DWORD GetProxyForUrl(LPCWSTR lpszUrl, WINHTTP_AUTOPROXY_OPTIONS *pAutoProxyOptions)
            {
                return WinHttpGetProxyForUrlEx(m_hInternet,
                    lpszUrl,
                    pAutoProxyOptions,
                    reinterpret_cast<DWORD_PTR>(static_cast<T *>(this)));
            }

#if (WINVER >= 0x0602)
            DWORD GetProxyResult(WinHttpProxyResult &result)
            {
                return WinHttpGetProxyResult(m_hInternet, &result);
            }
#endif
        };

        template <typename T>
        class WinHttpConnectionT : public WinHttpHandleT<T>
        {
        public:
            WinHttpConnectionT() :
                m_bSecure(false)
            {

            }

            ~WinHttpConnectionT()
            {

            }

        public:
            template <typename U>
            bool Initialize(const WinHttpSessionT<U> &session,
                LPCWSTR lpszServerName,
                INTERNET_PORT nServerPort = INTERNET_DEFAULT_PORT,
                bool bSecure = false)
            {
                m_hInternet = WinHttpConnect(session, lpszServerName, nServerPort, 0);

                if (m_hInternet == nullptr)
                {
                    return false;
                }

                m_bSecure = bSecure;

                return true;
            }

            bool IsSecure() const
            {
                return m_bSecure;
            }

        protected:
            bool m_bSecure;
        };

        template <typename T>
        class WinHttpRequestT : public WinHttpHandleT<T>
        {
        public:
            WinHttpRequestT()
            {

            }

            ~WinHttpRequestT()
            {

            }

        public:
            template <typename U>
            bool Initialize(const WinHttpConnectionT<U> &connection,
                LPCWSTR lpszVerb,
                LPCWSTR lpszObjectName,
                LPCWSTR lpszVersion = nullptr,
                LPCWSTR lpszReferrer = nullptr,
                LPCWSTR *ppwszAcceptTypes = WINHTTP_DEFAULT_ACCEPT_TYPES,
                DWORD dwFlags = 0)
            {
                if (connection.IsSecure())
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

                SetStatusCallback(WINHTTP_CALLBACK_FLAG_ALL_NOTIFICATIONS);

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

            bool SendRequest(LPCWSTR lpszHeaders = nullptr,
                DWORD dwHeadersLength = 0,
                LPVOID lpOptional = nullptr,
                DWORD dwOptionalLength = 0,
                DWORD dwTotalLength = 0)
            {
                if (!WinHttpSendRequest(m_hInternet,
                    lpszHeaders,
                    dwHeadersLength,
                    lpOptional,
                    dwOptionalLength,
                    dwTotalLength,
                    reinterpret_cast<DWORD_PTR>(static_cast<T *>(this))))
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
        };

        class WinHttpCallback
        {
        public:
            WinHttpCallback()
            {

            }

            ~WinHttpCallback()
            {

            }

        protected:
            void OnCallback(DWORD dwInternetStatus,
                LPVOID lpvStatusInformation,
                DWORD dwStatusInformationLength)
            {
                switch (dwInternetStatus)
                {
                case WINHTTP_CALLBACK_STATUS_CLOSING_CONNECTION:
                    OnClosingConnection();
                    break;
                case WINHTTP_CALLBACK_STATUS_CONNECTED_TO_SERVER:
                    OnConnectedToServer(static_cast<LPCWSTR>(lpvStatusInformation));
                    break;
                case WINHTTP_CALLBACK_STATUS_CONNECTING_TO_SERVER:
                    OnConnectingServer(static_cast<LPCWSTR>(lpvStatusInformation));
                    break;
                case WINHTTP_CALLBACK_STATUS_CONNECTION_CLOSED:
                    OnConnectionClosed();
                    break;
                case WINHTTP_CALLBACK_STATUS_DATA_AVAILABLE:
                    OnDataAvailable(*static_cast<DWORD *>(lpvStatusInformation));
                    break;
                case WINHTTP_CALLBACK_STATUS_HANDLE_CREATED:
                    OnHandleCreated(static_cast<HINTERNET>(lpvStatusInformation));
                    break;
                case WINHTTP_CALLBACK_STATUS_HANDLE_CLOSING:
                    OnHandleClosing(static_cast<HINTERNET>(lpvStatusInformation));
                    break;
                case WINHTTP_CALLBACK_STATUS_HEADERS_AVAILABLE:
                    OnHeadersAvaiable();
                    break;
                case WINHTTP_CALLBACK_STATUS_INTERMEDIATE_RESPONSE:
                    OnIntermediateResponse(*static_cast<DWORD *>(lpvStatusInformation));
                    break;
                case WINHTTP_CALLBACK_STATUS_NAME_RESOLVED:
                    OnNameResolved(static_cast<LPCWSTR>(lpvStatusInformation));
                    break;
                case WINHTTP_CALLBACK_STATUS_READ_COMPLETE:
                    OnReadComplete(dwStatusInformationLength);
                    break;
                case WINHTTP_CALLBACK_STATUS_RECEIVING_RESPONSE:
                    OnReceivingResponse();
                    break;
                case WINHTTP_CALLBACK_STATUS_REDIRECT:
                    OnRedirect(static_cast<LPCWSTR>(lpvStatusInformation));
                    break;
                case WINHTTP_CALLBACK_STATUS_REQUEST_ERROR:
                    OnRequestError(*static_cast<WINHTTP_ASYNC_RESULT *>(lpvStatusInformation));
                    break;
                case WINHTTP_CALLBACK_STATUS_REQUEST_SENT:
                    OnRequestSent(*static_cast<DWORD *>(lpvStatusInformation));
                    break;
                case WINHTTP_CALLBACK_STATUS_RESOLVING_NAME:
                    OnResolvingName(static_cast<LPCWSTR>(lpvStatusInformation));
                    break;
                case WINHTTP_CALLBACK_STATUS_RESPONSE_RECEIVED:
                    OnResponseReceived(*static_cast<DWORD *>(lpvStatusInformation));
                    break;
                case WINHTTP_CALLBACK_STATUS_SECURE_FAILURE:
                    OnSecureFailure();
                    break;
                case WINHTTP_CALLBACK_STATUS_SENDING_REQUEST:
                    OnSendingRequest();
                    break;
                case WINHTTP_CALLBACK_STATUS_SENDREQUEST_COMPLETE:
                    OnSendRequestComplete();
                    break;
                case WINHTTP_CALLBACK_STATUS_WRITE_COMPLETE:
                    OnWriteComplete(*static_cast<DWORD *>(lpvStatusInformation));
                    break;
#if (WINVER >= 0x0602)
                case WINHTTP_CALLBACK_STATUS_GETPROXYFORURL_COMPLETE:
                    OnGetProxyForUrlComplete();
                    break;
                case WINHTTP_CALLBACK_STATUS_CLOSE_COMPLETE:
                    OnCloseComplete();
                    break;
                case WINHTTP_CALLBACK_STATUS_SHUTDOWN_COMPLETE:
                    OnShutdownComplete();
                    break;
#endif
                default:
                    break;
                }
            }

        protected:
            virtual void OnClosingConnection()
            {

            }

            virtual void OnConnectedToServer(LPCWSTR lpszIpAddress)
            {

            }

            virtual void OnConnectingServer(LPCWSTR lpszIpAddress)
            {

            }

            virtual void OnConnectionClosed()
            {

            }

            virtual void OnDataAvailable(DWORD cbSize)
            {

            }

            virtual void OnHandleCreated(HINTERNET hInternet)
            {

            }

            virtual void OnHandleClosing(HINTERNET hInternet)
            {

            }

            virtual void OnHeadersAvaiable()
            {

            }

            virtual void OnIntermediateResponse(DWORD dwStatusCode)
            {

            }

            virtual void OnNameResolved(LPCWSTR lpszName)
            {

            }

            virtual void OnReadComplete(DWORD cbSizeRead)
            {

            }

            virtual void OnReceivingResponse()
            {

            }

            virtual void OnRedirect(LPCWSTR lpszNewUrl)
            {

            }

            virtual void OnRequestError(const WINHTTP_ASYNC_RESULT &result)
            {

            }

            virtual void OnRequestSent(DWORD cbSent)
            {

            }

            virtual void OnResolvingName(LPCWSTR lpszServerName)
            {

            }

            virtual void OnResponseReceived(DWORD cbReceived)
            {

            }

            virtual void OnSecureFailure()
            {

            }

            virtual void OnSendingRequest()
            {

            }

            virtual void OnSendRequestComplete()
            {

            }

            virtual void OnWriteComplete(DWORD cbWritten)
            {

            }

            virtual void OnGetProxyForUrlComplete()
            {

            }

            virtual void OnCloseComplete()
            {

            }

            virtual void OnShutdownComplete()
            {

            }
        };

        typedef WinHttpHandleT<WinHttpCallback>         WinHttpHandle;
        typedef WinHttpSessionT<WinHttpCallback>        WinHttpSession;
        typedef WinHttpProxyResolverT<WinHttpCallback>  WinHttpProxyResolver;
        typedef WinHttpConnectionT<WinHttpCallback>     WinHttpConnection;
        typedef WinHttpRequestT<WinHttpCallback>        WinHttpRequest;

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLWINHTTP_H_AABABE1B_FA77_496D_AE29_1FE0DDDF7436_INCLUDED__
