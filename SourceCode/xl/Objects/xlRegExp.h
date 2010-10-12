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


#include <xl/Objects/xlString.h>

namespace xl
{
    template <typename T>
    class RegExpT
    {

    };

    typedef RegExpT<char> RegExpA;
    typedef RegExpT<wchar_t> RegExp;


} // namespace xl

#endif // #ifndef __XLREGEXP_H_D261C180_AEB3_495C_A81B_B0B2AA509797_INCLUDED__
