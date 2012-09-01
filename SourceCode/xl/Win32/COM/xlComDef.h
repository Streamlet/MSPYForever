//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlComDef.h
//    Author:      Streamlet
//    Create Time: 2012-09-01
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLCOMDEF_H_4B89206D_F947_4052_B92D_FD7B1E00CB8F_INCLUDED__
#define __XLCOMDEF_H_4B89206D_F947_4052_B92D_FD7B1E00CB8F_INCLUDED__


#include <unknwn.h>

namespace xl
{
#define XL_COM_INTERFACE_BEGIN()                                \
                                                                \
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppvObject) \
    {                                                           \
        *ppvObject = nullptr;                                   \

#define XL_COM_INTERFACE(i)             \
                                        \
        if (riid == __uuidof(i))        \
        {                               \
            *ppvObject = (i *)this;     \
            AddRef();                   \
            return S_OK;                \
        }                               \

#define XL_COM_INTERFACE_CHAIN(c)                           \
                                                            \
        if (SUCCEEDED(c::QueryInterface(riid, ppvObject)))  \
        {                                                   \
            return S_OK;                                    \
        }                                                   \

#define XL_COM_INTERFACE_END()       \
                                    \
        return E_NOINTERFACE;       \
    }                               \

} // namespace xl

#endif // #ifndef __XLCOMDEF_H_4B89206D_F947_4052_B92D_FD7B1E00CB8F_INCLUDED__
