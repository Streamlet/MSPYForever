//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlRegistry.h
//    Author:      Streamlet
//    Create Time: 2012-09-05
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLREGISTRY_H_75705091_0710_47A5_8543_92548C6AAF46_INCLUDED__
#define __XLREGISTRY_H_75705091_0710_47A5_8543_92548C6AAF46_INCLUDED__


#include "../../Common/Containers/xlArray.h"
#include "../../Common/Memory/xlSmartPtr.h"
#include "../../Common/Meta/xlScopeExit.h"
#include "../../Common/Meta/xlNonInstantiable.h"
#include "../../Common/String/xlString.h"
#include "../xlWin32Ver.h"
#include <winscard.h>

namespace xl
{
    namespace Windows
    {
        enum RegistryView
        {
            RV_Default,
            RV_X86,
            RV_X64
        };

        template <int V = RV_Default>
        class RegistryT : public NonInstantiable
        {
        public:
            static bool GetString(HKEY hRootKey, const String &strPath, const String &strName, String *pValue)
            {
                if (pValue == nullptr)
                {
                    return false;
                }

                HKEY hKey = nullptr;

                if (RegOpenKeyEx(hRootKey, strPath, 0, KEY_QUERY_VALUE | GetExtraFlags(), &hKey) != ERROR_SUCCESS)
                {
                    return false;
                }

                XL_ON_BLOCK_EXIT(RegCloseKey, hKey);

                DWORD dwType = REG_NONE;
                DWORD cbSize = 0;
                LONG lRet = RegQueryValueEx(hKey, strName, nullptr, &dwType, nullptr, &cbSize);

                if (dwType != REG_SZ && dwType != REG_EXPAND_SZ)
                {
                    return false;
                }

                if (lRet == ERROR_SUCCESS || cbSize == 0)
                {
                    pValue->Clear();
                    return true;
                }

                if (lRet != ERROR_MORE_DATA)
                {
                    return false;
                }

                SharedPtr<wchar_t> spBuffer = new wchar_t[cbSize / sizeof(wchar_t)];
                lRet = RegQueryValueEx(hKey, strName, nullptr, nullptr, (LPBYTE)spBuffer.RawPointer(), &cbSize);

                if (lRet != ERROR_SUCCESS)
                {
                    return false;
                }

                *pValue = spBuffer.RawPointer();

                return true;
            }

            static bool SetString(HKEY hRootKey, const String &strPath, const String &strName, const String &strValue)
            {
                HKEY hKey = nullptr;

                if (RegCreateKeyEx(hRootKey, strPath, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | GetExtraFlags(), NULL, &hKey, NULL) != ERROR_SUCCESS)
                {
                    return false;
                }

                XL_ON_BLOCK_EXIT(RegCloseKey, hKey);

                if (RegSetValueEx(hKey, strName, 0, REG_SZ, (LPCBYTE)(LPCTSTR)strValue, (DWORD)(strValue.Length() + 1) * sizeof(wchar_t)) != ERROR_SUCCESS)
                {
                    return false;
                }

                return true;
            }

            static bool SetExpandString(HKEY hRootKey, const String &strPath, const String &strName, const String &strValue)
            {
                HKEY hKey = nullptr;

                if (RegCreateKeyEx(hRootKey, strPath, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | GetExtraFlags(), NULL, &hKey, NULL) != ERROR_SUCCESS)
                {
                    return false;
                }

                XL_ON_BLOCK_EXIT(RegCloseKey, hKey);

                if (RegSetValueEx(hKey, strName, 0, REG_EXPAND_SZ, (LPCBYTE)(LPCTSTR)strValue, (DWORD)(strValue.Length() + 1) * sizeof(wchar_t)) != ERROR_SUCCESS)
                {
                    return false;
                }

                return true;
            }

            static bool GetDWORD(HKEY hRootKey, const String &strPath, const String &strName, DWORD *pValue)
            {
                if (pValue == nullptr)
                {
                    return false;
                }

                HKEY hKey = nullptr;

                if (RegOpenKeyEx(hRootKey, strPath, 0, KEY_QUERY_VALUE | GetExtraFlags(), &hKey) != ERROR_SUCCESS)
                {
                    return false;
                }

                XL_ON_BLOCK_EXIT(RegCloseKey, hKey);

                DWORD dwValue = 0;
                DWORD cbSize = sizeof(DWORD);
                DWORD dwType = REG_NONE;

                if (RegQueryValueEx(hKey, strName, nullptr, &dwType, (LPBYTE)&dwValue, &cbSize) != ERROR_SUCCESS)
                {
                    return false;
                }

                if (dwType != REG_DWORD)
                {
                    return false;
                }

                *pValue = dwValue;

                return true;
            }

