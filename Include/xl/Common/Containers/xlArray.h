//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlArray.h
//    Author:      Streamlet
//    Create Time: 2009-03-27
//    Description: Dynamic Array
//
//------------------------------------------------------------------------------

#ifndef __XLARRAY_H_3B18D7E2_B52A_4D57_BE4B_657F9D17320D_INCLUDED__
#define __XLARRAY_H_3B18D7E2_B52A_4D57_BE4B_657F9D17320D_INCLUDED__


#include "../Memory/xlMemory.h"

namespace xl
{
    enum ArrayAlignmentPolicy
    {
        ArrayAlignmentPolicy_Head,
        ArrayAlignmentPolicy_Center,
        ArrayAlignmentPolicy_Tail
    };

    template <typename T, ArrayAlignmentPolicy P = ArrayAlignmentPolicy_Head>
    class Array
    {
    public:
        Array(size_t nSize = 0)
            : m_pBuffer(nullptr), m_nMemorySize(0), m_nOffset(0), m_nLogicalSize(0)
        {
            Resize(nSize);
        }

        Array(size_t nSize, const T &tValue)
            : m_pBuffer(nullptr), m_nMemorySize(0), m_nOffset(0), m_nLogicalSize(0)
        {
            Resize(nSize);

            for (size_t i = 0; i < m_nLogicalSize; ++i)
            {
                m_pBuffer[m_nOffset + i] = tValue;
            }
        }

        Array(const Array<T> &that)
            : m_pBuffer(nullptr), m_nMemorySize(0), m_nOffset(0), m_nLogicalSize(0)
        {
            *this = that;
        }

        Array(Array<T> &&that)
            : m_pBuffer(nullptr), m_nMemorySize(0), m_nOffset(0), m_nLogicalSize(0)
        {
            *this = Memory::Move(that);
        }

        ~Array()
        {
            Release();
        }

    public:
        Array<T> &operator = (const Array<T> &that)
        {
            if (this == &that)
            {
                return *this;
            }

            Release();

            this->m_nMemorySize = that.m_nMemorySize;
            this->m_nOffset = that.m_nOffset;
            this->m_nLogicalSize = that.m_nLogicalSize;
            this->m_pBuffer = new T[this->m_nMemorySize];

            Memory::Copy(this->m_pBuffer + this->m_nOffset, that.m_pBuffer + that.m_nOffset, m_nLogicalSize);

            return *this;
        }

        Array<T> &operator = (Array<T> &&that)
        {
            if (this == &that)
            {
                return *this;
            }

            Memory::Copy(this, &that, 1);
            Memory::Zero(that);

            return *this;
        }

        bool operator == (const Array<T> &that) const
        {
            if (this == &that)
            {
                return true;
            }

            if (this->m_nLogicalSize != that.m_nLogicalSize)
            {
                return false;
            }

            for (size_t i = 0; i < this->m_nLogicalSize; ++i)
            {
                if (!(this->m_pBuffer[this->m_nOffset + i] == that.m_pBuffer[that.m_nOffset + i]))
                {
                    return false;
                }
            }

            return true;
        }

        bool operator != (const Array<T> &that) const
        {
            if (this == &that)
            {
                return false;
            }

            if (this->m_nLogicalSize != that.m_nLogicalSize)
            {
                return true;
            }

            for (size_t i = 0; i < this->m_nLogicalSize; ++i)
            {
                if (this->m_pBuffer[this->m_nOffset + i] != that.m_pBuffer[that.m_nOffset + i])
                {
                    return true;
                }
            }

            return false;
        }

    public:
        inline T &operator[](size_t nIndex)
        {
            return m_pBuffer[m_nOffset + nIndex];
        }

        inline const T &operator[](size_t nIndex) const
        {
            return m_pBuffer[m_nOffset + nIndex];
        }

    public:
        bool Empty() const
        {
            return m_nLogicalSize == 0;
        }

        size_t Size() const
        {
            return m_nLogicalSize;
        }

