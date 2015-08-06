//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfLangBarItem.h
//    Author:      Streamlet
//    Create Time: 2015-02-24
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFLANGBARITEM_H_B7ECDEF3_B73C_40E9_85F6_58D10368115F_INCLUDED__
#define __XLITFLANGBARITEM_H_B7ECDEF3_B73C_40E9_85F6_58D10368115F_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <ctfutb.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ITfLangBarItem>
        class ITfLangBarItemImpl : public IUnknownImpl<T>
        {
        public: // ITfLangBarItem Methods
            STDMETHODIMP GetInfo(TF_LANGBARITEMINFO *pInfo)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP GetStatus(DWORD *pdwStatus)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP Show(BOOL fShow)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP GetTooltipString(BSTR *pbstrToolTip)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLITFLANGBARITEM_H_B7ECDEF3_B73C_40E9_85F6_58D10368115F_INCLUDED__
