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


#include <xl/xlDef.h>
#include <xl/Containers/xlRBTree.h>

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
        RBTree<T> m_tData;

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
        Iterator FindMaxBelowGiven(const T &tValue, bool bIncludeEqual = true);
        Iterator FindMinAboveGiven(const T &tValue, bool bIncludeEqual = true);
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

        this->m_tData = that.m_tData;

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

        for (typename RBTree<T>::Iterator itThis = this->m_tData.Begin(), itThat = that.m_tData.Begin();
            itThis != this->m_tData.End() && itThat != that.m_tData.End();
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
        return !(*this == that);
    }

    template <typename T>
    inline typename Set<T>::Iterator Set<T>::Begin() const
    {
        return m_tData.Begin();
    }

    template <typename T>
    inline bool Set<T>::Empty() const
    {
        return m_tData.Empty();
    }

    template <typename T>
    inline size_t Set<T>::Size() const
    {
        return m_tData.Size();
    }

    template <typename T>
    inline void Set<T>::Clear()
    {
        m_tData.Clear();
    }

    template <typename T>
    inline typename Set<T>::Iterator Set<T>::End() const
    {
        return m_tData.End();
    }

    template <typename T>
    inline typename Set<T>::ReverseIterator Set<T>::ReverseBegin() const
    {
        return m_tData.ReverseBegin();
    }

    template <typename T>
    inline typename Set<T>::ReverseIterator Set<T>::ReverseEnd() const
    {
        return m_tData.ReverseEnd();
    }

    template <typename T>
    inline typename Set<T>::Iterator Set<T>::Find(const T &tValue)
    {
        return m_tData.Find(tValue);
    }

    template <typename T>
    inline typename Set<T>::Iterator Set<T>::FindMaxBelowGiven(const T &tValue, bool bIncludeEqual /*= true*/)
    {
        return m_tData.FindMaxBelowGiven(tValue, bIncludeEqual);
    }

    template <typename T>
    inline typename Set<T>::Iterator Set<T>::FindMinAboveGiven(const T &tValue, bool bIncludeEqual /*= true*/)
    {
        return m_tData.FindMinAboveGiven(tValue, bIncludeEqual);
    }


    template <typename T>
    inline typename Set<T>::Iterator Set<T>::Insert(const T &tValue)
    {
        return m_tData.Insert(tValue);
    }

    template <typename T>
    template <typename I>
    inline void Set<T>::Insert(const I &itFirstToInsert, const I &itAfterLastToInsert)
    {
        m_tData.Insert(itFirstToInsert, itAfterLastToInsert);
    }

    template <typename T>
    inline typename Set<T>::Iterator Set<T>::Delete(const Iterator &itWhich)
    {
        return m_tData.Delete(itWhich);
    }

    template <typename T>
    inline typename Set<T>::ReverseIterator Set<T>::Delete(const ReverseIterator &itWhich)
    {
        return m_tData.Delete(itWhich);
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
//             $e.m_tData.m_nSize,
//             "](",
//             #tree(
//                 head: $e.m_tData.m_pRoot,
//                 left: pLeft,
//                 right: pRight,
//                 size: $e.m_tData.m_nSize
//             ) : $e.tValue,
//             ")"
//         )
//     )
//     children (
//         #(
//             #tree(
//                 head: $e.m_tData.m_pRoot,
//                 left: pLeft,
//                 right: pRight,
//                 size: $e.m_tData.m_nSize
//             ) : $e.tValue
//         )
//     )
// }
//

#endif // #ifndef __XLSET_H_11EAD852_068B_4809_B06D_F0FDF1E34E48_INCLUDED__
