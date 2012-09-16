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


#include <Windows.h>
#include <Unknwn.h>

namespace xl
{
    struct InterfaceEntry
    {
    	const IID *piid;
        DWORD_PTR dwOffset;
    };

    struct IComModule
    {
    public:
        virtual ULONG STDMETHODCALLTYPE ObjectAddRef() PURE;
        virtual ULONG STDMETHODCALLTYPE ObjectRelease() PURE;

    public:
        virtual ULONG STDMETHODCALLTYPE LockAddRef() PURE;
        virtual ULONG STDMETHODCALLTYPE LockRelease() PURE;

    public:
        STDMETHOD(GetTypeInfo)(_In_ REFIID riid, _Outptr_ ITypeInfo **ppTinfo) PURE;

    public:
        STDMETHOD(DllCanUnloadNow)() PURE;
        STDMETHOD(DllGetClassObject)(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID *ppv) PURE;
        STDMETHOD(DllRegisterServer)() PURE;
        STDMETHOD(DllUnregisterServer)() PURE;
        STDMETHOD(DllInstall)(BOOL bInstall, _In_opt_ LPCTSTR lpszCmdLine) PURE;
    };

    __declspec(selectany) IComModule *g_pComModule = nullptr;

#define XL_COM_INTERFACE_BEGIN(c)                                                                       \
                                                                                                        \
        typedef c ComMapClass;                                                                          \
                                                                                                        \
        static const xl::InterfaceEntry *GetEntries()                                                   \
        {                                                                                               \
            static const xl::InterfaceEntry entries[] =                                                 \
            {                                                                                           \

#define XL_COM_INTERFACE(i)                                                                             \
                                                                                                        \
                { &__uuidof(i), (DWORD_PTR)((i *)(ComMapClass *)sizeof(nullptr)) - sizeof(nullptr) },   \

#define XL_COM_INTERFACE_END()                                                                          \
                                                                                                        \
                { nullptr, 0 }                                                                          \
            };                                                                                          \
                                                                                                        \
            return entries;                                                                             \
        }                                                                                               \
                                                                                                        \
        STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppvObject)                                     \
        {                                                                                               \
            return InternalQueryInterface(GetEntries(), riid, ppvObject);                               \
        }                                                                                               \
                                                                                                        \
        ULONG STDMETHODCALLTYPE AddRef()                                                                \
        {                                                                                               \
            return InternalAddRef();                                                                    \
        }                                                                                               \
                                                                                                        \
        ULONG STDMETHODCALLTYPE Release()                                                               \
        {                                                                                               \
            return InternalRelease();                                                                   \
        }                                                                                               \

    typedef IClassFactory *(*ClassFactoryCreator)();

    struct ClassEntry
    {
        const CLSID        *pClsid;
        ClassFactoryCreator pfnCreator;
        LPCTSTR             lpszClassDesc;
        LPCTSTR             lpszProgID;
        LPCTSTR             lpszVersion;
    };

#pragma section("XL_COM$__a", read)
#pragma section("XL_COM$__m", read)
#pragma section("XL_COM$__z", read)

    extern "C"
    {
        __declspec(selectany) __declspec(allocate("XL_COM$__a"))
            const xl::ClassEntry *LP_CLASS_BEGIN = nullptr;
        __declspec(selectany) __declspec(allocate("XL_COM$__z"))
            const xl::ClassEntry *LP_CLASS_END = nullptr;
    }

#if !defined(_M_IA64)
#pragma comment(linker, "/merge:XL_COM=.rdata")
#endif

#if defined(_M_IX86)
#define XL_CLASS_MAP_PRAGMA(class) __pragma(comment(linker, "/include:_LP_CLASS_ENTRY_" # class));
#elif defined(_M_IA64) || defined(_M_AMD64)
#define XL_CLASS_MAP_PRAGMA(class) __pragma(comment(linker, "/include:LP_CLASS_ENTRY_" # class));
#else
#error Unknown Platform. define XL_CLASS_MAP_PRAGMA
#endif

#define XL_DECLARE_COM_CLASS(class, desc, progid, version)                      \
                                                                                \
    const xl::ClassEntry CLASS_ENTRY_##class =                                  \
    {                                                                           \
        &__uuidof(class),                                                       \
        &xl::ClassFactory<class>::CreateFactory,                                \
        desc,                                                                   \
        progid,                                                                 \
        version                                                                 \
    };                                                                          \
    extern "C" __declspec(allocate("XL_COM$__m")) __declspec(selectany)         \
        const xl::ClassEntry * LP_CLASS_ENTRY_##class = &CLASS_ENTRY_##class;   \
    XL_CLASS_MAP_PRAGMA(class)                                                  \


} // namespace xl

#endif // #ifndef __XLCOMDEF_H_4B89206D_F947_4052_B92D_FD7B1E00CB8F_INCLUDED__
