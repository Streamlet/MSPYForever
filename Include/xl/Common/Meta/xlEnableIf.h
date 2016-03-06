//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlEnableIf.h
//    Author:      Streamlet
//    Create Time: 2015-07-01
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLENABLEIF_H_3091E0D8_6B5B_41F1_B29A_B881C5D833D4_INCLUDED__
#define __XLENABLEIF_H_3091E0D8_6B5B_41F1_B29A_B881C5D833D4_INCLUDED__


#include "../../xlDef.h"

namespace xl
{
    template <bool expr, typename EnableType>
    struct EnableIf;

    template <typename EnableType>
    struct EnableIf<true, EnableType>
    {
        typedef EnableType Type;
    };

} // namespace xl


#endif // #ifndef __XLENABLEIF_H_3091E0D8_6B5B_41F1_B29A_B881C5D833D4_INCLUDED__
