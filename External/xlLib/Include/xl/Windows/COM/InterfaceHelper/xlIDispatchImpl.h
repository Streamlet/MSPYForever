//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIDispatchImpl.h
//    Author:      Streamlet
//    Create Time: 2012-09-01
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLIDISPATCHIMPL_H_7A443B6E_EA9F_486C_B4D3_771DB7560CF8_INCLUDED__
#define __XLIDISPATCHIMPL_H_7A443B6E_EA9F_486C_B4D3_771DB7560CF8_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <oaidl.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = IDispatch>
        class IDispatchImpl : public IUnknownImpl<T>
        {
        public: // IDispatch Methods
            STDMETHOD(GetTypeInfoCount)(UINT *pctinfo)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(Invoke)(DISPID dispIdMember,
                              REFIID riid,
                              LCID lcid,
                              WORD wFlags,
                              DISPPARAMS *pDispParams,
                              VARIANT *pVarResult,
                              EXCEPINFO *pExcepInfo,
                              UINT *puArgErr)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLIDISPATCHIMPL_H_7A443B6E_EA9F_486C_B4D3_771DB7560CF8_INCLUDED__
