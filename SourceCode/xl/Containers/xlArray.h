//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlArray.h
//    Author:      Streamlet
//    Create Time: 2009-03-27
//    Description: Dynamic Array
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLARRAY_H_3B18D7E2_B52A_4D57_BE4B_657F9D17320D_INCLUDED__
#define __XLARRAY_H_3B18D7E2_B52A_4D57_BE4B_657F9D17320D_INCLUDED__


#include <xl/xlDef.h>

namespace xl
{
    template <typename T>
    class Array
    {
    public:
        Array(size_t nSize = 0);
        Array(size_t nSize, const T &tValue);
        Array(const Array<T> &that);
        ~Array();

    public:
        Array<T> &operator = (const Array<T> &that);
        bool operator == (const Array<T> &that) const;
        bool operator != (const Array<T> &that) const;

    public:
        T &operator[](size_t nIndex);
        const T &operator[](size_t nIndex) const;

    public:
        bool Empty() const;
        size_t Size() const;
        void Resize(size_t nSize);
        void Resize(size_t nSize, const T &tValue);

    public:
        void InsertBuffer(size_t nIndex, const T *pStart, int nCount);
        void Insert(size_t nIndex, const T &tValue, int nCount);
        void Insert(size_t nIndex, const T &tValue);
        void PushFront(const T &tValue);
        void PushBack(const T &tValue);
        void Delete(size_t nIndex, int nCount);
        void Delete(size_t nIndex);
        void PopFront();
        void PopBack();
        void Clear();

    protected:
        T *m_pData;
        size_t m_nSize;
        size_t m_nStart;
        size_t m_nEof;

    protected:
        void Release();
        size_t GetWellSize(size_t nSize) const;
        void MoveData(T *pMem, size_t nCount, int nDistance);
        void CopyData(const T *pMem, size_t nCount, T *pNewMem);

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

    template <typename T>
    inline Array<T>::Array(size_t nSize /*= 0*/)
        : m_pData(nullptr), m_nSize(0), m_nStart(0), m_nEof(0)
    {
        Resize(nSize);
    }

    template <typename T>
    inline Array<T>::Array(size_t nSize, const T &tValue)
        : m_pData(nullptr), m_nSize(0), m_nStart(0), m_nEof(0)
    {
        Resize(nSize);

        for (size_t i = m_nStart; i != m_nEof; ++i)
        {
            m_pData[i] = tValue;
        }
    }

    template <typename T>
    inline Array<T>::Array(const Array<T> &that)
        : m_pData(nullptr), m_nSize(0), m_nStart(0), m_nEof(0)
    {
        *this = that;
    }

    template <typename T>
    inline Array<T>::~Array()
    {
        Release();
    }

    template <typename T>
    Array<T> &Array<T>::operator = (const Array<T> &that)
    {
        if (this == &that)
        {
            return *this;
        }

        Release();

        size_t nSize = that.m_nEof - that.m_nStart;
        this->m_nSize = GetWellSize(nSize);
        this->m_nStart = (this->m_nSize - nSize) / 2;
        this->m_nEof = this->m_nStart + nSize;
        this->m_pData = new T[this->m_nSize];

        CopyData(that.m_pData + that.m_nStart, that.m_nEof - that.m_nStart, this->m_pData + this->m_nStart);

        return *this;
    }

