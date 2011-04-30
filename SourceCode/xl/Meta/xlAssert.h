//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlAssert.h
//    Author:      Streamlet
//    Create Time: 2011-04-24
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLASSERT_H_BABCC0B2_7AD9_4F55_99F2_5DBB6EAD1F4D_INCLUDED__
#define __XLASSERT_H_BABCC0B2_7AD9_4F55_99F2_5DBB6EAD1F4D_INCLUDED__


#include <xl/xlDef.h>

namespace xl
{

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

} // namespace xl

#endif // #ifndef __XLASSERT_H_BABCC0B2_7AD9_4F55_99F2_5DBB6EAD1F4D_INCLUDED__
