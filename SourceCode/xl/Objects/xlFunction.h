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

namespace xl
{
    template <typename S>
    class Function;

    //------------------------------------------------------------------------------
    // R()
    //------------------------------------------------------------------------------

    template <typename R>
    class Function0Base
    {
    public:
        virtual R operator ()() = 0;
    };

    template <typename R, typename T>
    class Function0 : public Function0Base<R>
    {
    private:
        T m_tFunction;
    public:
        Function0(const T &tFunction)
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
    class Function0Obj : public Function0Base<R>
    {
    private:
        T *m_pObject;
        R (T::*m_pFunction)();

    public:
        Function0Obj(T *pObject, R (T::*pFunction)())
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
        QIPtr<Function0Base<R>> m_pFunction;

    public:
        template <typename T>
        Function(T tFunction)
        {
            m_pFunction = new Function0<R, T>(tFunction);
        }

        template <typename T>
        Function(T *pObject, R (T::*pFunction)())
        {
            m_pFunction = new Function0Obj<R, T>(pObject, pFunction);
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
    // void ()
    //------------------------------------------------------------------------------

    class Function0BaseVoid
    {
    public:
        virtual void operator ()() = 0;
    };

    template <typename T>
    class Function0Void : public Function0BaseVoid
    {
    private:
        T m_tFunction;
    public:
        Function0Void(const T &tFunction)
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
    class Function0ObjVoid : public Function0BaseVoid
    {
    private:
        T *m_pObject;
        void (T::*m_pFunction)();

    public:
        Function0ObjVoid(T *pObject, void (T::*pFunction)())
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
        QIPtr<Function0BaseVoid> m_pFunction;

    public:
        template <typename T>
        Function(T tFunction)
        {
            m_pFunction = new Function0Void<T>(tFunction);
        }

        template <typename T>
        Function(T *pObject, void (T::*pFunction)())
        {
            m_pFunction = new Function0ObjVoid<T>(pObject, pFunction);
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
    // R(T0)
    //------------------------------------------------------------------------------

    template <typename R, typename T0>
    class Function1Base
    {
    public:
        virtual R operator ()(T0) = 0;
    };

    template <typename R, typename T0, typename T>
    class Function1 : public Function1Base<R, T0>
    {
    private:
        T m_tFunction;
    public:
        Function1(const T &tFunction)
            : m_tFunction(tFunction)
        {

        }
    public:
        R operator ()(T0 v0)
        {
            return m_tFunction(v0);
        }
    };

    template <typename R, typename T0, typename T>
    class Function1Obj : public Function1Base<R, T0>
    {
    private:
        T *m_pObject;
        R (T::*m_pFunction)(T0);

    public:
        Function1Obj(T *pObject, R (T::*pFunction)(T0))
            : m_pObject(pObject), m_pFunction(pFunction)
        {

        }
    public:
        R operator ()(T0 v0)
        {
            return (m_pObject->*m_pFunction)(v0);
        }
    };

    template <typename R, typename T0>
    class Function<R (T0)>
    {
    private:
        QIPtr<Function1Base<R, T0>> m_pFunction;

    public:
        template <typename T>
        Function(T tFunction)
        {
            m_pFunction = new Function1<R, T0, T>(tFunction);
        }

        template <typename T>
        Function(T *pObject, R (T::*pFunction)(T0))
        {
            m_pFunction = new Function1Obj<R, T0, T>(pObject, pFunction);
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
        R operator()(T0 v0)
        {
            return (*m_pFunction)(v0);
        }
    };

    //------------------------------------------------------------------------------
    // void (T0)
    //------------------------------------------------------------------------------

    template <typename T0>
    class Function1BaseVoid
    {
    public:
        virtual void operator ()(T0) = 0;
    };

    template <typename T0, typename T>
    class Function1Void : public Function1BaseVoid<T0>
    {
    private:
        T m_tFunction;
    public:
        Function1Void(const T &tFunction)
            : m_tFunction(tFunction)
        {

        }
    public:
        void operator ()(T0 v0)
        {
            return m_tFunction(v0);
        }
    };

    template <typename T0, typename T>
    class Function1ObjVoid : public Function1BaseVoid<T0>
    {
    private:
        T *m_pObject;
        void (T::*m_pFunction)(T0);

    public:
        Function1ObjVoid(T *pObject, void (T::*pFunction)(T0))
            : m_pObject(pObject), m_pFunction(pFunction)
        {

        }
    public:
        void operator ()(T0 v0)
        {
            (m_pObject->*m_pFunction)(v0);
        }
    };

    template <typename T0>
    class Function<void (T0)>
    {
    private:
        QIPtr<Function1BaseVoid<T0>> m_pFunction;

    public:
        template <typename T>
        Function(T tFunction)
        {
            m_pFunction = new Function1Void<T0, T>(tFunction);
        }

        template <typename T>
        Function(T *pObject, void (T::*pFunction)(T0))
        {
            m_pFunction = new Function1ObjVoid<T0, T>(pObject, pFunction);
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
        void operator()(T0 v0)
        {
            (*m_pFunction)(v0);
        }
    };


} // namespace xl

#endif // #ifndef __XLFUNCTION_H_83D86772_25B2_4625_8A4F_0C5EAAF1E93C_INCLUDED__
