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
#include <xl/Win32/File/xlIniFile.h>
#include <xl/Win32/COM/xlComDef.h>
#include <xl/Win32/COM/xlClassFactory.h>
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

namespace xl
{
    class ComModule : public IComModule
    {
    public:
        ComModule(HMODULE hModule = nullptr, LPCTSTR lpLibName = nullptr) :
            m_hModule(hModule), m_strLibName(lpLibName), m_nObjectRefCount(0), m_nLockRefCount(0), m_pTypeLib(nullptr)
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

            HRESULT hr = LoadTypeLib(m_strModulePath.GetAddress(), &m_pTypeLib);

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
        ULONG STDMETHODCALLTYPE ObjectAddRef()
        {
            return (ULONG)InterlockedIncrement(&m_nObjectRefCount);
        }

        ULONG STDMETHODCALLTYPE ObjectRelease()
        {
            return (ULONG)InterlockedDecrement(&m_nObjectRefCount);
        }

    public:
        ULONG STDMETHODCALLTYPE LockAddRef()
        {
            return (ULONG)InterlockedIncrement(&m_nLockRefCount);
        }

        ULONG STDMETHODCALLTYPE LockRelease()
        {
            return (ULONG)InterlockedDecrement(&m_nLockRefCount);
        }

    public:
        STDMETHODIMP GetTypeInfo(_In_ REFIID riid, _Outptr_ ITypeInfo **ppTinfo)
        {
            return m_pTypeLib->GetTypeInfoOfGuid(riid, ppTinfo);
        }

    public:
        STDMETHODIMP DllCanUnloadNow()
        {
            return (m_nObjectRefCount > 0 || m_nLockRefCount > 0) ? S_FALSE : S_OK;
        }

        STDMETHODIMP DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID *ppv)
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

        STDMETHODIMP DllRegisterServer()
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

        STDMETHODIMP DllUnregisterServer()
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

        STDMETHODIMP DllInstall(BOOL bInstall, _In_opt_ LPCTSTR lpszCmdLine)
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

            if (strCmdLineLower == _T("ini") || strCmdLineLower.IndexOf(_T("ini:")) == 0)
            {
                String strIniFileName = _T("xlComReg.ini");

                if (strCmdLine.Length() > 4)
                {
                    strIniFileName = strCmdLine.SubString(4);
                }

                if (bInstall)
                {
                    if (!RegisterTypeLibToIni(strIniFileName))
                    {
                        return E_FAIL;
                    }

                    if (!RegisterComClassesToIni(strIniFileName))
                    {
                        return E_FAIL;
                    }

                    return S_OK;
                }
                else
                {
                    if (!UnregisterComClassesToIni(strIniFileName))
                    {
                        return E_FAIL;
                    }

                    if (!UnregisterTypeLibToIni(strIniFileName))
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

        bool UnregisterTypeLibToIni(const String &strIniFileName)
        {
            if (!IniFile::DeleteSection(strIniFileName, m_strLibID))
            {
                return false;
            }

            return true;        
        }

        bool RegisterComClassesToIni(const String &strIniFileName)
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

        bool UnregisterComClassesToIni(const String &strIniFileName)
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
            
            if (GetFullPathName(strIniFileName.GetAddress(), ARRAYSIZE(szIniPathAbsolute), szIniPathAbsolute, nullptr) == 0)
            {
                return m_strModulePath;
            }

            TCHAR szModuleRelativePath[MAX_PATH] = {};

            if (!PathRelativePathTo(szModuleRelativePath, szIniPathAbsolute, 0, m_strModulePath.GetAddress(), 0))
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
    };

} // namespace xl

#endif // #ifndef __XLCOMMODULE_H_89C4A369_6CBD_4316_947D_122F6E6C3F55_INCLUDED__
