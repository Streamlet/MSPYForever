//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIObjectWithSiteImpl.h
//    Author:      Streamlet
//    Create Time: 2012-12-02
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLIOBJECTWITHSITEIMPL_H_11E45695_BD45_422C_9222_FE0892155057_INCLUDED__
#define __XLIOBJECTWITHSITEIMPL_H_11E45695_BD45_422C_9222_FE0892155057_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <Ocidl.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = IObjectWithSite>
        class IObjectWithSiteImpl : public IUnknownImpl<T>
        {
        public:
            STDMETHOD(SetSite)(IUnknown *pUnkSite)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetSite)(REFIID riid, void **ppvSite)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLIOBJECTWITHSITEIMPL_H_11E45695_BD45_422C_9222_FE0892155057_INCLUDED__
