//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlString.h
//    Author:      Streamlet
//    Create Time: 2009-03-27
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLSTRING_H_27999BE8_99C9_4C06_87AB_AA916A88B287_INCLUDED__
#define __XLSTRING_H_27999BE8_99C9_4C06_87AB_AA916A88B287_INCLUDED__


#include "../../xlDef.h"
#include "../Containers/xlArray.h"

namespace xl
{
    template <typename T>
    class StringT
    {
    public:
        StringT();
        StringT(const T *szString);
        StringT(const T *szString, size_t nLength);
        StringT(const StringT<T> &that);
        ~StringT();

    public:
        StringT<T> &operator = (const StringT<T> &that);
        bool operator == (const StringT<T> &that) const;
        bool operator != (const StringT<T> &that) const;
        bool operator <  (const StringT<T> &that) const;
        bool operator >  (const StringT<T> &that) const;
        bool operator <= (const StringT<T> &that) const;
        bool operator >= (const StringT<T> &that) const;
        bool operator == (const T *that) const;
        bool operator != (const T *that) const;
        bool operator <  (const T *that) const;
        bool operator >  (const T *that) const;
        bool operator <= (const T *that) const;
        bool operator >= (const T *that) const;
        StringT<T> operator + (const StringT<T> &that) const;
        StringT<T> &operator += (const StringT<T> &that);
        T &operator [] (int nIndex);
        const T &operator [] (int nIndex) const;

    public:
        operator const T*() const;

    public:
        int Length() const;
        bool Empty() const;

    public:
        StringT<T> &MakeLower();
        StringT<T> &MakeUpper();
        StringT<T> ToLower() const;
        StringT<T> ToUpper() const;

    public:
        StringT<T> &TrimLeft(T ch = T(' '));
        StringT<T> &TrimRight(T ch = T(' '));
        StringT<T> &Trim(T ch = T(' '));

    public:
        StringT<T> &AppendFront(T ch, int nCount = 1);
        StringT<T> &AppendBack(T ch, int nCount = 1);
        void Clear();

    public:
        StringT<T> Left(int nLength) const;
        StringT<T> Right(int nLength) const;
        StringT<T> SubString(int nStart, int nLength = -1) const;

    public:
        int IndexOf(const StringT<T> &strFind, int nStart) const;
        int IndexOf(const StringT<T> &strFind) const;
        int LastIndexOf(const StringT<T> &strFind, int nStart) const;
        int LastIndexOf(const StringT<T> &strFind) const;

    public:
        StringT<T> Replace(const StringT<T> &strFind, const StringT<T> &strReplaceWith, int nCount = 0) const;
        Array<StringT<T>> Split(const StringT<T> &strSeparator, int nCount = 0) const;

    protected:
        Array<T> m_aData;
    };

    typedef char    Char8,  CharA;
    typedef wchar_t Char16, CharW;
    typedef int     Char32;
    typedef CharW   Char;

    typedef StringT<Char8>  StringU8;
    typedef StringT<Char16> StringU16;
    typedef StringT<Char32> StringU32;
    typedef StringT<CharA>  StringA;
    typedef StringT<CharW>  StringW;

#ifdef _UNICODE
    typedef StringW         String;
#else
    typedef StringA         String;
#endif

    template <typename T>
    inline StringT<T>::StringT()
    {
        m_aData.PushBack(T(0));
    }

    template <typename T>
    StringT<T>::StringT(const T *szString)
    {
        if (szString != nullptr)
        {
            while (*szString != T(0))
            {
                m_aData.PushBack(*szString++);
            }
        }

        m_aData.PushBack(T(0));
    }

    template <typename T>
    StringT<T>::StringT(const T *szString, size_t nLength)
    {
        if (szString != nullptr)
        {
            for (size_t i = 0; i < nLength; ++i)
            {
                m_aData.PushBack(szString[i]);
            }
        }

        if (m_aData.Empty() || *m_aData.ReverseBegin() != T(0))
        {
            m_aData.PushBack(T(0));
        }
    }

    template <typename T>
    inline StringT<T>::StringT(const StringT<T> &that)
    {
        *this = that;
    }

    template <typename T>
    inline StringT<T>::~StringT()
    {

    }

    template <typename T>
    inline StringT<T> &StringT<T>::operator = (const StringT<T> &that)
    {
        this->m_aData = that.m_aData;

        return *this;
    }