            static bool SetDWORD(HKEY hRootKey, const String &strPath, const String &strName, DWORD dwValue)
            {
                HKEY hKey = nullptr;

                if (RegCreateKeyEx(hRootKey, strPath, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | GetExtraFlags(), NULL, &hKey, NULL) != ERROR_SUCCESS)
                {
                    return false;
                }

                XL_ON_BLOCK_EXIT(RegCloseKey, hKey);

                if (RegSetValueEx(hKey, strName, nullptr, REG_DWORD, (LPCBYTE)&dwValue, sizeof(DWORD)) != ERROR_SUCCESS)
                {
                    return false;
                }

                return true;
            }

            static bool GetBinary(HKEY hRootKey, const String &strPath, const String &strName, Array<BYTE> *pValue)
            {
                if (pValue == nullptr)
                {
                    return false;
                }

                HKEY hKey = nullptr;

                if (RegOpenKeyEx(hRootKey, strPath, 0, KEY_QUERY_VALUE | GetExtraFlags(), &hKey) != ERROR_SUCCESS)
                {
                    return false;
                }

                DWORD dwType = REG_NONE;
                DWORD cbSize = 0;
                LONG lRet = RegQueryValueEx(hKey, strName, nullptr, &dwType, nullptr, &cbSize);

                if (dwType != REG_BINARY)
                {
                    return false;
                }

                if (lRet == ERROR_SUCCESS || cbSize == 0)
                {
                    pValue->Clear();
                    return true;
                }

                if (lRet != ERROR_MORE_DATA)
                {
                    return false;
                }

                pValue->Resize(cbSize);
                lRet = RegQueryValueEx(hKey, strName, nullptr, nullptr, (LPCBYTE)&(*pValue)[0], &cbSize);

                if (lRet != ERROR_SUCCESS)
                {
                    return false;
                }

                return true;
            }


            static bool SetBinary(HKEY hRootKey, const String &strPath, const String &strName, LPCBYTE lpbyBuffer, DWORD dwSize)
            {
                HKEY hKey = nullptr;

                if (RegCreateKeyEx(hRootKey, strPath, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | GetExtraFlags(), NULL, &hKey, NULL) != ERROR_SUCCESS)
                {
                    return false;
                }

                XL_ON_BLOCK_EXIT(RegCloseKey, hKey);

                if (RegSetValueEx(hKey, strName, nullptr, REG_BINARY, (LPBYTE)lpbyBuffer, dwSize) != ERROR_SUCCESS)
                {
                    return false;
                }

                return true;
            }

            static bool CreateKey(HKEY hRootKey, const String &strPath)
            {
                HKEY hKey = nullptr;

                if (RegCreateKeyEx(hRootKey, strPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_QUERY_VALUE | GetExtraFlags(), NULL, &hKey, NULL) != ERROR_SUCCESS)
                {
                    return false;
                }

                RegCloseKey(hKey);

                return true;
            }

            static bool EnumSubKey(HKEY hRootKey, const String &strPath, Array<String> *pKeyNames)
            {
                if (pKeyNames == nullptr)
                {
                    return false;
                }

                HKEY hKey = nullptr;

                if (RegOpenKeyEx(hRootKey, strPath, 0, KEY_ENUMERATE_SUB_KEYS | GetExtraFlags(), &hKey) != ERROR_SUCCESS)
                {
                    return false;
                }

                XL_ON_BLOCK_EXIT(RegCloseKey, hKey);

                LONG lRet = ERROR_SUCCESS;
                wchar_t szName[MAX_PATH] = {};

                for (int i = 0; true; ++i)
                {
                    DWORD dwSize = sizeof(szName);
                    lRet = RegEnumKeyEx(hKey, i, szName, &dwSize, nullptr, nullptr, nullptr, nullptr);

                    if (lRet == ERROR_NO_MORE_ITEMS)
                    {
                        break;
                    }

                    if (lRet != ERROR_SUCCESS)
                    {
                        return false;
                    }

                    pKeyNames->PushBack(szName);
                }

                return true;
            }

