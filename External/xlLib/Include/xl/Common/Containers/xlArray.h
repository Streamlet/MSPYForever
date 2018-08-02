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


#include "../../xlDef.h"
#include "../Memory/xlMemory.h"
#include "xlIterator.h"

namespace xl
{
    enum ArrayAlignmentPolicy
    {
        ArrayAlignmentPolicy_Head,
        ArrayAlignmentPolicy_Center,
        ArrayAlignmentPolicy_Tail
    };

    template <typename T, ArrayAlignmentPolicy P = ArrayAlignmentPolicy_Center>
    class ArrayT
    {
    public:
        inline ArrayT(size_t nSize = 0)
            : m_pBuffer(nullptr), m_nMemorySize(0), m_nOffset(0), m_nLogicalSize(0)
        {
            Resize(nSize);
        }

        inline ArrayT(size_t nSize, const T &tValue)
            : m_pBuffer(nullptr), m_nMemorySize(0), m_nOffset(0), m_nLogicalSize(0)
        {
            Resize(nSize);

            for (size_t i = 0; i < m_nLogicalSize; ++i)
            {
                m_pBuffer[m_nOffset + i] = tValue;
            }
        }

        inline ArrayT(const ArrayT &that)
            : m_pBuffer(nullptr), m_nMemorySize(0), m_nOffset(0), m_nLogicalSize(0)
        {
            *this = that;
        }

#ifdef __XL_CPP11

        inline ArrayT(ArrayT &&that)
            : m_pBuffer(nullptr), m_nMemorySize(0), m_nOffset(0), m_nLogicalSize(0)
        {
            *this = Memory::Move(that);
        }

        inline ~ArrayT()
        {
            Release();
        }

#endif

    public:
        inline ArrayT &operator = (const ArrayT &that)
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

            Memory::CopyT(this->m_pBuffer + this->m_nOffset, that.m_pBuffer + that.m_nOffset, m_nLogicalSize);

            return *this;
        }

#ifdef __XL_CPP11

        inline ArrayT &operator = (ArrayT &&that)
        {
            if (this == &that)
            {
                return *this;
            }

            Memory::CopyT(this, &that, 1);
            Memory::Zero(that);

            return *this;
        }

#endif

        inline bool operator == (const ArrayT &that) const
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

        inline bool operator != (const ArrayT &that) const
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
        inline bool Empty() const
        {
            return m_nLogicalSize == 0;
        }

        inline size_t Size() const
        {
            return m_nLogicalSize;
        }

    public:
        inline void Reserve(size_t nSize)
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

        inline void Resize(size_t nSize)
        {
            if (nSize == 0)
            {
                Release();
                return;
            }

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

        inline void Resize(size_t nSize, const T &tValue)
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
            Memory::CopyT(m_pBuffer + m_nOffset + nIndex, pBuffer, nCount);
        }

        inline void Insert(size_t nIndex, const T &tValue, size_t nCount)
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

