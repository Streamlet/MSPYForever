//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIDocHostUIHandlerImpl.h
//    Author:      Streamlet
//    Create Time: 2012-09-01
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLIDOCHOSTUIHANDLERIMPL_H_2BC6BA59_38F5_435F_A863_FEC9D1C1CD6F_INCLUDED__
#define __XLIDOCHOSTUIHANDLERIMPL_H_2BC6BA59_38F5_435F_A863_FEC9D1C1CD6F_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <Mshtmhst.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = IDocHostUIHandler>
        class IDocHostUIHandlerImpl : public IUnknownImpl<T>
        {
        public: // IDocHostUIHandler Methods
            STDMETHOD(ShowContextMenu)(DWORD dwID, POINT *ppt, IUnknown *pcmdtReserved, IDispatch *pdispReserved)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetHostInfo)(DOCHOSTUIINFO *pInfo)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(ShowUI)(DWORD dwID,
                IOleInPlaceActiveObject *pActiveObject,
                IOleCommandTarget *pCommandTarget,
                IOleInPlaceFrame *pFrame,
                IOleInPlaceUIWindow *pDoc)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(HideUI)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(UpdateUI)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(EnableModeless)(BOOL fEnable)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(OnDocWindowActivate)(BOOL fActivate)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(OnFrameWindowActivate)(BOOL fActivate)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(ResizeBorder)(LPCRECT prcBorder, IOleInPlaceUIWindow *pUIWindow, BOOL fRameWindow)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(TranslateAccelerator)(LPMSG lpMsg, const GUID *pguidCmdGroup, DWORD nCmdID)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetOptionKeyPath)(LPOLESTR *pchKey, DWORD dw)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetDropTarget)(IDropTarget *pDropTarget, IDropTarget **ppDropTarget)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(GetExternal)(IDispatch **ppDispatch)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(TranslateUrl)(DWORD dwTranslate, OLECHAR *pchURLIn, OLECHAR **ppchURLOut)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(FilterDataObject)(IDataObject *pDO, IDataObject **ppDORet)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLIDOCHOSTUIHANDLERIMPL_H_2BC6BA59_38F5_435F_A863_FEC9D1C1CD6F_INCLUDED__
