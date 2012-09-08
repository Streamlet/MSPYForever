//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlBind.h
//    Author:      Streamlet
//    Create Time: 2011-02-24
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLBIND_H_E78F97BF_251C_4570_B0C4_0F876ADED799_INCLUDED__
#define __XLBIND_H_E78F97BF_251C_4570_B0C4_0F876ADED799_INCLUDED__

#include <xl/xlDef.h>
#include <xl/Meta/xlMacros.h>
#include <xl/Meta/xlTypeList.h>
#include <xl/Meta/xlFunction.h>

namespace xl
{
#ifndef XL_BIND_DEFINE_MAX
#define XL_BIND_DEFINE_MAX  XL_FUNCTION_DEFINE_MAX
#endif

#define XL_BIND_TYPENAME_DECLARE_PATTERN(n)     typename A##n
#define XL_BIND_TYPENAME_DECLARE(n)             XL_REPZ(XL_BIND_TYPENAME_DECLARE_PATTERN, n, XL_COMMA)

#define XL_BIND_TYPENAME_DECLARE_PATTERN_B(n)   typename B##n
#define XL_BIND_TYPENAME_DECLARE_B(n)           XL_REPZ(XL_BIND_TYPENAME_DECLARE_PATTERN_B, n, XL_COMMA)

#define XL_BIND_TYPENAME_LIST_PATTERN(n)        A##n
#define XL_BIND_TYPENAME_LIST(n)                XL_REPZ(XL_BIND_TYPENAME_LIST_PATTERN, n, XL_COMMA)

#define XL_BIND_TYPENAME_LIST_PATTERN_B(n)      B##n
#define XL_BIND_TYPENAME_LIST_B(n)              XL_REPZ(XL_BIND_TYPENAME_LIST_PATTERN_B, n, XL_COMMA)

#define XL_BIND_TYPENAME_VARIABLE_NO_RREF(n)    A##n a##n
#define XL_BIND_TYPENAME_VARIABLE_PATTERN(n)    A##n &&a##n
#define XL_BIND_TYPENAME_VARIABLE(n)            XL_REPZ(XL_BIND_TYPENAME_VARIABLE_PATTERN, n, XL_COMMA)

#define XL_BIND_VARIABLE_INITIALIZE_PATTERN(n)  a##n(static_cast<A##n &&>(a##n))
#define XL_BIND_VARIABLE_INITIALIZE(n)          XL_REPZ(XL_BIND_VARIABLE_INITIALIZE_PATTERN, n, XL_COMMA)

#define XL_BIND_VARIABLE_LIST_PATTERN(n)        static_cast<A##n &&>(a##n)
#define XL_BIND_VARIABLE_LIST(n)                XL_REPZ(XL_BIND_VARIABLE_LIST_PATTERN, n, XL_COMMA)

#define XL_BIND_ARGUMENTS_QUERY_PATTERN(n)      a[static_cast<A##n &&>(a##n)]
#define XL_BIND_ARGUMENTS_QUERY(n)              XL_REPZ(XL_BIND_ARGUMENTS_QUERY_PATTERN, n, XL_COMMA)

    template <int i>
    struct PlaceHolder
    {

    };

//     static PlaceHolder<1> _1;

#define XL_BIND_PLACEHOLDER_DECLARE_PATTERN(n)  static PlaceHolder<n> _##n
#define XL_BIND_PLACEHOLDER_DECLARE(n)          XL_REPZ(XL_BIND_PLACEHOLDER_DECLARE_PATTERN, n, ;)

    XL_BIND_PLACEHOLDER_DECLARE(XL_BIND_DEFINE_MAX);


