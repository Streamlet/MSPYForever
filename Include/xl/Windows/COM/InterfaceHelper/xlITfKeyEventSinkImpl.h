//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfKeyEventSinkImpl.h
//    Author:      Streamlet
//    Create Time: 2014-12-16
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFKEYEVENTSINKIMPL_H_E452CAC4_CCA8_4304_872A_F96529E6B926_INCLUDED__
#define __XLITFKEYEVENTSINKIMPL_H_E452CAC4_CCA8_4304_872A_F96529E6B926_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <msctf.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ITfKeyEventSink>
        class ITfKeyEventSinkImpl : public IUnknownImpl<T>
        {
        public: // ITfKeyEventSink Methods
            STDMETHODIMP OnSetFocus(BOOL fForeground)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP OnTestKeyDown(ITfContext *pContext, WPARAM wParam, LPARAM lParam, BOOL *pIsEaten)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP OnKeyDown(ITfContext *pContext, WPARAM wParam, LPARAM lParam, BOOL *pIsEaten)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP OnTestKeyUp(ITfContext *pContext, WPARAM wParam, LPARAM lParam, BOOL *pIsEaten)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP OnKeyUp(ITfContext *pContext, WPARAM wParam, LPARAM lParam, BOOL *pIsEaten)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP OnPreservedKey(ITfContext *pContext, REFGUID rguid, BOOL *pIsEaten)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLITFKEYEVENTSINKIMPL_H_E452CAC4_CCA8_4304_872A_F96529E6B926_INCLUDED__
