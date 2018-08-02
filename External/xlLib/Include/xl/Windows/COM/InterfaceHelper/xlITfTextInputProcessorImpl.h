//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfTextInputProcessorImpl.h
//    Author:      Streamlet
//    Create Time: 2014-12-16
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFTEXTINPUTPROCESSORIMPL_H_57FEFBAA_A653_401C_9696_F62A9DA3DA2E_INCLUDED__
#define __XLITFTEXTINPUTPROCESSORIMPL_H_57FEFBAA_A653_401C_9696_F62A9DA3DA2E_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <msctf.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ITfTextInputProcessor>
        class ITfTextInputProcessorImpl : public IUnknownImpl<T>
        {
        public: // ITfTextInputProcessor Methods
            STDMETHODIMP Activate(ITfThreadMgr *ptim, TfClientId tid)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP Deactivate()
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLITFTEXTINPUTPROCESSORIMPL_H_57FEFBAA_A653_401C_9696_F62A9DA3DA2E_INCLUDED__
