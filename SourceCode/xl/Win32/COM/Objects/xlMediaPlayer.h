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


#include <xl/Win32/COM/Objects/xlOleContainer.h>
#include <xl/Win32/COM/InterfaceHelper/xlIWMPPlayerImpl.h>

namespace xl
{
    class MediaPlayer : public OleContainer,
                        public IWMPPlayerImpl<>
    {
    public:
        MediaPlayer() : m_pWMPPlayer(nullptr)
        {

        }

        virtual ~MediaPlayer()
        {
            if (m_pWMPPlayer != NULL)
            {
                m_pWMPPlayer->Release();
                m_pWMPPlayer = nullptr;
            }
        }

    public:
        bool CreateMediaPlayer(HWND hWnd, LPCRECT lpRect = nullptr)
        {
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

    public: // IUnknown Methods
        XL_COM_INTERFACE_BEGIN()
            XL_COM_INTERFACE_CHAIN(OleContainer)
            XL_COM_INTERFACE_CHAIN(IWMPPlayerImpl)
        XL_COM_INTERFACE_END()

    protected:
        IWMPPlayer *m_pWMPPlayer;
    };

} // namespace xl

#endif // #ifndef __XLMEDIAPLAYER_H_90C6295E_B667_44F2_98D6_BA0F435FECB0_INCLUDED__
