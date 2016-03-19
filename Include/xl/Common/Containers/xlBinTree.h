//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlBinTree.h
//    Author:      Streamlet
//    Create Time: 2011-10-15
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLBINTREE_H_6C3F6F71_DCAC_4B1D_9BAC_1333FB803DEE_INCLUDED__
#define __XLBINTREE_H_6C3F6F71_DCAC_4B1D_9BAC_1333FB803DEE_INCLUDED__


#include "../../xlDef.h"
#include "../Memory/xlMemory.h"
#include "xlBinTreeNode.h"
#include "xlIterator.h"

namespace xl
{
    template <typename T, typename NodeType = BinTreeNode<T>>
    class BinTree
    {
    public:
        BinTree() : m_pRoot(nullptr)
        {

        }

        BinTree(const BinTree &that) : m_pRoot(CopySubTree(that.m_pRoot))
        {

        }

#ifdef __XL_CPP11

        BinTree(BinTree &&that) : m_pRoot(that.m_pRoot)
        {
            that.m_pRoot = nullptr;
        }

#endif

        BinTree &operator = (const BinTree &that)
        {
            if (this == &that)
            {
                return *this;
            }

            this->SetRoot(CopySubTree(that.m_pRoot));

            return *this;
        }

#ifdef __XL_CPP11

        BinTree &operator = (BinTree &&that)
        {
            if (this == &that)
            {
                return *this;
            }

            this->SetRoot(that.m_pRoot);
            that.m_pRoot = nullptr;

            return *this;
        }

#endif

        ~BinTree()
        {
            Clear();
        }

    protected:
        NodeType *m_pRoot;

    public:
        bool operator == (const BinTree &that) const
        {
            if (this == &that)
            {
                return true;
            }

            return IsSubTreeEqual(this->m_pRoot, that.m_pRoot);
        }

        bool operator != (const BinTree &that) const
        {
            if (this == &that)
            {
                return false;
            }

            return IsSubTreeUnequal(this->m_pRoot, that.m_pRoot);
        }

    public:
        NodeType *Root() const
        {
            return m_pRoot;
        }

        bool Empty() const
        {
            return m_pRoot == nullptr;
        }

    public:
        void Clear()
        {
            DeleteSubTree(m_pRoot);
        }

        NodeType *SetRoot(NodeType *pNode)
        {
            m_pRoot = pNode;

            return m_pRoot;
        }

    public:
        static bool IsSubTreeEqual(NodeType *pThisNode, NodeType *pThatNode)
        {
            if (pThisNode == pThatNode)
            {
                return true;
            }

            if (pThisNode == nullptr || pThatNode == nullptr)
            {
                return false;
            }

            if (pThisNode->tValue != pThatNode->tValue)
            {
                return false;
            }

            return (IsSubTreeEqual(pThisNode->pLeft, pThatNode->pLeft) &&
                    IsSubTreeEqual(pThisNode->pRight, pThatNode->pRight));
        }

        static bool IsSubTreeUnequal(NodeType *pThisNode, NodeType *pThatNode)
        {
            if (pThisNode == pThatNode)
            {
                return false;
            }

            if (pThisNode == nullptr || pThatNode == nullptr)
            {
                return true;
            }

            if (pThisNode->tValue != pThatNode->tValue)
            {
                return true;
            }

            return (IsSubTreeUnequal(pThisNode->pLeft, pThatNode->pLeft) ||
                    IsSubTreeUnequal(pThisNode->pRight, pThatNode->pRight));
        }

    public:
        NodeType *CopySubTree(NodeType *pSubTreeRoot)
        {
            if (pSubTreeRoot == nullptr)
            {
                return nullptr;
            }

            NodeType *pNode = new NodeType(pSubTreeRoot->tValue);

            if (pSubTreeRoot->pLeft != nullptr)
            {
                NodeType *pLeft = CopySubTree(pSubTreeRoot->pLeft);
                pLeft->pParent = pNode;
                pNode->pLeft = pLeft;
            }

            if (pSubTreeRoot->pRight != nullptr)
            {
                NodeType *pRight = CopySubTree(pSubTreeRoot->pRight);
                pRight->pParent = pNode;
                pNode->pRight = pRight;
            }

            return pNode;
        }

        NodeType *SetLeftSubTree(NodeType *pParent, NodeType *pSubTreeRoot)
        {
            if (pSubTreeRoot == nullptr)
            {
                return nullptr;
            }

            if (pParent == nullptr)
            {
                return nullptr;
            }

            pSubTreeRoot->pParent = pParent;

            if (pParent->pLeft != nullptr)
            {
                DeleteSubTree(pParent->pLeft);
            }

            pParent->pLeft = pSubTreeRoot;

            return pSubTreeRoot;
        }

        NodeType *SetRightSubTree(NodeType *pParent, NodeType *pSubTreeRoot)
        {
            if (pSubTreeRoot == nullptr)
            {
                return nullptr;
            }

            if (pParent == nullptr)
            {
                return nullptr;
            }

            pSubTreeRoot->pParent = pParent;

            if (pParent->pRight != nullptr)
            {
                DeleteSubTree(pParent->pRight);
            }

            pParent->pRight = pSubTreeRoot;

            return pSubTreeRoot;
        }

