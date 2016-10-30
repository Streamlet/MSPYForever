//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIDispatchExImpl.h
//    Author:      Streamlet
//    Create Time: 2016-01-03
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLIDISPATCHEXIMPL_H_C42982BA_3189_43BD_9099_3A2E803EF644_INCLUDED__
#define __XLIDISPATCHEXIMPL_H_C42982BA_3189_43BD_9099_3A2E803EF644_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIDispatchImpl.h"
#include <dispex.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = IDispatchEx>
        class IDispatchExImpl : public IDispatchImpl<T>
        {
        public: // IDispatchEx Methods
            STDMETHOD(GetDispID)(BSTR bstrName, DWORD grfdex, DISPID *pid)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(InvokeEx)(DISPID id,
                                LCID lcid,
                                WORD wFlags,
                                DISPPARAMS *pdp,
                                VARIANT *pvarRes,
                                EXCEPINFO *pei,
                                IServiceProvider *pspCaller)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(DeleteMemberByName)(BSTR bstrName, DWORD grfdex)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(DeleteMemberByDispID)(DISPID id)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetMemberProperties)(DISPID id, DWORD grfdexFetch, DWORD *pgrfdex)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetMemberName)(DISPID id, __RPC__deref_out_opt BSTR *pbstrName)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetNextDispID)(DWORD grfdex, DISPID id, DISPID *pid)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetNameSpaceParent)(IUnknown **ppunk)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLIDISPATCHEXIMPL_H_C42982BA_3189_43BD_9099_3A2E803EF644_INCLUDED__
