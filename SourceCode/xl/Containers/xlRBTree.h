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


#include <xl/xlDef.h>

namespace xl
{
    template <typename T>
    class RBTree
    {
    public:
        RBTree();
        RBTree(const RBTree &that);
        ~RBTree();

    protected:

        enum NodeColor
        {
            Black,
            Red
        };

        struct Node
        {
            T tValue;
            NodeColor ncColor;
            Node *pParent;
            Node *pLeft;
            Node *pRight;
            
            Node() : ncColor(Black), pParent(nullptr), pLeft(nullptr), pRight(nullptr) { }
            Node(const T &tValue, NodeColor ncColor = Black, Node *pParent = nullptr, Node *pLeft = nullptr, Node *pRight = nullptr)
                : tValue(tValue), ncColor(ncColor), pParent(pParent), pLeft(pLeft), pRight(pRight) { }
        };

    protected:
        Node *m_pRoot;
        size_t m_nSize;

    public:
        RBTree &operator = (const RBTree &that);
        bool operator == (const RBTree &that) const;
        bool operator != (const RBTree &that) const;

    public:
        bool Empty() const;
        size_t Size() const;

    public:
        void Clear();

    protected:
        Node *RotateLeft(Node *pNode);
        Node *RotateRight(Node *pNode);
        void SwapNode(Node *pNode1, Node *pNode2);

    protected:
        void InsertFixup(Node *pNode);
        void InsertFixupCase1(Node *pNode);
        void InsertFixupCase2L(Node *pNode);
        void InsertFixupCase2R(Node *pNode);
        void InsertFixupCase3L(Node *pNode);
        void InsertFixupCase3R(Node *pNode);
        void InsertFixupCase4L(Node *pNode);
        void InsertFixupCase4R(Node *pNode);
        void DeleteFixup(Node *pNode, Node *pParent);
        void DeleteFixupCase1L(Node *pNode, Node *pParent);
        void DeleteFixupCase1R(Node *pNode, Node *pParent);
        void DeleteFixupCase2L(Node *pNode, Node *pParent);
        void DeleteFixupCase2R(Node *pNode, Node *pParent);
        void DeleteFixupCase3L(Node *pNode, Node *pParent);
        void DeleteFixupCase3R(Node *pNode, Node *pParent);
        void DeleteFixupCase4L(Node *pNode, Node *pParent);
        void DeleteFixupCase4R(Node *pNode, Node *pParent);
        void DeleteFixupCase5L(Node *pNode, Node *pParent);
        void DeleteFixupCase5R(Node *pNode, Node *pParent);

    protected:
        static Node *FindInSubTree(const T &tValue, Node *pRoot);
        static Node *FindMaxInSubTree(Node *pRoot);
        static Node *FindMinInSubTree(Node *pRoot);
        static Node *FindMaxBelowGiven(const T &tValue, Node *pRoot, bool bIncludeEqual = true);
        static Node *FindMinAboveGiven(const T &tValue, Node *pRoot, bool bIncludeEqual = true);
        static bool IsSubTreeEqual(Node *pThisNode, Node *pThatNode);
        static Node *FindPrev(Node *pNode);
        static Node *FindNext(Node *pNode);

    public:
        class Iterator;
        class ReverseIterator;

    protected:
        friend class Iterator;
        friend class ReverseIterator;

    protected:
        void CopySubTree(Node *&pDestNode, Node *pSrcNode, Node *pParent = nullptr);
        Node *InsertToSubTree(const T &tValue, Node *pRoot);
        void DeleteSubTree(Node *pNode);
        void Delete(Node *pNode);
        Node *InsertValue(const T &tValue);

    public:
        void Delete(const T &tValue);

    protected:
        void Release();

    // Iterator

    public:
        class Iterator
        {
        public:
            Iterator();
            Iterator(const Iterator &that);

        public:
            typedef T ValueType;

        protected:
            Iterator(Node *pCurrent);
            Iterator(Node *pCurrent, Node *pHead);
            friend class RBTree;

        protected:
            Node *m_pCurrent;
            Node *m_pHead;

