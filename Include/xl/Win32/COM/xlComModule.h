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


#include "../../Meta/xlAssert.h"
#include "../../Meta/xlScopeExit.h"
#include "../../Meta/xlUtility.h"
#include "../../String/xlString.h"
#include "../File/xlIniFile.h"
#include "../Registry/xlRegistry.h"
#include "../xlWin32Ver.h"
#include "xlComDef.h"
#include "xlClassFactory.h"
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

namespace xl
{
    class ComModule : public IComModule
    {
    public:
        ComModule(HMODULE hModule = nullptr, LPCTSTR lpLibName = nullptr) :
            m_hModule(hModule),
            m_strLibName(lpLibName),
            m_nObjectRefCount(0),
            m_nLockRefCount(0),
            m_pTypeLib(nullptr),
            m_pTLibAttr(nullptr),
            m_dwThreadId(0)
        {
            TCHAR szModulePath[MAX_PATH] = {};
            GetModuleFileName(m_hModule, szModulePath, ARRAYSIZE(szModulePath));

            TCHAR szModulePathCanonicalized[MAX_PATH] = {};
            
            if (PathCanonicalize(szModulePathCanonicalized, szModulePath))
            {
                m_strModulePath = szModulePathCanonicalized;
            }
            else
            {
                m_strModulePath = szModulePath;
            }

            HRESULT hr = LoadTypeLib(m_strModulePath, &m_pTypeLib);

            if (FAILED(hr) || m_pTypeLib == nullptr)
            {
                XL_ASSERT(false);
            }

            hr = m_pTypeLib->GetLibAttr(&m_pTLibAttr);

            if (FAILED(hr) || m_pTLibAttr == nullptr)
            {
                XL_ASSERT(false);
            }

            TCHAR szTLibID[40] = {};
            StringFromGUID2(m_pTLibAttr->guid, szTLibID, ARRAYSIZE(szTLibID));
            m_strLibID = szTLibID;

            TCHAR szVersion[40] = {};
            _stprintf_s(szVersion, _T("%u.%u"), (DWORD)m_pTLibAttr->wMajorVerNum, (DWORD)m_pTLibAttr->wMinorVerNum);
            m_strLibVersion = szVersion;
        }

        ~ComModule()
        {
            if (m_pTLibAttr != nullptr)
            {
                m_pTypeLib->ReleaseTLibAttr(m_pTLibAttr);
                m_pTLibAttr = nullptr;
            }

            if (m_pTypeLib != nullptr)
            {
                m_pTypeLib->Release();
                m_pTypeLib = nullptr;
            }
        }

    public:
        ULONG STDMETHODCALLTYPE ObjectAddRef()
        {
            return (ULONG)InterlockedIncrement(&m_nObjectRefCount);
        }

        ULONG STDMETHODCALLTYPE ObjectRelease()
        {
            ULONG lResult = (ULONG)InterlockedDecrement(&m_nObjectRefCount);

            if (m_dwThreadId != 0 && CanUnloadNow())
            {
                PostThreadMessage(m_dwThreadId, WM_QUIT, 0, 0);
            }

            return lResult;
        }

    public:
        ULONG STDMETHODCALLTYPE LockAddRef()
        {
            return (ULONG)InterlockedIncrement(&m_nLockRefCount);
        }

        ULONG STDMETHODCALLTYPE LockRelease()
        {
            ULONG lResult = (ULONG)InterlockedDecrement(&m_nLockRefCount);

            if (m_dwThreadId != 0 && CanUnloadNow())
            {
                PostThreadMessage(m_dwThreadId, WM_QUIT, 0, 0);
            }

            return lResult;
        }

    public:
        STDMETHODIMP GetTypeInfo(REFIID riid, ITypeInfo **ppTinfo)
        {
            return m_pTypeLib->GetTypeInfoOfGuid(riid, ppTinfo);
        }

    public:
        STDMETHODIMP DllCanUnloadNow()
        {
            return CanUnloadNow() ? S_OK : S_FALSE;
        }