    public:
        void Reserve(size_t nSize)
        {
            if (nSize < m_nLogicalSize)
            {
                return;
            }

            size_t nIncreaseSize = m_nLogicalSize - nSize;

            if (P == ArrayAlignmentPolicy_Tail)
            {
                PrepareInsert(0, nIncreaseSize);
                m_nOffset += nIncreaseSize;
                m_nLogicalSize -= nIncreaseSize;
            }
            else
            {
                PrepareInsert(m_nLogicalSize, nIncreaseSize);
                m_nLogicalSize -= nIncreaseSize;
            }
        }

        void Resize(size_t nSize)
        {
            if (nSize < m_nLogicalSize)
            {
                m_nLogicalSize = nSize;
                return;
            }

            size_t nIncreaseSize = nSize - m_nLogicalSize;

            if (P == ArrayAlignmentPolicy_Tail)
            {
                PrepareInsert(0, nIncreaseSize);
                m_nOffset += nIncreaseSize;
            }
            else
            {
                PrepareInsert(m_nLogicalSize, nIncreaseSize);
            }
        }

        void Resize(size_t nSize, const T &tValue)
        {
            Resize(nSize);

            for (size_t i = 0; i < m_nLogicalSize; ++i)
            {
                m_pBuffer[m_nOffset + i] = tValue;
            }
        }

    public:
        inline void Insert(size_t nIndex, const T *pBuffer, size_t nCount)
        {
            if (nIndex > m_nLogicalSize)
            {
                return;
            }

            PrepareInsert(nIndex, nCount);
            Memory::Copy(m_pBuffer + m_nOffset + nIndex, pBuffer, nCount);
        }

        void Insert(size_t nIndex, const T &tValue, size_t nCount)
        {
            if (nIndex > m_nLogicalSize)
            {
                return;
            }

            PrepareInsert(nIndex, nCount);

            for (size_t i = 0; i < nCount; ++i)
            {
                m_pBuffer[m_nOffset + nIndex + i] = tValue;
            }
        }

        inline void Insert(size_t nIndex, const T &tValue)
        {
            Insert(nIndex, tValue, 1);
        }

        inline void PushFront(const T &tValue)
        {
            Insert(0, tValue);
        }

        inline void PushBack(const T &tValue)
        {
            Insert(m_nLogicalSize, tValue);
        }

        void Delete(size_t nIndex, size_t nCount)
        {
            if (nIndex + nIndex > m_nLogicalSize)
            {
                return;
            }

            size_t nMoveCountHead = nIndex;
            size_t nMoveCountTail = m_nLogicalSize - nIndex;

            if (P == ArrayAlignmentPolicy_Tail || P == ArrayAlignmentPolicy_Center && nMoveCountHead < nMoveCountTail)
            {
                Memory::Copy(m_pBuffer + m_nOffset + nCount, m_pBuffer + m_nOffset, nIndex);
                m_nOffset += nCount;
                m_nLogicalSize -= nCount;
            }
            else
            {
                Memory::Copy(m_pBuffer + m_nOffset + nIndex, m_pBuffer + m_nOffset + nIndex + nCount, m_nLogicalSize - (nIndex + nCount));
                m_nLogicalSize -= nCount;
            }
        }

        inline void Delete(size_t nIndex)
        {
            Delete(nIndex, 1);
        }

        inline void PopFront()
        {
            Delete(0);
        }

        inline void PopBack()
        {
            Delete(m_nLogicalSize - 1);
        }

        inline void Clear()
        {
            Release();
        }

