//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlRegExp.h
//    Author:      Streamlet
//    Create Time: 2010-10-12
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLREGEXP_H_D261C180_AEB3_495C_A81B_B0B2AA509797_INCLUDED__
#define __XLREGEXP_H_D261C180_AEB3_495C_A81B_B0B2AA509797_INCLUDED__


#include <xl/xlDef.h>
#include <xl/String/xlString.h>

namespace xl
{
    template <typename T>
    class RegExpT
    {
    public:
        RegExpT();
        ~RegExpT();

    public:
        bool Parse(StringT<T> strPattern);

    public:
        bool Test(StringT<T> strText);
        StringT<T> Replace(StringT<T> strText, StringT<T> strFormat);
    };

    typedef RegExpT<char> RegExpA;
    typedef RegExpT<wchar_t> RegExp;

    template <typename T>
    RegExpT<T>::RegExpT()
    {

    }

    template <typename T>
    RegExpT<T>::~RegExpT()
    {

    }

    template <typename T>
    bool RegExpT<T>::Parse(StringT<T> strPattern)
    {
        return true;
    }

    template <typename T>
    bool RegExpT<T>::Test(StringT<T> strText)
    {
        return true;
    }

    template <typename T>
    StringT<T> RegExpT<T>::Replace(StringT<T> strText, StringT<T> strFormat)
    {
        return StringT<T>();
    }


} // namespace xl

#endif // #ifndef __XLREGEXP_H_D261C180_AEB3_495C_A81B_B0B2AA509797_INCLUDED__
