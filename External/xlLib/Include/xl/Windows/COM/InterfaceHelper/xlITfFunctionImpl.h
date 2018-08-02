//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfFnGetPreferredTouchKeyboardLayout.h
//    Author:      Streamlet
//    Create Time: 2014-12-16
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFFNGETPREFERREDTOUCHKEYBOARDLAYOUT_H_AED6DB87_9E15_4E7A_BC5F_0B9D15CD6EC8_INCLUDED__
#define __XLITFFNGETPREFERREDTOUCHKEYBOARDLAYOUT_H_AED6DB87_9E15_4E7A_BC5F_0B9D15CD6EC8_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <msctf.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ITfFunction>
        class ITfFunctionImpl : public IUnknownImpl<T>
        {
        public: // ITfFunction Methods
            STDMETHODIMP GetDisplayName(BSTR *pbstrDisplayName)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLITFFNGETPREFERREDTOUCHKEYBOARDLAYOUT_H_AED6DB87_9E15_4E7A_BC5F_0B9D15CD6EC8_INCLUDED__
