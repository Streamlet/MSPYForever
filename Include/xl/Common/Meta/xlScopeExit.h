//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlScopeExit.h
//    Author:      Streamlet
//    Create Time: 2012-04-22
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLSCOPEEXIT_H_8093BA2C_C4CA_4DB4_99C6_BAA42C6380F0_INCLUDED__
#define __XLSCOPEEXIT_H_8093BA2C_C4CA_4DB4_99C6_BAA42C6380F0_INCLUDED__


#include "../../xlDef.h"
#include "../Meta/xlBind.h"
#include "../Meta/xlMacros.h"

namespace xl
{
    class ScopeGuardImplBase
    {
    public:
        ScopeGuardImplBase() : m_bDismissed(false)
        {

        }

        ScopeGuardImplBase(ScopeGuardImplBase &that) :
            m_bDismissed(that.m_bDismissed)
        {
            that.Dismiss();
        }

        ~ScopeGuardImplBase()
        {

        }

    protected:
        template <typename J>
        static void StaticExecute(J &j)
        {
            if (!j.m_bDismissed)
            {
                j.Execute();
            }
        }

    public:
        void Dismiss() const
        {
            m_bDismissed = true;
        }

    private:
        mutable bool m_bDismissed;
    };

    typedef const ScopeGuardImplBase& ScopeGuard;

    template <typename F>
    class ScopeGuardImpl : public ScopeGuardImplBase
    {
    public:
        ScopeGuardImpl(F fn) :
            ScopeGuardImplBase(), m_fn(fn)
        {

        }

        ~ScopeGuardImpl()
        {
            StaticExecute(*this);
        }

        void Execute() 
        {
            m_fn();
        }

    private:
        F m_fn;
    };

    template <typename F> 
    inline ScopeGuardImpl<F> MakeGuard(F f)
    {
        return ScopeGuardImpl<F>(f);
    }

#define XL_ON_BLOCK_EXIT(...) ::xl::ScopeGuard XL_CONN(sg, __LINE__) = ::xl::MakeGuard(::xl::Bind(__VA_ARGS__))

} // namespace xl

#endif // #ifndef __XLSCOPEEXIT_H_8093BA2C_C4CA_4DB4_99C6_BAA42C6380F0_INCLUDED__
