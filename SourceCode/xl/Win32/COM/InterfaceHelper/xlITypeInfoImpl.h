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
            return E_NOTEMPL;
        }
        
        STDMETHOD(GetTypeComp)(__RPC__deref_out_opt ITypeComp **ppTComp)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(GetFuncDesc)(UINT index, FUNCDESC **ppFuncDesc)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(GetVarDesc)(UINT index, VARDESC **ppVarDesc)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(GetNames)( MEMBERID memid, BSTR *rgBstrNames, UINT cMaxNames, UINT *pcNames)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(GetRefTypeOfImplType)(UINT index, __RPC__out HREFTYPE *pRefType)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(GetImplTypeFlags)( UINT index, __RPC__out INT *pImplTypeFlags)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(GetIDsOfNames)(__RPC__in_ecount(cNames) LPOLESTR *rgszNames,
                                 UINT cNames,
                                 MEMBERID *pMemId)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(Invoke)(PVOID pvInstance,
                          MEMBERID memid,
                          WORD wFlags,
                          DISPPARAMS *pDispParams,
                          VARIANT *pVarResult,
                          EXCEPINFO *pExcepInfo,
                          UINT *puArgErr)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(GetDocumentation)(MEMBERID memid,
                                    BSTR *pBstrName,
                                    BSTR *pBstrDocString,
                                    DWORD *pdwHelpContext,
                                    BSTR *pBstrHelpFile)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(GetDllEntry)(MEMBERID memid,
                               INVOKEKIND invKind,
                               BSTR *pBstrDllName,
                               BSTR *pBstrName,
                               WORD *pwOrdinal)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(GetRefTypeInfo)(HREFTYPE hRefType, __RPC__deref_out_opt ITypeInfo **ppTInfo)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(AddressOfMember)(MEMBERID memid, INVOKEKIND invKind, PVOID *ppv)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(CreateInstance)(IUnknown *pUnkOuter, REFIID riid, PVOID *ppvObj)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(GetMops)(MEMBERID memid, __RPC__deref_out_opt BSTR *pBstrMops)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(GetContainingTypeLib(ITypeLib **ppTLib, UINT *pIndex)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(ReleaseTypeAttr)(TYPEATTR *pTypeAttr)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(ReleaseFuncDesc)(FUNCDESC *pFuncDesc)
        {
            return E_NOTEMPL;
        }
        
        STDMETHOD(ReleaseVarDesc)(VARDESC *pVarDesc)
        {
            return E_NOTEMPL;
        }
    };

} // namespace xl

#endif // #ifndef __XLITYPEINFOIMPL_H_BE0F75E0_E2D3_4D0E_AEFC_293D13F8DB08_INCLUDED__