            static bool EnumValueName(HKEY hRootKey, const String &strPath, Array<String> *pValueNames)
            {
                if (pValueNames == nullptr)
                {
                    return false;
                }

                HKEY hKey = nullptr;

                if (RegOpenKeyEx(hRootKey, strPath, 0, KEY_QUERY_VALUE | GetExtraFlags(), &hKey) != ERROR_SUCCESS)
                {
                    return FALSE;
                }

                XL_ON_BLOCK_EXIT(RegCloseKey, hKey);

                LONG lRet = ERROR_SUCCESS;
                wchar_t szName[MAX_PATH] = {};

                for (int i = 0; true; ++i)
                {
                    DWORD dwSize = sizeof(szName);
                    lRet = RegEnumValue(hKey, i, szName, &dwSize, NULL, NULL, NULL, NULL);

                    if (lRet == ERROR_NO_MORE_ITEMS)
                    {
                        break;
                    }

                    if (lRet != ERROR_SUCCESS)
                    {
                        return false;
                    }

                    pValueNames->PushBack(szName);
                }

                return true;
            }

            static bool DeleteValue(HKEY hRootKey, const String &strPath, const String &strName)
            {
                HKEY hKey = nullptr;

                if (RegOpenKeyEx(hRootKey, strPath, 0, KEY_SET_VALUE | GetExtraFlags(), &hKey) != ERROR_SUCCESS)
                {
                    return false;
                }

                XL_ON_BLOCK_EXIT(RegCloseKey, hKey);

                if (RegDeleteValue(hKey, strName) != ERROR_SUCCESS)
                {
                    return false;
                }

                return true;
            }

            static bool DeleteKey(HKEY hRootKey, const String &strPath)
            {
                HKEY hKey = nullptr;
                String strName;

                int nLastPos = strPath.Length();

                while (true)
                {
                    if (nLastPos <= 0)
                    {
                        return false;
                    }

                    int nPos = strPath.LastIndexOf(L"\\", nLastPos);

                    if (nPos == nLastPos - 1)
                    {
                        nLastPos = nPos;
                        continue;
                    }

                    if (nPos >= 0)
                    {
                        strName = strPath.SubString(nPos + 1, nLastPos - nPos);
                        String strSuperPath = strPath.SubString(0, nPos);

                        if (RegOpenKeyEx(hRootKey, strSuperPath, 0, DELETE | GetExtraFlags(), &hKey) != ERROR_SUCCESS)
                        {
                            return false;
                        }
                    }
                    else
                    {
                        hKey = hRootKey;
                        strName = strPath;
                    }

                    break;
                }

                LONG lRet = RegDeleteKey(hKey, strName);

                if (hKey != hRootKey)
                {
                    RegCloseKey(hKey);
                }

                if (lRet != ERROR_SUCCESS)
                {
                    return false;
                }

                return true;
            }

            static bool DeleteKeyRecursion(HKEY hRootKey, const String &strPath)
            {
                Array<String> arrKeys;

                if (!EnumSubKey(hRootKey, strPath, &arrKeys))
                {
                    return false;
                }

                if (!arrKeys.Empty())
                {
                    for (auto it = arrKeys.Begin(); it != arrKeys.End(); ++it)
                    {
                        if (!DeleteKeyRecursion(hRootKey, strPath + L"\\" + *it))
                        {
                            return false;
                        }
                    }
                }

                return  DeleteKey(hRootKey, strPath);
            }

        private:
            static DWORD GetExtraFlags()
            {
                DWORD dwFlags = 0;

                switch (V)
                {
                case RV_Default:
                    break;
                case RV_X86:
                    dwFlags |= KEY_WOW64_32KEY;
                    break;
                case RV_X64:
                    dwFlags |= KEY_WOW64_64KEY;
                    break;
                default:
                    break;
                }

                return dwFlags;
            }
        };

        typedef RegistryT<RV_Default>    Registry;
        typedef RegistryT<RV_X86>        Registry32;
        typedef RegistryT<RV_Default>    Registry64;

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLREGISTRY_H_75705091_0710_47A5_8543_92548C6AAF46_INCLUDED__
