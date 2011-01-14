//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlList.h
//    Author:      Streamlet
//    Create Time: 2009-09-26
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLLIST_H_2BEF1B3C_A056_4EC7_B5E3_9898E7945B54_INCLUDED__
#define __XLLIST_H_2BEF1B3C_A056_4EC7_B5E3_9898E7945B54_INCLUDED__


#include <xl/xlDef.h>

namespace xl
{
    template <typename T>
    class List
    {
    public:
        List();
        List(const List<T> &that);
        ~List();

    protected:
        struct Node
        {
            T tValue;
            Node *pPrev;
            Node *pNext;

            Node() : tValue(), pPrev(nullptr), pNext(nullptr) { }
            Node(const T &tValue) : tValue(tValue), pPrev(nullptr), pNext(nullptr) { }
            Node(const T &tValue, Node *pPrev, Node *pNext) : tValue(tValue), pPrev(pPrev), pNext(pNext) { }
        };

    public:
        List<T> &operator = (const List<T> &that);
        bool operator == (const List<T> &that) const;
        bool operator != (const List<T> &that) const;

    public:
        bool Empty() const;
        size_t Size() const;

    protected:
        void Insert(Node *pNode, const T &tValue);
        void Delete(Node *pNode);

    public:
        void PushFront(const T &tValue);
        void PushBack(const T &tValue);
        void PopFront();
        void PopBack();
        void Clear();

    protected:
        Node *m_pHead;
        size_t m_nSize;

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
            friend class List;

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

    template <typename T>
    inline List<T>::List()
        : m_pHead(nullptr), m_nSize(0)
    {

    }

    template <typename T>
    inline List<T>::List(const List<T> &that)
        : m_pHead(nullptr), m_nSize(0)
    {
        *this = that;
    }

    template <typename T>
    inline List<T>::~List()
    {
        Release();
    }

