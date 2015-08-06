//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlDispatcher.h
//    Author:      Streamlet
//    Create Time: 2012-09-10
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLDISPATCHER_H_E1D7EF30_0567_480C_A31C_C0463DD8EC33_INCLUDED__
#define __XLDISPATCHER_H_E1D7EF30_0567_480C_A31C_C0463DD8EC33_INCLUDED__


#include "../xlWin32Ver.h"
#include "xlComDef.h"
#include "InterfaceHelper/xlIDispatchImpl.h"
#include <oaidl.h>
#include <oleauto.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = IDispatch>
        class Dispatcher : public IDispatchImpl<T>
        {
        public:
            Dispatcher() : m_pTypeInfo(nullptr)
            {
                if (g_pComModule != nullptr)
                {
                    g_pComModule->GetTypeInfo(__uuidof(T), &m_pTypeInfo);
                }
            }

            ~Dispatcher()
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

                if (iTInfo != 0)
                {
                    return DISP_E_BADINDEX;
                }

                if (m_pTypeInfo == nullptr)
                {
                    return E_FAIL;
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

                if (m_pTypeInfo == nullptr)
                {
                    return E_FAIL;
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

                if (m_pTypeInfo == nullptr)
                {
                    return E_FAIL;
                }

                return DispInvoke(this, m_pTypeInfo, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
            }

        private:
            ITypeInfo *m_pTypeInfo;
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLDISPATCHER_H_E1D7EF30_0567_480C_A31C_C0463DD8EC33_INCLUDED__
