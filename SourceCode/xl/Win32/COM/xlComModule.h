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
#include <xl/Win32/File/IniFile.h>
#include <xl/Win32/COM/xlClassFactory.h>
#include <Windows.h>

namespace xl
{
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

    class ComModule : NonCopyable
    {
    public:
        ComModule(HMODULE hModule = nullptr, LPCTSTR lpLibName = nullptr) :
            m_hModule(hModule), m_strLibName(lpLibName), m_nGlobalRefCount(0), m_pTypeLib(nullptr)
        {
            TCHAR szModulePath[MAX_PATH] = {};
            GetModuleFileName(m_hModule, szModulePath, ARRAYSIZE(szModulePath));

            m_strModulePath = szModulePath;

            HRESULT hr = LoadTypeLib(szModulePath, &m_pTypeLib);

            if (FAILED(hr) || m_pTypeLib == nullptr)
            {
                return;
            }

            TLIBATTR *pTLibAttr = nullptr;
            hr = m_pTypeLib->GetLibAttr(&pTLibAttr);

            if (FAILED(hr) || pTLibAttr == nullptr)
            {
                return;
            }

            XL_ON_BLOCK_EXIT(m_pTypeLib, &ITypeLib::ReleaseTLibAttr, pTLibAttr);

            TCHAR szTLibID[40] = {};
            StringFromGUID2(pTLibAttr->guid, szTLibID, ARRAYSIZE(szTLibID));
            m_strLibID = szTLibID;

            TCHAR szVersion[40] = {};
            _stprintf_s(szVersion, _T("%u.%u"), (DWORD)pTLibAttr->wMajorVerNum, (DWORD)pTLibAttr->wMinorVerNum);
            m_strLibVersion = szVersion;
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

                if (rclsid == *(*ppEntry)->pClsid)
                {
                    IClassFactory *pClassFactory = (*ppEntry)->pfnCreator();
                    return pClassFactory->QueryInterface(riid, ppv);
                }
            }

            return CLASS_E_CLASSNOTAVAILABLE;
        }

        HRESULT DllRegisterServer()
        {
            if (!RegisterTypeLib(HKEY_LOCAL_MACHINE))
            {
                return E_FAIL;
            }

            if (!RegisterComClasses(HKEY_LOCAL_MACHINE))
            {
                return E_FAIL;
            }

            return S_OK;
        }

        HRESULT DllUnregisterServer()
        {
            if (!UnregisterComClasses(HKEY_LOCAL_MACHINE))
            {
                return E_FAIL;
            }

            if (!UnregisterTypeLib(HKEY_LOCAL_MACHINE))
            {
                return E_FAIL;
            }

            return S_OK;
        }

        HRESULT DllInstall(BOOL bInstall, _In_opt_ LPCTSTR lpszCmdLine)
        {
	        if (lpszCmdLine == nullptr)
	        {
                return E_INVALIDARG;
	        }

		    if (_tcsicmp(lpszCmdLine, _T("User")) == 0)
		    {
			    if (bInstall)
                {
                    if (!RegisterTypeLib(HKEY_CURRENT_USER))
                    {
                        return E_FAIL;
                    }

                    if (!RegisterComClasses(HKEY_CURRENT_USER))
                    {
                        return E_FAIL;
                    }

                    return S_OK;
                }
                else
                {
                    if (!UnregisterComClasses(HKEY_CURRENT_USER))
                    {
                        return E_FAIL;
                    }

                    if (!UnregisterTypeLib(HKEY_CURRENT_USER))
                    {
                        return E_FAIL;
                    }

                    return S_OK;
                }
		    }

		    if (_tcsicmp(lpszCmdLine, _T("INI")) == 0)
		    {
                LPCTSTR lpszIniFileName = _T("xlComReg.ini");
			    if (bInstall)
                {
                    if (!RegisterTypeLibToIni(lpszIniFileName))
                    {
                        return E_FAIL;
                    }

                    if (!RegisterComClassesToIni(lpszIniFileName))
                    {
                        return E_FAIL;
                    }

                    return S_OK;
                }
                else
                {
                    if (!UnregisterComClassesToIni(lpszIniFileName))
                    {
                        return E_FAIL;
                    }

                    if (!UnregisterTypeLibToIni(lpszIniFileName))
                    {
                        return E_FAIL;
                    }

                    return S_OK;
                }
		    }

            return E_FAIL;
        }

