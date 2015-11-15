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


#include "xlLinkedListNode.h"

namespace xl
{
    template <typename T, typename NodeType = LinkedListNode<T>>
    class List
    {
    public:
        List()
            : m_pHead(nullptr), m_nSize(0)
        {

        }

        List(const List<T, NodeType> &that)
            : m_pHead(nullptr), m_nSize(0)
        {
            *this = that;
        }

        ~List()
        {
            Release();
        }


    public:
        List<T, NodeType> &operator = (const List<T, NodeType> &that)
        {
            if (this == &that)
            {
                return *this;
            }

            this->Clear();

            for (NodeType *p = that.m_pHead; p != nullptr; )
            {
                this->PushBack(p->tValue);

                p = p->pNext;

                if (p == that.m_pHead)
                {
                    break;
                }
            }

            return *this;
        }

        bool operator == (const List<T, NodeType> &that) const
        {
            if (this == &that)
            {
                return true;
            }

            if (this->m_nSize != that.m_nSize)
            {
                return false;
            }

            for (NodeType *pThis = this->m_pHead, *pThat = that.m_pHead; pThis != nullptr && pThat != nullptr; )
            {
                if (pThis->tValue != pThat->tValue)
                {
                    return false;
                }

                pThis = pThis->pNext;
                pThat = pThat->pNext;

                if (pThis == this->m_pHead || pThat == that.m_pHead)
                {
                    break;
                }
            }

            return true;
        }

        bool operator != (const List<T, NodeType> &that) const
        {
            if (this == &that)
            {
                return false;
            }

            if (this->m_nSize != that.m_nSize)
            {
                return true;
            }

            for (NodeType *pThis = this->m_pHead, *pThat = that.m_pHead; pThis != nullptr && pThat != nullptr; )
            {
                if (pThis->tValue != pThat->tValue)
                {
                    return true;
                }

                pThis = pThis->pNext;
                pThat = pThat->pNext;

                if (pThis == this->m_pHead || pThat == that.m_pHead)
                {
                    break;
                }
            }

            return false;
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

    protected:
        void Insert(NodeType *pNode, const T &tValue)
        {
            NodeType *pNewNode = new NodeType(tValue);
            NodeType *pBefore = pNode == nullptr ? m_pHead : pNode;

            if (pBefore == nullptr)
            {
                pNewNode->pPrev = pNewNode;
                pNewNode->pNext = pNewNode;
            }
            else
            {
                pNewNode->pPrev = pBefore->pPrev;
                pNewNode->pNext = pBefore;
                pBefore->pPrev->pNext = pNewNode;
                pBefore->pPrev = pNewNode;
            }

            if (pNode == m_pHead || m_pHead == nullptr)
            {
                m_pHead = pNewNode;
            }

            ++m_nSize;
        }

        void Delete(NodeType *pNode)
        {
            if (pNode == nullptr)
            {
                return;
            }

            if (pNode == m_pHead)
            {
                m_pHead = pNode->pNext;

                if (m_pHead == pNode)
                {
                    m_pHead = nullptr;
                }
            }

            pNode->pPrev->pNext = pNode->pNext;
            pNode->pNext->pPrev = pNode->pPrev;

            delete pNode;
            --m_nSize;
        }

    public:
        void PushFront(const T &tValue)
        {
            Insert(m_pHead, tValue);
        }

        void PushBack(const T &tValue)
        {
            Insert(nullptr, tValue);
        }

        void PopFront()
        {
            Delete(m_pHead);
        }

        void PopBack()
        {
            Delete(m_pHead != nullptr ? m_pHead->pPrev : nullptr);
        }

        void Clear()
        {
            while (m_pHead != nullptr)
            {
                Delete(m_pHead);
            }
        }

    protected:
        NodeType *m_pHead;
        size_t m_nSize;

    protected:
        void Release()
        {
            Clear();
        }

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
            Iterator(NodeType *pCurrent);
            Iterator(NodeType *pCurrent, NodeType *pHead);
            friend class List;

        protected:
            NodeType *m_pCurrent;
            NodeType *m_pHead;

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
            ReverseIterator(NodeType *pCurrent);
            ReverseIterator(NodeType *pCurrent, NodeType *pHead);
            friend class List;

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
        void Insert(const Iterator &itBeforeWhich, const T &tValue);
        void Insert(const ReverseIterator &itBeforeWhich, const T &tValue);
        template <typename I>
        void Insert(const Iterator &itBeforeWhich, const I &itFirstToInsert, const I &itAfterLastToInsert);
        template <typename I>
        void Insert(const ReverseIterator &itBeforeWhich, const I &itFirstToInsert, const I &itAfterLastToInsert);
        Iterator Delete(const Iterator &itWhich);
        ReverseIterator Delete(const ReverseIterator &itWhich);
        Iterator Delete(const Iterator &itFirstToInsert, const Iterator &itAfterLastToDelete);
        ReverseIterator Delete(const ReverseIterator &itFirstToInsert, const ReverseIterator &itAfterLastToDelete);
    };