        STDMETHODIMP DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
        {
            for (const ClassEntry * const *ppEntry = &LP_CLASS_BEGIN + 1; ppEntry < &LP_CLASS_END; ++ppEntry)
            {
                if (*ppEntry == nullptr)
                {
                    continue;
                }

                if (rclsid == *(*ppEntry)->pClsid)
                {
                    IClassFactory *pClassFactory = (*ppEntry)->pfnCreator(true);
                    return pClassFactory->QueryInterface(riid, ppv);
                }
            }

            return CLASS_E_CLASSNOTAVAILABLE;
        }

        STDMETHODIMP DllRegisterServer()
        {
            xl::ScopeGuard sgUnregisterTypeLib = xl::MakeGuard(xl::Bind(this, &ComModule::UnregisterTypeLib, HKEY_LOCAL_MACHINE));
            xl::ScopeGuard sgUnregisterComClassed = xl::MakeGuard(xl::Bind(this, &ComModule::UnregisterComClasses, HKEY_LOCAL_MACHINE));

            if (!RegisterTypeLib(HKEY_LOCAL_MACHINE))
            {
                return E_FAIL;
            }

            if (!RegisterComClasses(HKEY_LOCAL_MACHINE))
            {
                return E_FAIL;
            }

            sgUnregisterComClassed.Dismiss();
            sgUnregisterTypeLib.Dismiss();

            return S_OK;
        }

        STDMETHODIMP DllUnregisterServer()
        {
            bool bSuccess = true;

            if (!UnregisterComClasses(HKEY_LOCAL_MACHINE))
            {
                bSuccess = false;
            }

            if (!UnregisterTypeLib(HKEY_LOCAL_MACHINE))
            {
                bSuccess = false;
            }

            return bSuccess ? S_OK : E_FAIL;
        }

        STDMETHODIMP DllInstall(BOOL bInstall, LPCTSTR lpszCmdLine)
        {
            if (lpszCmdLine == nullptr)
            {
                return E_INVALIDARG;
            }

            String strCmdLine = lpszCmdLine;
            String strCmdLineLower = strCmdLine.ToLower();

            if (strCmdLineLower == _T("user"))
            {
                if (bInstall)
                {
                    xl::ScopeGuard sgUnregisterTypeLib = xl::MakeGuard(xl::Bind(this, &ComModule::UnregisterTypeLib, HKEY_CURRENT_USER));
                    xl::ScopeGuard sgUnregisterComClassed = xl::MakeGuard(xl::Bind(this, &ComModule::UnregisterComClasses, HKEY_CURRENT_USER));

                    if (!RegisterTypeLib(HKEY_CURRENT_USER))
                    {
                        return E_FAIL;
                    }

                    if (!RegisterComClasses(HKEY_CURRENT_USER))
                    {
                        return E_FAIL;
                    }

                    sgUnregisterComClassed.Dismiss();
                    sgUnregisterTypeLib.Dismiss();

                    return S_OK;
                }
                else
                {
                    bool bSuccess = true;

                    if (!UnregisterComClasses(HKEY_CURRENT_USER))
                    {
                        bSuccess = false;
                    }

                    if (!UnregisterTypeLib(HKEY_CURRENT_USER))
                    {
                        bSuccess = false;
                    }

                    return bSuccess ? S_OK : E_FAIL;
                }
            }

            if (strCmdLineLower == _T("ini") || strCmdLineLower.IndexOf(_T("ini:")) == 0)
            {
                LPCTSTR DEFAULT_INI_FILENAME = _T("xlComReg.ini");
                String strIniFileName = DEFAULT_INI_FILENAME;

                if (strCmdLine.Length() > 4)
                {
                    strIniFileName = strCmdLine.SubString(4);

                    if (strIniFileName[strIniFileName.Length() - 1] == _T('\\'))
                    {
                        strIniFileName += DEFAULT_INI_FILENAME;
                    }
                }

                if (bInstall)
                {
                    xl::ScopeGuard sgUnregisterTypeLib = xl::MakeGuard(xl::Bind(this, &ComModule::UnregisterTypeLibFromIni, strIniFileName));
                    xl::ScopeGuard sgUnregisterComClassed = xl::MakeGuard(xl::Bind(this, &ComModule::UnregisterComClassesFromIni, strIniFileName));

                    if (!RegisterTypeLibToIni(strIniFileName))
                    {
                        return E_FAIL;
                    }

                    if (!RegisterComClassesToIni(strIniFileName))
                    {
                        return E_FAIL;
                    }

                    sgUnregisterComClassed.Dismiss();
                    sgUnregisterTypeLib.Dismiss();

                    return S_OK;
                }
                else
                {
                    bool bSuccess = true;

                    if (!UnregisterComClassesFromIni(strIniFileName))
                    {
                        bSuccess = false;
                    }

                    if (!UnregisterTypeLibFromIni(strIniFileName))
                    {
                        bSuccess = false;
                    }

                    return bSuccess ? S_OK : E_FAIL;
                }
            }

            return E_FAIL;
        }

