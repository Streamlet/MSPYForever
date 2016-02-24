//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlWebBrowser.h
//    Author:      Streamlet
//    Create Time: 2012-08-12
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLWEBBROWSER_H_CFE7C075_AA18_441D_AE2C_86773A6479B0_INCLUDED__
#define __XLWEBBROWSER_H_CFE7C075_AA18_441D_AE2C_86773A6479B0_INCLUDED__


#include "../InterfaceHelper/xlDWebBrowserEvents2Impl.h"
#include "../InterfaceHelper/xlIDocHostUIHandlerImpl.h"
#include "xlOleContainer.h"

namespace xl
{
    namespace Windows
    {
        class WebBrowserImpl : public OleContainerImpl,
                               public IDocHostUIHandlerImpl<>,
                               public DWebBrowserEvents2Impl<>
        {
        public:
            WebBrowserImpl() : m_pWebBrowser(nullptr),
                               m_pCPC(nullptr),
                               m_pCP(nullptr)
            {

            }

            ~WebBrowserImpl()
            {

            }

        public:
            bool CreateWebBrowser(HWND hWnd, LPCRECT lpRect = nullptr)
            {
                DestroyWebBrowser();

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

            void DestroyWebBrowser()
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

                DestroyOleObject();
            }

        protected:
            IWebBrowser2              *m_pWebBrowser;
            IConnectionPointContainer *m_pCPC;
            IConnectionPoint          *m_pCP;
        };

        class WebBrowser : public ComClass<WebBrowser>,
            public WebBrowserImpl
        {
        public:
            WebBrowser()
            {

            }

            ~WebBrowser()
            {

            }

        public:
            XL_COM_INTERFACE_BEGIN(WebBrowser)
                XL_COM_INTERFACE(IOleClientSite)
                XL_COM_INTERFACE(IOleInPlaceSite)
                XL_COM_INTERFACE(IOleInPlaceFrame)
                XL_COM_INTERFACE(IDocHostUIHandler)
                XL_COM_INTERFACE(DWebBrowserEvents2)
            XL_COM_INTERFACE_END()
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLWEBBROWSER_H_CFE7C075_AA18_441D_AE2C_86773A6479B0_INCLUDED__