    // Iterator


    template <typename T, typename NodeType>
    inline List<T, NodeType>::Iterator::Iterator()
        : m_pCurrent(nullptr), m_pHead(nullptr)
    {

    }

    template <typename T, typename NodeType>
    inline List<T, NodeType>::Iterator::Iterator(const Iterator &that)
        : m_pCurrent(nullptr), m_pHead(nullptr)
    {
        *this = that;
    }

    template <typename T, typename NodeType>
    inline List<T, NodeType>::Iterator::Iterator(NodeType *pCurrent)
        : m_pCurrent(pCurrent), m_pHead(nullptr)
    {

    }

    template <typename T, typename NodeType>
    inline List<T, NodeType>::Iterator::Iterator(NodeType *pCurrent, NodeType *pHead)
        : m_pCurrent(pCurrent), m_pHead(pHead)
    {

    }

    template <typename T, typename NodeType>
    inline T &List<T, NodeType>::Iterator::operator * ()
    {
        return m_pCurrent->tValue;
    }

    template <typename T, typename NodeType>
    inline T *List<T, NodeType>::Iterator::operator -> ()
    {
        return &m_pCurrent->tValue;
    }

    template <typename T, typename NodeType>
    inline List<T, NodeType>::Iterator::operator T * ()
    {
        return m_pCurrent->tValue;
    }

    template <typename T, typename NodeType>
    inline List<T, NodeType>::Iterator::operator const T * () const
    {
        return m_pCurrent->tValue;
    }

    template <typename T, typename NodeType>
    inline typename List<T, NodeType>::Iterator &List<T, NodeType>::Iterator::operator = (const typename List<T, NodeType>::Iterator &that)
    {
        if (this == & that)
        {
            return *this;
        }

        this->m_pCurrent = that.m_pCurrent;
        this->m_pHead = that.m_pHead;

        return *this;
    }

    template <typename T, typename NodeType>
    inline bool List<T, NodeType>::Iterator::operator == (const Iterator &that) const
    {
        return (this->m_pCurrent == that.m_pCurrent);
    }

    template <typename T, typename NodeType>
    inline bool List<T, NodeType>::Iterator::operator != (const Iterator &that) const
    {
        return (this->m_pCurrent != that.m_pCurrent);
    }

    template <typename T, typename NodeType>
    inline typename List<T, NodeType>::Iterator &List<T, NodeType>::Iterator::operator ++ ()
    {
        if (m_pCurrent != nullptr)
        {
            m_pCurrent = m_pCurrent->pNext;
        }

        if (m_pCurrent == m_pHead)
        {
            m_pCurrent = nullptr;
        }

        return *this;
    }

    template <typename T, typename NodeType>
    inline typename List<T, NodeType>::Iterator List<T, NodeType>::Iterator::operator ++ (int)
    {
        typename List<T, NodeType>::Iterator itRet = *this;

        ++*this;

        return itRet;
    }

    template <typename T, typename NodeType>
    inline typename List<T, NodeType>::Iterator &List<T, NodeType>::Iterator::operator -- ()
    {
        if (m_pCurrent != m_pHead)
        {
            if (m_pCurrent == nullptr)
            {
                if (m_pHead != nullptr)
                {
                    m_pCurrent = m_pHead->pPrev;
                }
            }
            else
            {
                m_pCurrent = m_pCurrent->pPrev;
            }
        }

        return *this;
    }

    template <typename T, typename NodeType>
    inline typename List<T, NodeType>::Iterator List<T, NodeType>::Iterator::operator -- (int)
    {
        typename List<T, NodeType>::Iterator itRet = *this;

        --*this;

        return itRet;
    }

    template <typename T, typename NodeType>
    inline List<T, NodeType>::ReverseIterator::ReverseIterator()
        : Iterator()
    {

    }

    template <typename T, typename NodeType>
    inline List<T, NodeType>::ReverseIterator::ReverseIterator(const Iterator &that)
        : Iterator(that)
    {

    }

