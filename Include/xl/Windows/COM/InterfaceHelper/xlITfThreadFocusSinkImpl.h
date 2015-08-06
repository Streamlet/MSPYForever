//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfThreadFocusSinkImpl.h
//    Author:      Streamlet
//    Create Time: 2014-12-16
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFTHREADFOCUSSINKIMPL_H_A703B446_4A44_4867_B1B2_BB54C969155B_INCLUDED__
#define __XLITFTHREADFOCUSSINKIMPL_H_A703B446_4A44_4867_B1B2_BB54C969155B_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <msctf.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ITfThreadFocusSink>
        class ITfThreadFocusSinkImpl : public IUnknownImpl<T>
        {
        public: // ITfThreadFocusSink Methods
            STDMETHODIMP OnSetThreadFocus()
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP OnKillThreadFocus()
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLITFTHREADFOCUSSINKIMPL_H_A703B446_4A44_4867_B1B2_BB54C969155B_INCLUDED__
