//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlRBTree.h
//    Author:      Streamlet
//    Create Time: 2009-09-26
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLTREE_H_6BB48AA6_133A_4E9F_944E_504B887B6980_INCLUDED__
#define __XLTREE_H_6BB48AA6_133A_4E9F_944E_504B887B6980_INCLUDED__


#include "../Memory/xlMemory.h"
#include "../xlDef.h"
#include "xlBinTree.h"

namespace xl
{
    template <typename T>
    class RBTree
    {
    public:
        RBTree() : m_nSize(0)
        {

        }

        RBTree(const RBTree &that) : m_nSize(0)
        {
            *this = that;
        }

    protected:

        enum NodeColor
        {
            NC_BLACK,
            NC_RED
        };

        struct NodeData
        {
            T tValue;
            NodeColor ncColor;

            NodeData() : ncColor(NC_BLACK)
            {

            }

            NodeData(const T &tValue, NodeColor ncColor = NC_BLACK) : tValue(tValue), ncColor(ncColor)
            {

            }

            NodeData(const NodeData &that)
            {
                *this = that;
            }

            NodeData &operator = (const NodeData &that)
            {
                if (this == &that)
                {
                    return *this;
                }

                this->tValue = that.tValue;
                this->ncColor = that.ncColor;

                return *this;
            }

            bool operator == (const NodeData &that)
            {
                if (this == &that)
                {
                    return true;
                }

                return this->tValue == that.tValue;
            }

            bool operator != (const NodeData &that)
            {
                if (this == &that)
                {
                    return false;
                }

                return this->tValue != that.tValue;
            }

            bool operator < (const NodeData &that)
            {
                if (this == &that)
                {
                    return false;
                }

                return this->tValue < that.tValue;
            }

            bool operator > (const NodeData &that)
            {
                if (this == &that)
                {
                    return false;
                }

                return this->tValue > that.tValue;
            }

            bool operator <= (const NodeData &that)
            {
                if (this == &that)
                {
                    return true;
                }

                return this->tValue <= that.tValue;
            }

            bool operator >= (const NodeData &that)
            {
                if (this == &that)
                {
                    return true;
                }

                return this->tValue >= that.tValue;
            }
        };

        typedef BinTreeNode<NodeData> NodeType;
        typedef BinTree<T, NodeType> InnerBinTree;
        typedef typename InnerBinTree::NodePtr NodePtr;  

    protected:
        InnerBinTree m_tBinTree;
        size_t       m_nSize;

    public:
        RBTree &operator = (const RBTree &that)
        {
            if (this == &that)
            {
                return *this;
            }

            this->m_tBinTree = that.m_tBinTree;
            this->m_nSize    = that.m_nSize;

            return *this;

        }

        bool operator == (const RBTree &that) const
        {
            if (this == &that)
            {
                return true;
            }

            if (this->m_nSize != that.m_nSize)
            {
                return false;
            }

            return this->m_tBinTree == that.m_tBinTree;
        }

        bool operator != (const RBTree &that) const
        {
            if (this == &that)
            {
                return false;
            }

            if (this->m_nSize != that.m_nSize)
            {
                return true;
            }

            return this->m_tBinTree != that.m_tBinTree;
        }

    public:
        bool Empty() const
        {
            return m_nSize == 0;
        }

        size_t Size() const
        {
            return m_nSize;
        }

    public:
        void Clear()
        {
            return m_tBinTree.Clear();
            m_nSize = 0;
        }

    protected:
        void SwapNode(NodePtr pNode1, NodePtr pNode2)
        {
            m_tBinTree.SwapNode(pNode1, pNode2);
            Memory::ElementSwap(pNode1->tValue.ncColor, pNode2->tValue.ncColor);
        }

    protected:
        // All cases
        void InsertFixup(NodePtr pNode)
        {
            // Is root
            if (pNode->pParent == nullptr)
            {
                pNode->tValue.ncColor = NC_BLACK;
            }
            else
            {
                InsertFixupCase1(pNode);
            }
        }

        // Not root
        void InsertFixupCase1(NodePtr pNode)
        {
            // Parent is black
            if (pNode->pParent->tValue.ncColor == NC_BLACK)
            {
                return;
            }
            else
            {
                if (pNode->pParent == pNode->pParent->pParent->pLeft)
                {
                    InsertFixupCase2L(pNode);
                }
                else
                {
                    InsertFixupCase2R(pNode);
                }
            }
        }

