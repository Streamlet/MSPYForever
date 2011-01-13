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
#include <xl/Objects/xlQIPtr.h>
#include <xl/Meta/xlMacros.h>
#include <xl/Meta/xlTypeList.h>

namespace xl
{
#define XL_FUNCTION_TYPENAME_DECLARE_PATTERN(n)     typename T##n
#define XL_FUNCTION_TYPENAME_DECLARE(n)             XL_REPZ(XL_FUNCTION_TYPENAME_DECLARE_PATTERN, n, XL_COMMA)

#define XL_FUNCTION_TYPENAME_LIST_PATTERN(n)        T##n
#define XL_FUNCTION_TYPENAME_LIST(n)                XL_REPZ(XL_FUNCTION_TYPENAME_LIST_PATTERN, n, XL_COMMA)

#define XL_FUNCTION_TYPENAME_VARIABLE_PATTERN(n)    T##n v##n
#define XL_FUNCTION_TYPENAME_VARIABLE(n)            XL_REPZ(XL_FUNCTION_TYPENAME_VARIABLE_PATTERN, n, XL_COMMA)

#define XL_FUNCTION_VARIABLE_LIST_PATTERN(n)        v##n
#define XL_FUNCTION_VARIABLE_LIST(n)                XL_REPZ(XL_FUNCTION_VARIABLE_LIST_PATTERN, n, XL_COMMA)

    template <typename S>
    class Function;

    //------------------------------------------------------------------------------
    // void ()
    //------------------------------------------------------------------------------

    class Function_BaseVoid
    {
    public:
        virtual void operator ()() = 0;
    };

    template <typename T>
    class Function_Void : public Function_BaseVoid
    {
    private:
        T m_tFunction;
    public:
        Function_Void(const T &tFunction)
            : m_tFunction(tFunction)
        {

        }
    public:
        void operator ()()
        {
            return m_tFunction();
        }
    };

    template <typename T>
    class Function_ObjVoid : public Function_BaseVoid
    {
    private:
        T *m_pObject;
        void (T::*m_pFunction)();

    public:
        Function_ObjVoid(T *pObject, void (T::*pFunction)())
            : m_pObject(pObject), m_pFunction(pFunction)
        {

        }
    public:
        void operator ()()
        {
            (m_pObject->*m_pFunction)();
        }
    };

    template <>
    class Function<void ()>
    {
    private:
        QIPtr<Function_BaseVoid> m_pFunction;

    public:
        template <typename T>
        Function(T tFunction)
        {
            m_pFunction = new Function_Void<T>(tFunction);
        }

        template <typename T>
        Function(T *pObject, void (T::*pFunction)())
        {
            m_pFunction = new Function_ObjVoid<T>(pObject, pFunction);
        }

    public:
        Function(const Function &that)
        {
            this->m_pFunction = that.m_pFunction;
        }

    public:
        Function &operator = (const Function &that)
        {
            this->m_pFunction = that.m_pFunction;
        }

    public:
        void operator()()
        {
            (*m_pFunction)();
        }
    };

    //------------------------------------------------------------------------------
    // R()
    //------------------------------------------------------------------------------

    template <typename R>
    class Function_Base
    {
    public:
        virtual R operator ()() = 0;
    };

    template <typename R, typename T>
    class Function_ : public Function_Base<R>
    {
    private:
        T m_tFunction;
    public:
        Function_(const T &tFunction)
            : m_tFunction(tFunction)
        {

        }
    public:
        R operator ()()
        {
            return m_tFunction();
        }
    };

    template <typename R, typename T>
    class Function_Obj : public Function_Base<R>
    {
    private:
        T *m_pObject;
        R (T::*m_pFunction)();

    public:
        Function_Obj(T *pObject, R (T::*pFunction)())
            : m_pObject(pObject), m_pFunction(pFunction)
        {

        }
    public:
        R operator ()()
        {
            return (m_pObject->*m_pFunction)();
        }
    };

    template <typename R>
    class Function<R ()>
    {
    private:
        QIPtr<Function_Base<R>> m_pFunction;

    public:
        template <typename T>
        Function(T tFunction)
        {
            m_pFunction = new Function_<R, T>(tFunction);
        }

        template <typename T>
        Function(T *pObject, R (T::*pFunction)())
        {
            m_pFunction = new Function_Obj<R, T>(pObject, pFunction);
        }

    public:
        Function(const Function &that)
        {
            this->m_pFunction = that.m_pFunction;
        }

    public:
        Function &operator = (const Function &that)
        {
            this->m_pFunction = that.m_pFunction;
        }

