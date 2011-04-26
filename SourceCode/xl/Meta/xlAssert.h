//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlStaticAssert.h
//    Author:      Streamlet
//    Create Time: 2011-04-24
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLSTATICASSERT_H_8D45F3AE_6AA7_436B_AB6A_2C4D7A442220_INCLUDED__
#define __XLSTATICASSERT_H_8D45F3AE_6AA7_436B_AB6A_2C4D7A442220_INCLUDED__


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



#endif // #ifndef __XLSTATICASSERT_H_8D45F3AE_6AA7_436B_AB6A_2C4D7A442220_INCLUDED__
