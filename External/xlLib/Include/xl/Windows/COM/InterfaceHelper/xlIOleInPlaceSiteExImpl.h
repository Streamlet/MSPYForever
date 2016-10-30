//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIOleInPlaceSiteImplEx.h
//    Author:      Streamlet
//    Create Time: 2016-01-05
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLIOLEINPLACESITEIMPLEX_H_2829542B_0978_40F4_A450_ED51256DD1DF_INCLUDED__
#define __XLIOLEINPLACESITEIMPLEX_H_2829542B_0978_40F4_A450_ED51256DD1DF_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIOleInPlaceSiteImpl.h"
#include <oleidl.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = IOleInPlaceSiteEx>
        class IOleInPlaceSiteExImpl : public IOleInPlaceSiteImpl<T>
        {
        public: // IOleInPlaceSiteEx Methods
            STDMETHOD(OnInPlaceActivateEx)(BOOL *pfNoRedraw, DWORD dwFlags)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(OnInPlaceDeactivateEx)(BOOL fNoRedraw)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(RequestUIActivate)()
            {
                return E_NOTIMPL;
            }

        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLIOLEINPLACESITEIMPLEX_H_2829542B_0978_40F4_A450_ED51256DD1DF_INCLUDED__
