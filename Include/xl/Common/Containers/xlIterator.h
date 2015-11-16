//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIterator.h
//    Author:      Streamlet
//    Create Time: 2015-11-12
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLITERATOR_H_786C7A8A_FB5F_4A51_9A22_5F999DE71B8C_INCLUDED__
#define __XLITERATOR_H_786C7A8A_FB5F_4A51_9A22_5F999DE71B8C_INCLUDED__


#include "../Meta/xlEnableIf.h"
#include "xlLinkedListNode.h"

namespace xl
{
    template <typename T, bool R>
    class BufferIteratorT
    {
    public:
        inline BufferIteratorT(T *pData = nullptr)
            : m_pData(pData)
        {

        }

        inline BufferIteratorT(const BufferIteratorT &that)
            : m_pData(that.m_pData)
        {

        }

    public:
        inline BufferIteratorT &operator = (const BufferIteratorT &that)
        {
            if (this == &that)
            {
                return *this;
            }

            this->m_pData = that.m_pData;

            return *this;
        }

    protected:
        T *m_pData;

    public:
        inline T &operator * () const
        {
            return *m_pData;
        }

        inline T *operator -> () const
        {
            return m_pData;
        }

        inline operator T * () const
        {
            return m_pData;
        }

        inline operator const T * () const
        {
            return m_pData;
        }

    public:
        inline bool operator == (const BufferIteratorT &that) const
        {
            return (this->m_pData == that.m_pData);
        }

        inline bool operator != (const BufferIteratorT &that) const
        {
            return (this->m_pData != that.m_pData);
        }

    public:
        template <bool RR = R>
        inline typename EnableIf<RR == R && !R, BufferIteratorT<T, R> &>::Type operator ++ ()
        {
            ++m_pData;
            return *this;
        }
        template <bool RR = R>
        inline typename EnableIf<RR == R && R, BufferIteratorT<T, R> &>::Type operator ++ ()
        {
            --m_pData;
            return *this;
        }

        inline BufferIteratorT operator ++ (int)
        {
            auto itRet = *this;
            ++*this;
            return itRet;
        }

        template <bool RR = R>
        inline typename EnableIf<RR == R && !R, BufferIteratorT<T, R> &>::Type operator -- ()
        {
            --m_pData;
            return *this;
        }
        template <bool RR = R>
        inline typename EnableIf<RR == R && R, BufferIteratorT<T, R> &>::Type operator -- ()
        {
            ++m_pData;
            return *this;
        }

        inline BufferIteratorT operator -- (int)
        {
            auto itRet = *this;
            --*this;
            return itRet;
        }

    public:
        template <bool RR = R>
        inline typename EnableIf<RR == R && !R, BufferIteratorT<T, R> &>::Type operator += (int nDistance)
        {
            m_pData += nDistance;
            return *this;
        }
        template <bool RR = R>
        inline typename EnableIf<RR == R && R, BufferIteratorT<T, R> &>::Type operator += (int nDistance)
        {
            m_pData -= nDistance;
            return *this;
        }

        template <bool RR = R>
        inline typename EnableIf<RR == R && !R, BufferIteratorT<T, R> &>::Type operator -= (int nDistance)
        {
            m_pData -= nDistance;
            return *this;
        }
        template <bool RR = R>
        inline typename EnableIf<RR == R && R, BufferIteratorT<T, R> &>::Type operator -= (int nDistance)
        {
            m_pData += nDistance;
            return *this;
        }

        inline BufferIteratorT operator + (int nDistance) const
        {
            auto itRet = *this;
            return itRet += nDistance;
        }

        inline BufferIteratorT operator - (int nDistance) const
        {
            auto itRet = *this;
            return itRet -= nDistance;
        }

        inline int operator - (const BufferIteratorT &that) const
        {
            return this->m_pData - that.m_pData;
        }
    };


    template <typename T, typename NodeType, bool R>
    class LinkedListIteratorT
    {
    public:
        LinkedListIteratorT(NodeType *pNode = nullptr)
            : m_pNode(pNode)
        {

        }

        LinkedListIteratorT(const LinkedListIteratorT &that)
            : m_pNode(nullptr), m_pHead(nullptr)
        {
            *this = that;
        }

        LinkedListIteratorT &operator = (const LinkedListIteratorT &that)
        {
            if (this == &that)
            {
                return *this;
            }

            this->m_pNode = that.m_pNode;

            return *this;
        }

    protected:
        NodeType *m_pNode;

    public:
        T &operator * () const
        {
            return m_pNode->tValue;
        }

        T *operator -> () const
        {
            return &m_pNode->tValue;
        }

        operator T * () const
        {
            return m_pNode->tValue;
        }

        operator const T * () const
        {
            return m_pNode->tValue;
        }

        operator NodeType * () const
        {
            return m_pNode;
        }

        operator const NodeType * () const
        {
            return m_pNode;
        }

    public:
        bool operator == (const LinkedListIteratorT &that) const
        {
            return (this->m_pNode == that.m_pNode);
        }

        bool operator != (const LinkedListIteratorT &that) const
        {
            return (this->m_pNode != that.m_pNode);
        }

    public:
        template <bool RR = R>
        inline typename EnableIf<RR == R && !R, LinkedListIteratorT<T, NodeType, R> &>::Type operator ++ ()
        {
            m_pNode = m_pNode->pNext;
            return *this;
        }
        template <bool RR = R>
        inline typename EnableIf<RR == R && R, LinkedListIteratorT<T, NodeType, R> &>::Type operator ++ ()
        {
            m_pNode = m_pNode->pPrev;
            return *this;
        }

        LinkedListIteratorT operator ++ (int)
        {
            auto itRet = *this;
            ++*this;
            return itRet;
        }

        template <bool RR = R>
        inline typename EnableIf<RR == R && !R, LinkedListIteratorT<T, NodeType, R> &>::Type operator -- ()
        {
            m_pNode = m_pNode->pPrev;
            return *this;
        }
        template <bool RR = R>
        inline typename EnableIf<RR == R && R, LinkedListIteratorT<T, NodeType, R> &>::Type operator -- ()
        {
            m_pNode = m_pNode->pNext;
            return *this;
        }

        LinkedListIteratorT operator -- (int)
        {
            auto itRet = *this;
            --*this;
            return itRet;
        }
    };

    template <typename T>
    using BufferIterator = BufferIteratorT<T, false>;

    template <typename T>
    using ReverseBufferIterator = BufferIteratorT<T, true>;


    template <typename T, typename NodeType>
    using LinkedListIterator = LinkedListIteratorT<T, NodeType, false>;

    template <typename T, typename NodeType>
    using ReverseLinkedListIterator = LinkedListIteratorT<T, NodeType, true>;

} // namespace xl

#endif // #ifndef __XLITERATOR_H_786C7A8A_FB5F_4A51_9A22_5F999DE71B8C_INCLUDED__
