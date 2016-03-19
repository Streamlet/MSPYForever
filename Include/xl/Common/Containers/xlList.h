//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlList.h
//    Author:      Streamlet
//    Create Time: 2009-09-26
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLLIST_H_2BEF1B3C_A056_4EC7_B5E3_9898E7945B54_INCLUDED__
#define __XLLIST_H_2BEF1B3C_A056_4EC7_B5E3_9898E7945B54_INCLUDED__


#include "../../xlDef.h"
#include "../Memory/xlMemory.h"
#include "../Meta/xlAssert.h"
#include "xlLinkedListNode.h"
#include "xlIterator.h"

namespace xl
{
    template <typename T, typename NodeType = LinkedListNode<T>>
    class List
    {
    public:
        inline List()
            : m_pHead(nullptr), m_pTail(nullptr), m_nSize(0)
        {

        }

        inline List(const List &that)
            : m_pHead(nullptr), m_pTail(nullptr), m_nSize(0)
        {
            *this = that;
        }

#ifdef __XL_CPP11

        inline List(List &&that)
            : m_pHead(nullptr), m_pTail(nullptr), m_nSize(0)
        {
            *this = Memory::Move(that);
        }

#endif

        inline ~List()
        {
            Release();
        }

    public:
        inline List &operator = (const List &that)
        {
            if (this == &that)
            {
                return *this;
            }

            this->Clear();

            for (NodeType *p = that.m_pHead; p != nullptr; p = p->pNext)
            {
                this->PushBack(p->tValue);
            }

            return *this;
        }

#ifdef __XL_CPP11

        inline List &&operator = (List &&that)
        {
            if (this == &that)
            {
                return *this;
            }

            this->m_pHead = that.m_pHead;
            this->m_pTail = that.m_pTail;
            this->m_nSize = that.m_nSize;

            that.m_pHead = nullptr;
            that.m_pTail = nullptr;
            that.m_nSize = 0;

            return *this;
        }

#endif

        inline bool operator == (const List &that) const
        {
            if (this == &that)
            {
                return true;
            }

            if (this->m_nSize != that.m_nSize)
            {
                return false;
            }

            for (NodeType *pThis = this->m_pHead, *pThat = that.m_pHead;
                 pThis != nullptr && pThat != nullptr;
                 pThis = pThis->pNext, pThat = pThat->pNext)
            {
                if (pThis->tValue != pThat->tValue)
                {
                    return false;
                }
            }

            return true;
        }

