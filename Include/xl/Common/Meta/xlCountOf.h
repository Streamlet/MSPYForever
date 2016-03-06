//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlCountOf.h
//    Author:      Streamlet
//    Create Time: 2015-11-07
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLCOUNTOF_H_239FC2D1_72EA_4D58_87EA_CD0074D03F11_INCLUDED__
#define __XLCOUNTOF_H_239FC2D1_72EA_4D58_87EA_CD0074D03F11_INCLUDED__


#include "../../xlDef.h"

namespace xl
{
    template <typename T, int N>
    char (&ArraySizeHelper(T(&)[N]))[N];

#define XL_COUNT_OF(arr) sizeof(::xl::ArraySizeHelper(arr))

} // namespace xl

#endif // #ifndef __XLCOUNTOF_H_239FC2D1_72EA_4D58_87EA_CD0074D03F11_INCLUDED__