    template <typename T, typename NodeType>
    inline List<T, NodeType>::ReverseIterator::ReverseIterator(NodeType *pCurrent)
        : Iterator(pCurrent)
    {

    }

    template <typename T, typename NodeType>
    inline List<T, NodeType>::ReverseIterator::ReverseIterator(NodeType *pCurrent, NodeType *pHead)
        : Iterator(pCurrent, pHead)
    {

    }

    template <typename T, typename NodeType>
    inline typename List<T, NodeType>::ReverseIterator &List<T, NodeType>::ReverseIterator::operator ++ ()
    {
        if (this->m_pCurrent != nullptr)
        {
            this->m_pCurrent = this->m_pCurrent->pPrev;
        }

        if (m_pHead != nullptr && this->m_pCurrent == m_pHead->pPrev)
        {
            this->m_pCurrent = nullptr;
        }

        return *this;
    }

    template <typename T, typename NodeType>
    inline typename List<T, NodeType>::ReverseIterator List<T, NodeType>::ReverseIterator::operator ++ (int)
    {
        typename List<T, NodeType>::ReverseIterator itRet = *this;

        ++*this;

        return *itRet;
    }

    template <typename T, typename NodeType>
    inline typename List<T, NodeType>::ReverseIterator &List<T, NodeType>::ReverseIterator::operator -- ()
    {
        if (m_pHead == nullptr || (m_pHead != nullptr && this->m_pCurrent != m_pHead->pPrev))
        {
            if (this->m_pCurrent == nullptr)
            {
                this->m_pCurrent = m_pHead;
            }
            else
            {
                if (this->m_pCurrent->pNext != m_pHead)
                {
                    this->m_pCurrent = this->m_pCurrent->pNext;
                }
            }
        }

        return *this;
    }

    template <typename T, typename NodeType>
    inline typename List<T, NodeType>::ReverseIterator List<T, NodeType>::ReverseIterator::operator -- (int)
    {
        typename List<T, NodeType>::ReverseIterator itRet = *this;

        ++*this;

        return *itRet;
    }

    template <typename T, typename NodeType>
    inline typename List<T, NodeType>::Iterator List<T, NodeType>::Begin() const
    {
        return typename List<T, NodeType>::Iterator(m_pHead, m_pHead);
    }

    template <typename T, typename NodeType>
    inline typename List<T, NodeType>::Iterator List<T, NodeType>::End() const
    {
        return typename List<T, NodeType>::Iterator(nullptr, m_pHead);
    }

    template <typename T, typename NodeType>
    inline typename List<T, NodeType>::ReverseIterator List<T, NodeType>::ReverseBegin() const
    {
        return typename List<T, NodeType>::ReverseIterator(m_pHead == nullptr ? nullptr : m_pHead->pPrev, m_pHead);
    }

    template <typename T, typename NodeType>
    inline typename List<T, NodeType>::ReverseIterator List<T, NodeType>::ReverseEnd() const
    {
        return typename List<T, NodeType>::ReverseIterator(nullptr, m_pHead);
    }


    template <typename T, typename NodeType>
    void List<T, NodeType>::Insert(const typename List<T, NodeType>::Iterator &itBeforeWhich, const T &tValue)
    {
        NodeType *pNode = new NodeType(tValue);
        NodeType *pBefore = itBeforeWhich.m_pCurrent;

        if (pBefore == nullptr)
        {
            pBefore = m_pHead;
        }

        if (pBefore == nullptr)
        {
            pNode->pPrev = pNode;
            pNode->pNext = pNode;
        }
        else
        {
            pNode->pPrev = pBefore->pPrev;
            pNode->pNext = pBefore;
            pBefore->pPrev->pNext = pNode;
            pBefore->pPrev = pNode;

        }

        if (itBeforeWhich.m_pCurrent == m_pHead || m_pHead == nullptr)
        {
            m_pHead = pNode;
        }

        ++m_nSize;
    }

    template <typename T, typename NodeType>
    void List<T, NodeType>::Insert(const typename List<T, NodeType>::ReverseIterator &itBeforeWhich, const T &tValue)
    {
        NodeType *pNode = new NodeType(tValue);
        NodeType *pBefore = itBeforeWhich.m_pCurrent;

        if (pBefore == nullptr && m_pHead != nullptr)
        {
            pBefore = m_pHead->pPrev;
        }

        if (pBefore == nullptr)
        {
            pNode->pPrev = pNode;
            pNode->pNext = pNode;
        }
        else
        {
            pNode->pPrev = pBefore;
            pNode->pNext = pBefore->pNext;
            pBefore->pNext->pPrev = pNode;
            pBefore->pNext = pNode;
        }

        if (itBeforeWhich.m_pCurrent == nullptr || m_pHead == nullptr)
        {
            m_pHead = pNode;
        }

        ++m_nSize;
    }


