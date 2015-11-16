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
        inline BufferIteratorT()
            : m_pBegin(nullptr), m_pEnd(nullptr), m_pCurrent(nullptr)
        {

        }

        inline BufferIteratorT(const BufferIteratorT &that)
            : m_pBegin(that.m_pBegin), m_pEnd(that.m_pEnd), m_pCurrent(that.m_pCurrent)
        {

        }

        inline BufferIteratorT(T *pBegin, T *pEnd, T *pCurrent)
            : m_pBegin(pBegin), m_pEnd(pEnd), m_pCurrent(pCurrent)
        {

        }

    public:
        inline BufferIteratorT &operator = (const BufferIteratorT &that)
        {
            if (this == &that)
            {
                return *this;
            }

            this->m_pBegin = that.m_pBegin;
            this->m_pEnd = that.m_pEnd;
            this->m_pCurrent = that.m_pCurrent;

            return *this;
        }

    protected:
        T *m_pBegin;
        T *m_pEnd;
        T *m_pCurrent;

    public:
        inline T &operator * () const
        {
            return *m_pCurrent;
        }

        inline T *operator -> () const
        {
            return m_pCurrent;
        }

        inline operator T * () const
        {
            return m_pCurrent;
        }

        inline operator const T * () const
        {
            return m_pCurrent;
        }

    public:
        inline bool operator == (const BufferIteratorT &that) const
        {
            return (this->m_pCurrent == that.m_pCurrent);
        }

        inline bool operator != (const BufferIteratorT &that) const
        {
            return (this->m_pCurrent != that.m_pCurrent);
        }

    public:
        template <bool RR = R>
        inline typename EnableIf<RR == R && !R, BufferIteratorT<T, R> &>::Type operator ++ ()
        {
            ++m_pCurrent;
            return *this;
        }
        template <bool RR = R>
        inline typename EnableIf<RR == R && R, BufferIteratorT<T, R> &>::Type operator ++ ()
        {
            --m_pCurrent;
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
            --m_pCurrent;
            return *this;
        }
        template <bool RR = R>
        inline typename EnableIf<RR == R && R, BufferIteratorT<T, R> &>::Type operator -- ()
        {
            ++m_pCurrent;
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
            m_pCurrent += nDistance;
            return *this;
        }
        template <bool RR = R>
        inline typename EnableIf<RR == R && R, BufferIteratorT<T, R> &>::Type operator += (int nDistance)
        {
            m_pCurrent -= nDistance;
            return *this;
        }

        template <bool RR = R>
        inline typename EnableIf<RR == R && !R, BufferIteratorT<T, R> &>::Type operator -= (int nDistance)
        {
            m_pCurrent -= nDistance;
            return *this;
        }
        template <bool RR = R>
        inline typename EnableIf<RR == R && R, BufferIteratorT<T, R> &>::Type operator -= (int nDistance)
        {
            m_pCurrent += nDistance;
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
            return this->m_pCurrent - that.m_pCurrent;
        }
    };

    template <typename T>
    using BufferIterator = BufferIteratorT<T, false>;

    template <typename T>
    using ReverseBufferIterator = BufferIteratorT<T, true>;


    template <typename T, typename NodeType, bool R>
    class LinkedListIteratorT
    {
    public:
        LinkedListIteratorT()
        {

        }
        LinkedListIteratorT(const LinkedListIteratorT &that);

        LinkedListIteratorT(NodeType *pCurrent);
        LinkedListIteratorT(NodeType *pCurrent, NodeType *pHead);

        LinkedListIteratorT &operator = (const LinkedListIteratorT &that);

    protected:
        NodeType *m_pCurrent;
        NodeType *m_pHead;

    public:
        T &operator * ();
        T *operator -> ();
        operator T * ();
        operator const T * () const;

    public:
        bool operator == (const LinkedListIteratorT &that) const;
        bool operator != (const LinkedListIteratorT &that) const;

    public:
        LinkedListIteratorT &operator ++ ();
        LinkedListIteratorT operator ++ (int);
        LinkedListIteratorT &operator -- ();
        LinkedListIteratorT operator -- (int);
    };

} // namespace xl

#endif // #ifndef __XLITERATOR_H_786C7A8A_FB5F_4A51_9A22_5F999DE71B8C_INCLUDED__
