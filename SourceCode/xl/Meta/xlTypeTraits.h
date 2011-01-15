//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlTypeTraits.h
//    Author:      Streamlet
//    Create Time: 2011-01-15
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLTYPETRAITS_H_F84DEF1B_BC39_41ED_A130_A31D78520A8A_INCLUDED__
#define __XLTYPETRAITS_H_F84DEF1B_BC39_41ED_A130_A31D78520A8A_INCLUDED__


#include <xl/xlDef.h>

namespace xl
{
    template <typename T>
    struct ConstTraits
    {
        enum { IsConst = false };
        typedef const T ConstType;
        typedef T       NonConstType;
    };

    template <typename T>
    struct ConstTraits<const T>
    {
        enum { IsConst = true };
        typedef const T ConstType;
        typedef T       NonConstType;
    };

    template <typename T>
    struct RefTraits
    {
        enum { IsRef = false };
        typedef NullType RefToType;
        typedef T       &RefType;
    };

    template <typename T>
    struct RefTraits <T &>
    {
        enum { IsRef = true };
        typedef T        RefToType;
        typedef NullType RefType;
    };

    template <typename T>
    struct RValueRefTraits
    {
        enum { IsRValueRef = false };
        typedef NullType RRefToType;
        typedef T       &RRefType;
    };

    template <typename T>
    struct RValueRefTraits <T &&>
    {
        enum { IsRValueRef = true };
        typedef T        RRefToType;
        typedef NullType RRefType;
    };

    template <typename T>
    struct PtrTraits
    {
        enum { IsPtr = false };
        typedef NullType PtrToType;
        typedef T       *PtrType;
    };

    template <typename T>
    struct PtrTraits<T *>
    {
        enum { IsPtr = true };
        typedef T  PtrToType;
        typedef T *PtrType;
    };

} // namespace xl

#endif // #ifndef __XLTYPETRAITS_H_F84DEF1B_BC39_41ED_A130_A31D78520A8A_INCLUDED__
