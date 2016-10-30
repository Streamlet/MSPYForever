//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlFlashPlayer.h
//    Author:      Streamlet
//    Create Time: 2016-01-03
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLFLASHPLAYER_H_AC535754_8791_43A5_A943_96F9861511F9_INCLUDED__
#define __XLFLASHPLAYER_H_AC535754_8791_43A5_A943_96F9861511F9_INCLUDED__


#include "../InterfaceHelper/xlIShockwaveFlashImpl.h"
#include "xlOleContainer.h"

namespace xl
{
    namespace Windows
    {
        class FlashPlayerImpl : public OleContainerImpl,
                                public _IShockwaveFlashEventsImpl<>
        {
        public:
            FlashPlayerImpl() : m_pFlashPlayer(nullptr),
                                m_pCPC(nullptr),
                                m_pCP(nullptr)
            {

            }

            ~FlashPlayerImpl()
            {

            }

        public:
            bool CreateFlashPlayer(HWND hWnd, LPCRECT lpRect = nullptr)
            {
                DestroyFlashPlayer();

                if (!CreateOleObject(__uuidof(ShockwaveFlashObjects::ShockwaveFlash)))
                {
                    return false;
                }

                if (!InPlaceActive(hWnd, lpRect))
                {
                    return false;
                }

                HRESULT hr = m_pOleObj->QueryInterface(__uuidof(ShockwaveFlashObjects::IShockwaveFlash), (LPVOID *)&m_pFlashPlayer);

                if (FAILED(hr))
                {
                    return false;
                }

                hr = m_pFlashPlayer->QueryInterface(__uuidof(IConnectionPointContainer), (LPVOID *)&m_pCPC);

                if (FAILED(hr))
                {
                    return false;
                }

                hr = m_pCPC->FindConnectionPoint(__uuidof(ShockwaveFlashObjects::_IShockwaveFlashEvents), &m_pCP);

                if (FAILED(hr))
                {
                    return false;
                }

                DWORD dwCookie = 0;
                hr = m_pCP->Advise((ShockwaveFlashObjects::_IShockwaveFlashEvents *)this, &dwCookie);

                if (FAILED(hr))
                {
                    return false;
                }

                return true;
            }

            void DestroyFlashPlayer()
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

                if (m_pFlashPlayer != nullptr)
                {
                    m_pFlashPlayer->Release();
                    m_pFlashPlayer = nullptr;
                }
            }

        protected:
            ShockwaveFlashObjects::IShockwaveFlash *m_pFlashPlayer;
            IConnectionPointContainer              *m_pCPC;
            IConnectionPoint                       *m_pCP;
        };

        class FlashPlayer : public ComClass<FlashPlayer>,
            public FlashPlayerImpl
        {
        public:
            FlashPlayer()
            {

            }

            ~FlashPlayer()
            {

            }

        public:
            XL_COM_INTERFACE_BEGIN(FlashPlayer)
                XL_COM_INTERFACE(IOleClientSite)
                XL_COM_INTERFACE(IOleInPlaceSite)
                XL_COM_INTERFACE(IOleInPlaceSiteWindowless)
                XL_COM_INTERFACE(IOleInPlaceFrame)
                XL_COM_INTERFACE(ShockwaveFlashObjects::_IShockwaveFlashEvents)
            XL_COM_INTERFACE_END()
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLFLASHPLAYER_H_AC535754_8791_43A5_A943_96F9861511F9_INCLUDED__
