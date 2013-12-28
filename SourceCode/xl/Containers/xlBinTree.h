//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlBinTree.h
//    Author:      Streamlet
//    Create Time: 2011-10-15
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLBINTREE_H_6C3F6F71_DCAC_4B1D_9BAC_1333FB803DEE_INCLUDED__
#define __XLBINTREE_H_6C3F6F71_DCAC_4B1D_9BAC_1333FB803DEE_INCLUDED__


#include "../Memory/xlMemory.h"

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

    template <typename T, typename NodeType = BinTreeNode<T>>
    class BinTree
    {
    public:
        typedef NodeType *NodePtr;

    public:
        BinTree() : m_pRoot(nullptr)
        {

        }

        BinTree(const BinTree &that) : m_pRoot(nullptr)
        {
            *this = that;
        }

        ~BinTree()
        {
            Clear();
        }

    protected:
        NodePtr m_pRoot;

    public:
        BinTree &operator = (const BinTree &that)
        {
            if (this == &that)
            {
                return *this;
            }

            this->SetRoot(CopySubTree(that.m_pRoot));

            return *this;
        }

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
        NodePtr Root() const
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

        NodePtr SetRoot(NodePtr pNode)
        {
            m_pRoot = pNode;

            return m_pRoot;
        }

    public:
        static bool IsSubTreeEqual(NodePtr pThisNode, NodePtr pThatNode)
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

        static bool IsSubTreeUnequal(NodePtr pThisNode, NodePtr pThatNode)
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

        static NodePtr RightmostOf(NodePtr pRoot)
        {
            if (pRoot == nullptr || pRoot->pRight == nullptr)
            {
                return pRoot;
            }

            return RightmostOf(pRoot->pRight);
        }

        static NodePtr LeftmostOf(NodePtr pRoot)
        {
            if (pRoot == nullptr || pRoot->pLeft == nullptr)
            {
                return pRoot;
            }

            return LeftmostOf(pRoot->pLeft);
        }

        static NodePtr PreviousOf(NodePtr pNode)
        {
            if (pNode == nullptr)
            {
                return nullptr;
            }

            if (pNode->pLeft != nullptr)
            {
                return RightmostOf(pNode->pLeft);
            }

            if (pNode->pParent == nullptr)
            {
                return nullptr;
            }

            while (pNode->pParent != nullptr && pNode == pNode->pParent->pLeft)
            {
                pNode = pNode->pParent;
            }

            return pNode->pParent;
        }

        static NodePtr NextOf(NodePtr pNode)
        {
            if (pNode == nullptr)
            {
                return nullptr;
            }

            if (pNode->pRight != nullptr)
            {
                return LeftmostOf(pNode->pRight);
            }

            if (pNode->pParent == nullptr)
            {
                return nullptr;
            }

            while (pNode->pParent != nullptr && pNode == pNode->pParent->pRight)
            {
                pNode = pNode->pParent;
            }

            return pNode->pParent;
        }

    public:
        NodePtr CopySubTree(NodePtr pSubTreeRoot)
        {
            if (pSubTreeRoot == nullptr)
            {
                return nullptr;
            }

            NodePtr pNode = new NodeType(pSubTreeRoot->tValue);

            if (pSubTreeRoot->pLeft != nullptr)
            {
                NodePtr pLeft = CopySubTree(pSubTreeRoot->pLeft);
                pLeft->pParent = pNode;
                pNode->pLeft = pLeft;
            }

            if (pSubTreeRoot->pRight != nullptr)
            {
                NodePtr pRight = CopySubTree(pSubTreeRoot->pRight);
                pRight->pParent = pNode;
                pNode->pRight = pRight;
            }

            return pNode;
        }

        NodePtr SetLeftSubTree(NodePtr pParent, NodePtr pSubTreeRoot)
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

        NodePtr SetRightSubTree(NodePtr pParent, NodePtr pSubTreeRoot)
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

        NodePtr DeleteSubTree(NodePtr pSubTreeRoot)
        {
            if (pSubTreeRoot == nullptr)
            {
                return nullptr;
            }

            NodePtr pParent = pSubTreeRoot->pParent;

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
        void SwapNode(NodePtr pNode1, NodePtr pNode2)
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

            NodePtr pParent1 = pNode1->pParent, pLeft1 = pNode1->pLeft, pRight1 = pNode1->pRight;
            NodePtr pParent2 = pNode2->pParent, pLeft2 = pNode2->pLeft, pRight2 = pNode2->pRight;
            NodePtr *ppParent1ToNode1 = nullptr, *ppParent2ToNode2 = nullptr;

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

        NodePtr RotateLeft(NodePtr pNode)
        {
            if (pNode == nullptr || pNode->pRight == nullptr)
            {
                return pNode;
            }

            NodePtr pNewNode = pNode->pRight;

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

        NodePtr RotateRight(NodePtr pNode)
        {
            if (pNode == nullptr || pNode->pLeft == nullptr)
            {
                return pNode;
            }

            NodePtr pNewNode = pNode->pLeft;

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

    // Iterator

    public:
        class Iterator
        {
        public:
            Iterator() : m_pCurrent(nullptr), m_pHead(nullptr)
            {

            }

            Iterator(const Iterator &that) : m_pCurrent(nullptr), m_pHead(nullptr)
            {
                *this = that;
            }

        protected:
            Iterator(NodePtr pCurrent) : m_pCurrent(pCurrent), m_pHead(nullptr)
            {

            }

            Iterator(NodePtr pCurrent, NodePtr pHead) : m_pCurrent(pCurrent), m_pHead(pHead)
            {

            }

        protected:
            friend class BinTree;

        protected:
            NodePtr m_pCurrent;
            NodePtr m_pHead;

        public:
            T &operator * ()
            {
                return m_pCurrent->tValue.tValue;
            }

            T *operator -> ()
            {
                return &m_pCurrent->tValue.tValue;
            }

            operator T * ()
            {
                return &m_pCurrent->tValue.tValue;
            }

            operator const T * () const
            {
                return &m_pCurrent->tValue.tValue;
            }

        public:
            Iterator &operator = (const Iterator &that)
            {
                if (this == &that)
                {
                    return *this;
                }

                this->m_pCurrent = that.m_pCurrent;
                this->m_pHead = that.m_pHead;

                return *this;
            }

            bool operator == (const Iterator &that) const
            {
                return (this->m_pCurrent == that.m_pCurrent);
            }

            bool operator != (const Iterator &that) const
            {
                return (this->m_pCurrent != that.m_pCurrent);
            }

        public:
            Iterator &operator ++ ()
            {
                m_pCurrent = BinTree::NextOf(m_pCurrent);

                return *this;
            }

            Iterator operator ++ (int)
            {
                typename RBTree<T>::Iterator itRet = *this;

                ++*this;

                return itRet;
            }

            Iterator &operator -- ()
            {
                if (m_pCurrent == nullptr)
                {
                    return BinTree::ReverseIterator(BinTree::RightmostOf(m_pRoot), m_pHead);
                }
                else
                {
                    m_pCurrent = BinTree::NextOf(m_pCurrent);
                }
            }

            Iterator operator -- (int)
            {
                typename RBTree<T>::Iterator itRet = *this;

                --*this;

                return itRet;
            }
        };

        class ReverseIterator : public Iterator
        {
        public:
            ReverseIterator() : Iterator()
            {

            }

            ReverseIterator(const ReverseIterator &that) : Iterator()
            {
                *this = that;
            }

        protected:
            ReverseIterator(NodePtr pCurrent) : Iterator(pCurrent)
            {

            }

            ReverseIterator(NodePtr pCurrent, NodePtr pHead) : Iterator(pCurrent, pHead)
            {

            }


        protected:
            friend class BinTree;

        public:
            ReverseIterator &operator ++ ()
            {
                m_pCurrent = BinTree::PreviousOf(m_pCurrent);

                return *this;
            }

            ReverseIterator operator ++ (int)
            {
                typename RBTree<T>::ReverseIterator itRet = *this;

                ++*this;

                return itRet;
            }

            ReverseIterator &operator -- ()
            {
                if (m_pCurrent == nullptr)
                {
                    return BinTree::ReverseIterator(BinTree::LeftmostOf(m_pRoot), m_pHead);
                }
                else
                {
                    m_pCurrent = BinTree::NextOf(m_pCurrent);
                }

                return *this;
            }

            ReverseIterator operator -- (int)
            {
                typename RBTree<T>::ReverseIterator itRet = *this;

                --*this;

                return itRet;
            }
        };

    public:
        Iterator Begin() const
        {
            return BinTree::Iterator(LeftmostOf(m_pRoot), m_pRoot);
        }

        Iterator End() const
        {
            return BinTree::Iterator(nullptr, m_pRoot);
        }

        ReverseIterator ReverseBegin() const
        {
            return BinTree::ReverseIterator(RightmostOf(m_pRoot), m_pRoot);
        }

        ReverseIterator ReverseEnd() const
        {
            return BinTree::ReverseIterator(nullptr, m_pRoot);
        }

    public:
        Iterator GetIterator(NodePtr pNode) const
        {
            return Iterator(pNode, m_pRoot);
        }

        ReverseIterator GetReverseIterator(NodePtr pNode) const
        {
            return ReverseIterator(pNode, m_pRoot);
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

#endif // #ifndef __XLBINTREE_H_6C3F6F71_DCAC_4B1D_9BAC_1333FB803DEE_INCLUDED__