        inline bool operator != (const List &that) const
        {
            if (this == &that)
            {
                return false;
            }

            if (this->m_nSize != that.m_nSize)
            {
                return true;
            }

            for (NodeType *pThis = this->m_pHead, *pThat = that.m_pHead;
                 pThis != nullptr && pThat != nullptr;
                 pThis = pThis->pNext, pThat = pThat->pNext)
            {
                if (pThis->tValue != pThat->tValue)
                {
                    return true;
                }
            }

            return false;
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

    protected:
        inline void Insert(NodeType *pWhere, const T &tValue)
        {
            NodeType *pNewNode = new NodeType(tValue);

            XL_ASSERT(m_pHead == nullptr && m_pTail == nullptr && m_nSize == 0 ||
                      m_pHead != nullptr && m_pTail != nullptr && m_nSize != 0);

            if (m_pHead == nullptr && m_pTail == nullptr)
            {
                m_pHead = pNewNode;
                m_pTail = pNewNode;
            }
            else if (pWhere == m_pHead)
            {
                pNewNode->pNext = m_pHead;
                m_pHead->pPrev = pNewNode;
                m_pHead = pNewNode;
            }
            else if (pWhere == nullptr)
            {
                pNewNode->pPrev = m_pTail;
                m_pTail->pNext = pNewNode;
                m_pTail = pNewNode;
            }
            else
            {
                pNewNode->pPrev = pWhere->pPrev;
                pNewNode->pNext = pWhere;
                pWhere->pPrev->pNext = pNewNode;
                pWhere->pPrev = pNewNode;
            }

            ++m_nSize;
        }

        inline void Delete(NodeType *pNode)
        {
            if (pNode == m_pHead && pNode == m_pTail && pNode != nullptr)
            {
                m_pHead = nullptr;
                m_pTail = nullptr;
            }
            else if (pNode == m_pHead && pNode != m_pTail)
            {
                pNode->pNext->pPrev = nullptr;
                m_pHead = pNode->pNext;
            }
            else if (pNode == m_pTail && pNode != m_pHead)
            {
                pNode->pPrev->pNext = nullptr;
                m_pTail = pNode->pPrev;
            }
            else
            {
                pNode->pPrev->pNext = pNode->pNext;
                pNode->pNext->pPrev = pNode->pPrev;
            }

            delete pNode;
            --m_nSize;

            XL_ASSERT(m_pHead == nullptr && m_pTail == nullptr && m_nSize == 0 ||
                      m_pHead != nullptr && m_pTail != nullptr && m_nSize != 0);
        }

    public:
        inline void PushFront(const T &tValue)
        {
            Insert(m_pHead, tValue);
        }

        inline void PushBack(const T &tValue)
        {
            Insert(nullptr, tValue);
        }

        inline void PopFront()
        {
            Delete(m_pHead);
        }

        inline void PopBack()
        {
            Delete(m_pTail);
        }

        inline void Clear()
        {
            Release();
        }

    protected:
        NodeType *m_pHead;
        NodeType *m_pTail;
        size_t m_nSize;

    public:
#ifdef __XL_CPP11
        typedef LinkedListIterator<T, NodeType> Iterator;
        typedef ReverseLinkedListIterator<T, NodeType> ReverseIterator;
#else
        typedef LinkedListIteratorT<T, NodeType, false> Iterator;
        typedef LinkedListIteratorT<T, NodeType, true> ReverseIterator;
#endif

    protected:
        inline void Release()
        {
            for (NodeType *p = m_pHead, *q = p; p != nullptr; q = p)
            {
                p = p->pNext;
                delete q;
            }

            m_pHead = nullptr;
            m_pTail = nullptr;
            m_nSize = 0;
        }

    public:
        inline Iterator Begin() const
        {
            return Iterator(m_pHead);
        }

        inline Iterator End() const
        {
            return Iterator(nullptr);
        }

        inline ReverseIterator ReverseBegin() const
        {
            return ReverseIterator(m_pTail);
        }

        inline ReverseIterator ReverseEnd() const
        {
            return ReverseIterator(nullptr);
        }

    public:
        inline void Insert(const Iterator &itWhere, const T &tValue)
        {
            NodeType *pWhere = (NodeType *)itWhere;
            Insert(pWhere, tValue);
        }

        inline void Insert(const ReverseIterator &itWhere, const T &tValue)
        {
            NodeType *pWhere = (NodeType *)itWhere;
            Insert(pWhere, tValue);
        }

        template <typename I>
        inline void Insert(const Iterator &itWhere, const I &itBegin, const I &itEnd)
        {
            for (I it = itBegin; it != itEnd; ++it)
            {
                Insert(itWhere, *it);
            }
        }

        template <typename I>
        inline void Insert(const ReverseIterator &itWhere, const I &itBegin, const I &itEnd)
        {
            for (I it = itBegin; it != itEnd; ++it)
            {
                Insert(itWhere, *it);
            }
        }

        inline Iterator Delete(const Iterator &itWhere)
        {
            NodeType *pNode = (NodeType *)itWhere;
            NodeType *pNext = pNode->pNext;
            Delete(pNode);
            return Iterator(pNext);
        }

        inline ReverseIterator Delete(const ReverseIterator &itWhere)
        {
            NodeType *pNode = (NodeType *)itWhere;
            NodeType *pPrev = pNode->pPrev;
            Delete(pNode);
            return ReverseIterator(pPrev);
        }

        inline Iterator Delete(const Iterator &itBegin, const Iterator &itEnd)
        {
            NodeType *pBegin = (NodeType *)itBegin;
            NodeType *pEnd = (NodeType *)itEnd;

            for (NodeType *p = pBegin; p != pEnd; p = p->pNext)
            {
                Delete(p);
            }

            return Iterator(pEnd);
        }

        inline ReverseIterator Delete(const ReverseIterator &itBegin, const ReverseIterator &itEnd)
        {
            NodeType *pBegin = (NodeType *)itBegin;
            NodeType *pEnd = (NodeType *)itEnd;

            for (NodeType *p = pBegin; p != pEnd; p = p->pNext)
            {
                Delete(p);
            }

            return ReverseIterator(pEnd);
        }
    };

} // namespace xl

#endif // #ifndef __XLLIST_H_2BEF1B3C_A056_4EC7_B5E3_9898E7945B54_INCLUDED__