    template <typename T>
    inline bool StringT<T>::operator == (const StringT<T> &that) const
    {
        return this->m_aData == that.m_aData;
    }

    template <typename T>
    inline bool StringT<T>::operator != (const StringT<T> &that) const
    {
        return !(*this == that);
    }

    template <typename T>
    bool StringT<T>::operator < (const StringT<T> &that) const
    {
        for (size_t i = 0; i < this->m_aData.Size(); ++i)
        {
            if (this->m_aData[i] != that.m_aData[i] || this->m_aData[i] == T(0) || that.m_aData[i] == T(0))
            {
                return this->m_aData[i] < that.m_aData[i];
            }
        }

        return false;
    }

    template <typename T>
    bool StringT<T>::operator > (const StringT<T> &that) const
    {
        for (size_t i = 0; i < this->m_aData.Size(); ++i)
        {
            if (this->m_aData[i] != that.m_aData[i] || this->m_aData[i] == T(0) || that.m_aData[i] == T(0))
            {
                return this->m_aData[i] > that.m_aData[i];
            }
        }

        return false;
    }

    template <typename T>
    inline bool StringT<T>::operator <= (const StringT<T> &that) const
    {
        return !(*this > that);
    }

    template <typename T>
    inline bool StringT<T>::operator >= (const StringT<T> &that) const
    {
        return !(*this < that);
    }

    template <typename T>
    inline bool StringT<T>::operator == (const T *that) const
    {
        return *this == StringT(that);
    }

    template <typename T>
    inline bool StringT<T>::operator != (const T *that) const
    {
        return *this != StringT(that);
    }

    template <typename T>
    inline bool StringT<T>::operator < (const T *that) const
    {
        return *this < StringT(that);
    }
    
    template <typename T>
    inline bool StringT<T>::operator > (const T *that) const
    {
        return *this > StringT(that);
    }

    template <typename T>
    inline bool StringT<T>::operator <= (const T *that) const
    {
        return *this <= StringT(that);
    }

    template <typename T>
    inline bool StringT<T>::operator >= (const T *that) const
    {
        return *this >= StringT(that);
    }
    
    template <typename T>
    inline StringT<T> StringT<T>::operator + (const StringT<T> &that) const
    {
        StringT<T> strRet;

        strRet.m_aData.PopBack();
        strRet.m_aData.Insert(strRet.m_aData.End(), this->m_aData.Begin(), this->m_aData.End());
        strRet.m_aData.PopBack();
        strRet.m_aData.Insert(strRet.m_aData.End(), that.m_aData.Begin(), that.m_aData.End());

        return strRet;
    }

    template <typename T>
    inline StringT<T> &StringT<T>::operator+=(const StringT<T> &that)
    {
        this->m_aData.PopBack();
        this->m_aData.Insert(this->m_aData.End(), that.m_aData.Begin(), that.m_aData.End());

        return *this;
    }

    template <typename T>
    inline T &StringT<T>::operator[](int nIndex)
    {
        return m_aData[nIndex];
    }

    template <typename T>
    inline const T &StringT<T>::operator[](int nIndex) const
    {
        return m_aData[nIndex];
    }

    template <typename T>
    StringT<T>::operator const T*() const
    {
        return &m_aData[0];
    }

    template <typename T>
    inline int StringT<T>::Length() const
    {
        return m_aData.Size() - 1;
    }

    template <typename T>
    inline bool StringT<T>::Empty() const
    {
        return Length() == 0;
    }

    template <typename T>
    StringT<T> &StringT<T>::MakeLower()
    {
        for (size_t i = 0; i < m_aData.Size(); ++i)
        {
            if (m_aData[i] >= T('A') && m_aData[i] <= T('Z'))
            {
                m_aData[i] += 'a' - 'A';
            }
        }

        return *this;
    }

    template <typename T>
    StringT<T> &StringT<T>::MakeUpper()
    {
        for (size_t i = 0; i < m_aData.Size(); ++i)
        {
            if (m_aData[i] >= T('a') && m_aData[i] <= T('z'))
            {
                m_aData[i] -= 'a' - 'A';
            }
        }

        return *this;
    }

