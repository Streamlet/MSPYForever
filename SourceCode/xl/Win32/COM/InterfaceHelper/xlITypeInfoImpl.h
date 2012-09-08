//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITypeInfoImpl.h
//    Author:      Streamlet
//    Create Time: 2012-09-07
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITYPEINFOIMPL_H_BE0F75E0_E2D3_4D0E_AEFC_293D13F8DB08_INCLUDED__
#define __XLITYPEINFOIMPL_H_BE0F75E0_E2D3_4D0E_AEFC_293D13F8DB08_INCLUDED__


#include <oaidl.h>
#include <xl/Win32/COM/InterfaceHelper/xlIUnknownImpl.h>

namespace xl
{
    template <typename T = ITypeInfo>
    class ITypeInfoImpl : public IUnknownImpl<T>
    {
    public: // ITypeInfo Methods
        STDMETHOD(GetTypeAttr)(TYPEATTR **ppTypeAttr)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetTypeComp)(__RPC__deref_out_opt ITypeComp **ppTComp)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetFuncDesc)(UINT index, FUNCDESC **ppFuncDesc)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetVarDesc)(UINT index, VARDESC **ppVarDesc)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetNames)(MEMBERID memid, BSTR *rgBstrNames, UINT cMaxNames, UINT *pcNames)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetRefTypeOfImplType)(UINT index, __RPC__out HREFTYPE *pRefType)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetImplTypeFlags)( UINT index, __RPC__out INT *pImplTypeFlags)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetIDsOfNames)(__RPC__in_ecount(cNames) LPOLESTR *rgszNames,
                                 UINT cNames,
                                 MEMBERID *pMemId)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(Invoke)(PVOID pvInstance,
                          MEMBERID memid,
                          WORD wFlags,
                          DISPPARAMS *pDispParams,
                          VARIANT *pVarResult,
                          EXCEPINFO *pExcepInfo,
                          UINT *puArgErr)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetDocumentation)(MEMBERID memid,
                                    BSTR *pBstrName,
                                    BSTR *pBstrDocString,
                                    DWORD *pdwHelpContext,
                                    BSTR *pBstrHelpFile)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetDllEntry)(MEMBERID memid,
                               INVOKEKIND invKind,
                               BSTR *pBstrDllName,
                               BSTR *pBstrName,
                               WORD *pwOrdinal)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetRefTypeInfo)(HREFTYPE hRefType, __RPC__deref_out_opt ITypeInfo **ppTInfo)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(AddressOfMember)(MEMBERID memid, INVOKEKIND invKind, PVOID *ppv)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(CreateInstance)(IUnknown *pUnkOuter, REFIID riid, PVOID *ppvObj)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetMops)(MEMBERID memid, __RPC__deref_out_opt BSTR *pBstrMops)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(GetContainingTypeLib(ITypeLib **ppTLib, UINT *pIndex)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(ReleaseTypeAttr)(TYPEATTR *pTypeAttr)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(ReleaseFuncDesc)(FUNCDESC *pFuncDesc)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(ReleaseVarDesc)(VARDESC *pVarDesc)
        {
            return E_NOTIMPL;
        }
    };

} // namespace xl

#endif // #ifndef __XLITYPEINFOIMPL_H_BE0F75E0_E2D3_4D0E_AEFC_293D13F8DB08_INCLUDED__
