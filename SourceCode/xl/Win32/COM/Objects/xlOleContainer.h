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
#include <xl/Win32/COM/InterfaceHelper/xlIOleClientSiteImpl.h>
#include <xl/Win32/COM/InterfaceHelper/xlIOleInPlaceSiteImpl.h>
#include <xl/Win32/COM/InterfaceHelper/xlIOleInPlaceFrameImpl.h>

namespace xl
{
    class OleContainer : public NonCopyable,
                         public IOleClientSiteImpl<>,
                         public IOleInPlaceSiteImpl<>,
                         public IOleInPlaceFrameImpl<>
    {
    public:
        OleContainer() : m_hOleParent(nullptr),
                         m_pStorage(nullptr),
                         m_pOleObj(nullptr),
                         m_pInPlaceObj(nullptr),
                         m_bInPlaceActived(false)
        {
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

            m_hOleParent = hWnd;

            RECT rect = {};

            if (lpRect == nullptr)
            {
                GetClientRect(m_hOleParent, &rect);
                lpRect = &rect;
            }

            HRESULT hr = m_pOleObj->DoVerb(OLEIVERB_INPLACEACTIVATE, nullptr, this, 0, m_hOleParent, lpRect);

            if (FAILED(hr))
            {
                return false;
            }

            return true;
        }

    public:
        XL_COM_INTERFACE_BEGIN()
            XL_COM_INTERFACE_CHAIN(IOleClientSiteImpl)
            XL_COM_INTERFACE_CHAIN(IOleInPlaceSiteImpl)
            XL_COM_INTERFACE_CHAIN(IOleInPlaceFrameImpl)
        XL_COM_INTERFACE_END()

    public:
        STDMETHOD(GetWindow)(HWND *phwnd)
        {
            *phwnd = m_hOleParent;
            return S_OK;
        }

        STDMETHOD(CanInPlaceActivate)()
        {
            return m_bInPlaceActived ? S_FALSE : S_OK;
        }

        STDMETHOD(GetWindowContext)(IOleInPlaceFrame **ppFrame,
                                    IOleInPlaceUIWindow **ppDoc,
                                    LPRECT lprcPosRect,
                                    LPRECT lprcClipRect,
                                    LPOLEINPLACEFRAMEINFO lpFrameInfo)
        {
            if (m_hOleParent == nullptr)
            {
                return E_NOTIMPL;
            }
 
            *ppFrame = (IOleInPlaceFrame*)this;
            IOleInPlaceFrameImpl::AddRef();

            *ppDoc = NULL;
 
            GetClientRect(m_hOleParent, lprcPosRect);
            GetClientRect(m_hOleParent, lprcClipRect);
 
            lpFrameInfo->cb = sizeof(OLEINPLACEFRAMEINFO);
            lpFrameInfo->fMDIApp = false;
            lpFrameInfo->hwndFrame = GetParent(m_hOleParent);
            lpFrameInfo->haccel = nullptr;
            lpFrameInfo->cAccelEntries = 0;
 
            return S_OK;
        }
        
    protected:
        HWND               m_hOleParent;
        IStorage          *m_pStorage;
        IOleObject        *m_pOleObj;
        IOleInPlaceObject *m_pInPlaceObj;
        bool               m_bInPlaceActived;
    };

} // namespace xl

#endif // #ifndef __XLOLECONTAINER_H_0B2334C9_4006_47C0_A940_CE8A19BE3568_INCLUDED__
