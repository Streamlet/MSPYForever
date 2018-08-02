//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlDWebBrowserEvents2Impl.h
//    Author:      Streamlet
//    Create Time: 2012-09-01
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLDWEBBROWSEREVENTS2IMPL_H_EA31A245_A931_42E6_9D29_E0C24E2B1ADC_INCLUDED__
#define __XLDWEBBROWSEREVENTS2IMPL_H_EA31A245_A931_42E6_9D29_E0C24E2B1ADC_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIDispatchImpl.h"
#include <ExDisp.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = DWebBrowserEvents2>
        class DWebBrowserEvents2Impl : public IDispatchImpl<T>
        {

        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLDWEBBROWSEREVENTS2IMPL_H_EA31A245_A931_42E6_9D29_E0C24E2B1ADC_INCLUDED__