    private:
        void PrepareInsert(size_t nInsertPos, size_t nInsertSize)
        {
            int nSpaceHead = (int)m_nOffset;
            int nSpaceTail = (int)(m_nMemorySize - (m_nOffset + m_nLogicalSize));
            int nMoveCountHead = (int)nInsertPos;
            int nMoveCountTail = (int)(m_nLogicalSize - nInsertPos);

            if (nMoveCountHead < nMoveCountTail && (int)nInsertSize < nSpaceHead)
            {
                Memory::Copy(m_pBuffer + m_nOffset - nInsertSize, m_pBuffer + m_nOffset, nMoveCountHead);
                m_nOffset -= nMoveCountHead;
                m_nLogicalSize += nInsertSize;
            }
            else if (nMoveCountHead >= nMoveCountTail && (int)nInsertSize < nSpaceTail)
            {
                Memory::Copy(m_pBuffer + m_nOffset + nInsertPos + nInsertSize, m_pBuffer + m_nOffset + nInsertPos, nMoveCountTail);
                m_nLogicalSize += nInsertSize;
            }
            else
            {
                size_t nNewMemorySize = (m_nLogicalSize + nInsertSize) * (P == ArrayAlignmentPolicy_Center ? 3 : 2);
                size_t nNewOffset = (P == ArrayAlignmentPolicy_Head ? 0 : m_nLogicalSize + nInsertSize);

                T *pNewBuffer = new T[nNewMemorySize];

                Memory::Copy(pNewBuffer + nNewOffset, m_pBuffer + m_nOffset, nInsertPos);
                Memory::Copy(pNewBuffer + nNewOffset + nInsertPos + nInsertSize, m_pBuffer + m_nOffset + nInsertPos, m_nLogicalSize - nInsertPos);

                delete[] m_pBuffer;
                m_pBuffer = pNewBuffer;
                m_nMemorySize = nNewMemorySize;
                m_nOffset = nNewOffset;
                m_nLogicalSize += nInsertSize;
            }
        }

        void Release()
        {
            if (m_pBuffer != nullptr)
            {
                delete[] m_pBuffer;
                m_pBuffer = nullptr;
            }

            m_nMemorySize = 0;
            m_nOffset = 0;
            m_nLogicalSize = 0;
        }

    private:
        T *m_pBuffer;
        size_t m_nMemorySize;
        size_t m_nOffset;
        size_t m_nLogicalSize;



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
            Iterator(T *pValue);
            Iterator(T *pValue, T *pStart, T *pEof);
            friend class Array;

        protected:
            T *m_pStart;
            T *m_pEof;
            T *m_pCurrent;

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

        public:
            Iterator operator + (int nDistance) const;
            Iterator operator - (int nDistance) const;
            Iterator &operator += (int nDistance);
            Iterator &operator -= (int nDistance);
            int operator - (const Iterator & that);
        };

        class ReverseIterator : public Iterator
        {
        public:
            ReverseIterator();
            ReverseIterator(const ReverseIterator &that);
            ReverseIterator(T *pValue);

        protected:
            ReverseIterator(T *pValue, T *pStart, T *pEof);
            friend class Array;

        public:
            ReverseIterator &operator ++ ();
            ReverseIterator operator ++ (int);
            ReverseIterator &operator -- ();
            ReverseIterator operator -- (int);

        public:
            ReverseIterator operator + (int nDistance) const;
            ReverseIterator operator - (int nDistance) const;
            ReverseIterator &operator += (int nDistance);
            ReverseIterator &operator -= (int nDistance);
            int operator - (const ReverseIterator & that);
        };

    public:
        Iterator Begin() const;
        Iterator End() const;
        ReverseIterator ReverseBegin() const;
        ReverseIterator ReverseEnd() const;

