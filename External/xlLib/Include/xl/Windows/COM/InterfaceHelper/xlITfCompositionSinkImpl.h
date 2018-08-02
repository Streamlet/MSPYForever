//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfCompositionSinkImpl.h
//    Author:      Streamlet
//    Create Time: 2014-12-16
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFCOMPOSITIONSINKIMPL_H_D217E6E4_34F8_401F_95BA_FD716280536D_INCLUDED__
#define __XLITFCOMPOSITIONSINKIMPL_H_D217E6E4_34F8_401F_95BA_FD716280536D_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <msctf.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ITfCompositionSink>
        class ITfCompositionSinkImpl : public IUnknownImpl<T>
        {
        public: // ITfCompositionSink Methods
            STDMETHODIMP OnCompositionTerminated(TfEditCookie ecWrite, _In_ ITfComposition *pComposition)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLITFCOMPOSITIONSINKIMPL_H_D217E6E4_34F8_401F_95BA_FD716280536D_INCLUDED__
