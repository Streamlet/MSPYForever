//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlSet.h
//    Author:      Streamlet
//    Create Time: 2009-11-07
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLSET_H_11EAD852_068B_4809_B06D_F0FDF1E34E48_INCLUDED__
#define __XLSET_H_11EAD852_068B_4809_B06D_F0FDF1E34E48_INCLUDED__


#include "../../xlDef.h"
#include "xlRBTree.h"

namespace xl
{
    template <typename T>
    using Set = RBTree<T>;

} // namespace xl

#endif // #ifndef __XLSET_H_11EAD852_068B_4809_B06D_F0FDF1E34E48_INCLUDED__