    protected:
        bool RegisterTypeLib(HKEY hRootKey)
        {
            String strPath;
            strPath += _T("Software\\Classes\\TypeLib\\");
            strPath += m_strLibID;
            strPath += _T("\\");
            strPath += m_strLibVersion;

            if (!Registry::SetString(hRootKey, strPath, _T(""), m_strLibName))
            {
                return false;
            }

            strPath += _T("\\0\\");
#ifdef _WIN64
            strPath += _T("Win64");
#else
            strPath += _T("Win32");
#endif

            if (!Registry::SetString(hRootKey, strPath, _T(""), m_strModulePath))
            {
                return false;
            }

            return true;
        }

        bool UnregisterTypeLib(HKEY hRootKey)
        {
            String strPath;
            strPath += _T("Software\\Classes\\TypeLib\\");
            strPath += m_strLibID;

            if (!Registry::DeleteKeyRecursion(hRootKey, strPath))
            {
                return false;
            }

            return true;        
        }

        bool RegisterComClasses(HKEY hRootKey)
        {
            for (const ClassEntry * const *ppEntry = &LP_CLASS_BEGIN + 1; ppEntry < &LP_CLASS_END; ++ppEntry)
            {
                if (*ppEntry == nullptr)
                {
                    continue;
                }

                TCHAR szClassID[40] = {};
                StringFromGUID2(*(*ppEntry)->pClsid, szClassID, ARRAYSIZE(szClassID));

                String strVersionIndependentProgID = (*ppEntry)->lpszProgID;
                String strProgID = strVersionIndependentProgID + _T(".") + (*ppEntry)->lpszVersion;

                String strPath;
                strPath = _T("Software\\Classes\\");
                String strClassIDPath = strPath + _T("CLSID\\") + szClassID;

                if (!Registry::SetString(hRootKey, strClassIDPath, _T(""), (*ppEntry)->lpszClassDesc))
                {
                    return false;
                }

                if (!Registry::SetString(hRootKey, strClassIDPath + _T("\\InprocServer32"), _T(""), m_strModulePath))
                {
                    return false;
                }

                if (!m_strLibID.Empty())
                {
                    if (!Registry::SetString(hRootKey, strClassIDPath + _T("\\TypeLib"), _T(""), m_strLibID))
                    {
                        return false;
                    }
                }

                if (!strProgID.Empty())
                {
                    if (!Registry::SetString(hRootKey, strClassIDPath + _T("\\ProgID"), _T(""), strProgID))
                    {
                        return false;
                    }

                    String strProgIDPath = strPath + strProgID;

                    if (!Registry::SetString(hRootKey, strProgIDPath, _T(""), (*ppEntry)->lpszClassDesc))
                    {
                        return false;
                    }

                    if (!Registry::SetString(hRootKey, strProgIDPath + _T("\\CLSID\\"), _T(""), szClassID))
                    {
                        return false;
                    }
                }

                if (!strVersionIndependentProgID.Empty())
                {
                    String strProgIDPath = strPath + strVersionIndependentProgID;

                    if (!Registry::SetString(hRootKey, strProgIDPath, _T(""), (*ppEntry)->lpszClassDesc))
                    {
                        return false;
                    }

                    if (!Registry::SetString(hRootKey, strProgIDPath + _T("\\CurVer\\"), _T(""), strProgID))
                    {
                        return false;
                    }

                    if (!Registry::SetString(hRootKey, strProgIDPath + _T("\\CLSID\\"), _T(""), szClassID))
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        bool UnregisterComClasses(HKEY hRootKey)
        {
            for (const ClassEntry * const *ppEntry = &LP_CLASS_BEGIN + 1; ppEntry < &LP_CLASS_END; ++ppEntry)
            {
                if (*ppEntry == nullptr)
                {
                    continue;
                }

                TCHAR szClassID[40] = {};
                StringFromGUID2(*(*ppEntry)->pClsid, szClassID, ARRAYSIZE(szClassID));

                String strVersionIndependentProgID = (*ppEntry)->lpszProgID;
                String strProgID = strVersionIndependentProgID + _T(".") + (*ppEntry)->lpszVersion;

                String strPath;
                strPath = _T("Software\\Classes\\");
                String strClassIDPath = strPath + _T("CLSID\\") + szClassID;

                if (!Registry::DeleteKeyRecursion(hRootKey, strClassIDPath))
                {
                    return false;
                }

                if (!strProgID.Empty())
                {
                    String strProgIDPath = strPath + strProgID;

                    if (!Registry::DeleteKeyRecursion(hRootKey, strProgIDPath))
                    {
                        return false;
                    }
                }

                if (!strVersionIndependentProgID.Empty())
                {
                    String strProgIDPath = strPath + strVersionIndependentProgID;

                    if (!Registry::DeleteKeyRecursion(hRootKey, strProgIDPath))
                    {
                        return false;
                    }
                }
            }

            return true;
        }

    protected:
        bool RegisterTypeLibToIni(LPCTSTR lpszFileName)
        {
            if (!IniFile::SetValue(lpszFileName, m_strLibID, _T("TypeLib"), m_strLibName))
            {
                return false;
            }

            if (!IniFile::SetValue(lpszFileName, m_strLibID, _T("Version"), m_strLibVersion))
            {
                return false;
            }

#ifdef _WIN64
            if (!IniFile::SetValue(lpszFileName, m_strLibID, _T("Win64"), m_strModulePath))
            {
                return false;
            }
#else
            if (!IniFile::SetValue(lpszFileName, m_strLibID, _T("Win32"), m_strModulePath))
            {
                return false;
            }
#endif

            return true;
        }

        bool UnregisterTypeLibToIni(LPCTSTR lpszFileName)
        {
            if (!IniFile::DeleteSection(lpszFileName, m_strLibID))
            {
                return false;
            }

            return true;        
        }

        bool RegisterComClassesToIni(LPCTSTR lpszFileName)
        {
            for (const ClassEntry * const *ppEntry = &LP_CLASS_BEGIN + 1; ppEntry < &LP_CLASS_END; ++ppEntry)
            {
                if (*ppEntry == nullptr)
                {
                    continue;
                }

                TCHAR szClassID[40] = {};
                StringFromGUID2(*(*ppEntry)->pClsid, szClassID, ARRAYSIZE(szClassID));

                String strVersionIndependentProgID = (*ppEntry)->lpszProgID;
                String strProgID = strVersionIndependentProgID + _T(".") + (*ppEntry)->lpszVersion;

                if (!IniFile::SetValue(lpszFileName, szClassID, _T("Class"), (*ppEntry)->lpszClassDesc))
                {
                    return false;
                }

                if (!IniFile::SetValue(lpszFileName, szClassID, _T("InprocServer32"), m_strModulePath))
                {
                    return false;
                }

                if (!m_strLibID.Empty())
                {
                    if (!IniFile::SetValue(lpszFileName, szClassID, _T("TypeLib"), m_strLibID))
                    {
                        return false;
                    }
                }

                if (!strProgID.Empty())
                {
                    if (!IniFile::SetValue(lpszFileName, szClassID, _T("ProgID"), strProgID))
                    {
                        return false;
                    }

                    if (!IniFile::SetValue(lpszFileName, strProgID, _T("Class"), (*ppEntry)->lpszClassDesc))
                    {
                        return false;
                    }

                    if (!IniFile::SetValue(lpszFileName, strProgID, _T("CLSID"), szClassID))
                    {
                        return false;
                    }
                }

                if (!strVersionIndependentProgID.Empty())
                {
                    if (!IniFile::SetValue(lpszFileName, strVersionIndependentProgID, _T("Class"), (*ppEntry)->lpszClassDesc))
                    {
                        return false;
                    }

                    if (!IniFile::SetValue(lpszFileName, strVersionIndependentProgID, _T("CurVer"), strProgID))
                    {
                        return false;
                    }

                    if (!IniFile::SetValue(lpszFileName, strVersionIndependentProgID, _T("CLSID"), szClassID))
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        bool UnregisterComClassesToIni(LPCTSTR lpszFileName)
        {
            for (const ClassEntry * const *ppEntry = &LP_CLASS_BEGIN + 1; ppEntry < &LP_CLASS_END; ++ppEntry)
            {
                if (*ppEntry == nullptr)
                {
                    continue;
                }

                TCHAR szClassID[40] = {};
                StringFromGUID2(*(*ppEntry)->pClsid, szClassID, ARRAYSIZE(szClassID));

                String strVersionIndependentProgID = (*ppEntry)->lpszProgID;
                String strProgID = strVersionIndependentProgID + _T(".") + (*ppEntry)->lpszVersion;

                if (!IniFile::DeleteSection(lpszFileName, szClassID))
                {
                    return false;
                }

                if (!strProgID.Empty())
                {
                    if (!IniFile::DeleteSection(lpszFileName, strProgID))
                    {
                        return false;
                    }
                }

                if (!strVersionIndependentProgID.Empty())
                {
                    if (!IniFile::DeleteSection(lpszFileName, strVersionIndependentProgID))
                    {
                        return false;
                    }
                }
            }

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
        String    m_strLibName;
        String    m_strModulePath;
        String    m_strLibID;
        String    m_strLibVersion;
        LONG      m_nGlobalRefCount;
        ITypeLib *m_pTypeLib;
    };

    __declspec(selectany) ComModule *g_pComModule = nullptr;

} // namespace xl

#endif // #ifndef __XLCOMMODULE_H_89C4A369_6CBD_4316_947D_122F6E6C3F55_INCLUDED__
