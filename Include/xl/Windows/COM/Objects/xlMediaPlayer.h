//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMediaPlayer.h
//    Author:      Streamlet
//    Create Time: 2012-09-01
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLMEDIAPLAYER_H_90C6295E_B667_44F2_98D6_BA0F435FECB0_INCLUDED__
#define __XLMEDIAPLAYER_H_90C6295E_B667_44F2_98D6_BA0F435FECB0_INCLUDED__


#include "../../xlWin32Ver.h"
#include "../InterfaceHelper/xlIDispatchImpl.h"
#include "xlOleContainer.h"
#include <wmp.h>

namespace xl
{
    namespace Windows
    {
        class MediaPlayerImpl : public OleContainerImpl,
                                public IDispatchImpl<>
        {
        public:
            MediaPlayerImpl() : m_pWMPPlayer(nullptr)
            {

            }

            ~MediaPlayerImpl()
            {
                DestroyMediaPlayer();
            }

        public:
            bool CreateMediaPlayer(HWND hWnd, LPCRECT lpRect = nullptr)
            {
                DestroyMediaPlayer();

                if (!CreateOleObject(__uuidof(WindowsMediaPlayer)))
                {
                    return false;
                }

                if (!InPlaceActive(hWnd, lpRect))
                {
                    return false;
                }

                HRESULT hr = m_pOleObj->QueryInterface(__uuidof(IWMPPlayer), (LPVOID *)&m_pWMPPlayer);

                if (FAILED(hr))
                {
                    return false;
                }

                return true;
            }

            void DestroyMediaPlayer()
            {
                if (m_pWMPPlayer != NULL)
                {
                    m_pWMPPlayer->Release();
                    m_pWMPPlayer = nullptr;
                }

                DestroyOleObject();
            }

        protected:
            IWMPPlayer *m_pWMPPlayer;
        };

        class MediaPlayer : public ComClass<MediaPlayer>,
                            public MediaPlayerImpl
        {
        public:
            MediaPlayer()
            {

            }

            ~MediaPlayer()
            {
                DestroyMediaPlayer();
            }

        public:
            XL_COM_INTERFACE_BEGIN(MediaPlayer)
                XL_COM_INTERFACE(IOleClientSite)
                XL_COM_INTERFACE(IOleInPlaceSite)
                XL_COM_INTERFACE(IOleInPlaceFrame)
                XL_COM_INTERFACE(IDispatch)
            XL_COM_INTERFACE_END()
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLMEDIAPLAYER_H_90C6295E_B667_44F2_98D6_BA0F435FECB0_INCLUDED__
