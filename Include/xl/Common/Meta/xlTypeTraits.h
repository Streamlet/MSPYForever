//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlTypeTraits.h
//    Author:      Streamlet
//    Create Time: 2011-01-15
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLTYPETRAITS_H_F84DEF1B_BC39_41ED_A130_A31D78520A8A_INCLUDED__
#define __XLTYPETRAITS_H_F84DEF1B_BC39_41ED_A130_A31D78520A8A_INCLUDED__


#include "../../xlDef.h"
#include "../Meta/xlMetaBase.h"
#include "../Meta/xlTypeList.h"

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

#ifdef __XL_CPP11

    template <size_t Index, typename... T>
    struct TypeAt;

    template <typename T0, typename... T>
    struct TypeAt<0, T0, T...>
    {
        typedef T0 Type;
    };

    template <size_t Index, typename T0, typename... T>
    struct TypeAt<Index, T0, T...>
    {
        typedef typename TypeAt<Index - 1, T...>::Type Type;
    };

#endif

    template <typename T>
    struct ConstTraits
    {
        static const bool IsConst = false;
        typedef const T ConstType;
        typedef T       NonConstType;
    };

    template <typename T>
    struct ConstTraits<const T>
    {
        static const bool IsConst = true;
        typedef const T ConstType;
        typedef T       NonConstType;
    };

    template <typename T>
    struct RefTraits
    {
        static const bool IsRef = false;
        typedef NullType RefToType;
        typedef T       &RefType;
    };

    template <typename T>
    struct RefTraits<T &>
    {
        static const bool IsRef = true;
        typedef T  RefToType;
        typedef T &RefType;
    };

#ifdef __XL_CPP11

    template <typename T>
    struct RValueRefTraits
    {
        static const bool IsRValueRef = false;
        typedef NullType RRefToType;
        typedef T       &RRefType;
    };

    template <typename T>
    struct RValueRefTraits<T &>
    {
        static const bool IsRValueRef = false;
        typedef NullType RRefToType;
        typedef T      &&RRefType;
    };

    template <typename T>
    struct RValueRefTraits<T &&>
    {
        static const bool IsRValueRef = true;
        typedef T   RRefToType;
        typedef T &&RRefType;
    };

#endif

    template <typename T>
    struct RemoveRef
    {
        typedef T Type;
    };

    template <typename T>
    struct RemoveRef<T &>
    {
        typedef T Type;
    };

#ifdef __XL_CPP11

    template <typename T>
    struct RemoveRef<T &&>
    {
        typedef T Type;
    };

#endif

    template <typename T>
    struct PtrTraits
    {
        static const bool IsPtr = false;
        typedef NullType PtrToType;
        typedef T       *PtrType;
    };

    template <typename T>
    struct PtrTraits<T *>
    {
        static const bool IsPtr = true;
        typedef T  PtrToType;
        typedef T *PtrType;
    };

    template <typename T>
    struct PtrTraits<const T *>
    {
        static const bool IsPtr = true;
        typedef const T  PtrToType;
        typedef const T *PtrType;
    };

    template <typename T>
    struct ArrayTraits
    {
        static const bool IsArray = false;
    };

    template <typename T, int N>
    struct ArrayTraits<T[N]>
    {
        static const bool IsArray = true;
        static const size_t Size = N;
    };

    template <int N>
    struct SizeToSignedIntType;

    template <>
    struct SizeToSignedIntType<1>
    {
        typedef char Type;
    };

    template <>
    struct SizeToSignedIntType<2>
    {
        typedef short Type;
    };

    template <>
    struct SizeToSignedIntType<4>
    {
        typedef int Type;
    };

    template <>
    struct SizeToSignedIntType<8>
    {
        typedef long long Type;
    };

    template <int N>
    struct SizeToUnignedIntType;

    template <>
    struct SizeToUnignedIntType<1>
    {
        typedef unsigned char Type;
    };

    template <>
    struct SizeToUnignedIntType<2>
    {
        typedef unsigned short Type;
    };

    template <>
    struct SizeToUnignedIntType<4>
    {
        typedef unsigned int Type;
    };

    template <>
    struct SizeToUnignedIntType<8>
    {
        typedef unsigned long long Type;
    };

    template <typename T>
    struct MemPtrTraits
    {
        static const bool IsMemPtr = false;
        typedef NullType ClassType;
        typedef NullType PtrToType;
    };

    template <typename T, typename C>
    struct MemPtrTraits<T C::*>
    {
        static const bool IsMemPtr = false;
        typedef C ClassType;
        typedef T PtrToType;
    };

    template <typename T, typename U>
    struct SameTypeDetect
    {
        static const bool IsSameType = false;
    };

    template <typename T>
    struct SameTypeDetect<T, T>
    {
        static const bool IsSameType = true;
    };

    template <typename T>
    struct FunctionTraits;

#ifdef __XL_CPP11

    template <typename R, typename ... Args>
    struct FunctionTraits < R(Args ...) >
    {
        typedef R ReturnType;
    };

#endif

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
        static const bool IsVoid  = (TLIndexOf<StdVoidTypes,  T>::Value >= 0);
        static const bool IsBool  = (TLIndexOf<StdBoolTypes,  T>::Value >= 0);
        static const bool IsSInt  = (TLIndexOf<StdSIntTypes,  T>::Value >= 0);
        static const bool IsUInt  = (TLIndexOf<StdUIntTypes,  T>::Value >= 0);
        static const bool IsFloat = (TLIndexOf<StdFloatTypes, T>::Value >= 0);
        static const bool IsChar  = (TLIndexOf<StdCharTypes,  T>::Value >= 0);

        static const bool IsInt     = (IsBool || IsSInt || IsUInt || IsChar);
        static const bool IsStdType = (IsVoid || IsInt || IsFloat);

    //public:
    //    typedef typename StaticSelect<IsStdType,
    //                                  T,
    //                                  typename RefTraits<T>::RefType>::Type
    //                     ParamType;
    };


} // namespace xl

#endif // #ifndef __XLTYPETRAITS_H_F84DEF1B_BC39_41ED_A130_A31D78520A8A_INCLUDED__