        public:
            T &operator * ();
            T *operator -> ();
            operator T * ();
            operator const T * () const;

        public:
            Iterator &operator = (const Iterator &that);
            bool operator == (const Iterator &that) const;
            bool operator != (const Iterator &that) const;

        public:
            Iterator &operator ++ ();
            Iterator operator ++ (int);
            Iterator &operator -- ();
            Iterator operator -- (int);
        };

        class ReverseIterator : public Iterator
        {
        public:
            ReverseIterator();
            ReverseIterator(const Iterator &that);

        protected:
            ReverseIterator(Node *pCurrent);
            ReverseIterator(Node *pCurrent, Node *pHead);
            friend class RBTree;

        public:
            ReverseIterator &operator ++ ();
            ReverseIterator operator ++ (int);
            ReverseIterator &operator -- ();
            ReverseIterator operator -- (int);
        };

    public:
        Iterator Begin() const;
        Iterator End() const;
        ReverseIterator ReverseBegin() const;
        ReverseIterator ReverseEnd() const;

    public:
        Iterator Find(const T &tValue) const;
        Iterator FindMaxBelowGiven(const T &tValue, bool bIncludeEqual = true) const;
        Iterator FindMinAboveGiven(const T &tValue, bool bIncludeEqual = true) const;
        Iterator Insert(const T &tValue);
        template <typename I>
        void Insert(const I &itFirstToInsert, const I &itAfterLastToInsert);
        Iterator Delete(const Iterator &itWhich);
        ReverseIterator Delete(const ReverseIterator &itWhich);
    };

    template <typename T>
    inline RBTree<T>::RBTree()
        : m_pRoot(nullptr), m_nSize(0)
    {

    }

    template <typename T>
    inline RBTree<T>::RBTree(const RBTree &that)
        : m_pRoot(nullptr), m_nSize(0)
    {
        *this = that;
    }

    template <typename T>
    inline RBTree<T>::~RBTree()
    {
        Release();
    }

    template <typename T>
    inline RBTree<T> &RBTree<T>::operator = (const RBTree<T> &that)
    {
        if (this == &that)
        {
            return *this;
        }

        Release();
        CopySubTree(this->m_pRoot, that.m_pRoot);
        this->m_nSize = that.m_nSize;

        return *this;
    }

    template <typename T>
    inline bool RBTree<T>::operator == (const RBTree<T> &that) const
    {
        if (this == &that)
        {
            return true;
        }

        return IsSubTreeEqual(this->m_pRoot, that.m_pRoot);
    }
    
    template <typename T>
    inline bool RBTree<T>::operator != (const RBTree<T> &that) const
    {
        return !(*this == that);
    }

    template <typename T>
    inline bool RBTree<T>::Empty() const
    {
        return m_nSize == 0;
    }

    template <typename T>
    inline size_t RBTree<T>::Size() const
    {
        return m_nSize;
    }

    template <typename T>
    inline void RBTree<T>::Clear()
    {
        Release();
    }

