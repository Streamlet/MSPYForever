//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIClassFactoryImpl.h
//    Author:      Streamlet
//    Create Time: 2012-09-05
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLICLASSFACTORYIMPL_H_04EDB751_8B92_43E3_A97B_AF1D75D51C05_INCLUDED__
#define __XLICLASSFACTORYIMPL_H_04EDB751_8B92_43E3_A97B_AF1D75D51C05_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"

namespace xl
{
    namespace Windows
    {
        template <typename T = IClassFactory>
        class IClassFactoryImpl : public IUnknownImpl<T>
        {
        public: // IClassFactory Methods
            STDMETHOD(CreateInstance)(IUnknown *pUnkOuter,
                                      REFIID riid,
                                      void **ppvObject)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(LockServer)(BOOL fLock)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLICLASSFACTORYIMPL_H_04EDB751_8B92_43E3_A97B_AF1D75D51C05_INCLUDED__
