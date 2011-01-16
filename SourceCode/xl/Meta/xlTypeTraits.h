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
#include <xl/Meta/xlMetaBase.h>
#include <xl/Meta/xlTypeList.h>

namespace xl
{
    template <bool expr, typename TypeIfTrue, typename TypeIfFalse>
    struct StaticSelect;

    template <typename TypeIfTrue, typename TypeIfFalse>
    struct StaticSelect<true, TypeIfTrue, TypeIfFalse>
    {
        typedef TypeIfTrue Type;
    };

    template <typename TypeIfTrue, typename TypeIfFalse>
    struct StaticSelect<false, TypeIfTrue, TypeIfFalse>
    {
        typedef TypeIfFalse Type;
    };

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
    struct RefTraits<T &>
    {
        enum { IsRef = true };
        typedef T  RefToType;
        typedef T &RefType;
    };

    template <typename T>
    struct RValueRefTraits
    {
        enum { IsRValueRef = false };
        typedef NullType RRefToType;
        typedef T       &RRefType;
    };

    template <typename T>
    struct RValueRefTraits<T &&>
    {
        enum { IsRValueRef = true };
        typedef T   RRefToType;
        typedef T &&RRefType;
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

    template <typename T>
    struct MemPtrTraits
    {
        enum { IsMemPtr = false };
        typedef NullType ClassType;
        typedef NullType PtrToType;
    };

    template <typename T, typename C>
    struct MemPtrTraits<T C::*>
    {
        enum { IsMemPtr = false };
        typedef C ClassType;
        typedef T PtrToType;
    };

    template <typename T>
    class StdTypeDetect
    {
    private:
        typedef typename MakeTypeList<void>::Type StdVoidTypes;
        typedef typename MakeTypeList<bool>::Type StdBoolTypes;

        typedef typename MakeTypeList<char,
                                      short,
                                      int,
                                      long,
                                      long long
                                     >::Type StdSIntTypes;

        typedef typename MakeTypeList<unsigned char,
                                      unsigned short,
                                      unsigned int,
                                      unsigned long,
                                      unsigned long long
                                     >::Type StdUIntTypes;

        typedef typename MakeTypeList<float,
                                      double,
                                      long double
                                     >::Type StdFloatTypes;

        typedef typename MakeTypeList<char,
                                      wchar_t
                                     >::Type StdCharTypes;

    public:
        enum { IsVoid  = (TLIndexOf<StdVoidTypes,  T>::Value >= 0) };
        enum { IsBool  = (TLIndexOf<StdBoolTypes,  T>::Value >= 0) };
        enum { IsSInt  = (TLIndexOf<StdSIntTypes,  T>::Value >= 0) };
        enum { IsUInt  = (TLIndexOf<StdUIntTypes,  T>::Value >= 0) };
        enum { IsFloat = (TLIndexOf<StdFloatTypes, T>::Value >= 0) };
        enum { IsChar  = (TLIndexOf<StdCharTypes,  T>::Value >= 0) };

        enum { IsInt     = (IsBool || IsSInt || IsUInt || IsChar) };
        enum { IsStdType = (IsVoid || IsInt || IsFloat) };

    public:
        typedef typename StaticSelect<IsStdType,
                                      T,
                                      typename RefTraits<T>::RefType>::Type
                         ParamType;
    };

    
} // namespace xl

#endif // #ifndef __XLTYPETRAITS_H_F84DEF1B_BC39_41ED_A130_A31D78520A8A_INCLUDED__
