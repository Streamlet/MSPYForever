//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlFunction.h
//    Author:      Streamlet
//    Create Time: 2011-01-09
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLFUNCTION_H_83D86772_25B2_4625_8A4F_0C5EAAF1E93C_INCLUDED__
#define __XLFUNCTION_H_83D86772_25B2_4625_8A4F_0C5EAAF1E93C_INCLUDED__


#include "../../xlDef.h"
#include "../Memory/xlSmartPtr.h"
#include "../Meta/xlMacros.h"
#include "../Meta/xlTypeList.h"

namespace xl
{
#ifndef XL_FUNCTION_DEFINE_MAX
#define XL_FUNCTION_DEFINE_MAX  20
#endif

#define XL_FUNCTION_TYPENAME_DECLARE_PATTERN(n)     typename A##n
#define XL_FUNCTION_TYPENAME_DECLARE(n)             XL_REPZ(XL_FUNCTION_TYPENAME_DECLARE_PATTERN, n, XL_COMMA)

#define XL_FUNCTION_TYPENAME_LIST_PATTERN(n)        A##n
#define XL_FUNCTION_TYPENAME_LIST(n)                XL_REPZ(XL_FUNCTION_TYPENAME_LIST_PATTERN, n, XL_COMMA)

#define XL_FUNCTION_TYPENAME_VARIABLE_PATTERN(n)    A##n a##n
#define XL_FUNCTION_TYPENAME_VARIABLE(n)            XL_REPZ(XL_FUNCTION_TYPENAME_VARIABLE_PATTERN, n, XL_COMMA)

#ifdef __XL_CPP11
#define XL_FUNCTION_VARIABLE_LIST_PATTERN(n)        static_cast<A##n &&>(a##n)
#else
#define XL_FUNCTION_VARIABLE_LIST_PATTERN(n)        a##n
#endif
#define XL_FUNCTION_VARIABLE_LIST(n)                XL_REPZ(XL_FUNCTION_VARIABLE_LIST_PATTERN, n, XL_COMMA)

    template <typename R, typename TL>
    class FunctionBase;

    template <typename R>
    class FunctionBase<R, XL_TYPELIST_0()>
    {
    public:
        virtual FunctionBase *Clone() const        = 0;
        virtual R Invoke()                         = 0;
        virtual bool IsEqual(FunctionBase *) const = 0;
        virtual ~FunctionBase() {}
    };

#define XL_FUNCTION_FUNCTORBASE_PATTERN(n)                                                          \
                                                                                                    \
    template <typename R, XL_FUNCTION_TYPENAME_DECLARE(n)>                                          \
    class FunctionBase<R, XL_EVAL(XL_CONN(XL_TYPELIST_, n), XL_FUNCTION_TYPENAME_LIST(n))>          \
    {                                                                                               \
    public:                                                                                         \
        virtual FunctionBase *Clone() const             = 0;                                        \
        virtual R Invoke(XL_FUNCTION_TYPENAME_LIST(n))  = 0;                                        \
        virtual bool IsEqual(FunctionBase *) const      = 0;                                        \
        virtual ~FunctionBase() {}                                                                  \
    };                                                                                              \

#define XL_FUNCTION_FUNCTORBASE(n)  XL_REPY(XL_FUNCTION_FUNCTORBASE_PATTERN, n, XL_NIL)

    XL_FUNCTION_FUNCTORBASE(XL_FUNCTION_DEFINE_MAX)

    template <typename R, typename P, typename F>
    class FunctionPointerHandler : public FunctionBase<R, P>
    {
    public:
        typedef R ReturnType;
        typedef P ParamList;
        typedef F FunctionType;

    public:
        FunctionPointerHandler(const FunctionType &fnFunctionPointer)
            : m_fnFunctionPointer(fnFunctionPointer)
        {

        }

    private:
        FunctionType m_fnFunctionPointer;

    public:
        FunctionBase *Clone() const
        {
            return m_fnFunctionPointer == nullptr ? nullptr : new FunctionPointerHandler(m_fnFunctionPointer);
        }

        ReturnType Invoke()
        {
            return m_fnFunctionPointer();
        }

