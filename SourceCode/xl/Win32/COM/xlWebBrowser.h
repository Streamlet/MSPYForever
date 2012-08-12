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


#include <xl/Win32/COM/xlOleContainer.h>
#include <Mshtmhst.h>
#include <ExDisp.h>

namespace xl
{
    class WebBrowser : public OleContainer,
                       public IDocHostUIHandler,
                       public DWebBrowserEvents2
    {
    public:
        WebBrowser() : m_nRefCount(0),
                       m_pWebBrowser(nullptr),
                       m_pCPC(nullptr),
                       m_pCP(nullptr)
        {
            AddRef();
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
        bool CreateWebBrowser(HWND hParent, LPCRECT lpRect)
        {
            if (!CreateOleObject(CLSID_WebBrowser))
            {
                return false;
            }

            RECT rect = {};

            if (lpRect != nullptr)
            {
                GetClientRect(hParent, &rect);
                lpRect = &rect;
            }

            if (!InPlaceActive(hParent, lpRect))
            {
                return false;
            }

            HRESULT hr = m_pOleObj->QueryInterface(IID_IWebBrowser2, (LPVOID *)&m_pWebBrowser);

            if (FAILED(hr))
            {
                return false;
            }

            hr = m_pWebBrowser->QueryInterface(IID_IConnectionPointContainer, (LPVOID *)&m_pCPC);

            if (FAILED(hr))
            {
                return false;
            }

            hr = m_pCPC->FindConnectionPoint(DIID_DWebBrowserEvents2, &m_pCP);

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
        HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID *ppvObject)
        {
            *ppvObject = nullptr;

            if (riid == IID_IUnknown)
            {
                *ppvObject = this;
            }
            else if(riid == IID_IOleObject)
            {
                *ppvObject = (IOleObject *)this;
            }
            else if (riid == IID_IOleInPlaceSite)
            {
                *ppvObject = (IOleInPlaceSite *)this;
            }
            else if (riid == IID_IOleInPlaceUIWindow)
            {
                *ppvObject = (IOleInPlaceUIWindow *)this;
            }
            else if (riid == IID_IOleInPlaceFrame)
            {   
                *ppvObject = (IOleInPlaceFrame *)this;
            }
            else if (riid == IID_IDocHostUIHandler)
            {
                *ppvObject = (IDocHostUIHandler *)this;
            }
            else if (riid == IID_IDispatch)
            {
                *ppvObject = (IDispatch *)this;
            }
            else if (riid == DIID_DWebBrowserEvents2)
            {
                *ppvObject = (DWebBrowserEvents2 *)this;
            }

            if (*ppvObject == nullptr)
            {
                return E_NOINTERFACE;
            }

            AddRef();
            return S_OK;
        }

        ULONG STDMETHODCALLTYPE AddRef()
        {
            return (ULONG)InterlockedIncrement(&m_nRefCount);
        }

        ULONG STDMETHODCALLTYPE Release()
        {
            LONG nRefCount = InterlockedDecrement(&m_nRefCount);

            if (nRefCount <= 0)
            {
                delete this;
            }

            return (ULONG)nRefCount;
        }

    public: // IDocHostUIHandler Methods
        STDMETHOD(ShowContextMenu)(DWORD dwID, POINT *ppt, IUnknown *pcmdtReserved, IDispatch *pdispReserved)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetHostInfo)(DOCHOSTUIINFO *pInfo)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(ShowUI)(DWORD dwID,
                          IOleInPlaceActiveObject *pActiveObject,
                          IOleCommandTarget *pCommandTarget,
                          IOleInPlaceFrame *pFrame,
                          IOleInPlaceUIWindow *pDoc)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(HideUI)()
        {
            return E_NOTIMPL;
        }

        STDMETHOD(UpdateUI)()
        {
            return E_NOTIMPL;
        }

        STDMETHOD(EnableModeless)(BOOL fEnable)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(OnDocWindowActivate)(BOOL fActivate)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(OnFrameWindowActivate)(BOOL fActivate)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(ResizeBorder)(LPCRECT prcBorder, IOleInPlaceUIWindow *pUIWindow, BOOL fRameWindow)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(TranslateAccelerator)(LPMSG lpMsg, const GUID *pguidCmdGroup, DWORD nCmdID)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetOptionKeyPath)(LPOLESTR *pchKey, DWORD dw)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetDropTarget)(IDropTarget *pDropTarget, IDropTarget **ppDropTarget)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetExternal)(IDispatch **ppDispatch)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(TranslateUrl)(DWORD dwTranslate, OLECHAR *pchURLIn, OLECHAR **ppchURLOut)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(FilterDataObject)(IDataObject *pDO, IDataObject **ppDORet)
        {
            return E_NOTIMPL;
        }

    public: // IDispatch Methods
        STDMETHOD(GetTypeInfoCount)(UINT *pctinfo)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(Invoke)(DISPID dispIdMember,
                          REFIID riid,
                          LCID lcid,
                          WORD wFlags,
                          DISPPARAMS *pDispParams,
                          VARIANT *pVarResult,
                          EXCEPINFO *pExcepInfo,
                          UINT *puArgErr)
        {
            return E_NOTIMPL;
        }

    private:
        LONG m_nRefCount;

    protected:
        IWebBrowser2              *m_pWebBrowser;
        IConnectionPointContainer *m_pCPC;
        IConnectionPoint          *m_pCP;

    };

} // namespace xl


#endif // #ifndef __XLWEBBROWSER_H_CFE7C075_AA18_441D_AE2C_86773A6479B0_INCLUDED__