    template <typename T>
    StringT<T> StringT<T>::ToLower() const
    {
        StringT<T> strRet;

        strRet.m_aData.Resize(this->m_aData.Size());

        for (size_t i = 0; i < m_aData.Size(); ++i)
        {
            if (this->m_aData[i] >= T('A') && this->m_aData[i] <= T('Z'))
            {
                strRet.m_aData[i] = m_aData[i] + ('a' - 'A');
            }
            else
            {
                strRet.m_aData[i] = m_aData[i];
            }
        }

        return strRet;
    }

    template <typename T>
    StringT<T> StringT<T>::ToUpper() const
    {
        StringT<T> strRet;

        strRet.m_aData.Resize(this->m_aData.Size());

        for (size_t i = 0; i < m_aData.Size(); ++i)
        {
            if (this->m_aData[i] >= T('a') && this->m_aData[i] <= T('z'))
            {
                strRet.m_aData[i] = m_aData[i] - (T('a') - T('A'));
            }
            else
            {
                strRet.m_aData[i] = m_aData[i];
            }
        }

        return strRet;
    }

    template <typename T>
    StringT<T> &StringT<T>::TrimLeft(T ch /*= T(' ')*/)
    {
        while (*m_aData.Begin() == ch)
        {
            m_aData.PopFront();
        }

        return *this;
    }
    
    template <typename T>
    StringT<T> &StringT<T>::TrimRight(T ch /*= T(' ')*/)
    {
        m_aData.PopBack();

        while (!m_aData.Empty() && *m_aData.ReverseBegin() == ch)
        {
            m_aData.PopBack();
        }

        m_aData.PushBack(T(0));

        return *this;
    }
    
    template <typename T>
    StringT<T> &StringT<T>::Trim(T ch /*= T(' ')*/)
    {
        TrimLeft(ch);
        TrimRight(ch);

        return *this;
    }

    template <typename T>
    StringT<T> &StringT<T>::AppendFront(T ch, int nCount /*= 1*/)
    {
        for (int i = 0; i < nCount; ++i)
        {
            m_aData.PushFront(ch);
        }

        return *this;
    }

    template <typename T>
    StringT<T> &StringT<T>::AppendBack(T ch, int nCount /*= 1*/)
    {
        if (nCount <= 0)
        {
            return *this;
        }

        m_aData.PopBack();

        for (int i = 0; i < nCount; ++i)
        {
            m_aData.PushBack(ch);
        }

        m_aData.PushBack(T(0));

        return *this;
    }

    template <typename T>
    void StringT<T>::Clear()
    {
        m_aData.Clear();
        m_aData.PushBack(T(0));
    }

    template <typename T>
    inline StringT<T> StringT<T>::Left(int nLength) const
    {
        return SubString(0, nLength);
    }

    template <typename T>
    inline StringT<T> StringT<T>::Right(int nLength) const
    {
        return SubString((int)m_aData.Size() - 1 - nLength, nLength);
    }

    template <typename T>
    StringT<T> StringT<T>::SubString(int nStart, int nLength /*= -1*/) const
    {
        StringT<T> strRet;
        strRet.m_aData.PopBack();

        if (nLength < 0)
        {
            nLength = (int)m_aData.Size() - 1 - nStart;
        }

        if (nStart + nLength > (int)m_aData.Size())
        {
            nLength = (int)m_aData.Size() - nStart;
        }

        if (nLength > 0)
        {
            strRet.m_aData.Insert(strRet.m_aData.End(), m_aData.Begin() + nStart, m_aData.Begin() + nStart + nLength);
        }

        if (strRet.m_aData.Empty() || strRet.m_aData[strRet.m_aData.Size() - 1] != T(0))
        {
            strRet.m_aData.PushBack(T(0));
        }

        return strRet;
    }

    template <typename T>
    inline int StringT<T>::IndexOf(const StringT<T> &strFind) const
    {
        return IndexOf(strFind, 0);
    }

    template <typename T>
    int StringT<T>::IndexOf(const StringT<T> &strFind, int nStart) const
    {
        if (strFind.Length() == 0)
        {
            return -1;
        }

        int i = nStart;

        while(i <= this->Length() - strFind.Length())
        {
            int j;

            for (j = 0; j < strFind.Length(); ++j)
            {
                if ((*this)[i + j] != strFind[j])
                {
                    if (i == this->Length() - strFind.Length())
                    {
                        return -1;
                    }

                    T ch = (*this)[i + strFind.Length()];

                    ++i;

                    for (int k = strFind.Length() - 1; strFind[k] != ch && k >= 0; --k)
                    {
                        ++i;
                    }

                    break;
                }
            }

            if (j >= strFind.Length())
            {
                return i;
            }
        }

        return -1;
    }