    public:
        void Insert(const Iterator &itBeforeWhich, const T &tValue);
        void Insert(const ReverseIterator &itBeforeWhich, const T &tValue);
        void Insert(const Iterator &itBeforeWhich, const Iterator &itFirstToInsert, const Iterator &itAfterLastToInsert);
        Iterator Delete(const Iterator &itWhich);
        ReverseIterator Delete(const ReverseIterator &itWhich);
        Iterator Delete(const Iterator &itFirstToInsert, const Iterator &itAfterLastToDelete);
        Iterator Delete(const ReverseIterator &itFirstToInsert, const ReverseIterator &itAfterLastToDelete);
    };

    // Iterator

    template <typename T, ArrayAlignmentPolicy P>
    inline Array<T, P>::Iterator::Iterator()
        : m_pStart(nullptr), m_pEof(nullptr), m_pCurrent(nullptr)
    {

    }

    template <typename T, ArrayAlignmentPolicy P>
    inline Array<T, P>::Iterator::Iterator(T *pValue)
        : m_pStart(nullptr), m_pEof(nullptr), m_pCurrent(pValue)
    {

    }

    template <typename T, ArrayAlignmentPolicy P>
    inline Array<T, P>::Iterator::Iterator(T *pValue, T *pStart, T *pEof)
        : m_pStart(pStart), m_pEof(pEof), m_pCurrent(pValue)
    {

    }

    template <typename T, ArrayAlignmentPolicy P>
    inline Array<T, P>::Iterator::Iterator(const Iterator &that)
        : m_pStart(nullptr), m_pEof(nullptr), m_pCurrent(nullptr)
    {
        *this = that;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline T &Array<T, P>::Iterator::operator * ()
    {
        return *m_pCurrent;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline T *Array<T, P>::Iterator::operator -> ()
    {
        return m_pCurrent;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline Array<T, P>::Iterator::operator T * ()
    {
        return m_pCurrent;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline Array<T, P>::Iterator::operator const T * () const
    {
        return m_pCurrent;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::Iterator &Array<T, P>::Iterator::operator = (const typename Array<T, P>::Iterator &that)
    {
        if (this == & that)
        {
            return *this;
        }

        this->m_pStart = that.m_pStart;
        this->m_pEof = that.m_pEof;
        this->m_pCurrent = that.m_pCurrent;

        return *this;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline bool Array<T, P>::Iterator::operator == (const typename Array<T, P>::Iterator &that) const
    {
        return (this->m_pCurrent == that.m_pCurrent);
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline bool Array<T, P>::Iterator::operator != (const typename Array<T, P>::Iterator &that) const
    {
        return (this->m_pCurrent != that.m_pCurrent);
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::Iterator &Array<T, P>::Iterator::operator ++ ()
    {
        if (m_pCurrent != m_pEof)
        {
            ++m_pCurrent;
        }

        return *this;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::Iterator Array<T, P>::Iterator::operator ++ (int)
    {
        typename Array<T, P>::Iterator itRet = *this;

        ++*this;

        return itRet;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::Iterator &Array<T, P>::Iterator::operator -- ()
    {
        if (m_pCurrent != m_pStart)
        {
            --m_pCurrent;
        }

        return *this;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::Iterator Array<T, P>::Iterator::operator -- (int)
    {
        typename Array<T, P>::Iterator itRet = *this;

        --*this;

        return itRet;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::Iterator Array<T, P>::Iterator::operator + (int nDistance) const
    {
        typename Array<T, P>::Iterator itRet = *this;

        itRet += nDistance;

        return itRet;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::Iterator Array<T, P>::Iterator::operator - (int nDistance) const
    {
        typename Array<T, P>::Iterator itRet = *this;

        itRet -= nDistance;

        return itRet;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::Iterator &Array<T, P>::Iterator::operator += (int nDistance)
    {
        m_pCurrent += nDistance;

        if (nDistance > 0 && m_pCurrent > m_pEof)
        {
            m_pCurrent = m_pEof;
        }
        else if (nDistance < 0 && m_pCurrent < m_pStart)
        {
            m_pCurrent = m_pStart;
        }

        return *this;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::Iterator &Array<T, P>::Iterator::operator -= (int nDistance)
    {
        m_pCurrent -= nDistance;

        if (nDistance > 0 && m_pCurrent > m_pEof)
        {
            m_pCurrent = m_pEof;
        }
        else if (nDistance < 0 && m_pCurrent < m_pStart)
        {
            m_pCurrent = m_pStart;
        }

        return *this;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline int Array<T, P>::Iterator::operator -(const typename Array<T, P>::Iterator &that)
    {
        return this->m_pCurrent - that.m_pCurrent;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline Array<T, P>::ReverseIterator::ReverseIterator()
        : Iterator()
    {

    }

    template <typename T, ArrayAlignmentPolicy P>
    inline Array<T, P>::ReverseIterator::ReverseIterator(T *pValue)
        : Iterator(pValue)
    {

    }

    template <typename T, ArrayAlignmentPolicy P>
    inline Array<T, P>::ReverseIterator::ReverseIterator(T *pValue, T *pStart, T *pEof)
        : Iterator(pValue, pStart, pEof)
    {

    }

    template <typename T, ArrayAlignmentPolicy P>
    inline Array<T, P>::ReverseIterator::ReverseIterator(const typename Array<T, P>::ReverseIterator &that)
        : Iterator()
    {
        *this = that;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::ReverseIterator &Array<T, P>::ReverseIterator::operator ++ ()
    {
        if (this->m_pCurrent != this->m_pEof)
        {
            --this->m_pCurrent;
        }

        return *this;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::ReverseIterator Array<T, P>::ReverseIterator::operator ++ (int)
    {
        typename Array<T, P>::ReverseIterator itRet = *this;

        ++*this;

        return itRet;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::ReverseIterator &Array<T, P>::ReverseIterator::operator -- ()
    {
        if (this->m_pCurrent != this->m_pStart)
        {
            ++this->m_pCurrent;
        }

        return *this;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::ReverseIterator Array<T, P>::ReverseIterator::operator -- (int)
    {
        typename Array<T, P>::ReverseIterator itRet = *this;

        --*this;

        return itRet;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::ReverseIterator Array<T, P>::ReverseIterator::operator + (int nDistance) const
    {
        typename Array<T, P>::ReverseIterator itRet = *this;

        itRet += nDistance;

        return itRet;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::ReverseIterator Array<T, P>::ReverseIterator::operator - (int nDistance) const
    {
        typename Array<T, P>::ReverseIterator itRet = *this;

        itRet -= nDistance;

        return itRet;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::ReverseIterator &Array<T, P>::ReverseIterator::operator += (int nDistance)
    {
        this->m_pCurrent -= nDistance;

        if (nDistance > 0 && this->m_pCurrent > this->m_pStart)
        {
            this->m_pCurrent = this->m_pStart;
        }
        else if (nDistance < 0 && this->m_pCurrent < this->m_pEof)
        {
            this->m_pCurrent = this->m_pEof;
        }

        return *this;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::ReverseIterator &Array<T, P>::ReverseIterator::operator -= (int nDistance)
    {
        this->m_pCurrent += nDistance;

        if (nDistance > 0 && this->m_pCurrent > this->m_pStart)
        {
            this->m_pCurrent = this->m_pStart;
        }
        else if (nDistance < 0 && this->m_pCurrent < this->m_pEof)
        {
            this->m_pCurrent = this->m_pEof;
        }

        return *this;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline int Array<T, P>::ReverseIterator::operator -(const typename Array<T, P>::ReverseIterator &that)
    {
        return that.m_pCurrent - this->m_pCurrent;
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::Iterator Array<T, P>::Begin() const
    {
        return typename Array<T, P>::Iterator(m_pBuffer + m_nOffset, m_pBuffer + m_nOffset, m_pBuffer + m_nOffset + m_nLogicalSize);
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::Iterator Array<T, P>::End() const
    {
        return typename Array<T, P>::Iterator(m_pBuffer + m_nOffset + m_nLogicalSize, m_pBuffer + m_nOffset, m_pBuffer + m_nOffset + m_nLogicalSize);
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::ReverseIterator Array<T, P>::ReverseBegin() const
    {
        return typename Array<T, P>::ReverseIterator(m_pBuffer + m_nOffset + m_nLogicalSize - 1, m_pBuffer + m_nOffset + m_nLogicalSize - 1, m_pBuffer + m_nOffset - 1);
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::ReverseIterator Array<T, P>::ReverseEnd() const
    {
        return typename Array<T, P>::ReverseIterator(m_pBuffer + m_nOffset - 1, m_pBuffer + m_nOffset + m_nLogicalSize - 1, m_pBuffer + m_nOffset - 1);
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline void Array<T, P>::Insert(const typename Array<T, P>::Iterator &itBeforeWhich, const T &tValue)
    {
        size_t nIndex = itBeforeWhich.m_pCurrent - (m_pBuffer + m_nOffset);

        Insert(nIndex, tValue);
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline void Array<T, P>::Insert(const typename Array<T, P>::ReverseIterator &itBeforeWhich, const T &tValue)
    {
        size_t nIndex = itBeforeWhich.m_pCurrent - (m_pBuffer + m_nOffset);

        Insert(++nIndex, tValue);
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline void Array<T, P>::Insert(const Iterator &itBeforeWhich,
        const Iterator &itFirstToInsert, const Iterator &itAfterLastToInsert)
    {
        size_t nIndex = itBeforeWhich.m_pCurrent - (m_pBuffer + m_nOffset);

        Insert(nIndex, itFirstToInsert.m_pCurrent, (int)(itAfterLastToInsert - itFirstToInsert));
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::Iterator Array<T, P>::Delete(const typename Array<T, P>::Iterator &itWhich)
    {
        size_t nIndex = itWhich.m_pCurrent - (m_pBuffer + m_nOffset);

        Delete(nIndex);

        return typename Array<T, P>::Iterator(m_pBuffer + m_nOffset + nIndex, m_pBuffer + m_nOffset, m_pBuffer + m_nOffset + m_nLogicalSize);
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::ReverseIterator Array<T, P>::Delete(const typename Array<T, P>::ReverseIterator &itWhich)
    {
        size_t nIndex = itWhich.m_pCurrent - (m_pBuffer + m_nOffset) + 1;

        Delete(nIndex);

        return typename Array<T, P>::ReverseIterator(m_pBuffer + m_nOffset + nIndex - 1, m_pBuffer + m_nOffset, m_pBuffer + m_nOffset + m_nLogicalSize);

    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::Iterator Array<T, P>::Delete(
        const typename Array<T, P>::Iterator &itFirstToInsert,
        const typename Array<T, P>::Iterator &itAfterLastToDelete)
    {
        size_t nStart = itFirstToInsert.m_pCurrent - (m_pBuffer + m_nOffset);
        size_t nEof = itAfterLastToDelete.m_pCurrent - (m_pBuffer + m_nOffset);

        Delete(nStart, nEof - nStart);

        return typename Array<T, P>::Iterator(m_pBuffer + m_nOffset + nStart, m_pBuffer + m_nOffset, m_pBuffer + m_nOffset + m_nLogicalSize);
    }

    template <typename T, ArrayAlignmentPolicy P>
    inline typename Array<T, P>::Iterator Array<T, P>::Delete(
        const typename Array<T, P>::ReverseIterator &itFirstToInsert,
        const typename Array<T, P>::ReverseIterator &itAfterLastToDelete)
    {
        size_t nEof = itFirstToInsert.m_pCurrent - (m_pBuffer + m_nOffset) + 1;
        size_t nStart = itAfterLastToDelete.m_pCurrent - (m_pBuffer + m_nOffset) + 1;

        Delete(nStart, nEof - nStart);

        return typename Array<T, P>::Iterator(m_pBuffer + m_nOffset + nStart, m_pBuffer + m_nOffset, m_pBuffer + m_nOffset + m_nLogicalSize);
    }

} // namespace xl

//
// For convenience of debugging, put the following code to the [AutoExpand] section of
//     X:\Program Files\Microsoft Visual Studio 10.0\Common7\Packages\Debugger\autoexp.dat
//
// ;------------------------------------------------------------------------------
// ;  xl::Array
// ;------------------------------------------------------------------------------
// xl::Array<*>{
//     preview (
//         #(
//             "[",
//             $e.m_nEnd - $e.m_nOffset,
//             "](",
//             #array(
//                 expr: $e.m_pBuffer[$e.m_nOffset + $i],
//                 size: $e.m_nEnd - $e.m_nOffset
//             ),
//             ")"
//         )
//     )
//     children (
//         #(
//             #array(
//                 expr: $e.m_pBuffer[$e.m_nOffset + $i],
//                 size: $e.m_nEnd - $e.m_nOffset
//             )
//         )
//     )
// }
// xl::Array<*>::Iterator|xl::Array<*>::ReverseIterator{
//     preview (
//         *$e.m_pCurrent
//     )
//     children (
//         #([ptr] : $e.m_pCurrent)
//     )
// }
// 

#endif // #ifndef __XLARRAY_H_3B18D7E2_B52A_4D57_BE4B_657F9D17320D_INCLUDED__
