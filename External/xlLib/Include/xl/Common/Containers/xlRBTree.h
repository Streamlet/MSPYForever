//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlRBTree.h
//    Author:      Streamlet
//    Create Time: 2009-09-26
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLTREE_H_6BB48AA6_133A_4E9F_944E_504B887B6980_INCLUDED__
#define __XLTREE_H_6BB48AA6_133A_4E9F_944E_504B887B6980_INCLUDED__


#include "../../xlDef.h"
#include "../Memory/xlMemory.h"
#include "xlBinTree.h"

namespace xl
{
    enum RBTreeNodeColor
    {
        RBTreeNodeColor_Black,
        RBTreeNodeColor_Red
    };

    template <typename T>
    struct RBTreeNode
    {
        T tValue;
        RBTreeNode *pParent;
        RBTreeNode *pLeft;
        RBTreeNode *pRight;
        RBTreeNodeColor eColor;

        inline RBTreeNode(RBTreeNodeColor eColor = RBTreeNodeColor_Black) :
            tValue(), pParent(nullptr), pLeft(nullptr), pRight(nullptr), eColor(eColor)
        {

        }

        inline RBTreeNode(const T &tValue, RBTreeNodeColor eColor = RBTreeNodeColor_Black) :
            tValue(tValue), pParent(nullptr), pLeft(nullptr), pRight(nullptr), eColor(eColor)
        {

        }

        inline RBTreeNode(const RBTreeNode &that) :
            tValue(that.tValue), pParent(nullptr), pLeft(nullptr), pRight(nullptr), eColor(that.eColor)
        {

        }

        inline RBTreeNode &operator = (const RBTreeNode &that)
        {
            if (this == &that)
            {
                return *this;
            }

            this->tValue = that.tValue;
            this->pParent = nullptr;
            this->pLeft = nullptr;
            this->pRight = nullptr;
            this->eColor = that.eColor;

            return *this;
        }

        inline bool operator == (const RBTreeNode &that) const
        {
            return this->tValue == that.tValue;
        }

        inline bool operator != (const RBTreeNode &that) const
        {
            return this->tValue != that.tValue;
        }

        inline bool operator < (const RBTreeNode &that) const
        {
            return this->tValue < that.tValue;
        }

        inline bool operator > (const RBTreeNode &that) const
        {
            return this->tValue > that.tValue;
        }

        inline bool operator <= (const RBTreeNode &that) const
        {
            return this->tValue <= that.tValue;
        }

        inline bool operator >= (const RBTreeNode &that) const
        {
            return this->tValue >= that.tValue;
        }
    };

    template <typename T>
    class RBTree : public BinTree<T, RBTreeNode<T>>
    {
    public:
        inline RBTree() : m_nSize(0)
        {

        }

        inline RBTree(const RBTree &that) : BinTree(that), m_nSize(that.m_nSize)
        {

        }

#ifdef __XL_CPP11

        inline RBTree(RBTree &&that) : BinTree(that), m_nSize(that.m_nSize)
        {
            that.m_nSize = 0;
        }

#endif

        inline RBTree &operator = (const RBTree &that)
        {
            if (this == &that)
            {
                return *this;
            }

            *(BinTree *)this = (BinTree &)that;
            this->m_nSize = that.m_nSize;

            return *this;
        }

#ifdef __XL_CPP11

        inline RBTree &operator = (RBTree &&that)
        {
            if (this == &that)
            {
                return *this;
            }

            *(BinTree *)this = Memory::Move((BinTree &)that);
            this->m_nSize = that.m_nSize;
            that.m_nSize = 0;

            return *this;
        }

#endif

    public:
        typedef RBTreeNode<T> NodeType;

    protected:
        size_t m_nSize;

    public:
        inline bool operator == (const RBTree &that) const
        {
            if (this == &that)
            {
                return true;
            }

            if (this->m_nSize != that.m_nSize)
            {
                return false;
            }

            return *(BinTree *)this == (BinTree &)that;
        }

        inline bool operator != (const RBTree &that) const
        {
            if (this == &that)
            {
                return false;
            }

            if (this->m_nSize != that.m_nSize)
            {
                return true;
            }

            return *(BinTree *)this != (BinTree &)that;
        }

    public:
        inline bool Empty() const
        {
            return m_nSize == 0;
        }

        inline size_t Size() const
        {
            return m_nSize;
        }

