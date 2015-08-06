//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIOleObjectImpl.h
//    Author:      Streamlet
//    Create Time: 2012-09-01
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLIOLEOBJECTIMPL_H_2BA5B8AA_904B_41C5_AFA8_23A51DEECC4E_INCLUDED__
#define __XLIOLEOBJECTIMPL_H_2BA5B8AA_904B_41C5_AFA8_23A51DEECC4E_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIUnknownImpl.h"
#include <oleidl.h>

namespace xl
{
    namespace Windows
    {
        template <typename T = IOleWindow>
        class IOleWindowImpl : public IUnknownImpl<T>
        {
        public: // IOleWindow Methods
            STDMETHOD(GetWindow)(HWND *phwnd)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode)
            {
                return E_NOTIMPL;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLIOLEOBJECTIMPL_H_2BA5B8AA_904B_41C5_AFA8_23A51DEECC4E_INCLUDED__
