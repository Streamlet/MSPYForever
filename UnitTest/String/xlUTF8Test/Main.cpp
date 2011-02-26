//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2011-02-26
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Test/xlUnitTest.h>
#include <xl/String/xlUTF8.h>

#include <Windows.h>
#include <atlstr.h>

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
        delete szAnsi;
        return "";
    }

    CStringA ret = szAnsi;
    delete szAnsi;

    return ret;
}

XL_TEST_CASE()
{
    xl::StringA utf8;
    xl::String ucs2;
    xl::String test;
    bool b = false;

    test = L"";
    xl::UTF8::Encode(test, &utf8);
    b = xl::UTF8::Decode(utf8, &ucs2);
    XL_TEST_ASSERT(b);
    XL_TEST_ASSERT(utf8 == (LPCSTR)UnicodeToAnsi(test.GetAddress(), CP_UTF8));
    XL_TEST_ASSERT(ucs2 == test);

    test = L"啊";
    xl::UTF8::Encode(test, &utf8);
    b = xl::UTF8::Decode(utf8, &ucs2);
    XL_TEST_ASSERT(b);
    XL_TEST_ASSERT(utf8 == (LPCSTR)UnicodeToAnsi(test.GetAddress(), CP_UTF8));
    XL_TEST_ASSERT(ucs2 == test);

    test = L"你好";
    xl::UTF8::Encode(test, &utf8);
    b = xl::UTF8::Decode(utf8, &ucs2);
    XL_TEST_ASSERT(b);
    XL_TEST_ASSERT(utf8 == (LPCSTR)UnicodeToAnsi(test.GetAddress(), CP_UTF8));
    XL_TEST_ASSERT(ucs2 == test);

    test = L"你很好";
    xl::UTF8::Encode(test, &utf8);
    b = xl::UTF8::Decode(utf8, &ucs2);
    XL_TEST_ASSERT(b);
    XL_TEST_ASSERT(utf8 == (LPCSTR)UnicodeToAnsi(test.GetAddress(), CP_UTF8));
    XL_TEST_ASSERT(ucs2 == test);

    test = L"你非常好";
    xl::UTF8::Encode(test, &utf8);
    b = xl::UTF8::Decode(utf8, &ucs2);
    XL_TEST_ASSERT(b);
    XL_TEST_ASSERT(utf8 == (LPCSTR)UnicodeToAnsi(test.GetAddress(), CP_UTF8));
    XL_TEST_ASSERT(ucs2 == test);

    test = L"你真的很好";
    xl::UTF8::Encode(test, &utf8);
    b = xl::UTF8::Decode(utf8, &ucs2);
    XL_TEST_ASSERT(b);
    XL_TEST_ASSERT(utf8 == (LPCSTR)UnicodeToAnsi(test.GetAddress(), CP_UTF8));
    XL_TEST_ASSERT(ucs2 == test);

    test = L"你最好不过了";
    xl::UTF8::Encode(test, &utf8);
    b = xl::UTF8::Decode(utf8, &ucs2);
    XL_TEST_ASSERT(b);
    XL_TEST_ASSERT(utf8 == (LPCSTR)UnicodeToAnsi(test.GetAddress(), CP_UTF8));
    XL_TEST_ASSERT(ucs2 == test);

}

int main()
{
    return 0;
}