        bool IsEqual(FunctionBase *pfn) const
        {
            if (pfn == nullptr)
            {
                return false;
            }

            if (this == pfn)
            {
                return true;
            }

            FunctionPointerHandler *pfnFunctionHandler = dynamic_cast<FunctionPointerHandler *>(pfn);

            if (pfnFunctionHandler == nullptr)
            {
                return false;
            }

            if (pfnFunctionHandler->m_fnFunctionPointer == m_fnFunctionPointer)
            {
                return true;
            }

            return false;
        }

#define XL_FUNCTION_FUNCTIONPOINTER_INVOKE_PATTERN(n)                       \
                                                                            \
        typedef typename TLTypeAtNS<ParamList, XL_DEC(n), EmptyType>::Type  \
                XL_FUNCTION_TYPENAME_LIST_PATTERN(n);                       \
                                                                            \
        ReturnType Invoke(XL_FUNCTION_TYPENAME_VARIABLE(n))                 \
        {                                                                   \
            return m_fnFunctionPointer(XL_FUNCTION_VARIABLE_LIST(n));       \
        }                                                                   \

#define XL_FUNCTION_FUNCTIONPOINTER_INVOKE(n)  XL_REPY(XL_FUNCTION_FUNCTIONPOINTER_INVOKE_PATTERN, n, XL_NIL)

        XL_FUNCTION_FUNCTIONPOINTER_INVOKE(XL_FUNCTION_DEFINE_MAX)
    };

    template <typename R, typename P, typename F>
    class FunctorHandler : public FunctionBase<R, P>
    {
    public:
        typedef R ReturnType;
        typedef P ParamList;
        typedef F FunctionType;

    public:
        FunctorHandler(const FunctionType &fnFunctor)
            : m_fnFunctor(fnFunctor)
        {

        }

    private:
        FunctionType m_fnFunctor;

    public:
        FunctionBase *Clone() const
        {
            return new FunctorHandler(m_fnFunctor);
        }

        ReturnType Invoke()
        {
            return m_fnFunctor();
        }

        bool IsEqual(FunctionBase *pfn) const
        {
            if (pfn == nullptr)
            {
                return false;
            }

            if (this == pfn)
            {
                return true;
            }

            // Functors are always unequal.

            return false;
        }

#define XL_FUNCTION_FUNCTOR_INVOKE_PATTERN(n)                               \
                                                                            \
        typedef typename TLTypeAtNS<ParamList, XL_DEC(n), EmptyType>::Type  \
                XL_FUNCTION_TYPENAME_LIST_PATTERN(n);                       \
                                                                            \
        ReturnType Invoke(XL_FUNCTION_TYPENAME_VARIABLE(n))                 \
        {                                                                   \
            return m_fnFunctor(XL_FUNCTION_VARIABLE_LIST(n));               \
        }                                                                   \

#define XL_FUNCTION_FUNCTOR_INVOKE(n)  XL_REPY(XL_FUNCTION_FUNCTOR_INVOKE_PATTERN, n, XL_NIL)

        XL_FUNCTION_FUNCTOR_INVOKE(XL_FUNCTION_DEFINE_MAX)
    };

    template <typename R, typename P, typename T, typename F>
    class MemberFunctionHandler : public FunctionBase<R, P>
    {
    public:
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
            return m_fnFunction == nullptr ? nullptr : new MemberFunctionHandler(m_pObject, m_fnFunction);
        }

        ReturnType Invoke()
        {
            return (m_pObject->*m_fnFunction)();
        }

