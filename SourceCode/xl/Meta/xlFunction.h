//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlFunction.h
//    Author:      Streamlet
//    Create Time: 2011-01-09
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLFUNCTION_H_83D86772_25B2_4625_8A4F_0C5EAAF1E93C_INCLUDED__
#define __XLFUNCTION_H_83D86772_25B2_4625_8A4F_0C5EAAF1E93C_INCLUDED__


#include <xl/xlDef.h>
#include <xl/Memory/xlQIPtr.h>
#include <xl/Meta/xlMacros.h>
#include <xl/Meta/xlTypeList.h>

namespace xl
{
#define XL_FUNCTION_DEFINE_MAX  20

#define XL_FUNCTION_TYPENAME_DECLARE_PATTERN(n)     typename T##n
#define XL_FUNCTION_TYPENAME_DECLARE(n)             XL_REPZ(XL_FUNCTION_TYPENAME_DECLARE_PATTERN, n, XL_COMMA)

#define XL_FUNCTION_TYPENAME_LIST_PATTERN(n)        T##n
#define XL_FUNCTION_TYPENAME_LIST(n)                XL_REPZ(XL_FUNCTION_TYPENAME_LIST_PATTERN, n, XL_COMMA)

#define XL_FUNCTION_TYPENAME_VARIABLE_PATTERN(n)    T##n v##n
#define XL_FUNCTION_TYPENAME_VARIABLE(n)            XL_REPZ(XL_FUNCTION_TYPENAME_VARIABLE_PATTERN, n, XL_COMMA)

#define XL_FUNCTION_VARIABLE_LIST_PATTERN(n)        v##n
#define XL_FUNCTION_VARIABLE_LIST(n)                XL_REPZ(XL_FUNCTION_VARIABLE_LIST_PATTERN, n, XL_COMMA)

    template <typename R, typename TL>
    class FunctionBase;

    template <typename R>
    class FunctionBase<R, XL_TYPELIST_0()>
    {
    public:
        virtual FunctionBase *Clone() const = 0;
        virtual R Invoke()                  = 0;
        virtual ~FunctionBase() {}
    };

#define XL_FUNCTION_FUNCTORBASE_PATTERN(n)                                                          \
                                                                                                    \
    template <typename R, XL_FUNCTION_TYPENAME_DECLARE(n)>                                          \
    class FunctionBase<R, XL_EVAL(XL_CONN(XL_TYPELIST_, XL_INC(n)), XL_FUNCTION_TYPENAME_LIST(n))>  \
    {                                                                                               \
    public:                                                                                         \
        virtual FunctionBase *Clone() const             = 0;                                        \
        virtual R Invoke(XL_FUNCTION_TYPENAME_LIST(n))  = 0;                                        \
        virtual ~FunctionBase() {}                                                                  \
    };                                                                                              \

#define XL_FUNCTION_FUNCTORBASE(n)  XL_REPY(XL_FUNCTION_FUNCTORBASE_PATTERN, n, XL_NIL)

    XL_FUNCTION_FUNCTORBASE(XL_FUNCTION_DEFINE_MAX)

    template <typename R, typename P, typename F>
    class FunctionHandler : public FunctionBase<R, P>
    {
    private:
        typedef R ReturnType;
        typedef P ParamList;
        typedef F FunctionType;

    public:
        FunctionHandler(const FunctionType &fnFunction)
            : m_fnFunction(fnFunction)
        {

        }

    private:
        FunctionType m_fnFunction;

    public:
        FunctionBase *Clone() const
        {
            return new FunctionHandler(m_fnFunction);
        }

        ReturnType Invoke()
        {
            return m_fnFunction();
        }

#define XL_FUNCTION_FUNCTION_INVOKE_PATTERN(n)                          \
                                                                        \
        typedef typename TLTypeAtNS<ParamList, n, EmptyType>::Type      \
                XL_FUNCTION_TYPENAME_LIST_PATTERN(n);                   \
                                                                        \
        ReturnType Invoke(XL_FUNCTION_TYPENAME_VARIABLE(n))             \
        {                                                               \
            return m_fnFunction(XL_FUNCTION_VARIABLE_LIST(n));          \
        }                                                               \

#define XL_FUNCTION_FUNCTION_INVOKE(n)  XL_REPY(XL_FUNCTION_FUNCTION_INVOKE_PATTERN, n, XL_NIL)

        XL_FUNCTION_FUNCTION_INVOKE(XL_FUNCTION_DEFINE_MAX)
    };

    template <typename R, typename P, typename T, typename F>
    class MemberFunctionHandler : public FunctionBase<R, P>
    {
    private:
        typedef R ReturnType;
        typedef P ParamList;
        typedef T ClassPtrType;
        typedef F MemberFunctionType;

