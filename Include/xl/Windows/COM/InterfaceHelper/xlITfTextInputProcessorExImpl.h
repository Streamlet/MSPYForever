//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfTextInputProcessorExImpl.h
//    Author:      Streamlet
//    Create Time: 2014-12-16
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFTEXTINPUTPROCESSOREXIMPL_H_91E181C4_A55D_43FE_88B8_8F93A4D62F6A_INCLUDED__
#define __XLITFTEXTINPUTPROCESSOREXIMPL_H_91E181C4_A55D_43FE_88B8_8F93A4D62F6A_INCLUDED__


#include "xlITfTextInputProcessorImpl.h"

namespace xl
{
    namespace Windows
    {
        template <typename T = ITfTextInputProcessorEx>
        class ITfTextInputProcessorExImpl : public ITfTextInputProcessorImpl<T>
        {
        public: // ITfTextInputProcessorEx Methods
            STDMETHODIMP ActivateEx(ITfThreadMgr *ptim, TfClientId tid, DWORD dwFlags)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLITFTEXTINPUTPROCESSOREXIMPL_H_91E181C4_A55D_43FE_88B8_8F93A4D62F6A_INCLUDED__