        // Not root, Parent is red
        void InsertFixupCase2L(NodePtr pNode)
        {
            NodePtr pGrandParent = pNode->pParent->pParent;

            // Uncle is red
            if (pGrandParent->pRight != nullptr && pGrandParent->pRight->tValue.ncColor == NC_RED)
            {
                pGrandParent->tValue.ncColor = NC_RED;
                pGrandParent->pLeft->tValue.ncColor = NC_BLACK;
                pGrandParent->pRight->tValue.ncColor = NC_BLACK;

                InsertFixup(pGrandParent);
            }
            else
            {
                InsertFixupCase3L(pNode);
            }

        }

        void InsertFixupCase2R(NodePtr pNode)
        {
            NodePtr pGrandParent = pNode->pParent->pParent;

            if (pGrandParent->pLeft != nullptr && pGrandParent->pLeft->tValue.ncColor == NC_RED)
            {
                pGrandParent->tValue.ncColor = NC_RED;
                pGrandParent->pRight->tValue.ncColor = NC_BLACK;
                pGrandParent->pLeft->tValue.ncColor = NC_BLACK;

                InsertFixup(pGrandParent);
            }
            else
            {
                InsertFixupCase3R(pNode);
            }
        }

        // Not root, Parent is red, Uncle is black
        void InsertFixupCase3L(NodePtr pNode)
        {
            // New node is Parent's r-child
            if (pNode == pNode->pParent->pRight)
            {
                m_tBinTree.RotateLeft(pNode->pParent);
                InsertFixupCase4L(pNode->pLeft);
            }
            else
            {
                InsertFixupCase4L(pNode);
            }
        }

        void InsertFixupCase3R(NodePtr pNode)
        {
            if (pNode == pNode->pParent->pLeft)
            {
                m_tBinTree.RotateRight(pNode->pParent);
                InsertFixupCase4R(pNode->pRight);
            }
            else
            {
                InsertFixupCase4R(pNode);
            }
        }

        // Not root, Parent is red, Uncle is black, New node is Parent's l-child
        void InsertFixupCase4L(NodePtr pNode)
        {
            m_tBinTree.RotateRight(pNode->pParent->pParent);
            pNode->pParent->tValue.ncColor = NC_BLACK;
            pNode->pParent->pRight->tValue.ncColor = NC_RED;
        }

        void InsertFixupCase4R(NodePtr pNode)
        {
            m_tBinTree.RotateLeft(pNode->pParent->pParent);
            pNode->pParent->tValue.ncColor = NC_BLACK;
            pNode->pParent->pLeft->tValue.ncColor = NC_RED;
        }

        // All cases
        void DeleteFixup(NodePtr pNode, NodePtr pParent)
        {
            // Is root
            if (pParent == nullptr)
            {
                return;
            }

            if (pNode == pParent->pLeft)
            {
                if (pParent->pRight == nullptr)
                {
                    DeleteFixup(pParent, pParent->pParent);
                }
                else
                {
                    DeleteFixupCase1L(pNode, pParent);
                }
            }
            else
            {
                if (pParent->pLeft == nullptr)
                {
                    DeleteFixup(pParent, pParent->pParent);
                }
                else
                {
                    DeleteFixupCase1R(pNode, pParent);
                }
            }
        }

        // Not root
        void DeleteFixupCase1L(NodePtr pNode, NodePtr pParent)
        {
            // Sibling is red
            if (pParent->pRight->tValue.ncColor == NC_RED)
            {
                m_tBinTree.RotateLeft(pParent);
                pParent->tValue.ncColor = NC_RED;
                pParent->pParent->tValue.ncColor = NC_BLACK;
            }

            DeleteFixupCase2L(pNode, pParent);
        }

        void DeleteFixupCase1R(NodePtr pNode, NodePtr pParent)
        {
            if (pParent->pLeft->tValue.ncColor == NC_RED)
            {
                m_tBinTree.RotateRight(pParent);
                pParent->tValue.ncColor = NC_RED;
                pParent->pParent->tValue.ncColor = NC_BLACK;
            }

            DeleteFixupCase2R(pNode, pParent);
        }

        // Not root, Sibling is black
        void DeleteFixupCase2L(NodePtr pNode, NodePtr pParent)
        {
            NodePtr pSibling = pParent->pRight;

            // Sibling's r-child is red
            if (pSibling->pRight != nullptr && pSibling->pRight->tValue.ncColor == NC_RED)
            {
                m_tBinTree.RotateLeft(pParent);
                pSibling->pRight->tValue.ncColor = NC_BLACK;
                Memory::ElementSwap(pParent->tValue.ncColor, pSibling->tValue.ncColor);
            }
            else
            {
                DeleteFixupCase3L(pNode, pParent);
            }
        }

