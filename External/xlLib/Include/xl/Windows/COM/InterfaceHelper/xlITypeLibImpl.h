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


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <oaidl.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ITypeLib>
        class ITypeLibImpl : public IUnknownImpl<T>
        {
        public: // ITypeLib Methods
            STDMETHOD(GetTypeInfoCount)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetTypeInfo)(UINT index, ITypeInfo **ppTInfo)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetTypeInfoType)(UINT index, TYPEKIND *pTKind)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetTypeInfoOfGuid)(REFGUID guid,
                                         ITypeInfo **ppTinfo)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetLibAttr)(TLIBATTR **ppTLibAttr)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetTypeComp)(ITypeComp **ppTComp)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetDocumentation)(INT index,
                                        BSTR *pBstrName,
                                        BSTR *pBstrDocString,
                                        DWORD *pdwHelpContext,
                                        BSTR *pBstrHelpFile)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(IsName)(LPOLESTR szNameBuf,
                              ULONG lHashVal,
                              BOOL *pfName)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(FindName)(LPOLESTR szNameBuf,
                                ULONG lHashVal,
                                ITypeInfo **ppTInfo,
                                MEMBERID *rgMemId,
                                USHORT *pcFound)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(ReleaseTLibAttr)(TLIBATTR *pTLibAttr)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLITYPEINFOIMPL_H_BE0F75E0_E2D3_4D0E_AEFC_293D13F8DB08_INCLUDED__
