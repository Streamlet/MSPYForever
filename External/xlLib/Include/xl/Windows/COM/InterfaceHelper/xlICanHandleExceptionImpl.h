//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlICanHandleExceptionImpl.h
//    Author:      Streamlet
//    Create Time: 2016-01-03
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLICANHANDLEEXCEPTIONIMPL_H_0A447606_0765_45D1_9420_9EB1264B7C33_INCLUDED__
#define __XLICANHANDLEEXCEPTIONIMPL_H_0A447606_0765_45D1_9420_9EB1264B7C33_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <dispex.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ICanHandleException>
        class ICanHandleExceptionImpl : public IUnknownImpl<T>
        {
        public: // ICanHandleException Methods
            STDMETHOD(CanHandleException)(EXCEPINFO *pExcepInfo, VARIANT *pvar)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLICANHANDLEEXCEPTIONIMPL_H_0A447606_0765_45D1_9420_9EB1264B7C33_INCLUDED__
