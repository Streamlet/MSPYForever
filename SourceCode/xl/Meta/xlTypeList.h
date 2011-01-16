//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlTypeList.h
//    Author:      Streamlet
//    Create Time: 2011-01-12
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLTYPELIST_H_E9C48089_4173_48B2_9442_5D9B052D5652_INCLUDED__
#define __XLTYPELIST_H_E9C48089_4173_48B2_9442_5D9B052D5652_INCLUDED__


#include <xl/xlDef.h>
#include <xl/Meta/xlMacros.h>
#include <xl/Meta/xlMetaBase.h>

namespace xl
{
    template <typename H, typename T>
    struct TypeList
    {
        typedef H Head;
        typedef T Tail;
    };

    template <typename TL>
    struct TLLength;

    template <>
    struct TLLength<NullType>
    {
        enum { Value = 0 };
    };

    template <typename H>
    struct TLLength<TypeList<H, NullType>>
    {
        enum { Value = 1 };
    };

    template <typename H, typename T>
    struct TLLength<TypeList<H, T>>
    {
        enum { Value = 1 + TLLength<T>::Value };
    };

    template <typename TL, typename F>
    struct TLIndexOf;

    template <typename F>
    struct TLIndexOf<NullType, F>
    {
        enum { Value = -1 };
    };

    template <typename H, typename T>
    struct TLIndexOf<TypeList<H, T>, H>
    {
        enum { Value = 0 };
    };

    template <typename H, typename T, typename F>
    struct TLIndexOf<TypeList<H, T>, F>
    {
        enum { Value = TLIndexOf<T, F>::Value == -1 ? -1 : 1 + TLIndexOf<T, F>::Value };
    };

    template <typename TL, size_t i>
    struct TLTypeAt;

    template <typename H, typename T>
    struct TLTypeAt<TypeList<H, T>, 0>
    {
        typedef H Type;
    };

    template <typename H, typename T, size_t i>
    struct TLTypeAt<TypeList<H, T>, i>
    {
        typedef typename TLTypeAt<T, i - 1>::Type Type;
    };

    template <typename TL, size_t i, typename D>
    struct TLTypeAtNS;

    template <size_t i, typename D>
    struct TLTypeAtNS<NullType, i, D>
    {
        typedef D Type;
    };

    template <typename H, typename T, typename D>
    struct TLTypeAtNS<TypeList<H, T>, 0, D>
    {
        typedef H Type;
    };

    template <typename H, typename T, size_t i, typename D>
    struct TLTypeAtNS<TypeList<H, T>, i, D>
    {
        typedef typename TLTypeAtNS<T, i - 1, D>::Type Type;
    };

    template <typename TL, typename T>
    struct TLMerge;

    template <>
    struct TLMerge<NullType, NullType>
    {
        typedef NullType Type;
    };

    template <typename A>
    struct TLMerge<NullType, A>
    {
        typedef TypeList<A, NullType> Type;
    };

    template <typename H, typename T>
    struct TLMerge<NullType, TypeList<H, T>>
    {
        typedef TypeList<H, T> Type;
    };

    template <typename H, typename T, typename A>
    struct TLMerge<TypeList<H, T>, A>
    {
        typedef TypeList<H, typename TLMerge<T, A>::Type> Type;
    };

    template <typename TL, size_t i>
    struct TLSplit;

    template <typename H, typename T>
    struct TLSplit<TypeList<H, T>, 0>
    {
        typedef NullType Front;
        typedef TypeList<H, T> Back;
    };

    template <typename H, typename T>
    struct TLSplit<TypeList<H, T>, 1>
    {
        typedef typename TLMerge<NullType, H>::Type Front;
        typedef typename TLMerge<NullType, T>::Type Back;
    };

    template <typename H, typename T, size_t i>
    struct TLSplit<TypeList<H, T>, i>
    {
        typedef typename TLMerge<typename TLMerge<NullType, H>::Type, typename TLSplit<T, i - 1>::Front>::Type Front;
        typedef typename TLSplit<T, i - 1>::Back Back;
    };

