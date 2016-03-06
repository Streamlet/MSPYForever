//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlTree.h
//    Author:      Streamlet
//    Create Time: 2011-10-15
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLTREE_H_E8CDF772_F44E_4CB4_B760_DEC9AE4878A0_INCLUDED__
#define __XLTREE_H_E8CDF772_F44E_4CB4_B760_DEC9AE4878A0_INCLUDED__


#include "../../xlDef.h"
#include "xlArray.h"

namespace xl
{
    template <typename T>
    struct TreeNode
    {
        typedef TreeNode *NodePtr;
        typedef Array<NodePtr>  NodePtrList;

        T tValue;

        NodePtr     pParent;
        NodePtrList arrChilds;

        TreeNode() : pParent(nullptr)
        {

        }

        TreeNode(const T &tValue, NodePtr pParent = nullptr) : tValue(tValue), pParent(pParent)
        {

        }
    };

    template <typename T, typename NodeType = TreeNode<T>>
    class Tree
    {
    public:
        typedef NodeType *NodePtr;
        typedef Array<NodePtr> NodePtrList;

    public:
        Tree() : m_pRoot(nullptr)
        {

        }

        Tree(const Tree &that) : m_pRoot(nullptr)
        {
            *this = that;
        }

        ~Tree()
        {
            Clear();
        }

    protected:
        NodePtr m_pRoot;

    public:
        Tree &operator = (const Tree &that)
        {
            if (this == &that)
            {
                return *this;
            }

            this->SetRoot(CopySubTree(that.m_pRoot));

            return *this;
        }

        bool operator == (const Tree &that) const
        {
            if (this == &that)
            {
                return true;
            }

            return IsSubTreeEqual(this->m_pRoot, that->m_pRoot);
        }

        bool operator != (const Tree &that) const
        {
            if (this == &that)
            {
                return false;
            }

            return IsSubTreeUnequal(this->m_pRoot, that->m_pRoot);
        }

    public:
        NodePtr Root() const
        {
            return m_pRoot;
        }

        bool Empty() const
        {
            return m_pRoot == null;
        }

    public:
        void Clear()
        {
            DeleteSubTree(m_pRoot);
        }

        NodePtr SetRoot(NodePtr pNode)
        {
            Clear();

            m_pRoot = CopySubTree(pNode);

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

            if (pThisNode->arrChilds.Size() != pThatNode->arrChilds.Size())
            {
                return false;
            }

            if (pThisNode->tValue != pThatNode->tValue)
            {
                return false;
            }

            for (size_t i = 0; i < pThisNode->arrChilds.Size(); ++i)
            {
                if (!IsSubTreeEqual(pThisNode->arrChilds[i], pThatNode->arrChilds[i]))
                {
                    return false;
                }
            }

            return true;
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

            if (pThisNode->arrChilds.Size() != pThatNode->arrChilds.Size())
            {
                return true;
            }

            if (pThisNode->tValue != pThatNode->tValue)
            {
                return true;
            }

            for (size_t i = 0; i < pThisNode->arrChilds.Size(); ++i)
            {
                if (IsSubTreeUnequal(pThisNode->arrChilds[i], pThatNode->arrChilds[i]))
                {
                    return true;
                }
            }

            return false;
        }

    public:
        NodePtr CopySubTree(NodePtr pSubTreeRoot)
        {
            if (pSubTreeRoot == nullptr)
            {
                return nullptr;
            }

            NodePtr pNode = new Node(pSubTreeRoot->tValue);

            for (auto it = pSubTreeRoot->arrChilds.Begin(); it != pSubTreeRoot->arrChilds.End(); ++it)
            {
                NodePtr pSubNode = CopySubTree(*it);
                pSubNode->pParent = pNode;
                pNode->arrChilds.PushBack(pSubNode);
            }

            return pNode;
        }

        NodePtr InsertSubTree(NodePtr pParent, size_t nInsetAt, NodePtr pSubTreeRoot)
        {
            if (pSubTreeRoot == nullptr)
            {
                return nullptr;
            }

            if (pParent == nullptr)
            {
                return nullptr;
            }

            NodePtr pNode = CopySubTree(pSubTreeRoot);
            pNode->pParent = pParent;

            if (nInsetAt < 0 || nInsetAt >= pParent->arrChilds.Size())
            {
                pParent->arrChilds.PushBack(pNode);
            }
            else
            {
                pParent->arrChilds.Insert(nInsetAt, pNode);
            }

            return pNode;
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
                for (auto it = pParent->arrChilds.Begin(); it != pParent->arrChilds.End(); ++it)
                {
                    if (*it == pSubTreeRoot)
                    {
                        pParent->arrChilds.Delete(it);
                        break;
                    }
                }
            }

            for (auto it = pSubTreeRoot->arrChilds.Begin(); it != pSubTreeRoot->arrChilds.End(); ++it)
            {
                DeleteSubTree(*it);
            }

            delete pSubTreeRoot;

            return pParent;
        }
    };

} // namespace xl

#endif // #ifndef __XLTREE_H_E8CDF772_F44E_4CB4_B760_DEC9AE4878A0_INCLUDED__