        void DeleteFixupCase2R(NodePtr pNode, NodePtr pParent)
        {
            NodePtr pSibling = pParent->pLeft;

            if (pSibling->pLeft != nullptr && pSibling->pLeft->tValue.ncColor == NC_RED)
            {
                m_tBinTree.RotateRight(pParent);
                pSibling->pLeft->tValue.ncColor = NC_BLACK;
                Memory::ElementSwap(pParent->tValue.ncColor, pSibling->tValue.ncColor);
            }
            else
            {
                DeleteFixupCase3R(pNode, pParent);
            }
        }

        // Not root, Sibling is black, Sibling's r-child is black
        void DeleteFixupCase3L(NodePtr pNode, NodePtr pParent)
        {
            NodePtr pSibling = pParent->pRight;

            // Sibling's l-child is red
            if (pSibling->pLeft != nullptr && pSibling->pLeft->tValue.ncColor == NC_RED)
            {
                m_tBinTree.RotateRight(pSibling);
                pSibling->pLeft->tValue.ncColor = NC_BLACK;
                pSibling->tValue.ncColor = NC_RED;

                DeleteFixupCase2L(pNode, pParent);
            }
            else
            {
                DeleteFixupCase4L(pNode, pParent);
            }
        }

        void DeleteFixupCase3R(NodePtr pNode, NodePtr pParent)
        {
            NodePtr pSibling = pParent->pLeft;

            if (pSibling->pRight != nullptr && pSibling->pRight->tValue.ncColor == NC_RED)
            {
                m_tBinTree.RotateLeft(pSibling);
                pSibling->pRight->tValue.ncColor = NC_BLACK;
                pSibling->tValue.ncColor = NC_RED;

                DeleteFixupCase2R(pNode, pParent);
            }
            else
            {
                DeleteFixupCase4R(pNode, pParent);
            }
        }

        // Not root, Sibling is black, Sibling's r-child is black, Sibling's l-child is black
        void DeleteFixupCase4L(NodePtr pNode, NodePtr pParent)
        {
            // Parent is red
            if (pParent->tValue.ncColor == NC_RED)
            {
                pParent->tValue.ncColor = NC_BLACK;
                pParent->pRight->tValue.ncColor = NC_RED;
            }
            else
            {
                DeleteFixupCase5L(pNode, pParent);
            }

        }

        void DeleteFixupCase4R(NodePtr pNode, NodePtr pParent)
        {
            if (pParent->tValue.ncColor == NC_RED)
            {
                pParent->tValue.ncColor = NC_BLACK;
                pParent->pLeft->tValue.ncColor = NC_RED;
            }
            else
            {
                DeleteFixupCase5R(pNode, pParent);
            }
        }

        // Not root, Sibling is black, Sibling's r-child is black, Sibling's l-child is black, Parent is black
        void DeleteFixupCase5L(NodePtr pNode, NodePtr pParent)
        {
            pParent->pRight->tValue.ncColor = NC_RED;

            DeleteFixup(pParent, pParent->pParent);
        }

        void DeleteFixupCase5R(NodePtr pNode, NodePtr pParent)
        {
            pParent->pLeft->tValue.ncColor = NC_RED;

            DeleteFixup(pParent, pParent->pParent);
        }

    protected:
        NodePtr Find(const T &tValue, NodePtr pRoot) const
        {
            if (pRoot == nullptr)
            {
                return pRoot;
            }

            if (pRoot->tValue.tValue == tValue)
            {
                return pRoot;
            }

            return Find(tValue, tValue < pRoot->tValue.tValue ? pRoot->pLeft : pRoot->pRight);
        }

        NodePtr FindMaxBelow(const T &tValue, NodePtr pRoot, bool bIncludeEqual = true) const
        {
            if (pRoot == nullptr)
            {
                return nullptr;
            }

            if (bIncludeEqual && pRoot->tValue.tValue == tValue)
            {
                return pRoot;
            }

            if (pRoot->tValue.tValue < tValue)
            {
                if (pRoot->pRight == nullptr || tValue < pRoot->pRight->tValue.tValue)
                {
                    return pRoot;
                }
                else
                {
                    return FindMaxBelow(tValue, pRoot->pLeft);
                }
            }
            else
            {
                return FindMaxBelow(tValue, pRoot->pLeft);
            }
        }

