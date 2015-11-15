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


namespace xl
{
    template <typename T>
    struct BinTreeNode
    {
        typedef BinTreeNode *NodePtr;

        T tValue;

        NodePtr pParent;
        NodePtr pLeft;
        NodePtr pRight;

        BinTreeNode() : pParent(nullptr), pLeft(nullptr), pRight(nullptr)
        {

        }

        BinTreeNode(const T &tValue, NodePtr pParent = nullptr, NodePtr pLeft = nullptr, NodePtr pRight = nullptr) :
            tValue(tValue), pParent(pParent), pLeft(pLeft), pRight(pRight)
        {

        }
    };

} // namespace xl

//
// For convenience of debugging, put the following code to the [AutoExpand] section of
//     X:\Program Files\Microsoft Visual Studio 10.0\Common7\Packages\Debugger\autoexp.dat
// 
// ;------------------------------------------------------------------------------
// ;  xl::BinTree
// ;------------------------------------------------------------------------------
// xl::BinTree<*>::Iterator|xl::BinTree<*>::ReverseIterator{
//     preview (
//         $e.m_pCurrent->tValue.tValue
//     )
//     children (
//         #(
//             [ptr] : &$e.m_pCurrent->tValue.tValue
//         )
//     )
// }
//

#endif // #ifndef __XLBINTREENODE_H_EF0AD2F0_D92E_4156_A689_28DEA2CF7465_INCLUDED__
