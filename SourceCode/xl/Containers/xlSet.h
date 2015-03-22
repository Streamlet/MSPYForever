//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlSet.h
//    Author:      Streamlet
//    Create Time: 2009-11-07
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLSET_H_11EAD852_068B_4809_B06D_F0FDF1E34E48_INCLUDED__
#define __XLSET_H_11EAD852_068B_4809_B06D_F0FDF1E34E48_INCLUDED__


#include "../xlDef.h"
#include "xlRBTree.h"

namespace xl
{
    template <typename T>
    class Set
    {
    public:
        Set();
        Set(const Set<T> &that);
        ~Set();

    public:
        Set<T> &operator = (const Set<T> &that);
        bool operator == (const Set<T> &that);
        bool operator != (const Set<T> &that);

    protected:
        RBTree<T> m_tRBTree;

    public:
        bool Empty() const;
        size_t Size() const;

    public:
        void Clear();

    // Iterator

    public:
        typedef typename RBTree<T>::Iterator Iterator;
        typedef typename RBTree<T>::ReverseIterator ReverseIterator;

    public:
        Iterator Begin() const;
        Iterator End() const;
        ReverseIterator ReverseBegin() const;
        ReverseIterator ReverseEnd() const;

    public:
        Iterator Find(const T &tValue);
        Iterator FindMaxBelow(const T &tValue, bool bIncludeEqual = true);
        Iterator FindMinAbove(const T &tValue, bool bIncludeEqual = true);
        Iterator Insert(const T &tValue);
        template <typename I>
        void Insert(const I &itFirstToInsert, const I &itAfterLastToInsert);
        Iterator Delete(const Iterator &itWhich);
        ReverseIterator Delete(const ReverseIterator &itWhich);
    };

    template <typename T>
    inline Set<T>::Set()
    {

    }

    template <typename T>
    inline Set<T>::Set(const Set<T> &that)
    {
        *this = that;
    }

    template <typename T>
    inline Set<T>::~Set()
    {

    }

    template <typename T>
    inline Set<T> &Set<T>::operator = (const Set<T> &that)
    {
        if (this == &that)
        {
            return *this;
        }

        this->m_tRBTree = that.m_tRBTree;

        return *this;
    }

    template <typename T>
    inline bool Set<T>::operator == (const Set<T> &that)
    {
        if (this == &that)
        {
            return true;
        }

        if (this->Size() != that.Size())
        {
            return false;
        }

        for (typename RBTree<T>::Iterator itThis = this->m_tRBTree.Begin(), itThat = that.m_tRBTree.Begin();
            itThis != this->m_tRBTree.End() && itThat != that.m_tRBTree.End();
            ++itThis, ++itThat)
        {
            if (*itThis != *itThat)
            {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    inline bool Set<T>::operator != (const Set<T> &that)
    {
        if (this == &that)
        {
            return false;
        }

        if (this->Size() != that.Size())
        {
            return true;
        }

        for (typename RBTree<T>::Iterator itThis = this->m_tRBTree.Begin(), itThat = that.m_tRBTree.Begin();
            itThis != this->m_tRBTree.End() && itThat != that.m_tRBTree.End();
            ++itThis, ++itThat)
        {
            if (*itThis != *itThat)
            {
                return true;
            }
        }

        return false;
    }

    template <typename T>
    inline typename Set<T>::Iterator Set<T>::Begin() const
    {
        return m_tRBTree.Begin();
    }

    template <typename T>
    inline bool Set<T>::Empty() const
    {
        return m_tRBTree.Empty();
    }

    template <typename T>
    inline size_t Set<T>::Size() const
    {
        return m_tRBTree.Size();
    }

    template <typename T>
    inline void Set<T>::Clear()
    {
        m_tRBTree.Clear();
    }

    template <typename T>
    inline typename Set<T>::Iterator Set<T>::End() const
    {
        return m_tRBTree.End();
    }

    template <typename T>
    inline typename Set<T>::ReverseIterator Set<T>::ReverseBegin() const
    {
        return m_tRBTree.ReverseBegin();
    }

    template <typename T>
    inline typename Set<T>::ReverseIterator Set<T>::ReverseEnd() const
    {
        return m_tRBTree.ReverseEnd();
    }

    template <typename T>
    inline typename Set<T>::Iterator Set<T>::Find(const T &tValue)
    {
        return m_tRBTree.Find(tValue);
    }

    template <typename T>
    inline typename Set<T>::Iterator Set<T>::FindMaxBelow(const T &tValue, bool bIncludeEqual /*= true*/)
    {
        return m_tRBTree.FindMaxBelow(tValue, bIncludeEqual);
    }

    template <typename T>
    inline typename Set<T>::Iterator Set<T>::FindMinAbove(const T &tValue, bool bIncludeEqual /*= true*/)
    {
        return m_tRBTree.FindMinAbove(tValue, bIncludeEqual);
    }


    template <typename T>
    inline typename Set<T>::Iterator Set<T>::Insert(const T &tValue)
    {
        return m_tRBTree.Insert(tValue);
    }

    template <typename T>
    template <typename I>
    inline void Set<T>::Insert(const I &itFirstToInsert, const I &itAfterLastToInsert)
    {
        m_tRBTree.Insert(itFirstToInsert, itAfterLastToInsert);
    }

    template <typename T>
    inline typename Set<T>::Iterator Set<T>::Delete(const Iterator &itWhich)
    {
        return m_tRBTree.Delete(itWhich);
    }

    template <typename T>
    inline typename Set<T>::ReverseIterator Set<T>::Delete(const ReverseIterator &itWhich)
    {
        return m_tRBTree.Delete(itWhich);
    }

} // namespace xl

//
// For convenience of debugging, put the following code to the [AutoExpand] section of
//     X:\Program Files\Microsoft Visual Studio 10.0\Common7\Packages\Debugger\autoexp.dat
//
// ;------------------------------------------------------------------------------
// ;  xl::Set
// ;------------------------------------------------------------------------------
// xl::Set<*>{
//     preview (
//         #(
//             "[",
//             $e.m_tRBTree.m_nSize,
//             "](",
//             #tree(
//                 head: $e.m_tRBTree.m_tBinTree.m_pRoot,
//                 left: pLeft,
//                 right: pRight,
//                 size: $e.m_tRBTree.m_nSize
//             ) : $e.tValue.tValue,
//             ")"
//         )
//     )
//     children (
//         #(
//             #tree(
//                 head: $e.m_tRBTree.m_tBinTree.m_pRoot,
//                 left: pLeft,
//                 right: pRight,
//                 size: $e.m_tRBTree.m_nSize
//             ) : $e.tValue.tValue
//         )
//     )
// }
//

#endif // #ifndef __XLSET_H_11EAD852_068B_4809_B06D_F0FDF1E34E48_INCLUDED__