    template <typename TL, size_t i>
    struct TLRSplit
    {
        typedef typename TLSplit<TL, TLLength<TL>::Value - i>::Front Front;
        typedef typename TLSplit<TL, TLLength<TL>::Value - i>::Back Back;
    };

    template <typename TL, typename F, typename R>
    struct TLReplace;

    template <typename F, typename R>
    struct TLReplace<NullType, F, R>
    {
        typedef NullType Type;
    };

    template <typename T, typename F, typename R>
    struct TLReplace<TypeList<F, T>, F, R>
    {
        typedef typename TLMerge<typename TLMerge<NullType, R>::Type, typename TLReplace<T, F, R>::Type>::Type Type;
    };

    template <typename H, typename T, typename F, typename R>
    struct TLReplace<TypeList<H, T>, F, R>
    {
        typedef typename TLMerge<typename TLMerge<NullType, H>::Type, typename TLReplace<T, F, R>::Type>::Type Type;
    };

    template <typename TL>
    struct TLReverse;

    template <>
    struct TLReverse<NullType>
    {
        typedef NullType Type;
    };

    template <typename H>
    struct TLReverse<TypeList<H, NullType>>
    {
        typedef TypeList<H, NullType> Type;
    };

    template <typename H, typename T>
    struct TLReverse<TypeList<H, T>>
    {
        typedef typename TLMerge<typename TLReverse<T>::Type, typename TLMerge<NullType, H>::Type>::Type Type;
    };

#define XL_TYPELIST_TYPENAME_DECLARE_PATTERN(n) typename T##n = NullType
#define XL_TYPELIST_TYPENAME_DECLARE(n)         XL_REPZ(XL_TYPELIST_TYPENAME_DECLARE_PATTERN, n, XL_COMMA)
#define XL_TYPELIST_TYPENAME_LIST_PATTERN(n)    T##n
#define XL_TYPELIST_TYPENAME_LIST(n)            XL_REPZ(XL_TYPELIST_TYPENAME_LIST_PATTERN,    n, XL_COMMA)

    template <typename T = NullType, XL_TYPELIST_TYPENAME_DECLARE(XL_REP_MAX)>
    struct MakeTypeList
    {
        typedef TypeList<T, typename MakeTypeList<XL_TYPELIST_TYPENAME_LIST(XL_REP_MAX)>::Type> Type;
    };

