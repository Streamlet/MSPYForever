//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIUnknownImpl.h
//    Author:      Streamlet
//    Create Time: 2012-09-01
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLIUNKNOWNIMPL_H_02B7268E_6F8B_47E7_BF44_1EDB0C545C42_INCLUDED__
#define __XLIUNKNOWNIMPL_H_02B7268E_6F8B_47E7_BF44_1EDB0C545C42_INCLUDED__


#include <Unknwn.h>
#include <Windows.h>
#include <xl/Win32/COM/xlComDef.h>

namespace xl
{
    template <typename T = IUnknown>
    class IUnknownImpl : public T
    {
    public:
        IUnknownImpl()
        {

        }

        ~IUnknownImpl()
        {
        
        }

    public:

#define XL_COM_INTERFACE_BEGIN(c)                                                                   \
                                                                                                    \
        typedef c ComClass;                                                                         \
                                                                                                    \
        static const InterfaceEntry *GetEntries()                                                   \
        {                                                                                           \
            static const InterfaceEntry entries[] =                                                 \
            {                                                                                       \

#define XL_COM_INTERFACE(i)                                                                         \
                                                                                                    \
                { &__uuidof(i), (DWORD_PTR)((i *)(ComClass *)sizeof(nullptr)) - sizeof(nullptr) },  \

#define XL_COM_INTERFACE_END()                                                                      \
                                                                                                    \
                { nullptr, 0 }                                                                      \
            };                                                                                      \
                                                                                                    \
            return entries;                                                                         \
        }                                                                                           \
                                                                                                    \
        STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppvObject)                                 \
        {                                                                                           \
            return InternalQueryInterface(GetEntries(), riid, ppvObject);                           \
        }                                                                                           \
                                                                                                    \
        ULONG STDMETHODCALLTYPE AddRef()                                                            \
        {                                                                                           \
            return InternalAddRef();                                                                \
        }                                                                                           \
                                                                                                    \
        ULONG STDMETHODCALLTYPE Release()                                                           \
        {                                                                                           \
            return InternalRelease();                                                               \
        }                                                                                           \

    };

} // namespace xl

#endif // #ifndef __XLIUNKNOWNIMPL_H_02B7268E_6F8B_47E7_BF44_1EDB0C545C42_INCLUDED__
