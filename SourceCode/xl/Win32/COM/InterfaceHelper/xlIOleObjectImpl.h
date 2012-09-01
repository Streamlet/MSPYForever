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

#include <oleidl.h>
#include <xl/Win32/COM/xlComDef.h>
#include <xl/Win32/COM/InterfaceHelper/xlIUnknownImpl.h>

namespace xl
{
    template <typename T>
    class IOleObjectImpl : public IOleObject,
                           public IUnknownImpl<T>
    {
    };

} // namespace xl


#endif // #ifndef __XLIOLEOBJECTIMPL_H_2BA5B8AA_904B_41C5_AFA8_23A51DEECC4E_INCLUDED__