        NodePtr FindMinAbove(const T &tValue, NodePtr pRoot, bool bIncludeEqual = true) const 
        {
            if (pRoot == nullptr)
            {
                return nullptr;
            }

            if (bIncludeEqual && pRoot->tValue.tValue == tValue)
            {
                return pRoot;
            }

            if (tValue < pRoot->tValue.tValue)
            {
                if (pRoot->pLeft == nullptr || pRoot->pLeft->tValue.tValue < tValue)
                {
                    return pRoot;
                }
                else
                {
                    return FindMinAbove(tValue, pRoot->pLeft);
                }
            }
            else
            {
                return FindMaxBelow(tValue, pRoot->pLeft);
            }
        }

    protected:
        void DeleteNode(NodePtr pNode)
        {
            if (pNode == nullptr)
            {
                return;
            }

            NodePtr pNewNode = InnerBinTree::RightmostOf(pNode->pLeft);

            if (pNode->pLeft != nullptr && pNode->pRight != nullptr)
            {
                SwapNode(pNode, pNewNode);

                pNewNode = InnerBinTree::RightmostOf(pNode->pLeft);
            }

            pNewNode = (pNode->pLeft != nullptr ? pNode->pLeft : pNode->pRight);

            if(pNode->pParent == nullptr)
            {
                m_tBinTree.SetRoot(pNewNode);
            }
            else
            {
                if (pNode == pNode->pParent->pLeft)
                {
                    pNode->pParent->pLeft = pNewNode;
                }
                else
                {
                    pNode->pParent->pRight = pNewNode;
                }
            }

            if (pNewNode != nullptr)
            {
                if (pNewNode == pNewNode->pParent->pLeft)
                {
                    pNewNode->pParent->pLeft = nullptr;
                }
                else
                {
                    pNewNode->pParent->pRight = pNewNode;
                }

                pNewNode->pParent = pNode->pParent;

                if (pNewNode != pNode->pLeft)
                {
                    pNewNode->pLeft = pNode->pLeft;
                }

                if (pNewNode != pNode->pRight)
                {
                    pNewNode->pRight = pNode->pRight;
                }
            }

            NodeColor ncColor = pNode->tValue.ncColor;
            NodePtr pParent = pNode->pParent;

            delete pNode;
            --m_nSize;

            if (ncColor == NC_RED)
            {
                return;
            }

            if (pNewNode != nullptr && pNewNode->tValue.ncColor == NC_RED)
            {
                pNewNode->tValue.ncColor = NC_BLACK;
                return;
            }

            DeleteFixup(pNewNode, pNewNode == nullptr ? pParent : pNewNode->pParent);
        }

        NodePtr InsertValue(const T &tValue, NodePtr pRoot = nullptr)
        {
            if (pRoot == nullptr)
            {
                pRoot = m_tBinTree.Root();
            }

            if (pRoot == nullptr)
            {
                m_tBinTree.SetRoot(new NodeType(NodeData(tValue)));
                ++m_nSize;
                return m_tBinTree.Root();
            }

            if (tValue == pRoot->tValue.tValue)
            {
                pRoot->tValue.tValue = tValue;
                return nullptr;
            }

            if (tValue < pRoot->tValue.tValue)
            {
                if (pRoot->pLeft == nullptr)
                {
                    NodePtr pNode = m_tBinTree.SetLeftSubTree(pRoot, new NodeType(NodeData(tValue, NC_RED)));

                    ++m_nSize;

                    InsertFixup(pNode);

                    return pNode;
                }

                return InsertValue(tValue, pRoot->pLeft);
            }
            else
            {
                if (pRoot->pRight == nullptr)
                {
                    NodePtr pNode = m_tBinTree.SetRightSubTree(pRoot, new NodeType(NodeData(tValue, NC_RED)));

                    ++m_nSize;

                    InsertFixup(pNode);

                    return pNode;
                }

                return InsertValue(tValue, pRoot->pRight);
            }
        }

    public:
        void Delete(const T &tValue)
        {
            NodePtr pNode = Find(tValue, m_pRoot);

            if (pNode != nullptr)
            {
                DeleteNode(pNode);
            }
        }


    // Iterator

    public:
        class Iterator : public InnerBinTree::Iterator
        {
        public:
            Iterator() : InnerBinTree::Iterator()
            {

            }

            Iterator(const Iterator &that) : InnerBinTree::Iterator()
            {
                *this = that;
            }

