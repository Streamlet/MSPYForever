//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfTextEditSinkImpl.h
//    Author:      Streamlet
//    Create Time: 2015-01-06
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFTEXTEDITSINKIMPL_H_9550B0F8_00ED_4203_9D30_B4B8A42510D0_INCLUDED__
#define __XLITFTEXTEDITSINKIMPL_H_9550B0F8_00ED_4203_9D30_B4B8A42510D0_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <msctf.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ITfTextEditSink>
        class ITfTextEditSinkImpl : public IUnknownImpl<T>
        {
        public: // ITfTextEditSink Methods
            STDMETHODIMP OnEndEdit(ITfContext *pic, TfEditCookie ecReadOnly, ITfEditRecord *pEditRecord)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLITFTEXTEDITSINKIMPL_H_9550B0F8_00ED_4203_9D30_B4B8A42510D0_INCLUDED__