    public:
        STDMETHODIMP ExeRegisterServer()
        {
            if (!RegisterTypeLib(HKEY_LOCAL_MACHINE))
            {
                return E_FAIL;
            }

            if (!RegisterComClasses(HKEY_LOCAL_MACHINE, false))
            {
                return E_FAIL;
            }

            return S_OK;
        }
        
        STDMETHODIMP ExeUnregisterServer()
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
        
        STDMETHODIMP ExeRegisterClassObject()
        {
            HRESULT hr = CoInitialize(nullptr);

            if (FAILED(hr))
            {
                return hr;
            }

            for (const ClassEntry * const *ppEntry = &LP_CLASS_BEGIN + 1; ppEntry < &LP_CLASS_END; ++ppEntry)
            {
                if (*ppEntry == nullptr)
                {
                    continue;
                }

                IClassFactory *pClassFactory = (*ppEntry)->pfnCreator(false);

                if (pClassFactory == nullptr)
                {
                    return E_FAIL;
                }

                IUnknown *pUnk = nullptr;
                HRESULT hr = pClassFactory->QueryInterface(__uuidof(IUnknown), (LPVOID *)&pUnk);

                if (FAILED(hr) || pUnk == nullptr)
                {
                    return hr;
                }

                DWORD dwRegister = 0;
                hr = CoRegisterClassObject(*(*ppEntry)->pClsid,
                                           pUnk,
                                           CLSCTX_LOCAL_SERVER,
                                           REGCLS_MULTIPLEUSE,
                                           &dwRegister);
                pUnk->Release();

                if (FAILED(hr))
                {
                    return hr;
                }

                m_arrRegClassObjects.PushBack(dwRegister);
            }

            m_dwThreadId = GetCurrentThreadId();

            return S_OK;
        }
        
        STDMETHODIMP ExeUnregisterClassObject()
        {
            for (auto it = m_arrRegClassObjects.Begin(); it != m_arrRegClassObjects.End(); ++it)
            {
                CoRevokeClassObject(*it);
            }

            m_arrRegClassObjects.Clear();

            CoUninitialize();

            return S_OK;
        }

    protected:
        bool CanUnloadNow()
        {
            if (m_nObjectRefCount > 0 || m_nLockRefCount > 0)
            {
                return false;
            }

            return true;
        }

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

            for (UINT i = 0; i < m_pTypeLib->GetTypeInfoCount(); ++i)
            {
                TYPEKIND type = TKIND_MAX;
                HRESULT hr = m_pTypeLib->GetTypeInfoType(i, &type);

                if (FAILED(hr))
                {
                    return false;
                }

                if (type != TKIND_INTERFACE && type != TKIND_DISPATCH)
                {
                    continue;
                }

                ITypeInfo *pTypeInfo = nullptr;
                hr = m_pTypeLib->GetTypeInfo(i, &pTypeInfo);

                if (FAILED(hr))
                {
                    return false;
                }

                XL_ON_BLOCK_EXIT(pTypeInfo, &ITypeInfo::Release);

                TYPEATTR *pAttr = nullptr;
                pTypeInfo->GetTypeAttr(&pAttr);

                if (FAILED(hr))
                {
                    return false;
                }

                XL_ON_BLOCK_EXIT(pTypeInfo, &ITypeInfo::ReleaseTypeAttr, pAttr);

                TCHAR szInterfaceID[40] = {};
                StringFromGUID2(pAttr->guid, szInterfaceID, ARRAYSIZE(szInterfaceID));

                String strInterfacePath;
                strInterfacePath += _T("Software\\Classes\\Interface\\");
                strInterfacePath += szInterfaceID;

                if (!Registry::SetString(hRootKey, strInterfacePath + _T("\\ProxyStubClsid32"), _T(""), _T("{00020424-0000-0000-C000-000000000046}")))
                {
                    return false;
                }

                if (!Registry::SetString(hRootKey, strInterfacePath + _T("\\TypeLib"), _T(""), m_strLibID))
                {
                    return false;
                }

                if (!Registry::SetString(hRootKey, strInterfacePath + _T("\\TypeLib"), _T("Version"), m_strLibVersion))
                {
                    return false;
                }
            }

