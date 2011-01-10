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
    template <typename Signature>
    class Function
    {

    };

    template <typename R, typename Arg1>
    class Function1Base
    {
    public:
        virtual R operator ()(Arg1 arg1) = 0;
    };

    template <typename R, typename Arg1, typename T>
    class Function1 : public Function1Base<R, Arg1>
    {
    private:
        T m_tFunction;
    public:
        Function1(const T &tFunction)
            : m_tFunction(tFunction)
        {

        }
    public:
        R operator ()(Arg1 arg1)
        {
            return m_tFunction(arg1);
        }
    };

    template <typename R, typename Arg1, typename T>
    class Function1Obj : public Function1Base<R, Arg1>
    {
    private:
        T *m_pObject;
        R (T::*m_pFunction)(Arg1);

    public:
        Function1Obj(T *pObject, R (T::*pFunction)(Arg1))
            : m_pObject(pObject), m_pFunction(pFunction)
        {

        }
    public:
        R operator ()(Arg1 arg1)
        {
            return (m_pObject->*m_pFunction)(arg1);
        }
    };


    template <typename R, typename Arg1>
    class Function<R (Arg1)>
    {
    private:
        QIPtr<Function1Base<R, Arg1>> m_pFunction;

    public:
        template <typename T>
        Function(T tFunction)
        {
            m_pFunction = new Function1<R, Arg1, T>(tFunction);
        }

        template <typename T>
        Function(T *pObject, R (T::*pFunction)(Arg1))
        {
            m_pFunction = new Function1Obj<R, Arg1, T>(pObject, pFunction);
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
        R operator()(Arg1 arg1)
        {
            return (*m_pFunction)(arg1);
        }
    };


} // namespace xl

#endif // #ifndef __XLFUNCTION_H_83D86772_25B2_4625_8A4F_0C5EAAF1E93C_INCLUDED__