    template <typename TL = XL_TYPELIST_0()>
    struct BindArguments
    {

    };

//     template <typename A1>
//     struct BindArguments<XL_TYPELIST_1(A1)> :
//         public BindArguments<XL_TYPELIST_0()>
//     {
//         BindArguments(A1 &&a1) :
//             BindArguments<XL_TYPELIST_0()>(),
//             a1(static_cast<A1 &&>(a1))
//         {
// 
//         }
// 
//         A1 a1;
//     };
//     
//     template <typename A1, typename A2>
//     struct BindArguments<XL_TYPELIST_2(A1, A2)> :
//         public BindArguments<XL_TYPELIST_1(A1)>
//     {
//         BindArguments(A1 &&a1, A2 &&a2) :
//             BindArguments<XL_TYPELIST_1(A1)>(static_cast<A1 &&>(a1)),
//             a2(static_cast<A2 &&>(a2))
//         {
// 
//         }
// 
//         A2 a2;
//     };

#define XL_BIND_ARGUMENTS_PATTERN(n)                                                                        \
                                                                                                            \
    template <XL_BIND_TYPENAME_DECLARE(n)>                                                                  \
    struct BindArguments<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))> :                     \
        public BindArguments<XL_EVAL(XL_CONN(XL_TYPELIST_, XL_DEC(n)), XL_BIND_TYPENAME_LIST(XL_DEC(n)))>   \
    {                                                                                                       \
        BindArguments(XL_BIND_TYPENAME_VARIABLE(n)) :                                                       \
            BindArguments<XL_EVAL(XL_CONN(XL_TYPELIST_, XL_DEC(n)), XL_BIND_TYPENAME_LIST(XL_DEC(n)))>(     \
                XL_BIND_VARIABLE_LIST(XL_DEC(n))),                                                          \
            XL_BIND_VARIABLE_INITIALIZE_PATTERN(n)                                                          \
        {                                                                                                   \
                                                                                                            \
        }                                                                                                   \
                                                                                                            \
        XL_BIND_TYPENAME_VARIABLE_NO_RREF(n);                                                               \
    };

#define XL_BIND_ARGUMENTS(n)  XL_REPY(XL_BIND_ARGUMENTS_PATTERN, n, XL_NIL)

    XL_BIND_ARGUMENTS(XL_BIND_DEFINE_MAX)


    template <typename TL = XL_TYPELIST_0()>
    class CallList : public BindArguments<XL_TYPELIST_0()>
    {
    public:
        CallList() : BindArguments<XL_TYPELIST_0()>()
        {

        }

    public:
        template <typename T>
        T operator [](T &&t)
        {
            return static_cast<T &&>(t);
        }
    };

//     template <typename A1>
//     class CallList<XL_TYPELIST_1(A1)> :
//         public BindArguments<XL_TYPELIST_1(A1)>
//     {
//     public:
//         CallList(A1 &&a1) :
//             BindArguments<XL_TYPELIST_1(A1)>(static_cast<A1 &&>(a1))
//         {
// 
//         }
//  
//     public:
//         A1 operator [](PlaceHolder<1>)
//         {
//             return static_cast<A1 &&>(a1);
//         }
// 
//         template <typename T>
//         T operator [](T &&t)
//         {
//             return static_cast<T &&>(t);
//         }
//     };
// 
//     template <typename A1, typename A2>
//     class CallList<XL_TYPELIST_2(A1, A2)> :
//         public BindArguments<XL_TYPELIST_2(A1, A2)>
//     {
//     public:
//         CallList(A1 &&a1, A2 &&a2) :
//             BindArguments<XL_TYPELIST_2(A1, A2)>(static_cast<A1 &&>(a1), static_cast<A2 &&>(a2))
//         {
// 
//         }
//  
//     public:
//         A1 operator [](PlaceHolder<1>)
//         {
//             return static_cast<A1 &&>(a1);
//         }
// 
//         A2 operator [](PlaceHolder<2>)
//         {
//             return static_cast<A2 &&>(a2);
//         }
// 
//         template <typename T>
//         T operator [](T &&t)
//         {
//             return static_cast<T &&>(t);
//         }
//     };

#define XL_BIND_CALLLIST_OPERATOR_PLACEHOLDER_PATTERN(n)            \
                                                                    \
    XL_BIND_TYPENAME_LIST_PATTERN(n) operator [](PlaceHolder<n>)    \
    {                                                               \
        return XL_BIND_VARIABLE_LIST_PATTERN(n);                    \
    }

#define XL_BIND_CALLLIST_OPERATOR_PLACEHOLDER(n)  XL_REPY(XL_BIND_CALLLIST_OPERATOR_PLACEHOLDER_PATTERN, n, XL_NIL)

#define XL_BIND_CALLLIST_PATTERN(n)                                                                                 \
                                                                                                                    \
    template <XL_BIND_TYPENAME_DECLARE(n)>                                                                          \
    class CallList<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))> :                                   \
        public BindArguments<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))>                           \
    {                                                                                                               \
    public:                                                                                                         \
        CallList(XL_BIND_TYPENAME_VARIABLE(n)) :                                                                    \
            BindArguments<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))>(XL_BIND_VARIABLE_LIST(n))    \
        {                                                                                                           \
                                                                                                                    \
        }                                                                                                           \
                                                                                                                    \
    public:                                                                                                         \
        XL_BIND_CALLLIST_OPERATOR_PLACEHOLDER(n)                                                                    \
                                                                                                                    \
        template <typename T>                                                                                       \
        T operator [](T &&t)                                                                                        \
        {                                                                                                           \
            return static_cast<T &&>(t);                                                                            \
        }                                                                                                           \
    };

