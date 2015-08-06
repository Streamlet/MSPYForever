//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfLangBarItemButtonImpl.h
//    Author:      Streamlet
//    Create Time: 2015-02-24
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFLANGBARITEMBUTTONIMPL_H_511FC759_FA0A_4EBA_A28A_FFBD9344A008_INCLUDED__
#define __XLITFLANGBARITEMBUTTONIMPL_H_511FC759_FA0A_4EBA_A28A_FFBD9344A008_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlITfLangBarItemImpl.h"

namespace xl
{
    namespace Windows
    {
        template <typename T = ITfLangBarItemButton>
        class ITfLangBarItemButtonImpl : public ITfLangBarItemImpl<T>
        {
        public: // ITfLangBarItemButton Methods
            STDMETHODIMP OnClick(TfLBIClick click, POINT pt, __RPC__in const RECT *prcArea)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP InitMenu(ITfMenu *pMenu)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP OnMenuSelect(UINT wID)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP GetIcon(HICON *phIcon)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP GetText(BSTR *pbstrText)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLITFLANGBARITEMBUTTONIMPL_H_511FC759_FA0A_4EBA_A28A_FFBD9344A008_INCLUDED__