        inline void Delete(size_t nIndex, size_t nCount)
        {
            if (nIndex + nCount > m_nLogicalSize)
            {
                return;
            }

            size_t nMoveCountHead = nIndex;
            size_t nMoveCountTail = m_nLogicalSize - nIndex;

            if (P == ArrayAlignmentPolicy_Tail || P == ArrayAlignmentPolicy_Center && nMoveCountHead < nMoveCountTail)
            {
                Memory::CopyT(m_pBuffer + m_nOffset + nCount, m_pBuffer + m_nOffset, nIndex);
                m_nOffset += nCount;
                m_nLogicalSize -= nCount;
            }
            else
            {
                Memory::CopyT(m_pBuffer + m_nOffset + nIndex, m_pBuffer + m_nOffset + nIndex + nCount, m_nLogicalSize - (nIndex + nCount));
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
        inline void PrepareInsert(size_t nInsertPos, size_t nInsertSize)
        {
            int nSpaceHead = (int)m_nOffset;
            int nSpaceTail = (int)(m_nMemorySize - (m_nOffset + m_nLogicalSize));
            int nMoveCountHead = (int)nInsertPos;
            int nMoveCountTail = (int)(m_nLogicalSize - nInsertPos);

            if (nMoveCountHead >= nMoveCountTail && (int)nInsertSize < nSpaceTail)
            {
                if (nMoveCountTail > 0)
                {
                    Memory::CopyT(m_pBuffer + m_nOffset + nInsertPos + nInsertSize, m_pBuffer + m_nOffset + nInsertPos, nMoveCountTail);
                }

                m_nLogicalSize += nInsertSize;
            }
            else if (nMoveCountHead < nMoveCountTail && (int)nInsertSize < nSpaceHead)
            {
                if (nMoveCountHead > 0)
                {
                    Memory::CopyT(m_pBuffer + m_nOffset - nInsertSize, m_pBuffer + m_nOffset, nMoveCountHead);
                }

                m_nOffset -= nInsertSize + nMoveCountHead;
                m_nLogicalSize += nInsertSize;
            }
            else
            {
                size_t nNewMemorySize = (m_nLogicalSize + nInsertSize) * (P == ArrayAlignmentPolicy_Center ? 3 : 2);
                size_t nNewOffset = (P == ArrayAlignmentPolicy_Head ? 0 : m_nLogicalSize + nInsertSize);

                T *pNewBuffer = new T[nNewMemorySize];

                if (m_pBuffer != nullptr)
                {
                    if (nInsertPos > 0)
                    {
                        Memory::CopyT(pNewBuffer + nNewOffset, m_pBuffer + m_nOffset, nInsertPos);
                    }

                    if (nInsertPos < m_nLogicalSize)
                    {
                        Memory::CopyT(pNewBuffer + nNewOffset + nInsertPos + nInsertSize, m_pBuffer + m_nOffset + nInsertPos, m_nLogicalSize - nInsertPos);
                    }

                    delete[] m_pBuffer;
                }

                m_pBuffer = pNewBuffer;
                m_nMemorySize = nNewMemorySize;
                m_nOffset = nNewOffset;
                m_nLogicalSize += nInsertSize;
            }
        }

        inline void Release()
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

    public:
#ifdef __XL_CPP11
        typedef BufferIterator<T> Iterator;
        typedef ReverseBufferIterator<T> ReverseIterator;
#else
        typedef BufferIteratorT<T, false> Iterator;
        typedef BufferIteratorT<T, true> ReverseIterator;
#endif

    public:
        inline Iterator Begin() const
        {
            return Iterator(m_pBuffer + m_nOffset);
        }

        inline Iterator End() const
        {
            return Iterator(m_pBuffer + m_nOffset + m_nLogicalSize);
        }

        inline ReverseIterator ReverseBegin() const
        {
            return ReverseIterator(m_pBuffer + m_nOffset + m_nLogicalSize - 1);
        }

        inline ReverseIterator ReverseEnd() const
        {
            return ReverseIterator(m_pBuffer + m_nOffset - 1);
        }

    public:
        inline void Insert(const Iterator &itWhere, const T &tValue)
        {
            size_t nIndex = (T *)itWhere - (m_pBuffer + m_nOffset);
            Insert(nIndex, tValue);
        }

        inline void Insert(const ReverseIterator &itWhere, const T &tValue)
        {
            size_t nIndex = (T *)itWhere - (m_pBuffer + m_nOffset);
            Insert(++nIndex, tValue);
        }

        inline void Insert(const Iterator &itWhere, const Iterator &itBegin, const Iterator &itEnd)
        {
            size_t nIndex = (size_t)((T *)itWhere - (m_pBuffer + m_nOffset));
            Insert(nIndex, (T *)itBegin, (size_t)(itEnd - itBegin));
        }

        inline Iterator Delete(const Iterator &itWhere)
        {
            size_t nIndex = (T *)itWhere - (m_pBuffer + m_nOffset);
            Delete(nIndex);
            return Iterator(m_pBuffer + m_nOffset + nIndex);
        }

        inline ReverseIterator Delete(const ReverseIterator &itWhere)
        {
            size_t nIndex = (T *)itWhere - (m_pBuffer + m_nOffset);
            Delete(nIndex);
            return ReverseIterator(m_pBuffer + m_nOffset + nIndex - 1);
        }

        inline Iterator Delete(const Iterator &itBegin, const Iterator &itEnd)
        {
            size_t nIndex = (T *)itBegin - (m_pBuffer + m_nOffset);
            Delete(nIndex, itEnd - itBegin);
            return Iterator(m_pBuffer + m_nOffset + nIndex);
        }

        inline ReverseIterator Delete(const ReverseIterator &itBegin, const ReverseIterator &itEnd)
        {
            size_t nIndex = (T *)itBegin - (m_pBuffer + m_nOffset) + 1;
            Delete(nIndex, itEnd - itBegin);
            return ReverseIterator(m_pBuffer + m_nOffset + nIndex - 1);
        }
    };

#ifdef __XL_CPP11

    template <typename T>
    using Array = ArrayT<T, ArrayAlignmentPolicy_Center>;

    template <typename T>
    using Deque = ArrayT<T, ArrayAlignmentPolicy_Center>;

    template <typename T>
    using Vector = ArrayT<T, ArrayAlignmentPolicy_Head>;

    template <typename T>
    using Queue = ArrayT<T, ArrayAlignmentPolicy_Head>;

    template <typename T>
    using Stack = ArrayT<T, ArrayAlignmentPolicy_Tail>;

#else

#define Array ArrayT

#endif

} // namespace xl

#endif // #ifndef __XLARRAY_H_3B18D7E2_B52A_4D57_BE4B_657F9D17320D_INCLUDED__