#define XL_BIND_CALLLIST(n)  XL_REPX(XL_BIND_CALLLIST_PATTERN, n, XL_NIL)

    XL_BIND_CALLLIST(XL_BIND_DEFINE_MAX)


    template <typename TL = XL_TYPELIST_0()>
    class BindList : public BindArguments<XL_TYPELIST_0()>
    {
    public:
        BindList() : BindArguments<XL_TYPELIST_0()>()
        {

        }

    public:
        template <typename F, typename A>
        typename F::ReturnType operator ()(F f, A a)
        {
            return f();
        }
    };

//     template <typename A1>
//     class BindList<XL_TYPELIST_1(A1)> :
//         public BindArguments<XL_TYPELIST_1(A1)>
//     {
//     public:
//         BindList(A1 &&a1) :
//             BindArguments<XL_TYPELIST_1(A1)>(static_cast<A1 &&>(a1))
//         {
// 
//         }
// 
//     public:
//         template <typename F, typename A>
//         typename F::ReturnType operator ()(F f, A a)
//         {
//             return f(a[static_cast<A1 &&>(a1)]);
//         }
//     };
// 
//     template <typename A1, typename A2>
//     class BindList<XL_TYPELIST_2(A1, A2)> :
//         public BindArguments<XL_TYPELIST_2(A1, A2)>
//     {
//     public:
//         BindList(A1 &&a1, A2 &&a2) :
//             BindArguments<XL_TYPELIST_2(A1, A2)>(static_cast<A1 &&>(a1), static_cast<A2 &&>(a2))
//         {
//  
//         }
//  
//     public:
//         template <typename F, typename A>
//         typename F::ReturnType operator ()(F f, A a)
//         {
//             return f(a[static_cast<A1 &&>(a1)], a[static_cast<A2 &&>(a2)]);
//         }
//     };

#define XL_BIND_BINDLIST_PATTERN(n)                                                                                 \
                                                                                                                    \
    template <XL_BIND_TYPENAME_DECLARE(n)>                                                                          \
    class BindList<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))> :                                   \
        public BindArguments<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))>                           \
    {                                                                                                               \
    public:                                                                                                         \
        BindList(XL_BIND_TYPENAME_VARIABLE(n)) :                                                                    \
            BindArguments<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))>(XL_BIND_VARIABLE_LIST(n))    \
        {                                                                                                           \
                                                                                                                    \
        }                                                                                                           \
                                                                                                                    \
    public:                                                                                                         \
        template <typename F, typename A>                                                                           \
        typename F::ReturnType operator ()(F f, A a)                                                                \
        {                                                                                                           \
            return f(XL_BIND_ARGUMENTS_QUERY(n));                                                                   \
        }                                                                                                           \
    };

#define XL_BIND_BINDLIST(n)  XL_REPY(XL_BIND_BINDLIST_PATTERN, n, XL_NIL)

    XL_BIND_BINDLIST(XL_BIND_DEFINE_MAX)


    template <typename S, typename BL>
    class BindT
    {
    public:
        typedef typename Function<S>              FunctionType;
        typedef typename FunctionType::ReturnType ReturnType;

    public:
        BindT(FunctionType f, BL bl) : f(f), bl(bl)
        {

        }

    public:
        ReturnType operator ()()
        {
            return bl(f, CallList<XL_TYPELIST_0()>());
        }

//         template <typename A1>
//         ReturnType operator ()(A1 &&a1)
//         {
//             return bl(f,
//                       CallList<XL_TYPELIST_1(A1)>(
//                           static_cast<A1 &&>(a1)));
//         }

#define XL_BIND_BINDT_OPERATOR_PATTERN(n)                                                       \
                                                                                                \
        template <XL_BIND_TYPENAME_DECLARE(n)>                                                  \
        ReturnType operator ()(XL_BIND_TYPENAME_VARIABLE(n))                                    \
        {                                                                                       \
            return bl(f,                                                                        \
                      CallList<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))>(    \
                          XL_BIND_VARIABLE_LIST(n)));                                           \
        }

#define XL_BIND_BINDT_OPERATOR(n)  XL_REPY(XL_BIND_BINDT_OPERATOR_PATTERN, n, XL_NIL)

        XL_BIND_BINDT_OPERATOR(XL_BIND_DEFINE_MAX)

    private:
        FunctionType f;
        BL bl;
    };


    template <typename S>
    BindT<S, BindList<>> Bind(Function<S> f)
    {
        return BindT<S, BindList<>>(Function<S>(f), BindList<>());
    }

