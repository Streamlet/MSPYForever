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


#include <oaidl.h>
#include <oleauto.h>
#include <xl/Win32/COM/InterfaceHelper/xlIUnknownImpl.h>
#include <xl/Win32/COM/xlComModule.h>

namespace xl
{
    template <typename T = IDispatch>
    class IDispatchImpl : public IUnknownImpl<T>
    {
    public:
        IDispatchImpl() : m_pTypeInfo(nullptr)
        {
            if (g_pComModule != nullptr)
            {
                g_pComModule->GetTypeInfo(__uuidof(ITypeInfo), &m_pTypeInfo);
            }
        }

        ~IDispatchImpl()
        {
            if (m_pTypeInfo != nullptr)
            {
                m_pTypeInfo->Release();
                m_pTypeInfo = nullptr;
            }
        
        }

    public: // IDispatch Methods
        STDMETHOD(GetTypeInfoCount)(UINT *pctinfo)
        {
            if (g_pComModule == nullptr)
            {
                return E_NOTIMPL;
            }

            if (pctinfo == nullptr)
            {
                return E_INVALIDARG;
            }

            *pctinfo = 1;
            return S_OK;
        }

        STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
        {
            if (g_pComModule == nullptr)
            {
                return E_NOTIMPL;
            }

            if (m_pTypeInfo == nullptr)
            {
                return E_FAIL;
            }

            if (iTInfo != 0)
            {
                return DISP_E_BADINDEX;
            }

            *ppTInfo = m_pTypeInfo;
            (*ppTInfo)->AddRef();

            return S_OK;
        }

        STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
        {
            if (g_pComModule == nullptr)
            {
                return E_NOTIMPL;
            }

            if (riid != IID_NULL)
            {
                return E_INVALIDARG;
            }

            return DispGetIDsOfNames(m_pTypeInfo, rgszNames, cNames, rgDispId);
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
            if (g_pComModule == nullptr)
            {
                return E_NOTIMPL;
            }

            if (riid != IID_NULL)
            {
                return E_INVALIDARG;
            }

            return DispInvoke(this, m_pTypeInfo, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr); 
        }

    private:
        ITypeInfo *m_pTypeInfo;
    };

} // namespace xl


#endif // #ifndef __XLIDISPATCHIMPL_H_7A443B6E_EA9F_486C_B4D3_771DB7560CF8_INCLUDED__