    template <typename T>
    bool Array<T>::operator == (const Array<T> &that) const
    {
        if (this == &that)
        {
            return true;
        }

        if (this->m_nEof - this->m_nStart != that.m_nEof - that.m_nStart)
        {
            return false;
        }

        for (size_t i = 0; i < this->m_nEof - this->m_nStart; ++i)
        {
            if (this->m_pData[this->m_nStart + i] != that.m_pData[that.m_nStart + i])
            {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    inline bool Array<T>::operator != (const Array<T> &that) const
    {
        return !(*this == that);
    }

    template <typename T>
    inline T &Array<T>::operator [] (size_t nIndex)
    {
        return m_pData[m_nStart + nIndex];
    }

    template <typename T>
    inline const T &Array<T>::operator [] (size_t nIndex) const
    {
        return m_pData[m_nStart + nIndex];
    }

    template <typename T>
    inline bool Array<T>::Empty() const
    {
        return m_nStart == m_nEof;
    }

    template <typename T>
    inline size_t Array<T>::Size() const
    {
        return m_nEof - m_nStart;
    }

    template <typename T>
    void Array<T>:: Resize(size_t nSize)
    {
        // Free spaces at the back is enough
        if (m_nSize - m_nStart >= nSize)
        {
            m_nEof = m_nStart + nSize;

            return;
        }

        // Not enough spaces at the back
        size_t nWellSize = GetWellSize(nSize);

        if (nWellSize <= m_nSize)
        {
            // New space size is not larger than current space size
            // It implies there a lot of spaces wasted at the front
            // Recalculate the start offset and move the elements

            size_t nNewStart = (m_nSize - nSize) / 2;

            m_nStart = nNewStart;
            m_nEof = m_nStart + nSize;
        }
        else
        {
            // Current space is not large enough, reallocate and move elements

            T *pNewData = new T[nWellSize];
            size_t nNewStart = (nWellSize - nSize) / 2;

            Release();

            m_nStart = nNewStart;
            m_nEof = m_nStart + nSize;
            m_nSize = nWellSize;
            m_pData = pNewData;
        }
    }

    template <typename T>
    void Array<T>:: Resize(size_t nSize, const T &tValue)
    {
        Resize(nSize);

        for (size_t i = m_nStart; i != m_nEof; ++i)
        {
            m_pData[i] = tValue;
        }
    }

    template <typename T>
    void Array<T>::InsertBuffer(size_t nIndex, const T *pStart, int nCount)
    {
        if (nIndex < 0 || nIndex > m_nEof - m_nStart)
        {
            return;
        }

        if (nCount <= 0)
        {
            return;
        }

        if (m_nStart >= (size_t)nCount && nIndex <= m_nSize - (m_nStart + nIndex))
        {
            // In this case:
            // There are enough spaces at the front,
            // and (the position to insert is near the front, or there is not enough space at the back)

            MoveData(m_pData + m_nStart, nIndex, -nCount);
            CopyData(pStart, nCount, m_pData + m_nStart - nCount + nIndex);

            m_nStart -= nCount;

            return;
        }
        // Else:
        // There is not enough space at the front,
        // or (the position to insert is near the back, and there are enough spaces at the back)
        else if (m_nSize - m_nEof >= (size_t)nCount && nIndex > m_nSize - (m_nStart + nIndex))
        {
            // There are enough spaces at the back

            MoveData(m_pData + m_nStart + nIndex, m_nEof - m_nStart - nIndex, nCount);
            CopyData(pStart, nCount, m_pData + m_nStart + nIndex);

            m_nEof += nCount;

            return;
        }

        // Now the case is:
        // There is not enough space at the front or enough space at the back to hold the new elements itself
        // But the total of the spaces might hold them

        size_t nNewSize = m_nEof - m_nStart + nCount;
        size_t nWellSize = m_nSize != 0 ? m_nSize : nNewSize;

        while (nWellSize < nNewSize)
        {
            nWellSize *= 3;
        }
        
        // Not enough spaces, reallocate.

        T *pNewData = new T[nWellSize];
        size_t nNewStart = (nWellSize - nNewSize) / 2;

        CopyData(m_pData + m_nStart, nIndex, pNewData + nNewStart);
        CopyData(pStart, nCount, pNewData + nNewStart + nIndex);
        CopyData(m_pData + m_nStart + nIndex, m_nEof - m_nStart - nIndex, pNewData + nNewStart + nIndex + nCount);

        Release();

        m_nStart = nNewStart;
        m_nEof = nNewStart + nNewSize;
        m_nSize = nWellSize;
        m_pData = pNewData;
    }

    template <typename T>
    void Array<T>::Insert(size_t nIndex, const T &tValue, int nCount)
    {
        if (nIndex < 0 || nIndex > m_nEof - m_nStart)
        {
            return;
        }

        if (nCount <= 0)
        {
            return;
        }

        if (m_nStart >= (size_t)nCount && nIndex <= m_nSize - (m_nStart + nIndex))
        {
            // In this case:
            // There are enough spaces at the front,
            // and (the position to insert is near the front, or there is not enough space at the back)

            MoveData(m_pData + m_nStart, nIndex, -nCount);

            for (int i = 0; i < nCount; ++i)
            {
                m_pData[m_nStart - nCount + nIndex + i] = tValue;
            }

            m_nStart -= nCount;

            return;
        }
        // Else:
        // There is not enough space at the front,
        // or (the position to insert is near the back, and there are enough spaces at the back)
        else if (m_nSize - m_nEof >= (size_t)nCount && nIndex > m_nSize - (m_nStart + nIndex))
        {
            // There are enough spaces at the back

            MoveData(m_pData + m_nStart + nIndex, m_nEof - m_nStart - nIndex, nCount);

            for (int i = 0; i < nCount; ++i)
            {
                m_pData[m_nStart + nIndex + i] = tValue;
            }

            m_nEof += nCount;

            return;
        }

        // Now the case is:
        // There is not enough space at the front or enough space at the back to hold the new elements itself
        // But the total of the spaces might hold them

        size_t nNewSize = m_nEof - m_nStart + nCount;
        size_t nWellSize = m_nSize != 0 ? m_nSize : nNewSize;

        while (nWellSize < nNewSize)
        {
            nWellSize *= 3;
        }

        // Not enough spaces, reallocate.

        T *pNewData = new T[nWellSize];
        size_t nNewStart = (nWellSize - nNewSize) / 2;

        CopyData(m_pData + m_nStart, nIndex, pNewData + nNewStart);

        for (int i = 0; i < nCount; ++i)
        {
            pNewData[nNewStart + nIndex + i] = tValue;
        }

        CopyData(m_pData + m_nStart + nIndex, m_nEof - m_nStart - nIndex, pNewData + nNewStart + nIndex + nCount);

        Release();

        m_nStart = nNewStart;
        m_nEof = nNewStart + nNewSize;
        m_nSize = nWellSize;
        m_pData = pNewData;
    }

    template <typename T>
    inline void Array<T>::Insert(size_t nIndex, const T &tValue)
    {
        Insert(nIndex, tValue, 1);
    }

    template <typename T>
    inline void Array<T>::PushFront(const T &tValue)
    {
        Insert(0, tValue);
    }

    template <typename T>
    inline void Array<T>::PushBack(const T &tValue)
    {
        Insert(m_nEof - m_nStart, tValue);
    }

    template <typename T>
    void Array<T>::Delete(size_t nIndex, int nCount)
    {
        if (nCount <= 0)
        {
            return;
        }

        if (m_nStart + nIndex <= m_nSize - (m_nStart + nIndex))
        {
            // The element to be deleted is near the front

            MoveData(m_pData + m_nStart, nIndex, nCount);
            m_nStart += nCount;
        }
        else
        {
            // It is near the back

            MoveData(m_pData + m_nStart + nIndex + nCount, m_nEof - m_nStart - nIndex, -nCount);
            m_nEof -= nCount;
        }
    }

    template <typename T>
    inline void Array<T>::Delete(size_t nIndex)
    {
        Delete(nIndex, 1);
    }

    template <typename T>
    inline void Array<T>::PopFront()
    {
        Delete(0);
    }

    template <typename T>
    inline void Array<T>::PopBack()
    {
        Delete(m_nEof - m_nStart - 1);
    }

    template <typename T>
    inline void Array<T>::Clear()
    {
        Release();
    }

    template <typename T>
    void Array<T>::Release()
    {
        if (m_pData != nullptr)
        {
            delete[] m_pData;
            m_pData = nullptr;
        }

        m_nSize = 0;
        m_nStart = 0;
        m_nEof = 0;
    }

    template <typename T>
    size_t Array<T>::GetWellSize(size_t nSize) const
    {
        const size_t BITS_IN_A_BYTE = 8;

        nSize -= 1;

        for (size_t i = 1; i < sizeof(size_t) * BITS_IN_A_BYTE; i <<= 1)
        {
            nSize |= nSize >> i;
        }

        return ++nSize;
    }

    template <typename T>
    inline void Array<T>::MoveData(T *pMem, size_t nCount, int nDistance)
    {
         if (nDistance == 0)
         {
             return;
         }
         else if (nDistance > 0)
         {
             for (int i = (int)nCount - 1 + nDistance; i > - 1 + nDistance; --i)
             {
                 pMem[i] = pMem[i - nDistance];
             }
         }
         else if(nDistance < 0)
         {
             for (int i = nDistance; i < (int)nCount + nDistance; ++i)
             {
                 pMem[i] = pMem[i - nDistance];
             }
         }
    }

    template <typename T>
    inline void Array<T>::CopyData(const T *pMem, size_t nCount, T *pNewMem)
    {
         if (pNewMem >= pMem && pNewMem < pMem + m_nSize)
         {
             MoveData(const_cast<T *>(pMem), nCount, (int)(pNewMem - pMem));
         }
         else
         {
             for (size_t i = 0; i < nCount; ++i)
             {
                 *pNewMem++ = pMem[i];
             }
         }
    }

    // Iterator

    template <typename T>
    inline Array<T>::Iterator::Iterator()
        : m_pStart(nullptr), m_pEof(nullptr), m_pCurrent(nullptr)
    {

    }

    template <typename T>
    inline Array<T>::Iterator::Iterator(T *pValue)
        : m_pStart(nullptr), m_pEof(nullptr), m_pCurrent(pValue)
    {

    }

    template <typename T>
    inline Array<T>::Iterator::Iterator(T *pValue, T *pStart, T *pEof)
        : m_pStart(pStart), m_pEof(pEof), m_pCurrent(pValue)
    {

    }

    template <typename T>
    inline Array<T>::Iterator::Iterator(const Iterator &that)
        : m_pStart(nullptr), m_pEof(nullptr), m_pCurrent(nullptr)
    {
        *this = that;
    }

    template <typename T>
    inline T &Array<T>::Iterator::operator * ()
    {
        return *m_pCurrent;
    }

    template <typename T>
    inline T *Array<T>::Iterator::operator -> ()
    {
        return m_pCurrent;
    }

    template <typename T>
    inline Array<T>::Iterator::operator T * ()
    {
        return m_pCurrent;
    }

    template <typename T>
    inline Array<T>::Iterator::operator const T * () const
    {
        return m_pCurrent;
    }

    template <typename T>
    inline typename Array<T>::Iterator &Array<T>::Iterator::operator = (const typename Array<T>::Iterator &that)
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

    template <typename T>
    inline bool Array<T>::Iterator::operator == (const typename Array<T>::Iterator &that) const
    {
        return (this->m_pCurrent == that.m_pCurrent);
    }

    template <typename T>
    inline bool Array<T>::Iterator::operator != (const typename Array<T>::Iterator &that) const
    {
        return !(*this == that);
    }

    template <typename T>
    inline typename Array<T>::Iterator &Array<T>::Iterator::operator ++ ()
    {
        if (m_pCurrent != m_pEof)
        {
            ++m_pCurrent;
        }

        return *this;
    }

    template <typename T>
    inline typename Array<T>::Iterator Array<T>::Iterator::operator ++ (int)
    {
        typename Array<T>::Iterator itRet = *this;

        ++*this;

        return itRet;
    }

    template <typename T>
    inline typename Array<T>::Iterator &Array<T>::Iterator::operator -- ()
    {
        if (m_pCurrent != m_pStart)
        {
            --m_pCurrent;
        }

        return *this;
    }

    template <typename T>
    inline typename Array<T>::Iterator Array<T>::Iterator::operator -- (int)
    {
        typename Array<T>::Iterator itRet = *this;

        --*this;

        return itRet;
    }

    template <typename T>
    inline typename Array<T>::Iterator Array<T>::Iterator::operator + (int nDistance) const
    {
        typename Array<T>::Iterator itRet = *this;

        itRet += nDistance;

        return itRet;
    }

    template <typename T>
    inline typename Array<T>::Iterator Array<T>::Iterator::operator - (int nDistance) const
    {
        typename Array<T>::Iterator itRet = *this;

        itRet -= nDistance;

        return itRet;
    }

    template <typename T>
    inline typename Array<T>::Iterator &Array<T>::Iterator::operator += (int nDistance)
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

    template <typename T>
    inline typename Array<T>::Iterator &Array<T>::Iterator::operator -= (int nDistance)
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

    template <typename T>
    inline int Array<T>::Iterator::operator -(const typename Array<T>::Iterator &that)
    {
        return this->m_pCurrent - that.m_pCurrent;
    }

    template <typename T>
    inline Array<T>::ReverseIterator::ReverseIterator()
        : Iterator()
    {

    }

    template <typename T>
    inline Array<T>::ReverseIterator::ReverseIterator(T *pValue)
        : Iterator(pValue)
    {

    }

    template <typename T>
    inline Array<T>::ReverseIterator::ReverseIterator(T *pValue, T *pStart, T *pEof)
        : Iterator(pValue, pStart, pEof)
    {

    }

    template <typename T>
    inline Array<T>::ReverseIterator::ReverseIterator(const typename Array<T>::ReverseIterator &that)
        : Iterator()
    {
        *this = that;
    }

    template <typename T>
    inline typename Array<T>::ReverseIterator &Array<T>::ReverseIterator::operator ++ ()
    {
        if (this->m_pCurrent != this->m_pEof)
        {
            --this->m_pCurrent;
        }

        return *this;
    }

    template <typename T>
    inline typename Array<T>::ReverseIterator Array<T>::ReverseIterator::operator ++ (int)
    {
        typename Array<T>::ReverseIterator itRet = *this;

        ++*this;

        return itRet;
    }

    template <typename T>
    inline typename Array<T>::ReverseIterator &Array<T>::ReverseIterator::operator -- ()
    {
        if (this->m_pCurrent != this->m_pStart)
        {
            ++this->m_pCurrent;
        }

        return *this;
    }

    template <typename T>
    inline typename Array<T>::ReverseIterator Array<T>::ReverseIterator::operator -- (int)
    {
        typename Array<T>::ReverseIterator itRet = *this;

        --*this;

        return itRet;
    }

    template <typename T>
    inline typename Array<T>::ReverseIterator Array<T>::ReverseIterator::operator + (int nDistance) const
    {
        typename Array<T>::ReverseIterator itRet = *this;

        itRet += nDistance;

        return itRet;
    }

    template <typename T>
    inline typename Array<T>::ReverseIterator Array<T>::ReverseIterator::operator - (int nDistance) const
    {
        typename Array<T>::ReverseIterator itRet = *this;

        itRet -= nDistance;

        return itRet;
    }

    template <typename T>
    inline typename Array<T>::ReverseIterator &Array<T>::ReverseIterator::operator += (int nDistance)
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

    template <typename T>
    inline typename Array<T>::ReverseIterator &Array<T>::ReverseIterator::operator -= (int nDistance)
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

    template <typename T>
    inline int Array<T>::ReverseIterator::operator -(const typename Array<T>::ReverseIterator &that)
    {
        return that.m_pCurrent - this->m_pCurrent;
    }

    template <typename T>
    inline typename Array<T>::Iterator Array<T>::Begin() const
    {
        return typename Array<T>::Iterator(m_pData + m_nStart, m_pData + m_nStart, m_pData + m_nEof);
    }

    template <typename T>
    inline typename Array<T>::Iterator Array<T>::End() const
    {
        return typename Array<T>::Iterator(m_pData + m_nEof, m_pData + m_nStart, m_pData + m_nEof);
    }

    template <typename T>
    inline typename Array<T>::ReverseIterator Array<T>::ReverseBegin() const
    {
        return typename Array<T>::ReverseIterator(m_pData + m_nEof - 1, m_pData + m_nEof - 1, m_pData + m_nStart - 1);
    }

    template <typename T>
    inline typename Array<T>::ReverseIterator Array<T>::ReverseEnd() const
    {
        return typename Array<T>::ReverseIterator(m_pData + m_nStart - 1, m_pData + m_nEof - 1, m_pData + m_nStart - 1);
    }

    template <typename T>
    inline void Array<T>::Insert(const typename Array<T>::Iterator &itBeforeWhich, const T &tValue)
    {
        size_t nIndex = itBeforeWhich.m_pCurrent - (m_pData + m_nStart);

        Insert(nIndex, tValue);
    }

    template <typename T>
    inline void Array<T>::Insert(const typename Array<T>::ReverseIterator &itBeforeWhich, const T &tValue)
    {
        size_t nIndex = itBeforeWhich.m_pCurrent - (m_pData + m_nStart);

        Insert(++nIndex, tValue);
    }

    template <typename T>
    inline void Array<T>::Insert(const Iterator &itBeforeWhich,
        const Iterator &itFirstToInsert, const Iterator &itAfterLastToInsert)
    {
        size_t nIndex = itBeforeWhich.m_pCurrent - (m_pData + m_nStart);

        InsertBuffer(nIndex, itFirstToInsert.m_pCurrent, (int)(itAfterLastToInsert - itFirstToInsert));
    }

    template <typename T>
    inline typename Array<T>::Iterator Array<T>::Delete(const typename Array<T>::Iterator &itWhich)
    {
        size_t nIndex = itWhich.m_pCurrent - (m_pData + m_nStart);

        Delete(nIndex);

        return typename Array<T>::Iterator(m_pData + m_nStart + nIndex, m_pData + m_nStart, m_pData + m_nEof);
    }

    template <typename T>
    inline typename Array<T>::ReverseIterator Array<T>::Delete(const typename Array<T>::ReverseIterator &itWhich)
    {
        size_t nIndex = itWhich.m_pCurrent - (m_pData + m_nStart) + 1;

        Delete(nIndex);

        return typename Array<T>::ReverseIterator(m_pData + m_nStart + nIndex - 1, m_pData + m_nStart, m_pData + m_nEof);

    }

    template <typename T>
    inline typename Array<T>::Iterator Array<T>::Delete(
        const typename Array<T>::Iterator &itFirstToInsert,
        const typename Array<T>::Iterator &itAfterLastToDelete)
    {
        size_t nStart = itFirstToInsert.m_pCurrent - (m_pData + m_nStart);
        size_t nEof = itAfterLastToDelete.m_pCurrent - (m_pData + m_nStart);

        Delete(nStart, nEof - nStart);

        return typename Array<T>::Iterator(m_pData + m_nStart + nStart, m_pData + m_nStart, m_pData + m_nEof);
    }

    template <typename T>
    inline typename Array<T>::Iterator Array<T>::Delete(
        const typename Array<T>::ReverseIterator &itFirstToInsert,
        const typename Array<T>::ReverseIterator &itAfterLastToDelete)
    {
        size_t nEof = itFirstToInsert.m_pCurrent - (m_pData + m_nStart) + 1;
        size_t nStart = itAfterLastToDelete.m_pCurrent - (m_pData + m_nStart) + 1;

        Delete(nStart, nEof - nStart);

        return typename Array<T>::Iterator(m_pData + m_nStart + nStart, m_pData + m_nStart, m_pData + m_nEof);
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
//             $e.m_nEof - $e.m_nStart,
//             "](",
//             #array(
//                 expr: $e.m_pData[$e.m_nStart + $i],
//                 size: $e.m_nEof - $e.m_nStart
//             ),
//             ")"
//         )
//     )
//     children (
//         #(
//             #array(
//                 expr: $e.m_pData[$e.m_nStart + $i],
//                 size: $e.m_nEof - $e.m_nStart
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
