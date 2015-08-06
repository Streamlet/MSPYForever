//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfFnGetPreferredTouchKeyboardLayoutImpl.h
//    Author:      Streamlet
//    Create Time: 2014-12-16
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFFNGETPREFERREDTOUCHKEYBOARDLAYOUTIMPL_H_A8C51C21_E0B9_4714_AB94_E2C7B47809F8_INCLUDED__
#define __XLITFFNGETPREFERREDTOUCHKEYBOARDLAYOUTIMPL_H_A8C51C21_E0B9_4714_AB94_E2C7B47809F8_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlITfFunctionImpl.h"
#include <ctffunc.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ITfFnGetPreferredTouchKeyboardLayout>
        class ITfFnGetPreferredTouchKeyboardLayoutImpl : public ITfFunctionImpl<T>
        {
        public: // ITfFnGetPreferredTouchKeyboardLayout Methods
            STDMETHODIMP GetLayout(TKBLayoutType *ptkblayoutType, WORD *pwPreferredLayoutId)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLITFFNGETPREFERREDTOUCHKEYBOARDLAYOUTIMPL_H_A8C51C21_E0B9_4714_AB94_E2C7B47809F8_INCLUDED__
