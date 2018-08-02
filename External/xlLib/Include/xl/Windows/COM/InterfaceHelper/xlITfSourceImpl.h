//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfSourceImpl.h
//    Author:      Streamlet
//    Create Time: 2015-02-24
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFSOURCEIMPL_H_D0194DCB_B5EA_4E44_A5AD_A52F68D19A1D_INCLUDED__
#define __XLITFSOURCEIMPL_H_D0194DCB_B5EA_4E44_A5AD_A52F68D19A1D_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <msctf.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ITfSource>
        class ITfSourceImpl : public IUnknownImpl<T>
        {
        public: // ITfSource Methods
            STDMETHODIMP AdviseSink(REFIID riid, IUnknown *punk, DWORD *pdwCookie)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP UnadviseSink(DWORD dwCookie)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLITFSOURCEIMPL_H_D0194DCB_B5EA_4E44_A5AD_A52F68D19A1D_INCLUDED__
