//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlEncodingTest.cpp
//    Author:      Streamlet
//    Create Time: 2011-06-12
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/AppHelper/xlUnitTest.h"
#include "../../../Include/xl/Common/String/xlEncoding.h"
#include <atlstr.h>

namespace
{
    CStringA UnicodeToAnsi(const CStringW &strUnicode, DWORD dwCodePage /*= CP_ACP*/)
    {
        int size = WideCharToMultiByte(dwCodePage, 0, strUnicode, -1, NULL, 0, NULL, NULL);

        if (size == 0)
        {
            return "";
        }

        LPSTR szAnsi = new CHAR[size];

        if (WideCharToMultiByte(dwCodePage, 0, strUnicode, -1, szAnsi, size, NULL, NULL) == 0)
        {
            delete[] szAnsi;
            return "";
        }

        CStringA ret = szAnsi;
        delete[] szAnsi;

        return ret;
    }

    XL_TEST_CASE()
    {
        xl::StringU8  utf8;
        xl::StringU16 utf16;
        xl::StringU32 utf32;
        LPCWSTR test = NULL;
        bool b = false;

        test = L"";
        b = xl::Encoding::Utf16ToUtf8(test, &utf8);
        XL_TEST_ASSERT(b);
        b = xl::Encoding::Utf8ToUtf16(utf8, &utf16);
        XL_TEST_ASSERT(b);
        XL_TEST_ASSERT(utf8 == (LPCSTR)UnicodeToAnsi(test, CP_UTF8));
        XL_TEST_ASSERT(utf16 == test);

        test = L"°¡";
        b = xl::Encoding::Utf16ToUtf8(test, &utf8);
        XL_TEST_ASSERT(b);
        b = xl::Encoding::Utf8ToUtf16(utf8, &utf16);
        XL_TEST_ASSERT(b);
        XL_TEST_ASSERT(utf8 == (LPCSTR)UnicodeToAnsi(test, CP_UTF8));
        XL_TEST_ASSERT(utf16 == test);

        test = L"\xd834\xdd60";
        b = xl::Encoding::Utf16ToUtf8(test, &utf8);
        XL_TEST_ASSERT(b);
        b = xl::Encoding::Utf8ToUtf16(utf8, &utf16);
        XL_TEST_ASSERT(b);
        XL_TEST_ASSERT(utf8 == (LPCSTR)UnicodeToAnsi(test, CP_UTF8));
        XL_TEST_ASSERT(utf16 == test);
        b = xl::Encoding::Utf8ToUtf32(utf8, &utf32);
        XL_TEST_ASSERT(b);
        XL_TEST_ASSERT(utf32.Length() == 1 && utf32[0] == 0x1d160);
        b = xl::Encoding::Utf16ToUtf32(test, &utf32);
        XL_TEST_ASSERT(b);
        XL_TEST_ASSERT(utf32.Length() == 1 && utf32[0] == 0x1d160);
    }
}