//     template <typename R>
//     BindT<R(), BindList<>> Bind(R (*f)())
//     {
//         return BindT<R(), BindList<>>(Function<R ()>(f), BindList<>());
//     }
//  
//     template <typename R, typename T>
//     BindT<R(), BindList<>> Bind(T *p, R (T::*f)())
//     {
//         return BindT<R(), BindList<>>(Function<R ()>(p, f), BindList<>());
//     }

#define XL_BIND_FUNCTION_PARAM_0(cc)                                    \
                                                                        \
    template <typename R>                                               \
    BindT<R(), BindList<>> Bind(R (cc *f)())                            \
    {                                                                   \
        return BindT<R(), BindList<>>(Function<R ()>(f), BindList<>()); \
    }

#define XL_BIND_MEMBER_FUNCTION_PARAM_0(cc)                                 \
                                                                            \
    template <typename R, typename T>                                       \
    BindT<R(), BindList<>> Bind(T *p, R (cc T::*f)())                       \
    {                                                                       \
        return BindT<R(), BindList<>>(Function<R ()>(p, f), BindList<>());  \
    }

#ifdef _M_X64
    XL_BIND_FUNCTION_PARAM_0(XL_NIL)
    XL_BIND_MEMBER_FUNCTION_PARAM_0(XL_NIL)
#else
    XL_BIND_FUNCTION_PARAM_0(__cdecl)
    XL_BIND_FUNCTION_PARAM_0(__stdcall)
    XL_BIND_FUNCTION_PARAM_0(__fastcall)
    XL_BIND_MEMBER_FUNCTION_PARAM_0(__cdecl)
    XL_BIND_MEMBER_FUNCTION_PARAM_0(__stdcall)
    XL_BIND_MEMBER_FUNCTION_PARAM_0(__fastcall)
    XL_BIND_MEMBER_FUNCTION_PARAM_0(__thiscall)
#endif


//     template <typename S, typename A1>
//     BindT<S,
//           BindList<XL_TYPELIST_1(A1)>>
//     Bind(Function<S> f, A1 &&a1)
//     {
//         return BindT<S,
//                      BindList<XL_TYPELIST_1(A1)>>(
//                    f,
//                    BindList<XL_TYPELIST_1(A1)>(
//                        static_cast<A1 &&>(a1)));
//     }
// 
//     template <typename R, typename B1, typename A1>
//     BindT<R (B1),
//           BindList<XL_TYPELIST_1(A1)>>
//     Bind(R (*f)(B1), A1 &&a1)
//     {
//         return BindT<R (B1),
//                      BindList<XL_TYPELIST_1(A1)>>(
//                    Function<R (B1)>(f),
//                    BindList<XL_TYPELIST_1(A1)>(
//                        static_cast<A1 &&>(a1)));
//     }
//     
//     template <typename R, typename T, typename B1, typename A1>
//     BindT<R (B1),
//           BindList<XL_TYPELIST_1(A1)>>
//     Bind(T *p, R (T::*f)(B1), A1 &&a1)
//     {
//         return BindT<R (B1),
//                      BindList<XL_TYPELIST_1(A1)>>(
//                    Function<R (B1)>(p, f),
//                    BindList<XL_TYPELIST_1(A1)>(
//                        static_cast<A1 &&>(a1)));
//     }

#define XL_BIND_FUNCTOR_PARAM(n)                                                                \
                                                                                                \
    template <typename S, XL_BIND_TYPENAME_DECLARE(n)>                                          \
    BindT<S,                                                                                    \
          BindList<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))>>                \
    Bind(Function<S> f, XL_BIND_TYPENAME_VARIABLE(n))                                           \
    {                                                                                           \
        return BindT<S,                                                                         \
                     BindList<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))>>(    \
                   f,                                                                           \
                   BindList<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))>(       \
                       XL_BIND_VARIABLE_LIST(n)));                                              \
    }

#define XL_BIND_FUNCTION_PARAM(n, cc)                                                           \
                                                                                                \
    template <typename R, XL_BIND_TYPENAME_DECLARE(n), XL_BIND_TYPENAME_DECLARE_B(n)>           \
    BindT<R (XL_BIND_TYPENAME_LIST_B(n)),                                                       \
          BindList<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))>>                \
    Bind(R (cc *f)(XL_BIND_TYPENAME_LIST_B(n)), XL_BIND_TYPENAME_VARIABLE(n))                   \
    {                                                                                           \
        return BindT<R (XL_BIND_TYPENAME_LIST_B(n)),                                            \
                     BindList<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))>>(    \
                   Function<R (XL_BIND_TYPENAME_LIST_B(n))>(f),                                 \
                   BindList<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))>(       \
                       XL_BIND_VARIABLE_LIST(n)));                                              \
    }

