//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIOleInPlaceSiteWindowlessImpl.h
//    Author:      Streamlet
//    Create Time: 2016-01-05
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLIOLEINPLACESITEWINDOWLESSIMPL_H_CBD8C05F_5A19_4A42_A1F5_019216C954A5_INCLUDED__
#define __XLIOLEINPLACESITEWINDOWLESSIMPL_H_CBD8C05F_5A19_4A42_A1F5_019216C954A5_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIOleInPlaceSiteExImpl.h"
#include <oleidl.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = IOleInPlaceSiteWindowless>
        class IOleInPlaceSiteWindowlessImpl : public IOleInPlaceSiteExImpl<T>
        {
        public: // IOleInPlaceSiteWindowless Methods
            STDMETHOD(CanWindowlessActivate)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetCapture)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(SetCapture)(BOOL fCapture)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetFocus)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(SetFocus)(BOOL fFocus)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetDC)(LPCRECT pRect, DWORD grfFlags, HDC *phDC)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(ReleaseDC)(HDC hDC)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(InvalidateRect)(LPCRECT pRect, BOOL fErase)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(InvalidateRgn)(HRGN hRGN, BOOL fErase)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(ScrollRect)(INT dx, INT dy, LPCRECT pRectScroll, LPCRECT pRectClip)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(AdjustRect)(LPRECT prc)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(OnDefWindowMessage)(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT *plResult)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLIOLEINPLACESITEWINDOWLESSIMPL_H_CBD8C05F_5A19_4A42_A1F5_019216C954A5_INCLUDED__