    public:
        inline void Clear()
        {
            BinTree::Clear();
            m_nSize = 0;
        }

    protected:
        inline void SwapNode(NodeType *pNode1, NodeType *pNode2)
        {
            BinTree::SwapNode(pNode1, pNode2);
            Memory::Swap(pNode1->eColor, pNode2->eColor);
        }

    protected:
        // All cases
        inline void InsertFixup(NodeType *pNode)
        {
            // Is root
            if (pNode->pParent == nullptr)
            {
                pNode->eColor = RBTreeNodeColor_Black;
            }
            else
            {
                InsertFixupCase1(pNode);
            }
        }

        // Not root
        inline void InsertFixupCase1(NodeType *pNode)
        {
            // Parent is black
            if (pNode->pParent->eColor == RBTreeNodeColor_Black)
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
        inline void InsertFixupCase2L(NodeType *pNode)
        {
            NodeType *pGrandParent = pNode->pParent->pParent;

            // Uncle is red
            if (pGrandParent->pRight != nullptr && pGrandParent->pRight->eColor == RBTreeNodeColor_Red)
            {
                pGrandParent->eColor = RBTreeNodeColor_Red;
                pGrandParent->pLeft->eColor = RBTreeNodeColor_Black;
                pGrandParent->pRight->eColor = RBTreeNodeColor_Black;

                InsertFixup(pGrandParent);
            }
            else
            {
                InsertFixupCase3L(pNode);
            }

        }

        inline void InsertFixupCase2R(NodeType *pNode)
        {
            NodeType *pGrandParent = pNode->pParent->pParent;

            if (pGrandParent->pLeft != nullptr && pGrandParent->pLeft->eColor == RBTreeNodeColor_Red)
            {
                pGrandParent->eColor = RBTreeNodeColor_Red;
                pGrandParent->pRight->eColor = RBTreeNodeColor_Black;
                pGrandParent->pLeft->eColor = RBTreeNodeColor_Black;

                InsertFixup(pGrandParent);
            }
            else
            {
                InsertFixupCase3R(pNode);
            }
        }

        // Not root, Parent is red, Uncle is black
        inline void InsertFixupCase3L(NodeType *pNode)
        {
            // New node is Parent's r-child
            if (pNode == pNode->pParent->pRight)
            {
                RotateLeft(pNode->pParent);
                InsertFixupCase4L(pNode->pLeft);
            }
            else
            {
                InsertFixupCase4L(pNode);
            }
        }

        inline void InsertFixupCase3R(NodeType *pNode)
        {
            if (pNode == pNode->pParent->pLeft)
            {
                RotateRight(pNode->pParent);
                InsertFixupCase4R(pNode->pRight);
            }
            else
            {
                InsertFixupCase4R(pNode);
            }
        }

        // Not root, Parent is red, Uncle is black, New node is Parent's l-child
        inline void InsertFixupCase4L(NodeType *pNode)
        {
            RotateRight(pNode->pParent->pParent);
            pNode->pParent->eColor = RBTreeNodeColor_Black;
            pNode->pParent->pRight->eColor = RBTreeNodeColor_Red;
        }

        inline void InsertFixupCase4R(NodeType *pNode)
        {
            RotateLeft(pNode->pParent->pParent);
            pNode->pParent->eColor = RBTreeNodeColor_Black;
            pNode->pParent->pLeft->eColor = RBTreeNodeColor_Red;
        }

        // All cases
        inline void DeleteFixup(NodeType *pNode, NodeType *pParent)
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
        inline void DeleteFixupCase1L(NodeType *pNode, NodeType *pParent)
        {
            // Sibling is red
            if (pParent->pRight->eColor == RBTreeNodeColor_Red)
            {
                RotateLeft(pParent);
                pParent->eColor = RBTreeNodeColor_Red;
                pParent->pParent->eColor = RBTreeNodeColor_Black;
            }

            DeleteFixupCase2L(pNode, pParent);
        }

        inline void DeleteFixupCase1R(NodeType *pNode, NodeType *pParent)
        {
            if (pParent->pLeft->eColor == RBTreeNodeColor_Red)
            {
                RotateRight(pParent);
                pParent->eColor = RBTreeNodeColor_Red;
                pParent->pParent->eColor = RBTreeNodeColor_Black;
            }

            DeleteFixupCase2R(pNode, pParent);
        }

        // Not root, Sibling is black
        inline void DeleteFixupCase2L(NodeType *pNode, NodeType *pParent)
        {
            NodeType *pSibling = pParent->pRight;

            // Sibling's r-child is red
            if (pSibling->pRight != nullptr && pSibling->pRight->eColor == RBTreeNodeColor_Red)
            {
                RotateLeft(pParent);
                pSibling->pRight->eColor = RBTreeNodeColor_Black;
                Memory::Swap(pParent->eColor, pSibling->eColor);
            }
            else
            {
                DeleteFixupCase3L(pNode, pParent);
            }
        }

        inline void DeleteFixupCase2R(NodeType *pNode, NodeType *pParent)
        {
            NodeType *pSibling = pParent->pLeft;

            if (pSibling->pLeft != nullptr && pSibling->pLeft->eColor == RBTreeNodeColor_Red)
            {
                RotateRight(pParent);
                pSibling->pLeft->eColor = RBTreeNodeColor_Black;
                Memory::Swap(pParent->eColor, pSibling->eColor);
            }
            else
            {
                DeleteFixupCase3R(pNode, pParent);
            }
        }

        // Not root, Sibling is black, Sibling's r-child is black
        inline void DeleteFixupCase3L(NodeType *pNode, NodeType *pParent)
        {
            NodeType *pSibling = pParent->pRight;

            // Sibling's l-child is red
            if (pSibling->pLeft != nullptr && pSibling->pLeft->eColor == RBTreeNodeColor_Red)
            {
                RotateRight(pSibling);
                pSibling->pLeft->eColor = RBTreeNodeColor_Black;
                pSibling->eColor = RBTreeNodeColor_Red;

                DeleteFixupCase2L(pNode, pParent);
            }
            else
            {
                DeleteFixupCase4L(pNode, pParent);
            }
        }

        inline void DeleteFixupCase3R(NodeType *pNode, NodeType *pParent)
        {
            NodeType *pSibling = pParent->pLeft;

            if (pSibling->pRight != nullptr && pSibling->pRight->eColor == RBTreeNodeColor_Red)
            {
                RotateLeft(pSibling);
                pSibling->pRight->eColor = RBTreeNodeColor_Black;
                pSibling->eColor = RBTreeNodeColor_Red;

                DeleteFixupCase2R(pNode, pParent);
            }
            else
            {
                DeleteFixupCase4R(pNode, pParent);
            }
        }

        // Not root, Sibling is black, Sibling's r-child is black, Sibling's l-child is black
        inline void DeleteFixupCase4L(NodeType *pNode, NodeType *pParent)
        {
            // Parent is red
            if (pParent->eColor == RBTreeNodeColor_Red)
            {
                pParent->eColor = RBTreeNodeColor_Black;
                pParent->pRight->eColor = RBTreeNodeColor_Red;
            }
            else
            {
                DeleteFixupCase5L(pNode, pParent);
            }

        }

        inline void DeleteFixupCase4R(NodeType *pNode, NodeType *pParent)
        {
            if (pParent->eColor == RBTreeNodeColor_Red)
            {
                pParent->eColor = RBTreeNodeColor_Black;
                pParent->pLeft->eColor = RBTreeNodeColor_Red;
            }
            else
            {
                DeleteFixupCase5R(pNode, pParent);
            }
        }

        // Not root, Sibling is black, Sibling's r-child is black, Sibling's l-child is black, Parent is black
        inline void DeleteFixupCase5L(NodeType *pNode, NodeType *pParent)
        {
            pParent->pRight->eColor = RBTreeNodeColor_Red;

            DeleteFixup(pParent, pParent->pParent);
        }

        inline void DeleteFixupCase5R(NodeType *pNode, NodeType *pParent)
        {
            pParent->pLeft->eColor = RBTreeNodeColor_Red;

            DeleteFixup(pParent, pParent->pParent);
        }

    protected:
        inline NodeType *Find(const T &tValue, NodeType *pRoot) const
        {
            if (pRoot == nullptr)
            {
                return pRoot;
            }

            if (pRoot->tValue == tValue)
            {
                return pRoot;
            }

            return Find(tValue, tValue < pRoot->tValue ? pRoot->pLeft : pRoot->pRight);
        }

        inline NodeType *FindMaxBelow(const T &tValue, NodeType *pRoot, bool bIncludeEqual = true) const
        {
            if (pRoot == nullptr)
            {
                return nullptr;
            }

            if (bIncludeEqual && pRoot->tValue == tValue)
            {
                return pRoot;
            }

            if (pRoot->tValue < tValue)
            {
                if (pRoot->pRight == nullptr || tValue < pRoot->pRight->tValue)
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

        inline NodeType *FindMinAbove(const T &tValue, NodeType *pRoot, bool bIncludeEqual = true) const
        {
            if (pRoot == nullptr)
            {
                return nullptr;
            }

            if (bIncludeEqual && pRoot->tValue == tValue)
            {
                return pRoot;
            }

            if (tValue < pRoot->tValue)
            {
                if (pRoot->pLeft == nullptr || pRoot->pLeft->tValue < tValue)
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
        inline void DeleteNode(NodeType *pNode)
        {
            if (pNode == nullptr)
            {
                return;
            }

            NodeType *pNewNode = Iterator::RightmostChildOf(pNode->pLeft);

            if (pNode->pLeft != nullptr && pNode->pRight != nullptr)
            {
                SwapNode(pNode, pNewNode);

                pNewNode = Iterator::RightmostChildOf(pNode->pLeft);
            }

            pNewNode = (pNode->pLeft != nullptr ? pNode->pLeft : pNode->pRight);

            if(pNode->pParent == nullptr)
            {
                m_pRoot = pNewNode;
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

            RBTreeNodeColor eColor = pNode->eColor;
            NodeType *pParent = pNode->pParent;

            delete pNode;
            --m_nSize;

            if (eColor == RBTreeNodeColor_Red)
            {
                return;
            }

            if (pNewNode != nullptr && pNewNode->eColor == RBTreeNodeColor_Red)
            {
                pNewNode->eColor = RBTreeNodeColor_Black;
                return;
            }

            DeleteFixup(pNewNode, pNewNode == nullptr ? pParent : pNewNode->pParent);
        }

        inline NodeType *InsertValue(const T &tValue, NodeType *pRoot = nullptr)
        {
            if (pRoot == nullptr)
            {
                pRoot = m_pRoot;
            }

            if (pRoot == nullptr)
            {
                m_pRoot = new NodeType(tValue);
                ++m_nSize;
                return m_pRoot;
            }

            if (tValue == pRoot->tValue)
            {
                pRoot->tValue = tValue;
                return nullptr;
            }

            if (tValue < pRoot->tValue)
            {
                if (pRoot->pLeft == nullptr)
                {
                    NodeType *pNode = SetLeftSubTree(pRoot, new NodeType(tValue, RBTreeNodeColor_Red));

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
                    NodeType *pNode = SetRightSubTree(pRoot, new NodeType(tValue, RBTreeNodeColor_Red));

                    ++m_nSize;

                    InsertFixup(pNode);

                    return pNode;
                }

                return InsertValue(tValue, pRoot->pRight);
            }
        }

    public:
        inline void Delete(const T &tValue)
        {
            NodeType *pNode = Find(tValue, m_pRoot);

            if (pNode != nullptr)
            {
                DeleteNode(pNode);
            }
        }

    public:
        inline Iterator Find(const T &tValue) const
        {
            return Iterator(Find(tValue, m_pRoot));
        }

        inline Iterator FindMaxBelow(const T &tValue, bool bIncludeEqual = true) const
        {
            return Iterator(FindMaxBelow(tValue, m_pRoot, bIncludeEqual));
        }

        inline Iterator FindMinAbove(const T &tValue, bool bIncludeEqual = true) const
        {
            return Iterator(FindMinAbove(tValue, m_pRoot, bIncludeEqual));
        }

    public:
        inline Iterator Insert(const T &tValue)
        {
            return Iterator(InsertValue(tValue));
        }

        template <typename I>
        inline void Insert(const I &itBegin, const I &itEnd)
        {
            for (I it = itBegin; it != itEnd; ++it)
            {
                Insert(*it);
            }
        }

        inline Iterator Delete(const Iterator &itWhere)
        {
            Iterator itNext = itWhere;
            ++itNext;
            DeleteNode((NodeType *)itWhere);
            return itNext;
        }

        inline ReverseIterator Delete(const ReverseIterator &itWhere)
        {
            ReverseIterator itNext = itWhere;
            ++itNext;
            DeleteNode((NodeType *)itWhere);
            return itNext;
        }
    };

} // namespace xl

#endif // #ifndef __XLTREE_H_6BB48AA6_133A_4E9F_944E_504B887B6980_INCLUDED__