            return true;
        }

        bool UnregisterTypeLib(HKEY hRootKey)
        {
            for (UINT i = 0; i < m_pTypeLib->GetTypeInfoCount(); ++i)
            {
                TYPEKIND type = TKIND_MAX;
                HRESULT hr = m_pTypeLib->GetTypeInfoType(i, &type);

                if (FAILED(hr))
                {
                    return false;
                }

                if (type != TKIND_INTERFACE && type != TKIND_DISPATCH)
                {
                    continue;
                }

                ITypeInfo *pTypeInfo = nullptr;
                hr = m_pTypeLib->GetTypeInfo(i, &pTypeInfo);

                if (FAILED(hr))
                {
                    return false;
                }

                XL_ON_BLOCK_EXIT(pTypeInfo, &ITypeInfo::Release);

                TYPEATTR *pAttr = nullptr;
                pTypeInfo->GetTypeAttr(&pAttr);

                if (FAILED(hr))
                {
                    return false;
                }

                XL_ON_BLOCK_EXIT(pTypeInfo, &ITypeInfo::ReleaseTypeAttr, pAttr);

                TCHAR szInterfaceID[40] = {};
                StringFromGUID2(pAttr->guid, szInterfaceID, ARRAYSIZE(szInterfaceID));

                String strInterfacePath;
                strInterfacePath += _T("Software\\Classes\\Interface\\");
                strInterfacePath += szInterfaceID;

                if (!Registry::DeleteKeyRecursion(hRootKey, strInterfacePath))
                {
                    return false;
                }
            }

            String strPath;
            strPath += _T("Software\\Classes\\TypeLib\\");
            strPath += m_strLibID;

            if (!Registry::DeleteKeyRecursion(hRootKey, strPath))
            {
                return false;
            }

            return true;        
        }

        bool RegisterComClasses(HKEY hRootKey, bool bInprocServer = true)
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

