//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIWMPCoreImpl.h
//    Author:      Streamlet
//    Create Time: 2012-09-01
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLIWMPCOREIMPL_H_DD8CA807_093F_4DD8_BD06_46191EA16371_INCLUDED__
#define __XLIWMPCOREIMPL_H_DD8CA807_093F_4DD8_BD06_46191EA16371_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIDispatchImpl.h"
#include <wmp.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = IWMPCore>
        class IWMPCoreImpl : public IDispatchImpl<T>
        {
        public:
            STDMETHOD(close)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_URL)(BSTR *pbstrURL)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_URL)(BSTR bstrURL)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_openState)(WMPOpenState *pwmpos)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_playState)(WMPPlayState *pwmpps)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_controls)(IWMPControls **ppControl)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_settings)(IWMPSettings **ppSettings)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_currentMedia)(IWMPMedia **ppMedia)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_currentMedia)(IWMPMedia *pMedia)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_mediaCollection)(IWMPMediaCollection **ppMediaCollection)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_playlistCollection)(IWMPPlaylistCollection **ppPlaylistCollection)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_versionInfo)(BSTR *pbstrVersionInfo)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(launchURL)(BSTR bstrURL)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_network)(IWMPNetwork **ppQNI)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_currentPlaylist)(IWMPPlaylist **ppPL)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_currentPlaylist)(IWMPPlaylist *pPL)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_cdromCollection)(IWMPCdromCollection **ppCdromCollection)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_closedCaption)(IWMPClosedCaption **ppClosedCaption)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_isOnline)(VARIANT_BOOL *pfOnline)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_error)(IWMPError **ppError)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_status)(BSTR *pbstrStatus)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLIWMPCOREIMPL_H_DD8CA807_093F_4DD8_BD06_46191EA16371_INCLUDED__
