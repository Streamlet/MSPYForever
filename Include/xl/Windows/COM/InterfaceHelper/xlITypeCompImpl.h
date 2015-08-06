//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITypeCompImpl.h
//    Author:      Streamlet
//    Create Time: 2012-09-07
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITYPECOMPIMPL_H_04D4952F_296C_4D54_9FEA_9E9D46F3A2A6_INCLUDED__
#define __XLITYPECOMPIMPL_H_04D4952F_296C_4D54_9FEA_9E9D46F3A2A6_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <oaidl.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ITypeComp>
        class ITypeCompImpl : public IUnknownImpl<T>
        {
        public: // ITypeComp Methods
            STDMETHOD(Bind)(LPOLESTR szName,
                            ULONG lHashVal,
                            WORD wFlags,
                            ITypeInfo **ppTInfo,
                            DESCKIND *pDescKind,
                            BINDPTR *pBindPtr)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(BindType)(LPOLESTR szName,
                                ULONG lHashVal,
                                ITypeInfo **ppTInfo,
                                ITypeComp **ppTComp)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLITYPECOMPIMPL_H_04D4952F_296C_4D54_9FEA_9E9D46F3A2A6_INCLUDED__
