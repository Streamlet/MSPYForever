//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlComModule.h
//    Author:      Streamlet
//    Create Time: 2012-09-09
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLCOMMODULE_H_89C4A369_6CBD_4316_947D_122F6E6C3F55_INCLUDED__
#define __XLCOMMODULE_H_89C4A369_6CBD_4316_947D_122F6E6C3F55_INCLUDED__


#include <xl/Meta/xlUtility.h>
#include <xl/Meta/xlScopeExit.h>
#include <xl/String/xlString.h>
#include <xl/Win32/Registry/xlRegistry.h>
#include <xl/Win32/COM/xlClassFactory.h>
#include <Windows.h>

namespace xl
{
    typedef IClassFactory *(*ClassFactoryCreator)();

    struct ClassEntry
    {
    	const CLSID        *pclsid;
        ClassFactoryCreator pfnCreator;
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
#define XL_CLASS_MAP_PRAGMA(c) __pragma(comment(linker, "/include:_LP_CLASS_ENTRY_" # c));
#elif defined(_M_IA64) || defined(_M_AMD64)
#define XL_CLASS_MAP_PRAGMA(c) __pragma(comment(linker, "/include:LP_CLASS_ENTRY_" # c));
#else
#error Unknown Platform. define XL_CLASS_MAP_PRAGMA
#endif

#define XL_DECLARE_COM_CLASS(c)                                                                     \
                                                                                                    \
    const xl::ClassEntry CLASS_ENTRY_##c = { &__uuidof(c), &xl::ClassFactory<c>::CreateFactory };   \
    extern "C" __declspec(allocate("XL_COM$__m")) __declspec(selectany)                             \
        const xl::ClassEntry * LP_CLASS_ENTRY_##c = &CLASS_ENTRY_##c;                               \
    XL_CLASS_MAP_PRAGMA(c)                                                                          \

    class ComModule : NonCopyable
    {
    public:
        ComModule(HMODULE hModule) : m_hModule(hModule), m_nGlobalRefCount(0), m_pTypeLib(nullptr)
        {
            TCHAR szModulePath[MAX_PATH] = {};
            GetModuleFileName(m_hModule, szModulePath, ARRAYSIZE(szModulePath));

            m_strModulePath = szModulePath;

            LoadTypeLib(szModulePath, &m_pTypeLib);
        }

        ~ComModule()
        {
            if (m_pTypeLib != nullptr)
            {
                m_pTypeLib->Release();
                m_pTypeLib = nullptr;
            }
        }

    public:
        HRESULT DllCanUnloadNow()
        {
            return m_nGlobalRefCount > 0 ? S_FALSE : S_OK;
        }

        HRESULT DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID *ppv)
        {
            for (const ClassEntry * const *ppEntry = &LP_CLASS_BEGIN + 1; ppEntry < &LP_CLASS_END; ++ppEntry)
            {
                if (*ppEntry == nullptr)
                {
                    continue;
                }

                if (rclsid == *(*ppEntry)->pclsid)
                {
                    IClassFactory *pClassFactory = (*ppEntry)->pfnCreator();
                    return pClassFactory->QueryInterface(riid, ppv);
                }
            }

            return CLASS_E_CLASSNOTAVAILABLE;
        }

        HRESULT DllRegisterServer()
        {
            return Register<&ComModule::RegisterTypeLib, &ComModule::RegisterComClass>();
        }

        HRESULT DllUnregisterServer()
        {
            return Register<&ComModule::UnregisterTypeLib, &ComModule::UnregisterComClass>();
        }

        HRESULT DllInstall(BOOL bInstall, _In_opt_ LPCTSTR lpszCmdLine)
        {
            return S_OK;
        }

    protected:
        template <bool (ComModule::*fnRegisterTypeLib)(TLIBATTR *), bool (ComModule::*fnRegisterComClass)(TYPEATTR *)>
        HRESULT Register()
        {
            if (m_pTypeLib == nullptr)
            {
                return E_FAIL;
            }

            TLIBATTR *pTLibAttr = nullptr;
            HRESULT hr = m_pTypeLib->GetLibAttr(&pTLibAttr);

            if (FAILED(hr))
            {
                return E_FAIL;
            }

            XL_ON_BLOCK_EXIT(m_pTypeLib, &ITypeLib::ReleaseTLibAttr, pTLibAttr);

            if (!(this->*fnRegisterTypeLib)(HKEY_LOCAL_MACHINE, pTLibAttr))
            {
                return E_FAIL;
            }

            UINT nCount = m_pTypeLib->GetTypeInfoCount();

            for (UINT i = 0; i < nCount; ++i)
            {
                ITypeInfo *pTypeInfo = nullptr;
                HRESULT hr = m_pTypeLib->GetTypeInfo(i, &pTypeInfo);

                if (FAILED(hr))
                {
                    continue;
                }

                XL_ON_BLOCK_EXIT((IUnknown *)pTypeInfo, &ITypeInfo::Release);

                TYPEATTR *pTypeAttr = nullptr;
                hr = pTypeInfo->GetTypeAttr(&pTypeAttr);

                if (FAILED(hr))
                {
                    continue;
                }

                XL_ON_BLOCK_EXIT(pTypeInfo, &ITypeInfo::ReleaseTypeAttr, pTypeAttr);

                switch (pTypeAttr->typekind)
                {
                case TKIND_COCLASS:
                    if (!(this->*fnRegisterComClass)(HKEY_LOCAL_MACHINE, pTypeAttr, pTLibAttr))
                    {
                        return E_FAIL;
                    }
                    break;
                default:
                    break;
                }
            }
            
            return S_OK;
        }

        bool RegisterTypeLib(HKEY hRootKey, TLIBATTR *pTLibAttr)
        {
            return true;
        }

        bool UnregisterTypeLib(HKEY hRootKey, TLIBATTR *pTLibAttr)
        {
            xl::Registry::DeleteKeyRecursion(HKEY_CLASSES_ROOT,
                                             _T("TypeLib\\{22935FC2-282E-4727-B40F-E55128EA1072}"));


            return true;
        
        }

        bool RegisterComClass(HKEY hRootKey, TYPEATTR *pTypeAttr, TLIBATTR *pTLibAttr)
        {
            return true;
        }

        bool UnregisterComClass(HKEY hRootKey, TYPEATTR *pTypeAttr, TLIBATTR *pTLibAttr)
        {
            return true;
        }

    public:
        HRESULT GetTypeInfo(_In_ REFIID riid, _Outptr_ ITypeInfo **ppTinfo)
        {
            return m_pTypeLib->GetTypeInfoOfGuid(riid, ppTinfo);
        }

    public:
        ULONG GlobalAddRef()
        {
            return (ULONG)InterlockedIncrement(&m_nGlobalRefCount);
        }

        ULONG GlobalRelease()
        {
            return (ULONG)InterlockedDecrement(&m_nGlobalRefCount);
        }

    private:
        HMODULE   m_hModule;
        String    m_strModulePath;
        LONG      m_nGlobalRefCount;
        ITypeLib *m_pTypeLib;
    };

    __declspec(selectany) ComModule *g_pComModule = nullptr;

} // namespace xl

#endif // #ifndef __XLCOMMODULE_H_89C4A369_6CBD_4316_947D_122F6E6C3F55_INCLUDED__
