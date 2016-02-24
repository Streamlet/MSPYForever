//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlOleContainer.h
//    Author:      Streamlet
//    Create Time: 2012-08-12
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLOLECONTAINER_H_0B2334C9_4006_47C0_A940_CE8A19BE3568_INCLUDED__
#define __XLOLECONTAINER_H_0B2334C9_4006_47C0_A940_CE8A19BE3568_INCLUDED__


#include "../InterfaceHelper/xlIOleClientSiteImpl.h"
#include "../InterfaceHelper/xlIOleInPlaceFrameImpl.h"
#include "../InterfaceHelper/xlIOleInPlaceSiteWindowlessImpl.h"
#include "../xlComInclude.h"

namespace xl
{
    namespace Windows
    {
        class OleContainerImpl : public IOleClientSiteImpl<>,
                                 public IOleInPlaceSiteWindowlessImpl<>,
                                 public IOleInPlaceFrameImpl<>
        {
        public:
            OleContainerImpl() : m_hOleParent(nullptr),
                                 m_pStorage(nullptr),
                                 m_pOleObj(nullptr),
                                 m_pInPlaceObj(nullptr),
                                 m_bInPlaceActived(false),
                                 m_bUIActived(false)
            {
                ZeroMemory(&m_rect, sizeof(RECT));

                OleInitialize(nullptr);
            }

            ~OleContainerImpl()
            {
                OleUninitialize();
            }

        public:
            bool CreateOleObject(const IID &clsid)
            {
                DestroyOleObject();

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

            void DestroyOleObject()
            {
                if (m_pInPlaceObj != nullptr)
                {
                    m_pInPlaceObj->InPlaceDeactivate();
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
            }

            bool InPlaceActive(HWND hWnd, LPCRECT lpRect = nullptr)
            {
                HRESULT hr = CanInPlaceActivate();

                if (FAILED(hr))
                {
                    return false;
                }

                if (hWnd == nullptr || m_pOleObj == nullptr)
                {
                    return false;
                }

                m_hOleParent = hWnd;

                if (lpRect != nullptr)
                {
                    CopyMemory(&m_rect, lpRect, sizeof(RECT));
                }
                else
                {
                    GetClientRect(m_hOleParent, &m_rect);
                }

                hr = m_pOleObj->DoVerb(OLEIVERB_INPLACEACTIVATE, nullptr, this, 0, m_hOleParent, &m_rect);

                if (FAILED(hr))
                {
                    return false;
                }

                return true;
            }

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

            STDMETHOD(OnInPlaceActivate)()
            {
                if (m_bInPlaceActived)
                {
                    return E_UNEXPECTED;
                }

                m_bInPlaceActived = true;
                return S_OK;
            }

            STDMETHOD(OnUIActivate)()
            {
                if (m_bUIActived)
                {
                    return E_UNEXPECTED;
                }

                m_bUIActived = true;
                return S_OK;
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
                (*ppFrame)->AddRef();

                *ppDoc = NULL;

                CopyMemory(lprcPosRect, &m_rect, sizeof(RECT));
                CopyMemory(lprcClipRect, &m_rect, sizeof(RECT));

                lpFrameInfo->cb = sizeof(OLEINPLACEFRAMEINFO);
                lpFrameInfo->fMDIApp = false;
                lpFrameInfo->hwndFrame = GetParent(m_hOleParent);
                lpFrameInfo->haccel = nullptr;
                lpFrameInfo->cAccelEntries = 0;

                return S_OK;
            }

            STDMETHOD(OnUIDeactivate)(BOOL fUndoable)
            {
                if (!m_bUIActived)
                {
                    return E_UNEXPECTED;
                }

                m_bUIActived = false;
                return S_OK;
            }

            STDMETHOD(OnInPlaceDeactivate)()
            {
                if (!m_bInPlaceActived)
                {
                    return E_UNEXPECTED;
                }

                m_bInPlaceActived = false;
                return S_OK;
            }

        protected:
            HWND               m_hOleParent;
            IStorage          *m_pStorage;
            IOleObject        *m_pOleObj;
            IOleInPlaceObject *m_pInPlaceObj;
            bool               m_bInPlaceActived;
            bool               m_bUIActived;
            RECT               m_rect;
        };

        class OleContainer : public ComClass<OleContainer>,
                             public OleContainerImpl
        {
        public:
            OleContainer()
            {

            }

            ~OleContainer()
            {
                DestroyOleObject();
            }

        public:
            XL_COM_INTERFACE_BEGIN(OleContainer)
                XL_COM_INTERFACE(IOleClientSite)
                XL_COM_INTERFACE(IOleInPlaceSite)
                XL_COM_INTERFACE(IOleInPlaceSiteEx)
                XL_COM_INTERFACE(IOleInPlaceSiteWindowless)
                XL_COM_INTERFACE(IOleInPlaceFrame)
            XL_COM_INTERFACE_END()
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLOLECONTAINER_H_0B2334C9_4006_47C0_A940_CE8A19BE3568_INCLUDED__
