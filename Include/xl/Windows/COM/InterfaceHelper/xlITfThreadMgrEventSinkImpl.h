//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfThreadMgrEventSinkImpl.h
//    Author:      Streamlet
//    Create Time: 2015-01-06
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFTHREADMGREVENTSINKIMPL_H_7345FEB4_6F04_49FA_8B02_96FD02309A02_INCLUDED__
#define __XLITFTHREADMGREVENTSINKIMPL_H_7345FEB4_6F04_49FA_8B02_96FD02309A02_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <msctf.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = ITfThreadMgrEventSink>
        class ITfThreadMgrEventSinkImpl : public IUnknownImpl<T>
        {
        public: // ITfThreadMgrEventSink Methods
            STDMETHODIMP OnInitDocumentMgr(ITfDocumentMgr *pdim)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP OnUninitDocumentMgr(ITfDocumentMgr *pdim)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP OnSetFocus(ITfDocumentMgr *pdimFocus, ITfDocumentMgr *pdimPrevFocus)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP OnPushContext(ITfContext *pic)
            {
                return E_NOTIMPL;
            }

            STDMETHODIMP OnPopContext(ITfContext *pic)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLITFTHREADMGREVENTSINKIMPL_H_7345FEB4_6F04_49FA_8B02_96FD02309A02_INCLUDED__
