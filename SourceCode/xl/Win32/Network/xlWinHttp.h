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
        bool Initialize(LPCTSTR lpUserAgent = _T(""),
                        DWORD dwAccessType = WINHTTP_ACCESS_TYPE_NO_PROXY,
                        LPCTSTR lpszProxyName = WINHTTP_NO_PROXY_NAME,
                        LPCTSTR lpszProxyBypass = WINHTTP_NO_PROXY_BYPASS)
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
        bool Initialize(const WinHttpSession &session, LPCTSTR lpszServerName, INTERNET_PORT nServerPort = INTERNET_DEFAULT_PORT, bool bSsl = false)
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
                        LPCTSTR lpszVerb,
                        LPCTSTR lpszObjectName,
                        LPCTSTR lpszVersion = nullptr,
                        LPCTSTR lpszReferrer = nullptr,
                        LPCTSTR *ppwszAcceptTypes = WINHTTP_DEFAULT_ACCEPT_TYPES,
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
        
            return true;
        }

    private:
        static void CALLBACK StaticWinHttpStatusCallback(HINTERNET hInternet,
                                                         DWORD_PTR dwContext,
                                                         DWORD dwInternetStatus,
                                                         LPVOID lpvStatusInformation,
                                                         DWORD dwStatusInformationLength)
        {
            ((WinHttpRequest *)dwContext)->WinHttpStatusCallback(hInternet,
                                                                 dwInternetStatus,
                                                                 lpvStatusInformation,
                                                                 dwStatusInformationLength);
        }

    private:
        void WinHttpStatusCallback(HINTERNET hInternet,
                                   DWORD dwInternetStatus,
                                   LPVOID lpvStatusInformation,
                                   DWORD dwStatusInformationLength)
        {
            if (hInternet != m_hInternet)
            {
                return;
            }        
        }
    };

} // namespace xl

#endif // #ifndef __XLWINHTTP_H_AABABE1B_FA77_496D_AE29_1FE0DDDF7436_INCLUDED__