    public:
        MemberFunctionHandler(const ClassPtrType &pObject, const MemberFunctionType &fnFunction)
            : m_pObject(pObject), m_fnFunction(fnFunction)
        {

        }

    private:
        ClassPtrType        m_pObject;
        MemberFunctionType  m_fnFunction;

    public:
        FunctionBase *Clone() const
        {
            return new MemberFunctionHandler(m_pObject, m_fnFunction);
        }

        ReturnType Invoke()
        {
            return (m_pObject->*m_fnFunction)();
        }

#define XL_FUNCTION_MEMBERFUNCTION_INVOKE_PATTERN(n)                            \
                                                                                \
        typedef typename TLTypeAtNS<ParamList, n, EmptyType>::Type              \
                XL_FUNCTION_TYPENAME_LIST_PATTERN(n);                           \
                                                                                \
        ReturnType Invoke(XL_FUNCTION_TYPENAME_VARIABLE(n))                     \
        {                                                                       \
            return (m_pObject->*m_fnFunction)(XL_FUNCTION_VARIABLE_LIST(n));    \
        }                                                                       \

#define XL_FUNCTION_MEMBERFUNCTION_INVOKE(n)  XL_REPY(XL_FUNCTION_MEMBERFUNCTION_INVOKE_PATTERN, n, XL_NIL)

        XL_FUNCTION_MEMBERFUNCTION_INVOKE(XL_FUNCTION_DEFINE_MAX)
    };

    template <typename S>
    class Function;

    template <typename R>
    class Function<R ()>
    {
    private:
        typedef typename MakeTypeList<>::Type ParamList;

#define XL_FUCTION_IMPLEMENT_BODY()                                                                             \
                                                                                                                \
    private:                                                                                                    \
        typedef R                                   ReturnType;                                                 \
        typedef FunctionBase<ReturnType, ParamList> FunctionBaseType;                                           \
                                                                                                                \
    public:                                                                                                     \
        Function()                                                                                              \
            : m_pFunctionBase(nullptr)                                                                          \
        {                                                                                                       \
                                                                                                                \
        }                                                                                                       \
                                                                                                                \
        Function(const Function &that)                                                                          \
            : m_pFunctionBase(that.m_pFunctionBase)                                                             \
        {                                                                                                       \
                                                                                                                \
        }                                                                                                       \
                                                                                                                \
    public:                                                                                                     \
        template <typename F>                                                                                   \
        Function(F fnFunction)                                                                                  \
            : m_pFunctionBase(new FunctionHandler<ReturnType, ParamList, F>(fnFunction))                        \
        {                                                                                                       \
                                                                                                                \
        }                                                                                                       \
                                                                                                                \
        template <typename T, typename F>                                                                       \
        Function(T pObject, F pMemberFunction)                                                                  \
            : m_pFunctionBase(new MemberFunctionHandler<ReturnType, ParamList, T, F>(pObject, pMemberFunction)) \
        {                                                                                                       \
                                                                                                                \
        }                                                                                                       \
                                                                                                                \
    public:                                                                                                     \
        Function &operator = (const Function &that)                                                             \
        {                                                                                                       \
            this->m_pFunctionBase = that.m_pFunctionBase->Clone();                                              \
            return *this;                                                                                       \
        }                                                                                                       \
                                                                                                                \
    private:                                                                                                    \
        QIPtr<FunctionBaseType> m_pFunctionBase;                                                                \

        XL_FUCTION_IMPLEMENT_BODY()

    public:
        ReturnType operator()()
        {
            return m_pFunctionBase->Invoke();
        }
    };

#define XL_FUNCTION_IMPLEMENT_PATTERN(n)                                                \
                                                                                        \
    template <typename R, XL_FUNCTION_TYPENAME_DECLARE(n)>                              \
    class Function<R (XL_FUNCTION_TYPENAME_LIST(n))>                                    \
    {                                                                                   \
    private:                                                                            \
        typedef typename MakeTypeList<XL_FUNCTION_TYPENAME_LIST(n)>::Type ParamList;    \
                                                                                        \
        XL_FUCTION_IMPLEMENT_BODY()                                                     \
                                                                                        \
    public:                                                                             \
        ReturnType operator()(XL_FUNCTION_TYPENAME_VARIABLE(n))                         \
        {                                                                               \
            return m_pFunctionBase->Invoke(XL_FUNCTION_VARIABLE_LIST(n));               \
        }                                                                               \
    };                                                                                  \

#define XL_FUNCTION_IMPLEMENT(n)    XL_REPY(XL_FUNCTION_IMPLEMENT_PATTERN, n, XL_NIL)

    XL_FUNCTION_IMPLEMENT(XL_FUNCTION_DEFINE_MAX)

} // namespace xl

#endif // #ifndef __XLFUNCTION_H_83D86772_25B2_4625_8A4F_0C5EAAF1E93C_INCLUDED__
