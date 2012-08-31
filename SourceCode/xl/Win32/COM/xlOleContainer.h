//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlOleContainer.h
//    Author:      Streamlet
//    Create Time: 2012-08-12
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLOLECONTAINER_H_0B2334C9_4006_47C0_A940_CE8A19BE3568_INCLUDED__
#define __XLOLECONTAINER_H_0B2334C9_4006_47C0_A940_CE8A19BE3568_INCLUDED__


#include <xl/Meta/xlUtility.h>
#include <Windows.h>
#include <OleIdl.h>

namespace xl
{
    class OleContainer : public NonCopyable,
                         public IOleClientSite,
                         public IOleInPlaceSite,
                         public IOleInPlaceFrame
    {
    public:
        OleContainer() : m_nRefCount(0),
                         m_pStorage(nullptr),
                         m_pOleObj(nullptr),
                         m_pInPlaceObj(nullptr),
                         m_hWindow(nullptr)
        {
            AddRef();
            OleInitialize(nullptr);
        }

        virtual ~OleContainer()
        {
            if (m_pInPlaceObj != nullptr)
            {
                m_pInPlaceObj->Release();
                m_pInPlaceObj = nullptr;
            }

            if (m_pOleObj != nullptr)
            {
                m_pOleObj->Release();
                m_pOleObj = nullptr;
            }

            if (m_pStorage != nullptr)
            {
                m_pStorage->Release();
                m_pStorage = nullptr;
            }

            OleUninitialize();
        }

    public:
        bool CreateOleObject(const IID &clsid)
        {
            HRESULT hr = StgCreateDocfile(nullptr,
                                          STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_CREATE,
                                          0,
                                          &m_pStorage);
            if (FAILED(hr))
            {
                return false;
            }

            hr = OleCreate(clsid, IID_IOleObject, OLERENDER_DRAW, 0, this, m_pStorage, (LPVOID *)&m_pOleObj);

            if (FAILED(hr))
            {
                return false;
            }

            hr = m_pOleObj->QueryInterface(IID_IOleInPlaceObject, (LPVOID *)&m_pInPlaceObj);

            if (FAILED(hr))
            {
                return false;
            }

            return true;
        }

        bool InPlaceActive(HWND hWnd, LPCRECT lpRect = nullptr)
        {
            if (hWnd == nullptr)
            {
                return false;
            }

            RECT rect = {};

            if (lpRect == nullptr)
            {
                GetClientRect(hWnd, &rect);
                lpRect = &rect;
            }

            HRESULT hr = m_pOleObj->DoVerb(OLEIVERB_INPLACEACTIVATE, nullptr, this, 0, hWnd, lpRect);

            if (FAILED(hr))
            {
                return false;
            }

            m_hWindow = hWnd;

            return true;
        }

    public: // IUnknown Methods
        HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID *ppvObject)
        {
            *ppvObject = nullptr;

            if (riid == IID_IUnknown)
            {
                *ppvObject = (IOleClientSite *)this;
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

    public: // IOleClientSite Methods
        STDMETHOD(SaveObject)()
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetContainer)(IOleContainer **ppContainer)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(ShowObject)()
        {
            return E_NOTIMPL;
        }

        STDMETHOD(OnShowWindow)(BOOL fShow)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(RequestNewObjectLayout)()
        {
            return E_NOTIMPL;
        }

    public: // IOleWindow Methods
        STDMETHOD(GetWindow)(HWND *phwnd)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode)
        {
            return E_NOTIMPL;
        }

    public: // IOleInPlaceSite Methods
        STDMETHOD(CanInPlaceActivate)()
        {
            return m_hWindow == nullptr ? S_OK : S_FALSE;
        }

        STDMETHOD(OnInPlaceActivate)()
        {
            return E_NOTIMPL;
        }

        STDMETHOD(OnUIActivate)()
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetWindowContext)(IOleInPlaceFrame **ppFrame,
                                    IOleInPlaceUIWindow **ppDoc,
                                    LPRECT lprcPosRect,
                                    LPRECT lprcClipRect,
                                    LPOLEINPLACEFRAMEINFO lpFrameInfo)
        {
            if (m_hWindow == nullptr)
            {
                return E_NOTIMPL;
            }

            *ppFrame = (IOleInPlaceFrame*)this;
            *ppDoc = NULL;
            AddRef();

            GetClientRect(m_hWindow, lprcPosRect);
            GetClientRect(m_hWindow, lprcClipRect);

            lpFrameInfo->cb = sizeof(OLEINPLACEFRAMEINFO);
            lpFrameInfo->fMDIApp = false;
            lpFrameInfo->hwndFrame = GetParent(m_hWindow);
            lpFrameInfo->haccel = nullptr;
            lpFrameInfo->cAccelEntries = 0;

            return S_OK;
        }

        STDMETHOD(Scroll)(SIZE scrollExtant)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(OnUIDeactivate)(BOOL fUndoable)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(OnInPlaceDeactivate)()
        {
            return E_NOTIMPL;
        }

        STDMETHOD(DiscardUndoState)()
        {
            return E_NOTIMPL;
        }

        STDMETHOD(DeactivateAndUndo)()
        {
            return E_NOTIMPL;
        }

        STDMETHOD(OnPosRectChange)(LPCRECT lprcPosRect)
        {
            return E_NOTIMPL;
        }

    public: // IOleInPlaceUIWindow Methods
        STDMETHOD(GetBorder)(LPRECT lprectBorder)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(RequestBorderSpace)(LPCBORDERWIDTHS pborderwidths)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(SetBorderSpace)(LPCBORDERWIDTHS pborderwidths)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(SetActiveObject)(IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName)
        {
            return E_NOTIMPL;
        }

    public: // IOleInPlaceFrame Methods
        STDMETHOD(InsertMenus)(HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(SetMenu)(HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(RemoveMenus)(HMENU hmenuShared)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(SetStatusText)(LPCOLESTR pszStatusText)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(EnableModeless)(BOOL fEnable)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(TranslateAccelerator)(LPMSG lpmsg, WORD wID)
        {
            return E_NOTIMPL;
        }

    private:
        LONG m_nRefCount;

    protected:
        IStorage          *m_pStorage;
        IOleObject        *m_pOleObj;
        IOleInPlaceObject *m_pInPlaceObj;
        HWND               m_hWindow;
    };

} // namespace xl

#endif // #ifndef __XLOLECONTAINER_H_0B2334C9_4006_47C0_A940_CE8A19BE3568_INCLUDED__