#define XL_BIND_MEMBER_FUNCTION_PARAM(n, cc)                                                        \
                                                                                                    \
    template <typename R, typename T, XL_BIND_TYPENAME_DECLARE(n), XL_BIND_TYPENAME_DECLARE_B(n)>   \
    BindT<R (XL_BIND_TYPENAME_LIST_B(n)),                                                           \
          BindList<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))>>                    \
    Bind(T *p, R (cc T::*f)(XL_BIND_TYPENAME_LIST_B(n)), XL_BIND_TYPENAME_VARIABLE(n))              \
    {                                                                                               \
        return BindT<R (XL_BIND_TYPENAME_LIST_B(n)),                                                \
                     BindList<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))>>(        \
                   Function<R (XL_BIND_TYPENAME_LIST_B(n))>(p, f),                                  \
                   BindList<XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_BIND_TYPENAME_LIST(n))>(           \
                       XL_BIND_VARIABLE_LIST(n)));                                                  \
    }

// #ifdef _M_X64
//     XL_BIND_FUNCTOR_PARAM(1)
//     XL_BIND_FUNCTION_PARAM(1, XL_NIL)
//     XL_BIND_MEMBER_FUNCTION_PARAM(1, XL_NIL)
//     XL_BIND_FUNCTOR_PARAM(2)
//     XL_BIND_FUNCTION_PARAM(2, XL_NIL)
//     XL_BIND_MEMBER_FUNCTION_PARAM(2, XL_NIL)
// #else
//     XL_BIND_FUNCTOR_PARAM(1)
//     XL_BIND_FUNCTION_PARAM(1, __cdecl)
//     XL_BIND_FUNCTION_PARAM(1, __stdcall)
//     XL_BIND_FUNCTION_PARAM(1, __fastcall)
//     XL_BIND_MEMBER_FUNCTION_PARAM(1, __thiscall)
//     XL_BIND_MEMBER_FUNCTION_PARAM(1, __cdecl)
//     XL_BIND_MEMBER_FUNCTION_PARAM(1, __stdcall)
//     XL_BIND_MEMBER_FUNCTION_PARAM(1, __fastcall)
//     XL_BIND_FUNCTOR_PARAM(2)
//     XL_BIND_FUNCTION_PARAM(2, __cdecl)
//     XL_BIND_FUNCTION_PARAM(2, __stdcall)
//     XL_BIND_FUNCTION_PARAM(2, __fastcall)
//     XL_BIND_MEMBER_FUNCTION_PARAM(2, __thiscall)
//     XL_BIND_MEMBER_FUNCTION_PARAM(2, __cdecl)
//     XL_BIND_MEMBER_FUNCTION_PARAM(2, __stdcall)
//     XL_BIND_MEMBER_FUNCTION_PARAM(2, __fastcall)
// #endif

#ifdef _M_X64

#define XL_BIND_PARAM_PATTERN(n)                    \
                                                    \
    XL_BIND_FUNCTOR_PARAM(n)                        \
    XL_BIND_FUNCTION_PARAM(n, XL_NIL)               \
    XL_BIND_MEMBER_FUNCTION_PARAM(n, XL_NIL)

#else

#define XL_BIND_PARAM_PATTERN(n)                    \
                                                    \
    XL_BIND_FUNCTOR_PARAM(n)                        \
    XL_BIND_FUNCTION_PARAM(n, __cdecl)              \
    XL_BIND_FUNCTION_PARAM(n, __stdcall)            \
    XL_BIND_FUNCTION_PARAM(n, __fastcall)           \
    XL_BIND_MEMBER_FUNCTION_PARAM(n, __thiscall)    \
    XL_BIND_MEMBER_FUNCTION_PARAM(n, __cdecl)       \
    XL_BIND_MEMBER_FUNCTION_PARAM(n, __stdcall)     \
    XL_BIND_MEMBER_FUNCTION_PARAM(n, __fastcall)

#endif

#define XL_BIND_PARAM(n)  XL_REPY(XL_BIND_PARAM_PATTERN, n, XL_NIL)

    XL_BIND_PARAM(XL_BIND_DEFINE_MAX)

} // namespace xl

#endif // #ifndef __XLBIND_H_E78F97BF_251C_4570_B0C4_0F876ADED799_INCLUDED__