            Iterator(const typename InnerBinTree::Iterator &that) : InnerBinTree::Iterator(that)
            {

            }

        protected:
            Iterator(NodePtr pCurrent) : InnerBinTree::Iterator(m_pCurrent)
            {

            }

            Iterator(NodePtr pCurrent, NodePtr pHead) : InnerBinTree::Iterator(pCurrent, pHead)
            {

            }

        protected:
            friend class RBTree;
        };

        class ReverseIterator : public InnerBinTree::ReverseIterator
        {
        public:
            ReverseIterator() : InnerBinTree::ReverseIterator()
            {

            }

            ReverseIterator(const ReverseIterator &that) : InnerBinTree::ReverseIterator()
            {
                *this = that;
            }

            ReverseIterator(const typename InnerBinTree::ReverseIterator &that) : InnerBinTree::ReverseIterator(that)
            {

            }

        protected:
            ReverseIterator(NodePtr pCurrent) : InnerBinTree::ReverseIterator(pCurrent)
            {

            }

            ReverseIterator(NodePtr pCurrent, NodePtr pHead) : InnerBinTree::ReverseIterator(pCurrent, pHead)
            {

            }

        protected:
            friend class RBTree;
        };

    protected:
        friend Iterator;
        friend ReverseIterator;

    public:
        Iterator Find(const T &tValue) const
        {
            return m_tBinTree.GetIterator(Find(tValue, m_tBinTree.Root()));
        }

        Iterator FindMaxBelow(const T &tValue, bool bIncludeEqual = true) const
        {
            return m_tBinTree.GetIterator(FindMaxBelow(tValue, m_tBinTree.Root(), bIncludeEqual));
        }

        Iterator FindMinAbove(const T &tValue, bool bIncludeEqual = true) const
        {
            return m_tBinTree.GetIterator(FindMinAbove(tValue, m_tBinTree.Root(), bIncludeEqual));
        }

    public:
        Iterator Begin() const
        {
            return m_tBinTree.Begin();
        }

        Iterator End() const
        {
            return m_tBinTree.End();
        }

        ReverseIterator ReverseBegin() const
        {
            return m_tBinTree.ReverseBegin();
        }

        ReverseIterator ReverseEnd() const
        {
            return m_tBinTree.ReverseEnd();
        }

    public:
        Iterator Insert(const T &tValue)
        {
            return m_tBinTree.GetIterator(InsertValue(tValue));
        }

        template <typename I>
        void Insert(const I &itFirstToInsert, const I &itAfterLastToInsert)
        {
            for (I it = itFirstToInsert; it != itAfterLastToInsert; ++it)
            {
                Insert(*it);
            }
        }

        Iterator Delete(const Iterator &itWhich)
        {
            NodePtr pNext = m_tBinTree.NextOf(itWhich.m_pCurrent);

            DeleteNode(itWhich.m_pCurrent);

            return m_tBinTree.GetIterator(pNext);

        }

        ReverseIterator Delete(const ReverseIterator &itWhich)
        {
            NodePtr pPrev = m_tBinTree.PreviousOf(itWhich.m_pCurrent);

            DeleteNode(itWhich.m_pCurrent);

            return m_tBinTree.GetReverseIterator(pPrev);
        }
    };

} // namespace xl

//
// For convenience of debugging, put the following code to the [AutoExpand] section of
//     X:\Program Files\Microsoft Visual Studio 10.0\Common7\Packages\Debugger\autoexp.dat
// 
// ;------------------------------------------------------------------------------
// ;  xl::RBTree
// ;------------------------------------------------------------------------------
// xl::RBTree<*>{
//     preview (
//         #(
//             "[",
//             $e.m_nSize,
//             "](",
//             #tree(
//                 head: $e.m_tBinTree.m_pRoot,
//                 left: pLeft,
//                 right: pRight,
//                 size: $e.m_nSize
//             ) : $e.tValue.tValue,
//             ")"
//         )
//     )
//     children (
//         #(
//             #tree(
//                 head: $e.m_tBinTree.m_pRoot,
//                 left: pLeft,
//                 right: pRight,
//                 size: $e.m_nSize
//             ) : $e.tValue.tValue
//         )
//     )
// }
// xl::RBTree<*>::Iterator|xl::RBTree<*>::ReverseIterator{
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

#endif // #ifndef __XLTREE_H_6BB48AA6_133A_4E9F_944E_504B887B6980_INCLUDED__