                if (bInprocServer)
                {
                    if (!Registry::SetString(hRootKey, strClassIDPath + _T("\\InprocServer32"), _T(""), m_strModulePath))
                    {
                        return false;
                    }
                }
                else
                {
                    if (!Registry::SetString(hRootKey, strClassIDPath + _T("\\LocalServer32"), _T(""), m_strModulePath))
                    {
                        return false;
                    }
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
        bool RegisterTypeLibToIni(const String &strIniFileName)
        {
#if 0   // Do not register TypeLib to INI
            if (!IniFile::SetValue(strIniFileName, m_strLibID, _T("TypeLib"), m_strLibName))
            {
                return false;
            }

            if (!IniFile::SetValue(strIniFileName, m_strLibID, _T("Version"), m_strLibVersion))
            {
                return false;
            }

            String strModulePath = GetModuleRelativePathToIni(strIniFileName);

#ifdef _WIN64
            if (!IniFile::SetValue(strIniFileName, m_strLibID, _T("Win64"), strModulePath))
            {
                return false;
            }
#else
            if (!IniFile::SetValue(strIniFileName, m_strLibID, _T("Win32"), strModulePath))
            {
                return false;
            }
#endif
#endif
            return true;
        }

        bool UnregisterTypeLibFromIni(const String &strIniFileName)
        {
            if (!IniFile::DeleteSection(strIniFileName, m_strLibID))
            {
                return false;
            }

            return true;        
        }

        bool RegisterComClassesToIni(const String &strIniFileName, bool bInprocServer = true)
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

                if (!IniFile::SetValue(strIniFileName, szClassID, _T("Class"), (*ppEntry)->lpszClassDesc))
                {
                    return false;
                }

                String strModulePath = GetModuleRelativePathToIni(strIniFileName);

                if (bInprocServer)
                {
#ifdef _WIN64
                    if (!IniFile::SetValue(strIniFileName, szClassID, _T("InprocServer64"), strModulePath))
                    {
                        return false;
                    }
#else
                    if (!IniFile::SetValue(strIniFileName, szClassID, _T("InprocServer32"), strModulePath))
                    {
                        return false;
                    }
#endif
                }
                else
                {
#ifdef _WIN64
                    if (!IniFile::SetValue(strIniFileName, szClassID, _T("LocalServer64"), strModulePath))
                    {
                        return false;
                    }
#else
                    if (!IniFile::SetValue(strIniFileName, szClassID, _T("LocalServer32"), strModulePath))
                    {
                        return false;
                    }
#endif
                }

#if 0   // Do not register TypeLib and ProgID to INI
                if (!m_strLibID.Empty())
                {
                    if (!IniFile::SetValue(strIniFileName, szClassID, _T("TypeLib"), m_strLibID))
                    {
                        return false;
                    }
                }

                if (!strProgID.Empty())
                {
                    if (!IniFile::SetValue(strIniFileName, szClassID, _T("ProgID"), strProgID))
                    {
                        return false;
                    }

                    if (!IniFile::SetValue(strIniFileName, strProgID, _T("Class"), (*ppEntry)->lpszClassDesc))
                    {
                        return false;
                    }

                    if (!IniFile::SetValue(strIniFileName, strProgID, _T("CLSID"), szClassID))
                    {
                        return false;
                    }
                }

                if (!strVersionIndependentProgID.Empty())
                {
                    if (!IniFile::SetValue(strIniFileName, strVersionIndependentProgID, _T("Class"), (*ppEntry)->lpszClassDesc))
                    {
                        return false;
                    }

                    if (!IniFile::SetValue(strIniFileName, strVersionIndependentProgID, _T("CurVer"), strProgID))
                    {
                        return false;
                    }

                    if (!IniFile::SetValue(strIniFileName, strVersionIndependentProgID, _T("CLSID"), szClassID))
                    {
                        return false;
                    }
                }
#endif
            }

            return true;
        }

        bool UnregisterComClassesFromIni(const String &strIniFileName)
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

                if (!IniFile::DeleteSection(strIniFileName, szClassID))
                {
                    return false;
                }

                if (!strProgID.Empty())
                {
                    if (!IniFile::DeleteSection(strIniFileName, strProgID))
                    {
                        return false;
                    }
                }

                if (!strVersionIndependentProgID.Empty())
                {
                    if (!IniFile::DeleteSection(strIniFileName, strVersionIndependentProgID))
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        String GetModuleRelativePathToIni(const String &strIniFileName)
        {
            TCHAR szIniPathAbsolute[MAX_PATH] = {};
            
            if (GetFullPathName(strIniFileName, ARRAYSIZE(szIniPathAbsolute), szIniPathAbsolute, nullptr) == 0)
            {
                return m_strModulePath;
            }

            TCHAR szModuleRelativePath[MAX_PATH] = {};

            if (!PathRelativePathTo(szModuleRelativePath, szIniPathAbsolute, 0, m_strModulePath, 0))
            {
                return m_strModulePath;
            }

            return szModuleRelativePath;
        }

    private:
        HMODULE   m_hModule;
        String    m_strLibName;
        String    m_strModulePath;
        String    m_strLibID;
        String    m_strLibVersion;
        LONG      m_nObjectRefCount;
        LONG      m_nLockRefCount;
        ITypeLib *m_pTypeLib;
        TLIBATTR *m_pTLibAttr;
        DWORD     m_dwThreadId;
        xl::Array<DWORD> m_arrRegClassObjects;
    };

} // namespace xl

#endif // #ifndef __XLCOMMODULE_H_89C4A369_6CBD_4316_947D_122F6E6C3F55_INCLUDED__