        NodeType *DeleteSubTree(NodeType *pSubTreeRoot)
        {
            if (pSubTreeRoot == nullptr)
            {
                return nullptr;
            }

            NodeType *pParent = pSubTreeRoot->pParent;

            if (pParent == nullptr)
            {
                m_pRoot = nullptr;
            }
            else
            {
                if (pSubTreeRoot == pParent->pLeft)
                {
                    pParent->pLeft = nullptr;
                }
                else
                {
                    pParent->pRight = nullptr;
                }
            }

            delete pSubTreeRoot;

            return pParent;
        }

    public:
        void SwapNode(NodeType *pNode1, NodeType *pNode2)
        {
            if (pNode1->pLeft == pNode2)
            {
                pNode1->pLeft = pNode1;
                pNode2->pParent = pNode2;
            }

            if (pNode1->pRight == pNode2)
            {
                pNode1->pRight = pNode1;
                pNode2->pParent = pNode2;
            }

            if (pNode2->pLeft == pNode1)
            {
                pNode2->pLeft = pNode2;
                pNode1->pParent = pNode2;
            }

            if (pNode2->pRight == pNode1)
            {
                pNode2->pRight = pNode2;
                pNode1->pParent = pNode1;
            }

            NodeType *pParent1 = pNode1->pParent, *pLeft1 = pNode1->pLeft, *pRight1 = pNode1->pRight;
            NodeType *pParent2 = pNode2->pParent, *pLeft2 = pNode2->pLeft, *pRight2 = pNode2->pRight;
            NodeType **ppParent1ToNode1 = nullptr, **ppParent2ToNode2 = nullptr;

            if (pParent1 == nullptr)
            {
                m_pRoot = pNode2;
            }
            else
            {
                if (pNode1 == pParent1->pLeft)
                {
                    ppParent1ToNode1 = &pParent1->pLeft;
                }
                else
                {
                    ppParent1ToNode1 = &pParent1->pRight;
                }
            }

            if (pParent2 == nullptr)
            {
                m_pRoot = pNode1;
            }
            else
            {
                if (pNode2 == pParent2->pLeft)
                {
                    ppParent2ToNode2 = &pParent2->pLeft;
                }
                else
                {
                    ppParent2ToNode2 = &pParent2->pRight;
                }
            }

            if (ppParent1ToNode1 != nullptr)
            {
                *ppParent1ToNode1 = pNode2;
            }

            if (ppParent2ToNode2 != nullptr)
            {
                *ppParent2ToNode2 = pNode1;
            }

            pNode1->pParent = pParent2;
            pNode2->pParent = pParent1;

            pNode1->pLeft = pLeft2;
            pNode1->pRight = pRight2;

            pNode2->pLeft = pLeft1;
            pNode2->pRight = pRight1;

            if (pLeft1 != nullptr)
            {
                pLeft1->pParent = pNode2;
            }

            if (pRight1 != nullptr)
            {
                pRight1->pParent = pNode2;
            }

            if (pLeft2 != nullptr)
            {
                pLeft2->pParent = pNode1;
            }

            if (pRight2 != nullptr)
            {
                pRight2->pParent = pNode1;
            }
        }

        NodeType *RotateLeft(NodeType *pNode)
        {
            if (pNode == nullptr || pNode->pRight == nullptr)
            {
                return pNode;
            }

            NodeType *pNewNode = pNode->pRight;

            if (pNode->pParent == nullptr)
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

            pNewNode->pParent = pNode->pParent;
            pNode->pRight = pNewNode->pLeft;

            if (pNewNode->pLeft != nullptr)
            {
                pNewNode->pLeft->pParent = pNode;
            }

            pNode->pParent = pNewNode;
            pNewNode->pLeft = pNode;

            return pNewNode;
        }

        NodeType *RotateRight(NodeType *pNode)
        {
            if (pNode == nullptr || pNode->pLeft == nullptr)
            {
                return pNode;
            }

            NodeType *pNewNode = pNode->pLeft;

            if (pNode->pParent == nullptr)
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

            pNewNode->pParent = pNode->pParent;
            pNode->pLeft = pNewNode->pRight;

            if (pNewNode->pRight != nullptr)
            {
                pNewNode->pRight->pParent = pNode;
            }

            pNode->pParent = pNewNode;
            pNewNode->pRight = pNode;

            return pNewNode;
        }

    public:
#ifdef __XL_CPP11
        typedef BinTreeIterator<T, NodeType> Iterator;
        typedef ReverseBinTreeIterator<T, NodeType> ReverseIterator;
#else
        typedef BinTreeIteratorT<T, NodeType, false> Iterator;
        typedef BinTreeIteratorT<T, NodeType, true> ReverseIterator;
#endif

    public:
        Iterator Begin() const
        {
            return Iterator(Iterator::LeftmostChildOf(m_pRoot));
        }

        Iterator End() const
        {
            return Iterator(nullptr);
        }

        ReverseIterator ReverseBegin() const
        {
            return ReverseIterator(ReverseIterator::RightmostChildOf(m_pRoot));
        }

        ReverseIterator ReverseEnd() const
        {
            return ReverseIterator(nullptr);
        }
    };

} // namespace xl

#endif // #ifndef __XLBINTREE_H_6C3F6F71_DCAC_4B1D_9BAC_1333FB803DEE_INCLUDED__
