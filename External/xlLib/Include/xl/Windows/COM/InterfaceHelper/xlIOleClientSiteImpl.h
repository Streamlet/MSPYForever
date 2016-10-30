//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIOleClientSiteImpl.h
//    Author:      Streamlet
//    Create Time: 2012-09-01
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLIOLECLIENTSITEIMPL_H_2922E78C_E51C_4F47_8D7E_D651BFB23749_INCLUDED__
#define __XLIOLECLIENTSITEIMPL_H_2922E78C_E51C_4F47_8D7E_D651BFB23749_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <oleidl.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = IOleClientSite>
        class IOleClientSiteImpl : public IUnknownImpl<T>
        {
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
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLIOLECLIENTSITEIMPL_H_2922E78C_E51C_4F47_8D7E_D651BFB23749_INCLUDED__