        bool IsEqual(FunctionBase *pfn) const
        {
            if (pfn == nullptr)
            {
                return false;
            }

            if (this == pfn)
            {
                return true;
            }

            MemberFunctionHandler *pfnMemberFunctionHandler = dynamic_cast<MemberFunctionHandler *>(pfn);

            if (pfnMemberFunctionHandler == nullptr)
            {
                return false;
            }

            if (pfnMemberFunctionHandler->m_pObject == m_pObject
                && pfnMemberFunctionHandler->m_fnFunction == m_fnFunction)
            {
                return true;
            }

            return false;
        }

#define XL_FUNCTION_MEMBERFUNCTION_INVOKE_PATTERN(n)                            \
                                                                                \
        typedef typename TLTypeAtNS<ParamList, XL_DEC(n), EmptyType>::Type      \
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
    public:
        typedef typename MakeTypeList<>::Type ParamList;

#define XL_FUCTION_IMPLEMENT_BODY()                                                                                 \
                                                                                                                    \
    public:                                                                                                         \
        typedef R                                   ReturnType;                                                     \
        typedef FunctionBase<ReturnType, ParamList> FunctionBaseType;                                               \
                                                                                                                    \
    public:                                                                                                         \
        Function()                                                                                                  \
            : m_pFunctionBase(nullptr)                                                                              \
        {                                                                                                           \
                                                                                                                    \
        }                                                                                                           \
                                                                                                                    \
        Function(const Function &that)                                                                              \
            : m_pFunctionBase(that.m_pFunctionBase)                                                                 \
        {                                                                                                           \
                                                                                                                    \
        }                                                                                                           \
                                                                                                                    \
    public:                                                                                                         \
        Function(const void *)                                                                                      \
            : m_pFunctionBase(nullptr)                                                                              \
        {                                                                                                           \
                                                                                                                    \
        }                                                                                                           \
                                                                                                                    \
        template <typename F>                                                                                       \
        Function(F *pFunctionPointer)                                                                               \
            : m_pFunctionBase(nullptr)                                                                              \
        {                                                                                                           \
            if (pFunctionPointer != nullptr)                                                                        \
            {                                                                                                       \
                m_pFunctionBase = new FunctionPointerHandler<ReturnType, ParamList, F *>(pFunctionPointer);         \
            }                                                                                                       \
        }                                                                                                           \
                                                                                                                    \
        template <typename F>                                                                                       \
        Function(F fnFunctor)                                                                                       \
            : m_pFunctionBase(new FunctorHandler<ReturnType, ParamList, F>(fnFunctor))                              \
        {                                                                                                           \
                                                                                                                    \
        }                                                                                                           \
                                                                                                                    \
        template <typename T, typename F>                                                                           \
        Function(T pObject, F pMemberFunction)                                                                      \
            : m_pFunctionBase(nullptr)                                                                              \
        {                                                                                                           \
            if (pMemberFunction != nullptr)                                                                         \
            {                                                                                                       \
                m_pFunctionBase = new MemberFunctionHandler<ReturnType, ParamList, T, F>(pObject, pMemberFunction); \
            }                                                                                                       \
        }                                                                                                           \
                                                                                                                    \
    public:                                                                                                         \
        Function &operator = (const Function &that)                                                                 \
        {                                                                                                           \
            this->m_pFunctionBase = that.m_pFunctionBase->Clone();                                                  \
            return *this;                                                                                           \
        }                                                                                                           \
                                                                                                                    \
        Function &operator = (const void *)                                                                         \
        {                                                                                                           \
            this->m_pFunctionBase = nullptr;                                                                        \
            return *this;                                                                                           \
        }                                                                                                           \
                                                                                                                    \
        bool operator == (const void *) const                                                                       \
        {                                                                                                           \
            return this->m_pFunctionBase == nullptr;                                                                \
        }                                                                                                           \
                                                                                                                    \
        bool operator != (const void *) const                                                                       \
        {                                                                                                           \
            return this->m_pFunctionBase != nullptr;                                                                \
        }                                                                                                           \
                                                                                                                    \
        bool operator == (const Function &that) const                                                               \
        {                                                                                                           \
            if (this->m_pFunctionBase != nullptr && that.m_pFunctionBase != nullptr)                                \
            {                                                                                                       \
                return this->m_pFunctionBase->IsEqual(that.m_pFunctionBase.RawPointer());                           \
            }                                                                                                       \
            else                                                                                                    \
            {                                                                                                       \
                return this->m_pFunctionBase == nullptr && that.m_pFunctionBase == nullptr;                         \
            }                                                                                                       \
        }                                                                                                           \
                                                                                                                    \
        bool operator != (const Function &that) const                                                               \
        {                                                                                                           \
            return !*this == that;                                                                                  \
        }                                                                                                           \
                                                                                                                    \
    private:                                                                                                        \
        SharedPtr<FunctionBaseType> m_pFunctionBase;                                                                \

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
    public:                                                                             \
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