    template <>
    struct MakeTypeList<>
    {
        typedef NullType Type;
    };

#if defined(_MSC_VER)
#  define XL_TYPELIST(...)      ::xl::MakeTypeList<__VA_ARGS__>::Type
#elif defined(__GNUC__)
#  define XL_TYPELIST(args...)  ::xl::MakeTypeList<args>::Type
#endif

#define XL_TYPELIST_0() \
        ::xl::NullType
#define XL_TYPELIST_1(t1) \
        ::xl::TypeList<t1, XL_TYPELIST_0()>
#define XL_TYPELIST_2(t1, t2) \
        ::xl::TypeList<t1, XL_TYPELIST_1(t2)>
#define XL_TYPELIST_3(t1, t2, t3) \
        ::xl::TypeList<t1, XL_TYPELIST_2(t2, t3)>
#define XL_TYPELIST_4(t1, t2, t3, t4) \
        ::xl::TypeList<t1, XL_TYPELIST_3(t2, t3, t4)>
#define XL_TYPELIST_5(t1, t2, t3, t4, t5) \
        ::xl::TypeList<t1, XL_TYPELIST_4(t2, t3, t4, t5)>
#define XL_TYPELIST_6(t1, t2, t3, t4, t5, t6) \
        ::xl::TypeList<t1, XL_TYPELIST_5(t2, t3, t4, t5, t6)>
#define XL_TYPELIST_7(t1, t2, t3, t4, t5, t6, t7) \
        ::xl::TypeList<t1, XL_TYPELIST_6(t2, t3, t4, t5, t6, t7)>
#define XL_TYPELIST_8(t1, t2, t3, t4, t5, t6, t7, t8) \
        ::xl::TypeList<t1, XL_TYPELIST_7(t2, t3, t4, t5, t6, t7, t8)>
#define XL_TYPELIST_9(t1, t2, t3, t4, t5, t6, t7, t8, t9) \
        ::xl::TypeList<t1, XL_TYPELIST_8(t2, t3, t4, t5, t6, t7, t8, t9)>
#define XL_TYPELIST_10(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10) \
        ::xl::TypeList<t1, XL_TYPELIST_9(t2, t3, t4, t5, t6, t7, t8, t9, t10)>
#define XL_TYPELIST_11(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11) \
        ::xl::TypeList<t1, XL_TYPELIST_10(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11)>
#define XL_TYPELIST_12(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12) \
        ::xl::TypeList<t1, XL_TYPELIST_11(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12)>
#define XL_TYPELIST_13(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13) \
        ::xl::TypeList<t1, XL_TYPELIST_12(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13)>
#define XL_TYPELIST_14(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14) \
        ::xl::TypeList<t1, XL_TYPELIST_13(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14)>
#define XL_TYPELIST_15(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15) \
        ::xl::TypeList<t1, XL_TYPELIST_14(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15)>
#define XL_TYPELIST_16(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16) \
        ::xl::TypeList<t1, XL_TYPELIST_15(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16)>
#define XL_TYPELIST_17(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17) \
        ::xl::TypeList<t1, XL_TYPELIST_16(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17)>
#define XL_TYPELIST_18(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18) \
        ::xl::TypeList<t1, XL_TYPELIST_17(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18)>
#define XL_TYPELIST_19(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19) \
        ::xl::TypeList<t1, XL_TYPELIST_18(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19)>
#define XL_TYPELIST_20(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20) \
        ::xl::TypeList<t1, XL_TYPELIST_19(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20)>
#define XL_TYPELIST_21(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21) \
        ::xl::TypeList<t1, XL_TYPELIST_20(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21)>
#define XL_TYPELIST_22(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22) \
        ::xl::TypeList<t1, XL_TYPELIST_21(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22)>
#define XL_TYPELIST_23(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23) \
        ::xl::TypeList<t1, XL_TYPELIST_22(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23)>
#define XL_TYPELIST_24(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24) \
        ::xl::TypeList<t1, XL_TYPELIST_23(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24)>
#define XL_TYPELIST_25(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25) \
        ::xl::TypeList<t1, XL_TYPELIST_24(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25)>
#define XL_TYPELIST_26(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26) \
        ::xl::TypeList<t1, XL_TYPELIST_25(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26)>
#define XL_TYPELIST_27(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27) \
        ::xl::TypeList<t1, XL_TYPELIST_26(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27)>
#define XL_TYPELIST_28(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28) \
        ::xl::TypeList<t1, XL_TYPELIST_27(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28)>
#define XL_TYPELIST_29(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29) \
        ::xl::TypeList<t1, XL_TYPELIST_28(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29)>
#define XL_TYPELIST_30(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30) \
        ::xl::TypeList<t1, XL_TYPELIST_29(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30)>
#define XL_TYPELIST_31(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31) \
        ::xl::TypeList<t1, XL_TYPELIST_30(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31)>
#define XL_TYPELIST_32(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32) \
        ::xl::TypeList<t1, XL_TYPELIST_31(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32)>
#define XL_TYPELIST_33(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33) \
        ::xl::TypeList<t1, XL_TYPELIST_32(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33)>
#define XL_TYPELIST_34(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34) \
        ::xl::TypeList<t1, XL_TYPELIST_33(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34)>
#define XL_TYPELIST_35(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35) \
        ::xl::TypeList<t1, XL_TYPELIST_34(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35)>
#define XL_TYPELIST_36(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36) \
        ::xl::TypeList<t1, XL_TYPELIST_35(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36)>
#define XL_TYPELIST_37(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37) \
        ::xl::TypeList<t1, XL_TYPELIST_36(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37)>
#define XL_TYPELIST_38(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38) \
        ::xl::TypeList<t1, XL_TYPELIST_37(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38)>
#define XL_TYPELIST_39(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39) \
        ::xl::TypeList<t1, XL_TYPELIST_38(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39)>
#define XL_TYPELIST_40(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40) \
        ::xl::TypeList<t1, XL_TYPELIST_39(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40)>
#define XL_TYPELIST_41(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41) \
        ::xl::TypeList<t1, XL_TYPELIST_40(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41)>
#define XL_TYPELIST_42(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42) \
        ::xl::TypeList<t1, XL_TYPELIST_41(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42)>
#define XL_TYPELIST_43(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43) \
        ::xl::TypeList<t1, XL_TYPELIST_42(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43)>
#define XL_TYPELIST_44(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44) \
        ::xl::TypeList<t1, XL_TYPELIST_43(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44)>
#define XL_TYPELIST_45(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45) \
        ::xl::TypeList<t1, XL_TYPELIST_44(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45)>
#define XL_TYPELIST_46(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46) \
        ::xl::TypeList<t1, XL_TYPELIST_45(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46)>
#define XL_TYPELIST_47(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47) \
        ::xl::TypeList<t1, XL_TYPELIST_46(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47)>
#define XL_TYPELIST_48(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48) \
        ::xl::TypeList<t1, XL_TYPELIST_47(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48)>
#define XL_TYPELIST_49(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49) \
        ::xl::TypeList<t1, XL_TYPELIST_48(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49)>
#define XL_TYPELIST_50(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50) \
        ::xl::TypeList<t1, XL_TYPELIST_49(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50)>
#define XL_TYPELIST_51(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51) \
        ::xl::TypeList<t1, XL_TYPELIST_50(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51)>
#define XL_TYPELIST_52(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52) \
        ::xl::TypeList<t1, XL_TYPELIST_51(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52)>
#define XL_TYPELIST_53(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53) \
        ::xl::TypeList<t1, XL_TYPELIST_52(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53)>
#define XL_TYPELIST_54(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54) \
        ::xl::TypeList<t1, XL_TYPELIST_53(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54)>
#define XL_TYPELIST_55(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55) \
        ::xl::TypeList<t1, XL_TYPELIST_54(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55)>
#define XL_TYPELIST_56(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56) \
        ::xl::TypeList<t1, XL_TYPELIST_55(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56)>
#define XL_TYPELIST_57(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57) \
        ::xl::TypeList<t1, XL_TYPELIST_56(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57)>
#define XL_TYPELIST_58(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58) \
        ::xl::TypeList<t1, XL_TYPELIST_57(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58)>
#define XL_TYPELIST_59(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59) \
        ::xl::TypeList<t1, XL_TYPELIST_58(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59)>
#define XL_TYPELIST_60(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60) \
        ::xl::TypeList<t1, XL_TYPELIST_59(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60)>
#define XL_TYPELIST_61(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61) \
        ::xl::TypeList<t1, XL_TYPELIST_60(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61)>
#define XL_TYPELIST_62(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62) \
        ::xl::TypeList<t1, XL_TYPELIST_61(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62)>
#define XL_TYPELIST_63(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63) \
        ::xl::TypeList<t1, XL_TYPELIST_62(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63)>
#define XL_TYPELIST_64(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64) \
        ::xl::TypeList<t1, XL_TYPELIST_63(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64)>
#define XL_TYPELIST_65(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65) \
        ::xl::TypeList<t1, XL_TYPELIST_64(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65)>
#define XL_TYPELIST_66(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66) \
        ::xl::TypeList<t1, XL_TYPELIST_65(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66)>
#define XL_TYPELIST_67(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67) \
        ::xl::TypeList<t1, XL_TYPELIST_66(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67)>
#define XL_TYPELIST_68(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68) \
        ::xl::TypeList<t1, XL_TYPELIST_67(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68)>
#define XL_TYPELIST_69(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69) \
        ::xl::TypeList<t1, XL_TYPELIST_68(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69)>
#define XL_TYPELIST_70(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70) \
        ::xl::TypeList<t1, XL_TYPELIST_69(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70)>
#define XL_TYPELIST_71(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71) \
        ::xl::TypeList<t1, XL_TYPELIST_70(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71)>
#define XL_TYPELIST_72(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72) \
        ::xl::TypeList<t1, XL_TYPELIST_71(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72)>
#define XL_TYPELIST_73(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73) \
        ::xl::TypeList<t1, XL_TYPELIST_72(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73)>
#define XL_TYPELIST_74(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74) \
        ::xl::TypeList<t1, XL_TYPELIST_73(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74)>
#define XL_TYPELIST_75(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75) \
        ::xl::TypeList<t1, XL_TYPELIST_74(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75)>
#define XL_TYPELIST_76(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76) \
        ::xl::TypeList<t1, XL_TYPELIST_75(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76)>
#define XL_TYPELIST_77(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77) \
        ::xl::TypeList<t1, XL_TYPELIST_76(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77)>
#define XL_TYPELIST_78(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78) \
        ::xl::TypeList<t1, XL_TYPELIST_77(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78)>
#define XL_TYPELIST_79(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79) \
        ::xl::TypeList<t1, XL_TYPELIST_78(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79)>
#define XL_TYPELIST_80(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80) \
        ::xl::TypeList<t1, XL_TYPELIST_79(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80)>
#define XL_TYPELIST_81(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81) \
        ::xl::TypeList<t1, XL_TYPELIST_80(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81)>
#define XL_TYPELIST_82(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82) \
        ::xl::TypeList<t1, XL_TYPELIST_81(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82)>
#define XL_TYPELIST_83(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83) \
        ::xl::TypeList<t1, XL_TYPELIST_82(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83)>
#define XL_TYPELIST_84(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84) \
        ::xl::TypeList<t1, XL_TYPELIST_83(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84)>
#define XL_TYPELIST_85(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85) \
        ::xl::TypeList<t1, XL_TYPELIST_84(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85)>
#define XL_TYPELIST_86(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85, t86) \
        ::xl::TypeList<t1, XL_TYPELIST_85(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85, t86)>
#define XL_TYPELIST_87(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85, t86, t87) \
        ::xl::TypeList<t1, XL_TYPELIST_86(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85, t86, t87)>
#define XL_TYPELIST_88(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85, t86, t87, t88) \
        ::xl::TypeList<t1, XL_TYPELIST_87(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88)>
#define XL_TYPELIST_89(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85, t86, t87, t88, t89) \
        ::xl::TypeList<t1, XL_TYPELIST_88(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88, t89)>
#define XL_TYPELIST_90(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85, t86, t87, t88, t89, t90) \
        ::xl::TypeList<t1, XL_TYPELIST_89(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88, t89, t90)>
#define XL_TYPELIST_91(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91) \
        ::xl::TypeList<t1, XL_TYPELIST_90(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91)>
#define XL_TYPELIST_92(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92) \
        ::xl::TypeList<t1, XL_TYPELIST_91(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92)>
#define XL_TYPELIST_93(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93) \
        ::xl::TypeList<t1, XL_TYPELIST_92(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93)>
#define XL_TYPELIST_94(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94) \
        ::xl::TypeList<t1, XL_TYPELIST_93(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94)>
#define XL_TYPELIST_95(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94, t95) \
        ::xl::TypeList<t1, XL_TYPELIST_94(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94, t95)>
#define XL_TYPELIST_96(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94, t95, t96) \
        ::xl::TypeList<t1, XL_TYPELIST_95(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94, t95, t96)>
#define XL_TYPELIST_97(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94, t95, t96, t97) \
        ::xl::TypeList<t1, XL_TYPELIST_96(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94, t95, t96, t97)>
#define XL_TYPELIST_98(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94, t95, t96, t97, t98) \
        ::xl::TypeList<t1, XL_TYPELIST_97(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94, t95, t96, t97, \
              t98)>
#define XL_TYPELIST_99(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, \
              t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, \
              t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, \
              t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, \
              t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94, t95, t96, t97, t98, t99) \
        ::xl::TypeList<t1, XL_TYPELIST_98(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, \
              t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, \
              t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, \
              t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, \
              t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94, t95, t96, t97, \
              t98, t99)>

#define XL_TYPELIST_DEFINE_MAX  99

} // namespace xl

#endif // #ifndef __XLTYPELIST_H_E9C48089_4173_48B2_9442_5D9B052D5652_INCLUDED__
