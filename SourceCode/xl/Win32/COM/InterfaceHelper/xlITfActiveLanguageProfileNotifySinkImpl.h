//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlITfActiveLanguageProfileNotifySinkImpl.h
//    Author:      Streamlet
//    Create Time: 2014-12-16
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLITFACTIVELANGUAGEPROFILENOTIFYSINKIMPL_H_EB9EF7CD_7C2B_4D18_8071_479348D16273_INCLUDED__
#define __XLITFACTIVELANGUAGEPROFILENOTIFYSINKIMPL_H_EB9EF7CD_7C2B_4D18_8071_479348D16273_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <msctf.h>


namespace xl
{
    template <typename T = ITfActiveLanguageProfileNotifySink>
    class ITfActiveLanguageProfileNotifySinkImpl : public IUnknownImpl<T>
    {
    public: // ITfActiveLanguageProfileNotifySink Methods
        STDMETHODIMP OnActivated(_In_ REFCLSID clsid, _In_ REFGUID guidProfile, _In_ BOOL isActivated)
        {
            return E_NOTIMPL;
        }
    };

} // namespace xl


#endif // #ifndef __XLITFACTIVELANGUAGEPROFILENOTIFYSINKIMPL_H_EB9EF7CD_7C2B_4D18_8071_479348D16273_INCLUDED__
