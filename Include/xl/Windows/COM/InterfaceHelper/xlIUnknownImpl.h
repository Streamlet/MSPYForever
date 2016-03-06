//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIUnknownImpl.h
//    Author:      Streamlet
//    Create Time: 2012-09-01
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLIUNKNOWNIMPL_H_02B7268E_6F8B_47E7_BF44_1EDB0C545C42_INCLUDED__
#define __XLIUNKNOWNIMPL_H_02B7268E_6F8B_47E7_BF44_1EDB0C545C42_INCLUDED__


#include "../../xlWin32Ver.h"
#include <Unknwn.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = IUnknown>
        class IUnknownImpl : public T
        {
        public:
            IUnknownImpl()
            {

            }

            ~IUnknownImpl()
            {

            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLIUNKNOWNIMPL_H_02B7268E_6F8B_47E7_BF44_1EDB0C545C42_INCLUDED__
