//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIOleInPlaceFrameImpl.h
//    Author:      Streamlet
//    Create Time: 2012-09-01
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLIOLEINPLACEFRAMEIMPL_H_2A1FC107_C15E_4C42_B807_69FF9E40419C_INCLUDED__
#define __XLIOLEINPLACEFRAMEIMPL_H_2A1FC107_C15E_4C42_B807_69FF9E40419C_INCLUDED__


#include <oleidl.h>
#include <xl/Win32/COM/xlComDef.h>
#include <xl/Win32/COM/InterfaceHelper/xlIOleInPlaceUIWindowImpl.h>

namespace xl
{
    template <typename T = IOleInPlaceFrame>
    class IOleInPlaceFrameImpl : public IOleInPlaceUIWindowImpl<T>
    {
    public:
        XL_COM_INTERFACE_BEGIN()
            XL_COM_INTERFACE(IOleInPlaceFrame)
            XL_COM_INTERFACE_CHAIN(IOleInPlaceUIWindowImpl<T>)
        XL_COM_INTERFACE_END()

    public: // IOleInPlaceFrame Methods
        STDMETHOD(InsertMenus)(HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(SetMenu)(HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(RemoveMenus)(HMENU hmenuShared)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(SetStatusText)(LPCOLESTR pszStatusText)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(EnableModeless)(BOOL fEnable)
        {
            return E_NOTIMPL;
        }

        STDMETHOD(TranslateAccelerator)(LPMSG lpmsg, WORD wID)
        {
            return E_NOTIMPL;
        }
    };

} // namespace xl

#endif // #ifndef __XLIOLEINPLACEFRAMEIMPL_H_2A1FC107_C15E_4C42_B807_69FF9E40419C_INCLUDED__
