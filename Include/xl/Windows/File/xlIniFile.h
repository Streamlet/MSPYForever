//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   IniFile.h
//    Author:      Streamlet
//    Create Time: 2012-09-12
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __INIFILE_H_2AFF6877_40F9_4A15_B2ED_4355AD5A2963_INCLUDED__
#define __INIFILE_H_2AFF6877_40F9_4A15_B2ED_4355AD5A2963_INCLUDED__


#include "../../Common/Containers/xlArray.h"
#include "../../Common/Memory/xlSmartPtr.h"
#include "../../Common/Meta/xlScopeExit.h"
#include "../../Common/Meta/xlNonInstantiable.h"
#include "../../Common/String/xlString.h"
#include "../xlWin32Ver.h"

namespace xl
{
    namespace Windows
    {
        class IniFile : public NonInstantiable
        {
        public:
            static bool EnumSections(const String &strFilePath, Array<String> *pSectionNames)
            {
                if (pSectionNames == nullptr)
                {
                    return false;
                }

                wchar_t szFileNameAbsolute[MAX_PATH] = {};

                if (GetFullPathName(strFilePath, MAX_PATH, szFileNameAbsolute, nullptr) == 0)
                {
                    return false;
                }

                SharedPtr<wchar_t> spSectionNames = nullptr;
                DWORD dwSize = 1024;

                while (true)
                {
                    spSectionNames = new wchar_t[dwSize];

                    DWORD dwSizeUsed = GetPrivateProfileSectionNames(spSectionNames.RawPointer(), dwSize, szFileNameAbsolute);

                    if (dwSizeUsed < dwSize - 2)
                    {
                        break;
                    }

                    dwSize *= 2;
                }

                LPCTSTR lpszName = spSectionNames.RawPointer();
                pSectionNames->Clear();

                while (lpszName[0] != L'\0')
                {
                    String strSectionName = lpszName;
                    lpszName += strSectionName.Length() + 1;
                    pSectionNames->PushBack(strSectionName);
                }

                return true;
            }

            static bool GetSection(const String &strFilePath, const String &strSectionName, Array<String> *pLines)
            {
                if (strSectionName.Empty() || pLines == nullptr)
                {
                    return false;
                }

                wchar_t szFileNameAbsolute[MAX_PATH] = {};

                if (GetFullPathName(strFilePath, MAX_PATH, szFileNameAbsolute, nullptr) == 0)
                {
                    return false;
                }

                SharedPtr<wchar_t> spKeyNames = nullptr;
                DWORD dwSize = 1024;

                while (true)
                {
                    spKeyNames = new wchar_t[dwSize];

                    DWORD dwSizeUsed = GetPrivateProfileSection(strSectionName, spKeyNames.RawPointer(), dwSize, szFileNameAbsolute);

                    if (dwSizeUsed < dwSize - 2)
                    {
                        break;
                    }

                    dwSize *= 2;
                }

                LPCTSTR lpszName = spKeyNames.RawPointer();
                pLines->Clear();


                while (lpszName[0] != L'\0')
                {
                    String strLine = lpszName;
                    lpszName += strLine.Length() + 1;
                    pLines->PushBack(strLine);
                }

                return true;
            }

            static bool EnumKeys(const String &strFilePath, const String &strSectionName, Array<String> *pKeys)
            {
                if (!GetSection(strFilePath, strSectionName, pKeys))
                {
                    return false;
                }

                for (auto it = pKeys->Begin(); it != pKeys->End(); ++it)
                {
                    String &strLine = *it;

                    int nPos = strLine.IndexOf(L"=");

                    if (nPos >= 0)
                    {
                        strLine = strLine.Left(nPos);
                        strLine.Trim();
                    }
                }

                return true;
            }

            static bool EnumValues(const String &strFilePath, const String &strSectionName, Array<String> *pValues)
            {
                if (!GetSection(strFilePath, strSectionName, pValues))
                {
                    return false;
                }

                for (auto it = pValues->Begin(); it != pValues->End(); ++it)
                {
                    String &strLine = *it;

                    int nPos = strLine.IndexOf(L"=");

                    if (nPos >= 0)
                    {
                        strLine = strLine.SubString(nPos + 1);
                        strLine.Trim();
                    }
                }

                return true;
            }

            static bool GetValue(const String &strFilePath, const String &strSectionName, const String &strKeyName, String *pValue)
            {
                if (strSectionName.Empty() || strKeyName.Empty() || pValue == nullptr)
                {
                    return false;
                }

                wchar_t szFileNameAbsolute[MAX_PATH] = {};

                if (GetFullPathName(strFilePath, MAX_PATH, szFileNameAbsolute, nullptr) == 0)
                {
                    return false;
                }

                SharedPtr<wchar_t> spValue = nullptr;
                DWORD dwSize = 1024;

                while (true)
                {
                    spValue = new wchar_t[dwSize];

                    DWORD dwSizeUsed = GetPrivateProfileString(strSectionName,
                        strKeyName,
                        nullptr,
                        spValue.RawPointer(),
                        dwSize,
                        szFileNameAbsolute);

                    if (dwSizeUsed < dwSize - 1)
                    {
                        break;
                    }

                    dwSize *= 2;
                }

                *pValue = spValue.RawPointer();

                return !pValue->Empty();
            }

            static bool SetValue(const String &strFilePath, const String &strSectionName, const String &strKeyName, const String &strValue)
            {
                wchar_t szFileNameAbsolute[MAX_PATH] = {};

                if (GetFullPathName(strFilePath, MAX_PATH, szFileNameAbsolute, nullptr) == 0)
                {
                    return false;
                }

                HANDLE hFile = CreateFile(szFileNameAbsolute, GENERIC_WRITE, 0, nullptr, CREATE_NEW, 0, nullptr);

                if (hFile != INVALID_HANDLE_VALUE)
                {
                    WORD wUnicodeBOM = 0xfeff;
                    DWORD dwWritten = 0;
                    WriteFile(hFile, &wUnicodeBOM, sizeof(WORD), &dwWritten, NULL);
                    CloseHandle(hFile);
                }

                if (!WritePrivateProfileString(strSectionName,
                    strKeyName,
                    strValue,
                    szFileNameAbsolute))
                {
                    return false;
                }

                return true;
            }

            static bool DeleteKey(const String &strFilePath, const String &strSectionName, const String &strKeyName)
            {
                wchar_t szFileNameAbsolute[MAX_PATH] = {};

                if (GetFullPathName(strFilePath, MAX_PATH, szFileNameAbsolute, nullptr) == 0)
                {
                    return false;
                }

                if (!WritePrivateProfileString(strSectionName,
                    strKeyName,
                    nullptr,
                    szFileNameAbsolute))
                {
                    return false;
                }

                return true;
            }

            static bool DeleteSection(const String &strFilePath, const String &strSectionName)
            {
                wchar_t szFileNameAbsolute[MAX_PATH] = {};

                if (GetFullPathName(strFilePath, MAX_PATH, szFileNameAbsolute, nullptr) == 0)
                {
                    return false;
                }

                if (!WritePrivateProfileString(strSectionName,
                                               nullptr,
                                               nullptr,
                                               szFileNameAbsolute))
                {
                    return false;
                }

                return true;
            }
        };

    } // namspace Windows
} // namespace xl

#endif // #ifndef __INIFILE_H_2AFF6877_40F9_4A15_B2ED_4355AD5A2963_INCLUDED__