    template <typename T>
    typename RBTree<T>::Node *RBTree<T>::RotateLeft(typename RBTree<T>::Node *pNode)
    {
        if (pNode == nullptr || pNode->pRight == nullptr)
        {
            return pNode;
        }

        typename RBTree<T>::Node *pNewNode = pNode->pRight;

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

    template <typename T>
    typename RBTree<T>::Node *RBTree<T>::RotateRight(typename RBTree<T>::Node *pNode)
    {
        if (pNode == nullptr || pNode->pLeft == nullptr)
        {
            return pNode;
        }

        typename RBTree<T>::Node *pNewNode = pNode->pLeft;

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

    template <typename T>
    void RBTree<T>::SwapNode(typename RBTree<T>::Node *pNode1, typename RBTree<T>::Node *pNode2)
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

        typename RBTree<T>::Node *pParent1 = pNode1->pParent, *pLeft1 = pNode1->pLeft, *pRight1 = pNode1->pRight;
        typename RBTree<T>::Node *pParent2 = pNode2->pParent, *pLeft2 = pNode2->pLeft, *pRight2 = pNode2->pRight;

        typename RBTree<T>::Node **ppParent1ToNode1 = nullptr, **ppParent2ToNode2 = nullptr;

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

        NodeColor ncColor = pNode1->ncColor;
        pNode1->ncColor = pNode2->ncColor;
        pNode2->ncColor = ncColor;
    }


    // All cases
    template <typename T>
    void RBTree<T>::InsertFixup(typename RBTree<T>::Node *pNode)
    {
        // Is root
        if (pNode->pParent == nullptr)
        {
            pNode->ncColor = Black;
        }
        else
        {
            InsertFixupCase1(pNode);
        }
    }

    // Not root
    template <typename T>
    void RBTree<T>::InsertFixupCase1(typename RBTree<T>::Node *pNode)
    {
        // Parent is black
        if (pNode->pParent->ncColor == Black)
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
    template <typename T>
    void RBTree<T>::InsertFixupCase2L(typename RBTree<T>::Node *pNode)
    {
        typename RBTree<T>::Node *pGrandParent = pNode->pParent->pParent;

        // Uncle is red
        if (pGrandParent->pRight != nullptr && pGrandParent->pRight->ncColor == Red)
        {
            pGrandParent->ncColor = Red;
            pGrandParent->pLeft->ncColor = Black;
            pGrandParent->pRight->ncColor = Black;

            InsertFixup(pGrandParent);
        }
        else
        {
            InsertFixupCase3L(pNode);
        }
    }

    template <typename T>
    void RBTree<T>::InsertFixupCase2R(typename RBTree<T>::Node *pNode)
    {
        typename RBTree<T>::Node *pGrandParent = pNode->pParent->pParent;

        if (pGrandParent->pLeft != nullptr && pGrandParent->pLeft->ncColor == Red)
        {
            pGrandParent->ncColor = Red;
            pGrandParent->pRight->ncColor = Black;
            pGrandParent->pLeft->ncColor = Black;

            InsertFixup(pGrandParent);
        }
        else
        {
            InsertFixupCase3R(pNode);
        }
    }

    // Not root, Parent is red, Uncle is black
    template <typename T>
    void RBTree<T>::InsertFixupCase3L(typename RBTree<T>::Node *pNode)
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

    template <typename T>
    void RBTree<T>::InsertFixupCase3R(typename RBTree<T>::Node *pNode)
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
    template <typename T>
    void RBTree<T>::InsertFixupCase4L(typename RBTree<T>::Node *pNode)
    {
        RotateRight(pNode->pParent->pParent);
        pNode->pParent->ncColor = Black;
        pNode->pParent->pRight->ncColor = Red;
    }

    template <typename T>
    void RBTree<T>::InsertFixupCase4R(typename RBTree<T>::Node *pNode)
    {
        RotateLeft(pNode->pParent->pParent);
        pNode->pParent->ncColor = Black;
        pNode->pParent->pLeft->ncColor = Red;
    }

    // All cases
    template <typename T>
    void RBTree<T>::DeleteFixup(typename RBTree<T>::Node *pNode, typename RBTree<T>::Node *pParent)
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
    template <typename T>
    void RBTree<T>::DeleteFixupCase1L(typename RBTree<T>::Node *pNode, typename RBTree<T>::Node *pParent)
    {
        // Sibling is red
        if (pParent->pRight->ncColor == Red)
        {
            RotateLeft(pParent);
            pParent->ncColor = Red;
            pParent->pParent->ncColor = Black;
        }

        DeleteFixupCase2L(pNode, pParent);
    }

    template <typename T>
    void RBTree<T>::DeleteFixupCase1R(typename RBTree<T>::Node *pNode, typename RBTree<T>::Node *pParent)
    {
        if (pParent->pLeft->ncColor == Red)
        {
            RotateRight(pParent);
            pParent->ncColor = Red;
            pParent->pParent->ncColor = Black;
        }

        DeleteFixupCase2R(pNode, pParent);
    }

    // Not root, Sibling is black
    template <typename T>
    void RBTree<T>::DeleteFixupCase2L(typename RBTree<T>::Node *pNode, typename RBTree<T>::Node *pParent)
    {
        typename RBTree<T>::Node *pSibling = pParent->pRight;

        // Sibling's r-child is red
        if (pSibling->pRight != nullptr && pSibling->pRight->ncColor == Red)
        {
            RotateLeft(pParent);
            pSibling->pRight->ncColor = Black;
            NodeColor ncColor = pParent->ncColor;
            pParent->ncColor = pSibling->ncColor;
            pSibling->ncColor = ncColor;
        }
        else
        {
            DeleteFixupCase3L(pNode, pParent);
        }
    }

    template <typename T>
    void RBTree<T>::DeleteFixupCase2R(typename RBTree<T>::Node *pNode, typename RBTree<T>::Node *pParent)
    {
        typename RBTree<T>::Node *pSibling = pParent->pLeft;

        if (pSibling->pLeft != nullptr && pSibling->pLeft->ncColor == Red)
        {
            RotateRight(pParent);
            pSibling->pLeft->ncColor = Black;
            NodeColor ncColor = pParent->ncColor;
            pParent->ncColor = pSibling->ncColor;
            pSibling->ncColor = ncColor;
        }
        else
        {
            DeleteFixupCase3R(pNode, pParent);
        }
    }

    // Not root, Sibling is black, Sibling's r-child is black
    template <typename T>
    void RBTree<T>::DeleteFixupCase3L(typename RBTree<T>::Node *pNode, typename RBTree<T>::Node *pParent)
    {
        typename RBTree<T>::Node *pSibling = pParent->pRight;

        // Sibling's l-child is red
        if (pSibling->pLeft != nullptr && pSibling->pLeft->ncColor == Red)
        {
            RotateRight(pSibling);
            pSibling->pLeft->ncColor = Black;
            pSibling->ncColor = Red;

            DeleteFixupCase2L(pNode, pParent);
        }
        else
        {
            DeleteFixupCase4L(pNode, pParent);
        }
    }

    template <typename T>
    void RBTree<T>::DeleteFixupCase3R(typename RBTree<T>::Node *pNode, typename RBTree<T>::Node *pParent)
    {
        typename RBTree<T>::Node *pSibling = pParent->pLeft;

        if (pSibling->pRight != nullptr && pSibling->pRight->ncColor == Red)
        {
            RotateLeft(pSibling);
            pSibling->pRight->ncColor = Black;
            pSibling->ncColor = Red;

            DeleteFixupCase2R(pNode, pParent);
        }
        else
        {
            DeleteFixupCase4R(pNode, pParent);
        }
    }

    // Not root, Sibling is black, Sibling's r-child is black, Sibling's l-child is black
    template <typename T>
    void RBTree<T>::DeleteFixupCase4L(typename RBTree<T>::Node *pNode, typename RBTree<T>::Node *pParent)
    {
        // Parent is red
        if (pParent->ncColor == Red)
        {
            pParent->ncColor = Black;
            pParent->pRight->ncColor = Red;
        }
        else
        {
            DeleteFixupCase5L(pNode, pParent);
        }
    }

    template <typename T>
    void RBTree<T>::DeleteFixupCase4R(typename RBTree<T>::Node *pNode, typename RBTree<T>::Node *pParent)
    {
        if (pParent->ncColor == Red)
        {
            pParent->ncColor = Black;
            pParent->pLeft->ncColor = Red;
        }
        else
        {
            DeleteFixupCase5R(pNode, pParent);
        }
    }

    // Not root, Sibling is black, Sibling's r-child is black, Sibling's l-child is black, Parent is black
    template <typename T>
    void RBTree<T>::DeleteFixupCase5L(typename RBTree<T>::Node *pNode, typename RBTree<T>::Node *pParent)
    {
        pParent->pRight->ncColor = Red;

        DeleteFixup(pParent, pParent->pParent);
    }

    template <typename T>
    void RBTree<T>::DeleteFixupCase5R(typename RBTree<T>::Node *pNode, typename RBTree<T>::Node *pParent)
    {
        pParent->pLeft->ncColor = Red;

        DeleteFixup(pParent, pParent->pParent);
    }

    template <typename T>
    typename RBTree<T>::Node *RBTree<T>::FindInSubTree(const T &tValue, typename RBTree<T>::Node *pRoot)
    {
        if (pRoot == nullptr || tValue == pRoot->tValue)
        {
            return pRoot;
        }

        return FindInSubTree(tValue, tValue < pRoot->tValue ? pRoot->pLeft : pRoot->pRight);
    }

    template <typename T>
    typename RBTree<T>::Node *RBTree<T>::FindMaxInSubTree(typename RBTree<T>::Node *pRoot)
    {
        if (pRoot == nullptr || pRoot->pRight == nullptr)
        {
            return pRoot;
        }

        return FindMaxInSubTree(pRoot->pRight);
    }

    template <typename T>
    typename RBTree<T>::Node *RBTree<T>::FindMinInSubTree(typename RBTree<T>::Node *pRoot)
    {
        if (pRoot == nullptr || pRoot->pLeft == nullptr)
        {
            return pRoot;
        }

        return FindMinInSubTree(pRoot->pLeft);
    }

    template <typename T>
    typename RBTree<T>::Node *RBTree<T>::FindMaxBelowGiven(const T &tValue, typename RBTree<T>::Node *pRoot, bool bIncludeEqual /*= true*/)
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
                return FindMaxBelowGiven(tValue, pRoot->pLeft);
            }
        }
        else
        {
            return FindMaxBelowGiven(tValue, pRoot->pLeft);
        }
    }

    template <typename T>
    typename RBTree<T>::Node *RBTree<T>::FindMinAboveGiven(const T &tValue, typename RBTree<T>::Node *pRoot, bool bIncludeEqual /*= true*/)
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
                return FindMinAboveGiven(tValue, pRoot->pLeft);
            }
        }
        else
        {
            return FindMaxBelowGiven(tValue, pRoot->pLeft);
        }
    }

    template <typename T>
    bool RBTree<T>::IsSubTreeEqual(typename RBTree<T>::Node *pThisNode, typename RBTree<T>::Node *pThatNode)
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

        return IsSubTreeEqual(pThisNode->pLeft, pThatNode->pLeft) && IsSubTreeEqual(pThisNode->pRight, pThatNode->pRight);
    }

    template <typename T>
    typename RBTree<T>::Node *RBTree<T>::FindPrev(typename RBTree<T>::Node *pNode)
    {
        if (pNode == nullptr)
        {
            return nullptr;
        }

        if (pNode->pLeft != nullptr)
        {
            return FindMaxInSubTree(pNode->pLeft);
        }
        else if (pNode->pParent == nullptr)
        {
            return nullptr;
        }
        else
        {
            while (pNode->pParent != nullptr && pNode == pNode->pParent->pLeft)
            {
                pNode = pNode->pParent;
            }

            return pNode->pParent;
        }
    }

    template <typename T>
    typename RBTree<T>::Node *RBTree<T>::FindNext(typename RBTree<T>::Node *pNode)
    {
        if (pNode == nullptr)
        {
            return nullptr;
        }

        if (pNode->pRight != nullptr)
        {
            return FindMinInSubTree(pNode->pRight);
        }
        else if (pNode->pParent == nullptr)
        {
            return nullptr;
        }
        else
        {
            while (pNode->pParent != nullptr && pNode == pNode->pParent->pRight)
            {
                pNode = pNode->pParent;
            }

            return pNode->pParent;
        }
    }

    template <typename T>
    void RBTree<T>::CopySubTree(typename RBTree<T>::Node *&pDestNode, typename RBTree<T>::Node *pSrcNode, typename RBTree<T>::Node *pParent /*= nullptr*/)
    {
        if (pSrcNode == nullptr)
        {
            return;
        }

        if (pDestNode != nullptr)
        {
            DeleteSubTree(pDestNode);
        }

        pDestNode = new Node(pSrcNode->tValue, pSrcNode->ncColor, pParent, nullptr, nullptr);

        CopySubTree(pDestNode->pLeft, pSrcNode->pLeft, pDestNode);
        CopySubTree(pDestNode->pRight, pSrcNode->pRight, pDestNode);
    }

    template <typename T>
    typename RBTree<T>::Node *RBTree<T>::InsertToSubTree(const T &tValue, typename RBTree<T>::Node *pRoot)
    {
        if (tValue == pRoot->tValue)
        {
            pRoot->tValue = tValue;
            return nullptr;
        }

        RBTree::Node *&pNext = tValue < pRoot->tValue ? pRoot->pLeft : pRoot->pRight;

        if (pNext == nullptr)
        {
            pNext = new RBTree::Node(tValue, Red, pRoot);
            ++m_nSize;
            return pNext;
        }

        return InsertToSubTree(tValue, pNext);
    }

    template <typename T>
    void RBTree<T>::DeleteSubTree(typename RBTree<T>::Node *pNode)
    {
        if (pNode == nullptr)
        {
            return;
        }

        DeleteSubTree(pNode->pLeft);
        DeleteSubTree(pNode->pRight);

        delete pNode;
    }

    template <typename T>
    void RBTree<T>::Delete(typename RBTree<T>::Node *pNode)
    {
        if (pNode == nullptr)
        {
            return nullptr;
        }

        typename RBTree<T>::Node *pNewNode = FindMaxInSubTree(pNode->pLeft);

        if (pNode->pLeft != nullptr && pNode->pRight != nullptr)
        {
            SwapNode(pNode, pNewNode);

            pNewNode = FindMaxInSubTree(pNode->pLeft);
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

        NodeColor ncColor = pNode->ncColor;
        typename RBTree<T>::Node *pParent = pNode->pParent;

        delete pNode;
        --m_nSize;

        if (ncColor == Red)
        {
            return;
        }

        if (pNewNode != nullptr && pNewNode->ncColor == Red)
        {
            pNewNode->ncColor = Black;

            return;
        }

        DeleteFixup(pNewNode, pNewNode == nullptr ? pParent : pNewNode->pParent);
    }

    template <typename T>
    typename RBTree<T>::Node *RBTree<T>::InsertValue(const T &tValue)
    {
        if (m_pRoot == nullptr)
        {
            m_pRoot = new RBTree::Node(tValue);
            ++m_nSize;
            return m_pRoot;
        }

        typename RBTree<T>::Node *pNode = InsertToSubTree(tValue, m_pRoot);

        if (pNode != nullptr)
        {
            InsertFixup(pNode);
        }

        return pNode;
    }

    template <typename T>
    inline void RBTree<T>::Delete(const T &tValue)
    {
        typename RBTree<T>::Node *pNode = FindInSubTree(tValue, m_pRoot);

        if (pNode != nullptr)
        {
            Delete(pNode);
        }
    }


    template <typename T>
    inline void RBTree<T>::Release()
    {
        DeleteSubTree(m_pRoot);

        m_pRoot = nullptr;
        m_nSize = 0;
    }

    // Iterator

    template <typename T>
    inline RBTree<T>::Iterator::Iterator()
        : m_pCurrent(nullptr), m_pHead(nullptr)
    {

    }
    template <typename T>
    inline RBTree<T>::Iterator::Iterator(const typename RBTree<T>::Iterator &that)
        : m_pCurrent(nullptr), m_pHead(nullptr)
    {
        *this = that;
    }

    template <typename T>
    inline RBTree<T>::Iterator::Iterator(typename RBTree<T>::Node *pCurrent)
        : m_pCurrent(pCurrent), m_pHead(nullptr)
    {

    }
    template <typename T>
    inline RBTree<T>::Iterator::Iterator(typename RBTree<T>::Node *pCurrent, typename RBTree<T>::Node *pHead)
        : m_pCurrent(pCurrent), m_pHead(pHead)
    {

    }

    template <typename T>
    inline T &RBTree<T>::Iterator::operator * ()
    {
        return m_pCurrent->tValue;
    }

    template <typename T>
    inline T *RBTree<T>::Iterator::operator -> ()
    {
        return &m_pCurrent->tValue;
    }

    template <typename T>
    inline RBTree<T>::Iterator::operator T * ()
    {
        return &m_pCurrent->tValue;
    }

    template <typename T>
    inline RBTree<T>::Iterator::operator const T * () const
    {
        return &m_pCurrent->tValue;
    }

    template <typename T>
    inline typename RBTree<T>::Iterator &RBTree<T>::Iterator::operator = (const typename RBTree<T>::Iterator &that)
    {
        if (this == &that)
        {
            return *this;
        }

        this->m_pCurrent = that.m_pCurrent;
        this->m_pHead = that.m_pHead;

        return *this;
    }
    
    template <typename T>
    inline bool RBTree<T>::Iterator::operator == (const typename RBTree<T>::Iterator &that) const
    {
        return (this->m_pCurrent == that.m_pCurrent);
    }

    template <typename T>
    inline bool RBTree<T>::Iterator::operator != (const typename RBTree<T>::Iterator &that) const
    {
        return !(*this == that);
    }

    template <typename T>
    inline typename RBTree<T>::Iterator &RBTree<T>::Iterator::operator ++ ()
    {
        m_pCurrent = RBTree<T>::FindNext(m_pCurrent);

        return *this;
    }

    template <typename T>
    inline typename RBTree<T>::Iterator RBTree<T>::Iterator::operator ++ (int)
    {
        typename RBTree<T>::Iterator itRet = *this;

        ++*this;

        return itRet;
    }

    template <typename T>
    inline typename RBTree<T>::Iterator &RBTree<T>::Iterator::operator -- ()
    {
        if (m_pCurrent == nullptr)
        {
            return typename RBTree<T>::ReverseIterator(RBTree<T>::FindMaxInSubTree(m_pRoot), m_pHead);
        }
        else
        {
            m_pCurrent = RBTree<T>::FindNext(m_pCurrent);
        }
    }

    template <typename T>
    inline typename RBTree<T>::Iterator RBTree<T>::Iterator::operator -- (int)
    {
        typename RBTree<T>::Iterator itRet = *this;

        --*this;

        return itRet;
    }

    template <typename T>
    inline RBTree<T>::ReverseIterator::ReverseIterator()
        : Iterator()
    {

    }
    template <typename T>
    inline RBTree<T>::ReverseIterator::ReverseIterator(const typename RBTree<T>::Iterator &that)
        : Iterator(that)
    {

    }

    template <typename T>
    inline RBTree<T>::ReverseIterator::ReverseIterator(typename RBTree<T>::Node *pCurrent)
        : Iterator(pCurrent)
    {

    }

    template <typename T>
    inline RBTree<T>::ReverseIterator::ReverseIterator(typename RBTree<T>::Node *pCurrent, typename RBTree<T>::Node *pHead)
        : Iterator(pCurrent, pHead)
    {

    }

    template <typename T>
    typename RBTree<T>::ReverseIterator &RBTree<T>::ReverseIterator::operator ++ ()
    {
        this->m_pCurrent = RBTree<T>::FindPrev(this->m_pCurrent);

        return *this;
    }

    template <typename T>
    inline typename RBTree<T>::ReverseIterator RBTree<T>::ReverseIterator::operator ++ (int)
    {
        typename RBTree<T>::ReverseIterator itRet = *this;

        ++*this;

        return itRet;
    }

    template <typename T>
    inline typename RBTree<T>::ReverseIterator &RBTree<T>::ReverseIterator::operator -- ()
    {
        if (this->m_pCurrent == nullptr)
        {
            return typename RBTree<T>::ReverseIterator(RBTree<T>::FindMinInSubTree(m_pRoot), this->m_pHead);
        }
        else
        {
            this->m_pCurrent = RBTree<T>::FindNext(this->m_pCurrent);
        }

        return *this;
    }
    
    template <typename T>
    inline typename RBTree<T>::ReverseIterator RBTree<T>::ReverseIterator::operator -- (int)
    {
        typename RBTree<T>::ReverseIterator itRet = *this;

        --*this;

        return itRet;
    }

    template <typename T>
    inline typename RBTree<T>::Iterator RBTree<T>::Begin() const
    {
        return typename RBTree<T>::Iterator(FindMinInSubTree(m_pRoot), m_pRoot);
    }

    template <typename T>
    inline typename RBTree<T>::Iterator RBTree<T>::End() const
    {
        return typename RBTree<T>::Iterator(nullptr, m_pRoot);
    }

    template <typename T>
    inline typename RBTree<T>::ReverseIterator RBTree<T>::ReverseBegin() const
    {
        return typename RBTree<T>::ReverseIterator(FindMaxInSubTree(m_pRoot), m_pRoot);
    }

    template <typename T>
    inline typename RBTree<T>::ReverseIterator RBTree<T>::ReverseEnd() const
    {
        return typename RBTree<T>::ReverseIterator(nullptr, m_pRoot);
    }

    template <typename T>
    inline typename RBTree<T>::Iterator RBTree<T>::Find(const T &tValue) const
    {
        return typename RBTree<T>::Iterator(FindInSubTree(tValue, m_pRoot), m_pRoot);
    }

    template <typename T>
    inline typename RBTree<T>::Iterator RBTree<T>::FindMaxBelowGiven(const T &tValue, bool bIncludeEqual /*= true*/) const
    {
        return typename RBTree<T>::Iterator(FindMaxBelowGiven(tValue, m_pRoot, bIncludeEqual), m_pRoot);
    }

    template <typename T>
    inline typename RBTree<T>::Iterator RBTree<T>::FindMinAboveGiven(const T &tValue, bool bIncludeEqual /*= true*/) const
    {
        return typename RBTree<T>::Iterator(FindMinAboveGiven(tValue, m_pRoot, bIncludeEqual), m_pRoot);
    }

    template <typename T>
    typename RBTree<T>::Iterator RBTree<T>::Insert(const T &tValue)
    {
        return typename RBTree<T>::Iterator(InsertValue(tValue), m_pRoot);
    }

    template <typename T>
    template <typename I>
    void RBTree<T>::Insert(const I &itFirstToInsert, const I &itAfterLastToInsert)
    {
        for (I it = itFirstToInsert; it != itAfterLastToInsert; ++it)
        {
            Insert(*it);
        }
    }

    template <typename T>
    inline typename RBTree<T>::Iterator RBTree<T>::Delete(const typename RBTree<T>::Iterator &itWhich)
    {
        typename RBTree<T>::Node *pNext = FindNext(itWhich.m_pCurrent);
        
        Delete(itWhich.m_pCurrent);

        return typename RBTree<T>::Iterator(pNext, m_pRoot);
    }

    template <typename T>
    inline typename RBTree<T>::ReverseIterator RBTree<T>::Delete(const typename RBTree<T>::ReverseIterator &itWhich)
    {
        typename RBTree<T>::Node *pPrev = FindPrev(itWhich.m_pCurrent);

        Delete(itWhich.m_pCurrent);

        return typename RBTree<T>::Iterator(pPrev, m_pRoot);
    }

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
//                 head: $e.m_pRoot,
//                 left: pLeft,
//                 right: pRight,
//                 size: $e.m_nSize
//             ) : $e.tValue,
//             ")"
//         )
//     )
//     children (
//         #(
//             #tree(
//                 head: $e.m_pRoot,
//                 left: pLeft,
//                 right: pRight,
//                 size: $e.m_nSize
//             ) : $e.tValue
//         )
//     )
// }
// xl::RBTree<*>::Iterator|xl::RBTree<*>::ReverseIterator{
//     preview (
//         $e.m_pCurrent->tValue
//     )
//     children (
//         #(
//             [ptr] : &$e.m_pCurrent->tValue
//         )
//     )
// }
//

#endif // #ifndef __XLTREE_H_6BB48AA6_133A_4E9F_944E_504B887B6980_INCLUDED__