    public:
        R operator()()
        {
            return (*m_pFunction)();
        }
    };

    //------------------------------------------------------------------------------
    // void (T0, T0, ...)
    // R (T0, T1, ...)
    //------------------------------------------------------------------------------

#define XL_FUNCTION_GENERATOR(n)                                                                            \
                                                                                                            \
    template <XL_FUNCTION_TYPENAME_DECLARE(n)>                                                              \
    class Function##n##BaseVoid                                                                             \
    {                                                                                                       \
    public:                                                                                                 \
        virtual void operator ()(XL_FUNCTION_TYPENAME_LIST(n)) = 0;                                         \
    };                                                                                                      \
                                                                                                            \
    template <XL_FUNCTION_TYPENAME_DECLARE(n), typename T>                                                  \
    class Function##n##Void : public Function##n##BaseVoid<XL_FUNCTION_TYPENAME_LIST(n)>                    \
    {                                                                                                       \
    private:                                                                                                \
        T m_tFunction;                                                                                      \
    public:                                                                                                 \
        Function##n##Void(const T &tFunction)                                                               \
            : m_tFunction(tFunction)                                                                        \
        {                                                                                                   \
                                                                                                            \
        }                                                                                                   \
    public:                                                                                                 \
        void operator ()(XL_FUNCTION_TYPENAME_VARIABLE(n))                                                  \
        {                                                                                                   \
            return m_tFunction(XL_FUNCTION_VARIABLE_LIST(n));                                               \
        }                                                                                                   \
    };                                                                                                      \
                                                                                                            \
    template <XL_FUNCTION_TYPENAME_DECLARE(n), typename T>                                                  \
    class Function##n##ObjVoid : public Function##n##BaseVoid<XL_FUNCTION_TYPENAME_LIST(n)>                 \
    {                                                                                                       \
    private:                                                                                                \
        T *m_pObject;                                                                                       \
        void (T::*m_pFunction)(XL_FUNCTION_TYPENAME_LIST(n));                                               \
                                                                                                            \
    public:                                                                                                 \
        Function##n##ObjVoid(T *pObject, void (T::*pFunction)(XL_FUNCTION_TYPENAME_LIST(n)))                \
            : m_pObject(pObject), m_pFunction(pFunction)                                                    \
        {                                                                                                   \
                                                                                                            \
        }                                                                                                   \
    public:                                                                                                 \
        void operator ()(XL_FUNCTION_TYPENAME_VARIABLE(n))                                                  \
        {                                                                                                   \
            (m_pObject->*m_pFunction)(XL_FUNCTION_VARIABLE_LIST(n));                                        \
        }                                                                                                   \
    };                                                                                                      \
                                                                                                            \
    template <XL_FUNCTION_TYPENAME_DECLARE(n)>                                                              \
    class Function<void (XL_FUNCTION_TYPENAME_LIST(n))>                                                     \
    {                                                                                                       \
    private:                                                                                                \
        QIPtr<Function##n##BaseVoid<XL_FUNCTION_TYPENAME_LIST(n)>> m_pFunction;                             \
                                                                                                            \
    public:                                                                                                 \
        template <typename T>                                                                               \
        Function(T tFunction)                                                                               \
        {                                                                                                   \
            m_pFunction = new Function##n##Void<XL_FUNCTION_TYPENAME_LIST(n), T>(tFunction);                \
        }                                                                                                   \
                                                                                                            \
        template <typename T>                                                                               \
        Function(T *pObject, void (T::*pFunction)(XL_FUNCTION_TYPENAME_LIST(n)))                            \
        {                                                                                                   \
            m_pFunction = new Function##n##ObjVoid<XL_FUNCTION_TYPENAME_LIST(n), T>(pObject, pFunction);    \
        }                                                                                                   \
                                                                                                            \
    public:                                                                                                 \
        Function(const Function &that)                                                                      \
        {                                                                                                   \
            this->m_pFunction = that.m_pFunction;                                                           \
        }                                                                                                   \
                                                                                                            \
    public:                                                                                                 \
        Function &operator = (const Function &that)                                                         \
        {                                                                                                   \
            this->m_pFunction = that.m_pFunction;                                                           \
        }                                                                                                   \
                                                                                                            \
    public:                                                                                                 \
        void operator()(XL_FUNCTION_TYPENAME_VARIABLE(n))                                                   \
        {                                                                                                   \
            (*m_pFunction)(XL_FUNCTION_VARIABLE_LIST(n));                                                   \
        }                                                                                                   \
    };                                                                                                      \
                                                                                                            \
    template <typename R, XL_FUNCTION_TYPENAME_DECLARE(n)>                                                  \
    class Function##n##Base                                                                                 \
    {                                                                                                       \
    public:                                                                                                 \
        virtual R operator ()(XL_FUNCTION_TYPENAME_LIST(n)) = 0;                                            \
    };                                                                                                      \
                                                                                                            \
    template <typename R, XL_FUNCTION_TYPENAME_DECLARE(n), typename T>                                      \
    class Function##n## : public Function##n##Base<R, XL_FUNCTION_TYPENAME_LIST(n)>                         \
    {                                                                                                       \
    private:                                                                                                \
        T m_tFunction;                                                                                      \
    public:                                                                                                 \
        Function##n##(const T &tFunction)                                                                   \
            : m_tFunction(tFunction)                                                                        \
        {                                                                                                   \
                                                                                                            \
        }                                                                                                   \
    public:                                                                                                 \
        R operator ()(XL_FUNCTION_TYPENAME_VARIABLE(n))                                                     \
        {                                                                                                   \
            return m_tFunction(XL_FUNCTION_VARIABLE_LIST(n));                                               \
        }                                                                                                   \
    };                                                                                                      \
                                                                                                            \
    template <typename R, XL_FUNCTION_TYPENAME_DECLARE(n), typename T>                                      \
    class Function##n##Obj : public Function##n##Base<R, XL_FUNCTION_TYPENAME_LIST(n)>                      \
    {                                                                                                       \
    private:                                                                                                \
        T *m_pObject;                                                                                       \
        R (T::*m_pFunction)(XL_FUNCTION_TYPENAME_LIST(n));                                                  \
                                                                                                            \
    public:                                                                                                 \
        Function##n##Obj(T *pObject, R (T::*pFunction)(XL_FUNCTION_TYPENAME_LIST(n)))                       \
            : m_pObject(pObject), m_pFunction(pFunction)                                                    \
        {                                                                                                   \
                                                                                                            \
        }                                                                                                   \
    public:                                                                                                 \
        R operator ()(XL_FUNCTION_TYPENAME_VARIABLE(n))                                                     \
        {                                                                                                   \
            return (m_pObject->*m_pFunction)(XL_FUNCTION_VARIABLE_LIST(n));                                 \
        }                                                                                                   \
    };                                                                                                      \
                                                                                                            \
    template <typename R, XL_FUNCTION_TYPENAME_DECLARE(n)>                                                  \
    class Function<R (XL_FUNCTION_TYPENAME_LIST(n))>                                                        \
    {                                                                                                       \
    private:                                                                                                \
        QIPtr<Function##n##Base<R, XL_FUNCTION_TYPENAME_LIST(n)>> m_pFunction;                              \
                                                                                                            \
    public:                                                                                                 \
        template <typename T>                                                                               \
        Function(T tFunction)                                                                               \
        {                                                                                                   \
            m_pFunction = new Function##n##<R, XL_FUNCTION_TYPENAME_LIST(n), T>(tFunction);                 \
        }                                                                                                   \
                                                                                                            \
        template <typename T>                                                                               \
        Function(T *pObject, R (T::*pFunction)(XL_FUNCTION_TYPENAME_LIST(n)))                               \
        {                                                                                                   \
            m_pFunction = new Function##n##Obj<R, XL_FUNCTION_TYPENAME_LIST(n), T>(pObject, pFunction);     \
        }                                                                                                   \
                                                                                                            \
    public:                                                                                                 \
        Function(const Function &that)                                                                      \
        {                                                                                                   \
            this->m_pFunction = that.m_pFunction;                                                           \
        }                                                                                                   \
                                                                                                            \
    public:                                                                                                 \
        Function &operator = (const Function &that)                                                         \
        {                                                                                                   \
            this->m_pFunction = that.m_pFunction;                                                           \
        }                                                                                                   \
                                                                                                            \
    public:                                                                                                 \
        R operator()(XL_FUNCTION_TYPENAME_VARIABLE(n))                                                      \
        {                                                                                                   \
            return (*m_pFunction)(XL_FUNCTION_VARIABLE_LIST(n));                                            \
        }                                                                                                   \
    };                                                                                                      \

    XL_REPX(XL_FUNCTION_GENERATOR, 99, XL_NIL)

} // namespace xl

#endif // #ifndef __XLFUNCTION_H_83D86772_25B2_4625_8A4F_0C5EAAF1E93C_INCLUDED__
