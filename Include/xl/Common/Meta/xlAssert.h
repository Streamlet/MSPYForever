//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlAssert.h
//    Author:      Streamlet
//    Create Time: 2011-04-24
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLASSERT_H_BABCC0B2_7AD9_4F55_99F2_5DBB6EAD1F4D_INCLUDED__
#define __XLASSERT_H_BABCC0B2_7AD9_4F55_99F2_5DBB6EAD1F4D_INCLUDED__


#include "../../xlDef.h"

namespace xl
{

#ifdef _DEBUG
#define XL_ASSERT(expr)                 \
                                        \
    do                                  \
    {                                   \
        if (!(expr))                    \
        {                               \
            throw "Assert fails.";      \
        }                               \
                                        \
    } while (false)
#else
    #define XL_ASSERT(expr)
#endif

} // namespace xl

#endif // #ifndef __XLASSERT_H_BABCC0B2_7AD9_4F55_99F2_5DBB6EAD1F4D_INCLUDED__