    template <typename T>
    inline int StringT<T>::LastIndexOf(const StringT<T> &strFind) const
    {
        return LastIndexOf(strFind, this->Length() - 1);
    }

    template <typename T>
    int StringT<T>::LastIndexOf(const StringT<T> &strFind, int nStart) const
    {
        if (strFind.Length() == 0)
        {
            return -1;
        }

        int i = nStart + 1 - strFind.Length();

        while(i >= 0)
        {
            int j;

            for (j = strFind.Length() - 1; j >= 0; --j)
            {
                if ((*this)[i + j] != strFind[j])
                {
                    if (i == 0)
                    {
                        return -1;
                    }

                    T ch = (*this)[i - 1];

                    --i;

                    for (int k = 0; strFind[k] != ch && k < strFind.Length(); ++k)
                    {
                        --i;
                    }

                    break;
                }
            }

            if (j < 0)
            {
                return i;
            }

        }

        return -1;
    }

    template <typename T>
    StringT<T> StringT<T>::Replace(const StringT<T> &strFind, const StringT<T> &strReplaceWith, int nCount /*= 0*/) const
    {
        StringT<T> strRet;

        int nFrom = 0;
        int nTo = this->IndexOf(strFind, nFrom);

        int nReplaceCount = 0;

        while (nTo != -1)
        {
            strRet += this->SubString(nFrom, nTo - nFrom);
            strRet += strReplaceWith;
            nFrom = nTo + strFind.Length();
            nTo = this->IndexOf(strFind, nFrom);

            if (nCount != 0 && ++nReplaceCount >= nCount)
            {
                break;
            }
        }

        strRet += this->Right(this->Length() - nFrom);

        return strRet;
    }

    template <typename T>
    Array<StringT<T> > StringT<T>::Split(const StringT<T> &strSeparator, int nCount /*= 0*/) const
    {
        Array<StringT<T> > astrRet;

        int nFrom = 0;
        int nTo = this->IndexOf(strSeparator, nFrom);

        int nSplitCount = 1;

        while (nTo != -1)
        {
            astrRet.PushBack(this->SubString(nFrom, nTo - nFrom));
            nFrom = nTo + strSeparator.Length();
            nTo = this->IndexOf(strSeparator, nFrom);

            if (nCount != 0 && ++nSplitCount >= nCount)
            {
                break;
            }
        }

        astrRet.PushBack(this->Right(this->Length() - nFrom));

        return astrRet;
    }

} // namespace xl

//
// For convenience of debugging, put the following code to the [AutoExpand] section of
//     X:\Program Files\Microsoft Visual Studio 10.0\Common7\Packages\Debugger\autoexp.dat
//
// ;------------------------------------------------------------------------------
// ;  xl::String
// ;------------------------------------------------------------------------------
// xl::StringT<wchar_t>{
//     preview (
//         [&$e.m_aData.m_pData[$e.m_aData.m_nStart],su]
//     )
//     stringview (
//         [&$e.m_aData.m_pData[$e.m_aData.m_nStart],sub]
//     )
//     children (
//         #(
//             #array(
//                 expr: $e.m_aData.m_pData[$e.m_aData.m_nStart + $i],
//                 size: $e.m_aData.m_nEof - $e.m_aData.m_nStart
//             )
//         )
//     )
// }
// xl::StringT<char>{
//     preview (
//         [&$e.m_aData.m_pData[$e.m_aData.m_nStart],s]
//     )
//     stringview (
//         [&$e.m_aData.m_pData[$e.m_aData.m_nStart],sb]
//     )
//     children (
//         #(
//             #array(
//                 expr: $e.m_aData.m_pData[$e.m_aData.m_nStart + $i],
//                 size: $e.m_aData.m_nEof - $e.m_aData.m_nStart
//             )
//         )
//     )
// }
//

#endif // #ifndef __XLSTRING_H_27999BE8_99C9_4C06_87AB_AA916A88B287_INCLUDED__
