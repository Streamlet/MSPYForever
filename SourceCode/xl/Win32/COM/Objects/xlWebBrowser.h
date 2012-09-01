//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlWebBrowser.h
//    Author:      Streamlet
//    Create Time: 2012-08-12
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLWEBBROWSER_H_CFE7C075_AA18_441D_AE2C_86773A6479B0_INCLUDED__
#define __XLWEBBROWSER_H_CFE7C075_AA18_441D_AE2C_86773A6479B0_INCLUDED__


#include <xl/Win32/COM/Objects/xlOleContainer.h>
#include <xl/Win32/COM/InterfaceHelper/xlIDocHostUIHandlerImpl.h>
#include <xl/Win32/COM/InterfaceHelper/xlDWebBrowserEvents2Impl.h>


namespace xl
{
    class WebBrowser : public OleContainer,
                       public IDocHostUIHandlerImpl<>,
                       public DWebBrowserEvents2Impl<>
    {
    public:
        WebBrowser() : m_pWebBrowser(nullptr),
                       m_pCPC(nullptr),
                       m_pCP(nullptr)
        {

        }

        virtual ~WebBrowser()
        {
            if (m_pCP != nullptr)
            {
                m_pCP->Release();
                m_pCP = nullptr;
            }

            if (m_pCPC != nullptr)
            {
                m_pCPC->Release();
                m_pCPC = nullptr;
            }

            if (m_pWebBrowser != nullptr)
            {
                m_pWebBrowser->Release();
                m_pWebBrowser = nullptr;
            }
        }

    public:
        bool CreateWebBrowser(HWND hWnd, LPCRECT lpRect = nullptr)
        {
            if (!CreateOleObject(__uuidof(::WebBrowser)))
            {
                return false;
            }

            if (!InPlaceActive(hWnd, lpRect))
            {
                return false;
            }

            HRESULT hr = m_pOleObj->QueryInterface(__uuidof(IWebBrowser2), (LPVOID *)&m_pWebBrowser);

            if (FAILED(hr))
            {
                return false;
            }

            hr = m_pWebBrowser->QueryInterface(__uuidof(IConnectionPointContainer), (LPVOID *)&m_pCPC);

            if (FAILED(hr))
            {
                return false;
            }

            hr = m_pCPC->FindConnectionPoint(__uuidof(DWebBrowserEvents2), &m_pCP);

            if (FAILED(hr))
            {
                return false;
            }

            DWORD dwCookie = 0;
            hr = m_pCP->Advise((DWebBrowserEvents2 *)this, &dwCookie);

            if (FAILED(hr))
            {
                return false;
            }

            return true;
        }

    public: // IUnknown Methods
        XL_COM_INTERFACE_BEGIN()
            XL_COM_INTERFACE_CHAIN(OleContainer)
            XL_COM_INTERFACE_CHAIN(IDocHostUIHandlerImpl)
            XL_COM_INTERFACE_CHAIN(DWebBrowserEvents2Impl)
        XL_COM_INTERFACE_END()
        
    protected:
        IWebBrowser2              *m_pWebBrowser;
        IConnectionPointContainer *m_pCPC;
        IConnectionPoint          *m_pCP;
    };

} // namespace xl


#endif // #ifndef __XLWEBBROWSER_H_CFE7C075_AA18_441D_AE2C_86773A6479B0_INCLUDED__