    template <typename T, typename NodeType>
    template <typename I>
    void List<T, NodeType>::Insert(const Iterator &itBeforeWhich, const I &itFirstToInsert, const I &itAfterLastToInsert)
    {
        for (I it = itFirstToInsert; it != itAfterLastToInsert; ++it)
        {
            Insert(itBeforeWhich, *it);
        }
    }

    template <typename T, typename NodeType>
    template <typename I>
    void List<T, NodeType>::Insert(const ReverseIterator &itBeforeWhich, const I &itFirstToInsert, const I &itAfterLastToInsert)
    {
        for (I it = itFirstToInsert; it != itAfterLastToInsert; ++it)
        {
            Insert(itBeforeWhich, *it);
        }
    }

    template <typename T, typename NodeType>
    typename List<T, NodeType>::Iterator List<T, NodeType>::Delete(const typename List<T, NodeType>::Iterator &itWhich)
    {
        NodeType *pNode = itWhich.m_pCurrent;

        if (pNode == nullptr)
        {
            return typename List<T, NodeType>::Iterator(nullptr, m_pHead);
        }

        if (pNode == m_pHead)
        {
            m_pHead = pNode->pNext;

            if (m_pHead == pNode)
            {
                m_pHead = nullptr;
            }
        }

        typename List<T, NodeType>::Iterator itRet(pNode->pNext != pNode ? pNode->pNext : nullptr, m_pHead);

        pNode->pPrev->pNext = pNode->pNext;
        pNode->pNext->pPrev = pNode->pPrev;

        delete pNode;
        --m_nSize;

        return itRet;
    }

    template <typename T, typename NodeType>
    typename List<T, NodeType>::ReverseIterator List<T, NodeType>::Delete(const ReverseIterator &itWhich)
    {
        NodeType *pNode = itWhich.m_pCurrent;

        if (pNode == nullptr)
        {
            return typename List<T, NodeType>::Iterator(nullptr, m_pHead);
        }

        if (pNode == m_pHead)
        {
            m_pHead = pNode->pNext;

            if (m_pHead == pNode)
            {
                m_pHead = nullptr;
            }
        }

        typename List<T, NodeType>::ReverseIterator itRet(pNode->pPrev != pNode ? pNode->pPrev : nullptr, m_pHead);

        pNode->pPrev->pNext = pNode->pNext;
        pNode->pNext->pPrev = pNode->pPrev;

        delete pNode;
        --m_nSize;

        return itRet;
    }

    template <typename T, typename NodeType>
    typename List<T, NodeType>::Iterator List<T, NodeType>::Delete(const Iterator &itFirstToInsert, const Iterator &itAfterLastToDelete)
    {
        typename List<T, NodeType>::Iterator it = itFirstToInsert;

        while (it != itAfterLastToDelete)
        {
            it = Delete(it);
        }

        return it;
    }

    template <typename T, typename NodeType>
    typename List<T, NodeType>::ReverseIterator List<T, NodeType>::Delete(const ReverseIterator &itFirstToInsert, const ReverseIterator &itAfterLastToDelete)
    {
        typename List<T, NodeType>::ReverseIterator it = itFirstToInsert;

        while (it != itAfterLastToDelete)
        {
            it = Delete(it);
        }

        return it;
    }

} // namespace xl

//
// For convenience of debugging, put the following code to the [AutoExpand] section of
//     X:\Program Files\Microsoft Visual Studio 10.0\Common7\Packages\Debugger\autoexp.dat
//
// ;------------------------------------------------------------------------------
// ;  xl::List
// ;------------------------------------------------------------------------------
// xl::List<*>{
//     preview (
//         #(
//             "[",
//             $e.m_nSize,
//             "](",
//             #list(
//                 head: $e.m_pHead,
//                 size: $e.m_nSize,
//                 next: pNext
//             ) : $e.tValue,
//             ")"
//         )
//     )
//     children (
//         #list(
//             head: $e.m_pHead,
//             size: $e.m_nSize,
//             next: pNext
//         ) : $e.tValue
//     )
// }
// xl::List<*>::Iterator|xl::List<*>::ReverseIterator{
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

#endif // #ifndef __XLLIST_H_2BEF1B3C_A056_4EC7_B5E3_9898E7945B54_INCLUDED__