    template <typename T>
    List<T> &List<T>::operator = (const List<T> &that)
    {
        if (this == &that)
        {
            return *this;
        }

        this->Clear();

        for (typename List<T>::Node *p = that.m_pHead; p != nullptr; )
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

    template <typename T>
    bool List<T>::operator == (const List<T> &that) const
    {
        if (this == &that)
        {
            return true;
        }

        if (this->m_nSize != that.m_nSize)
        {
            return false;
        }

        for (typename List<T>::Node *pThis = this->m_pHead, *pThat = that.m_pHead; pThis != nullptr && pThat != nullptr; )
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

    template <typename T>
    inline bool List<T>::operator != (const List<T> &that) const
    {
        return !(*this == that);
    }

    template <typename T>
    inline bool List<T>::Empty() const
    {
        return m_nSize == 0;
    }

    template <typename T>
    inline size_t List<T>:: Size() const
    {
        return m_nSize;
    }

    template <typename T>
    void List<T>::Insert(typename List<T>::Node *pNode, const T &tValue)
    {
        typename List<T>::Node *pNewNode = new typename List<T>::Node(tValue);
        typename List<T>::Node *pBefore = pNode == nullptr ? m_pHead : pNode;

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

    template <typename T>
    inline void List<T>::PushFront(const T &tValue)
    {
        Insert(m_pHead, tValue);
    }

    template <typename T>
    inline void List<T>::PushBack(const T &tValue)
    {
        Insert(nullptr, tValue);
    }

    template <typename T>
    void List<T>::Delete(Node *pNode)
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

    template <typename T>
    inline void List<T>::PopFront()
    {
        Delete(m_pHead);
    }

    template <typename T>
    inline void List<T>::PopBack()
    {
        Delete(m_pHead != nullptr ? m_pHead->pPrev : nullptr);
    }

    template <typename T>
    void List<T>::Clear()
    {
        while (m_pHead != nullptr)
        {
            Delete(m_pHead);
        }
    }

    template <typename T>
    inline void List<T>::Release()
    {
        Clear();
    }

    // Iterator


    template <typename T>
    inline List<T>::Iterator::Iterator()
        : m_pCurrent(nullptr), m_pHead(nullptr)
    {

    }

    template <typename T>
    inline List<T>::Iterator::Iterator(const Iterator &that)
        : m_pCurrent(nullptr), m_pHead(nullptr)
    {
        *this = that;
    }

    template <typename T>
    inline List<T>::Iterator::Iterator(Node *pCurrent)
        : m_pCurrent(pCurrent), m_pHead(nullptr)
    {

    }

    template <typename T>
    inline List<T>::Iterator::Iterator(Node *pCurrent, Node *pHead)
        : m_pCurrent(pCurrent), m_pHead(pHead)
    {

    }

    template <typename T>
    inline T &List<T>::Iterator::operator * ()
    {
        return m_pCurrent->tValue;
    }

    template <typename T>
    inline T *List<T>::Iterator::operator -> ()
    {
        return &m_pCurrent->tValue;
    }

    template <typename T>
    inline List<T>::Iterator::operator T * ()
    {
        return m_pCurrent->tValue;
    }

    template <typename T>
    inline List<T>::Iterator::operator const T * () const
    {
        return m_pCurrent->tValue;
    }

    template <typename T>
    inline typename List<T>::Iterator &List<T>::Iterator::operator = (const typename List<T>::Iterator &that)
    {
        if (this == & that)
        {
            return *this;
        }

        this->m_pCurrent = that.m_pCurrent;
        this->m_pHead = that.m_pHead;

        return *this;
    }

    template <typename T>
    inline bool List<T>::Iterator::operator == (const Iterator &that) const
    {
        return (this->m_pCurrent == that.m_pCurrent);
    }

    template <typename T>
    inline bool List<T>::Iterator::operator != (const Iterator &that) const
    {
        return !(*this == that);
    }

    template <typename T>
    inline typename List<T>::Iterator &List<T>::Iterator::operator ++ ()
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

    template <typename T>
    inline typename List<T>::Iterator List<T>::Iterator::operator ++ (int)
    {
        typename List<T>::Iterator itRet = *this;

        ++*this;

        return *itRet;
    }

    template <typename T>
    inline typename List<T>::Iterator &List<T>::Iterator::operator -- ()
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

    template <typename T>
    inline typename List<T>::Iterator List<T>::Iterator::operator -- (int)
    {
        typename List<T>::Iterator itRet = *this;

        --*this;

        return *itRet;
    }

    template <typename T>
    inline List<T>::ReverseIterator::ReverseIterator()
        : Iterator()
    {

    }

    template <typename T>
    inline List<T>::ReverseIterator::ReverseIterator(const Iterator &that)
        : Iterator(that)
    {

    }

    template <typename T>
    inline List<T>::ReverseIterator::ReverseIterator(Node *pCurrent)
        : Iterator(pCurrent)
    {

    }

    template <typename T>
    inline List<T>::ReverseIterator::ReverseIterator(Node *pCurrent, Node *pHead)
        : Iterator(pCurrent, pHead)
    {

    }

    template <typename T>
    inline typename List<T>::ReverseIterator &List<T>::ReverseIterator::operator ++ ()
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

    template <typename T>
    inline typename List<T>::ReverseIterator List<T>::ReverseIterator::operator ++ (int)
    {
        typename List<T>::ReverseIterator itRet = *this;

        ++*this;

        return *itRet;
    }

    template <typename T>
    inline typename List<T>::ReverseIterator &List<T>::ReverseIterator::operator -- ()
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

    template <typename T>
    inline typename List<T>::ReverseIterator List<T>::ReverseIterator::operator -- (int)
    {
        typename List<T>::ReverseIterator itRet = *this;

        ++*this;

        return *itRet;
    }

    template <typename T>
    inline typename List<T>::Iterator List<T>::Begin() const
    {
        return typename List<T>::Iterator(m_pHead, m_pHead);
    }

    template <typename T>
    inline typename List<T>::Iterator List<T>::End() const
    {
        return typename List<T>::Iterator(nullptr, m_pHead);
    }

    template <typename T>
    inline typename List<T>::ReverseIterator List<T>::ReverseBegin() const
    {
        return typename List<T>::ReverseIterator(m_pHead == nullptr ? nullptr : m_pHead->pPrev, m_pHead);
    }

    template <typename T>
    inline typename List<T>::ReverseIterator List<T>::ReverseEnd() const
    {
        return typename List<T>::ReverseIterator(nullptr, m_pHead);
    }


    template <typename T>
    void List<T>::Insert(const typename List<T>::Iterator &itBeforeWhich, const T &tValue)
    {
        typename List<T>::Node *pNode = new typename List<T>::Node(tValue);
        typename List<T>::Node *pBefore = itBeforeWhich.m_pCurrent;

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

    template <typename T>
    void List<T>::Insert(const typename List<T>::ReverseIterator &itBeforeWhich, const T &tValue)
    {
        typename List<T>::Node *pNode = new typename List<T>::Node(tValue);
        typename List<T>::Node *pBefore = itBeforeWhich.m_pCurrent;

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


    template <typename T>
    template <typename I>
    void List<T>::Insert(const Iterator &itBeforeWhich, const I &itFirstToInsert, const I &itAfterLastToInsert)
    {
        for (I it = itFirstToInsert; it != itAfterLastToInsert; ++it)
        {
            Insert(itBeforeWhich, *it);
        }
    }

    template <typename T>
    template <typename I>
    void List<T>::Insert(const ReverseIterator &itBeforeWhich, const I &itFirstToInsert, const I &itAfterLastToInsert)
    {
        for (I it = itFirstToInsert; it != itAfterLastToInsert; ++it)
        {
            Insert(itBeforeWhich, *it);
        }
    }

    template <typename T>
    typename List<T>::Iterator List<T>::Delete(const typename List<T>::Iterator &itWhich)
    {
        typename List<T>::Node *pNode = itWhich.m_pCurrent;

        if (pNode == nullptr)
        {
            return typename List<T>::Iterator(nullptr, m_pHead);
        }

        if (pNode == m_pHead)
        {
            m_pHead = pNode->pNext;

            if (m_pHead == pNode)
            {
                m_pHead = nullptr;
            }
        }

        typename List<T>::Iterator itRet(pNode->pNext != pNode ? pNode->pNext : nullptr, m_pHead);

        pNode->pPrev->pNext = pNode->pNext;
        pNode->pNext->pPrev = pNode->pPrev;

        delete pNode;
        --m_nSize;

        return itRet;
    }

    template <typename T>
    typename List<T>::ReverseIterator List<T>::Delete(const ReverseIterator &itWhich)
    {
        typename List<T>::Node *pNode = itWhich.m_pCurrent;

        if (pNode == nullptr)
        {
            return typename List<T>::Iterator(nullptr, m_pHead);
        }

        if (pNode == m_pHead)
        {
            m_pHead = pNode->pNext;

            if (m_pHead == pNode)
            {
                m_pHead = nullptr;
            }
        }

        typename List<T>::ReverseIterator itRet(pNode->pPrev != pNode ? pNode->pPrev : nullptr, m_pHead);

        pNode->pPrev->pNext = pNode->pNext;
        pNode->pNext->pPrev = pNode->pPrev;

        delete pNode;
        --m_nSize;

        return itRet;
    }

    template <typename T>
    typename List<T>::Iterator List<T>::Delete(const Iterator &itFirstToInsert, const Iterator &itAfterLastToDelete)
    {
        typename List<T>::Iterator it = itFirstToInsert;

        while (it != itAfterLastToDelete)
        {
            it = Delete(it);
        }

        return it;
    }

    template <typename T>
    typename List<T>::ReverseIterator List<T>::Delete(const ReverseIterator &itFirstToInsert, const ReverseIterator &itAfterLastToDelete)
    {
        typename List<T>::ReverseIterator it = itFirstToInsert;

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
