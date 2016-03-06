//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlBinTreeNode.h
//    Author:      Streamlet
//    Create Time: 2015-11-13
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLBINTREENODE_H_EF0AD2F0_D92E_4156_A689_28DEA2CF7465_INCLUDED__
#define __XLBINTREENODE_H_EF0AD2F0_D92E_4156_A689_28DEA2CF7465_INCLUDED__


#include "../../xlDef.h"

namespace xl
{
    template <typename T>
    struct BinTreeNode
    {
        T tValue;
        BinTreeNode *pParent;
        BinTreeNode *pLeft;
        BinTreeNode *pRight;

        BinTreeNode() : pParent(nullptr), pLeft(nullptr), pRight(nullptr)
        {

        }

        BinTreeNode(const T &tValue, BinTreeNode *pParent = nullptr, BinTreeNode *pLeft = nullptr, BinTreeNode *pRight = nullptr) :
            tValue(tValue), pParent(pParent), pLeft(pLeft), pRight(pRight)
        {

        }
    };

} // namespace xl

#endif // #ifndef __XLBINTREENODE_H_EF0AD2F0_D92E_4156_A689_28DEA2CF7465_INCLUDED__
