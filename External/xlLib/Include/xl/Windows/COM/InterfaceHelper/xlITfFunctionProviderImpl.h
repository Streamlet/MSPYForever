//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfFunctionProviderImpl.h
//    Author:      Streamlet
//    Create Time: 2014-12-16
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFFUNCTIONPROVIDERIMPL_H_4F4231A0_87DC_43C2_94FC_2DFF66CB0EFA_INCLUDED__
#define __XLITFFUNCTIONPROVIDERIMPL_H_4F4231A0_87DC_43C2_94FC_2DFF66CB0EFA_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <msctf.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ITfFunctionProvider>
        class ITfFunctionProviderImpl : public IUnknownImpl<T>
        {
        public: // ITfFunctionProvider Methods
            STDMETHODIMP GetType(GUID *pguid)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP GetDescription(BSTR *pbstrDesc)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP GetFunction(REFGUID rguid, REFIID riid, IUnknown **ppunk)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLITFFUNCTIONPROVIDERIMPL_H_4F4231A0_87DC_43C2_94FC_2DFF66CB0EFA_INCLUDED__
