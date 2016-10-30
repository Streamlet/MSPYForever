//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfDisplayAttributeProviderImpl.h
//    Author:      Streamlet
//    Create Time: 2014-12-16
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFDISPLAYATTRIBUTEPROVIDERIMPL_H_A59B4B23_6587_4475_93EE_2F9736398252_INCLUDED__
#define __XLITFDISPLAYATTRIBUTEPROVIDERIMPL_H_A59B4B23_6587_4475_93EE_2F9736398252_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <msctf.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ITfDisplayAttributeProvider>
        class ITfDisplayAttributeProviderImpl : public IUnknownImpl<T>
        {
        public: // ITfDisplayAttributeProvider Methods
            STDMETHODIMP EnumDisplayAttributeInfo(IEnumTfDisplayAttributeInfo **ppEnum)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP GetDisplayAttributeInfo(REFGUID guidInfo, ITfDisplayAttributeInfo **ppInfo)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLITFDISPLAYATTRIBUTEPROVIDERIMPL_H_A59B4B23_6587_4475_93EE_2F9736398252_INCLUDED__
