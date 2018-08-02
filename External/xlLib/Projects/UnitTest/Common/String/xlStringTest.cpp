//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlStringTest.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../../Include/xl/AppHelper/xlUnitTest.h"
#include "../../../../Include/xl/Common/String/xlString.h"

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        String a;
        XL_TEST_ASSERT(a == L"");

        String b(L"123");
        XL_TEST_ASSERT(b == L"123");

        String c(b);
        XL_TEST_ASSERT(c == L"123");

        String d(L"123", 3);
        XL_TEST_ASSERT(d == L"123");

        String e(L"123", 4);
        XL_TEST_ASSERT(e == L"123");

        String f(L"1\00023", 3);
        XL_TEST_ASSERT(f.Length() == 3 && f[0] == L'1' && f[1] == L'\0' && f[2] == L'2');
    }

    XL_TEST_CASE()
    {
        String a(L"123");
        String b(L"456");

        b = a;
        XL_TEST_ASSERT(b == a);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(String(L"") == L"");
        XL_TEST_ASSERT(String(L"123") != L"");
        XL_TEST_ASSERT(String(L"") != L"123");
        XL_TEST_ASSERT(String(L"123") == L"123");
        XL_TEST_ASSERT(String(L"123") <= L"123");
        XL_TEST_ASSERT(String(L"123") >= L"123");
        XL_TEST_ASSERT(String(L"123") < L"223");
        XL_TEST_ASSERT(String(L"123") <= L"223");
        XL_TEST_ASSERT(String(L"123") > L"023");
        XL_TEST_ASSERT(String(L"123") >= L"023");
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(String(L"") + String(L"") == L"");
        XL_TEST_ASSERT(String(L"a") + String(L"") == L"a");
        XL_TEST_ASSERT(String(L"") + String(L"b") == L"b");
        XL_TEST_ASSERT(String(L"a") + String(L"b") == L"ab");

        XL_TEST_ASSERT((String(L"") += String(L"")) == L"");
        XL_TEST_ASSERT((String(L"a") += String(L"")) == L"a");
        XL_TEST_ASSERT((String(L"") += String(L"b")) == L"b");
        XL_TEST_ASSERT((String(L"a") += String(L"b")) == L"ab");
    }

    XL_TEST_CASE()
    {
        String a(L"123");

        XL_TEST_ASSERT(a[0] == L'1');
        XL_TEST_ASSERT(a[1] == L'2');
        XL_TEST_ASSERT(a[2] == L'3');
        XL_TEST_ASSERT(a[3] == L'\0');

        a[0] = L'4';
        a[1] = L'5';
        a[2] = L'6';

        XL_TEST_ASSERT(a[0] == L'4');
        XL_TEST_ASSERT(a[1] == L'5');
        XL_TEST_ASSERT(a[2] == L'6');
    }

    XL_TEST_CASE()
    {
        String a(L"123");
        XL_TEST_ASSERT((const wchar_t *)a == &a[0]);
    }

    XL_TEST_CASE()
    {
        String a;
        XL_TEST_ASSERT(a.Length() == 0);
        XL_TEST_ASSERT(a.Empty());

        a = L"1";
        XL_TEST_ASSERT(a.Length() == 1);
        XL_TEST_ASSERT(!a.Empty());

        a = L"12";
        XL_TEST_ASSERT(a.Length() == 2);
        XL_TEST_ASSERT(!a.Empty());

        a = L"123";
        XL_TEST_ASSERT(a.Length() == 3);
        XL_TEST_ASSERT(!a.Empty());
    }

    XL_TEST_CASE()
    {
        String a(L"Hello!");

        XL_TEST_ASSERT(a.ToLower() == L"hello!");
        XL_TEST_ASSERT(a.ToUpper() == L"HELLO!");

        XL_TEST_ASSERT(a == L"Hello!");
        a.MakeLower();
        XL_TEST_ASSERT(a == L"hello!");
        a.MakeUpper();
        XL_TEST_ASSERT(a == L"HELLO!");
    }

    XL_TEST_CASE()
    {
        String a(L"123");

        a.AppendBack(L'a');
        XL_TEST_ASSERT(a == L"123a");

        a.AppendFront(L'a');
        XL_TEST_ASSERT(a == L"a123a");

        a.AppendBack(L'b', 3);
        XL_TEST_ASSERT(a == L"a123abbb");

        a.AppendFront(L'b', 3);
        XL_TEST_ASSERT(a == L"bbba123abbb");

        a.Clear();
        XL_TEST_ASSERT(a == L"");
    }

    XL_TEST_CASE()
    {
        String a(L"12345");

        XL_TEST_ASSERT(a.Left(0) == L"");
        XL_TEST_ASSERT(a.Left(1) == L"1");
        XL_TEST_ASSERT(a.Left(2) == L"12");
        XL_TEST_ASSERT(a.Left(3) == L"123");
        XL_TEST_ASSERT(a.Left(4) == L"1234");
        XL_TEST_ASSERT(a.Left(5) == L"12345");
        XL_TEST_ASSERT(a.Right(0) == L"");
        XL_TEST_ASSERT(a.Right(1) == L"5");
        XL_TEST_ASSERT(a.Right(2) == L"45");
        XL_TEST_ASSERT(a.Right(3) == L"345");
        XL_TEST_ASSERT(a.Right(4) == L"2345");
        XL_TEST_ASSERT(a.Right(5) == L"12345");
        XL_TEST_ASSERT(a.SubString(0, 0) == L"");
        XL_TEST_ASSERT(a.SubString(0, 1) == L"1");
        XL_TEST_ASSERT(a.SubString(0, 2) == L"12");
        XL_TEST_ASSERT(a.SubString(0, 3) == L"123");
        XL_TEST_ASSERT(a.SubString(0, 4) == L"1234");
        XL_TEST_ASSERT(a.SubString(0, 5) == L"12345");
        XL_TEST_ASSERT(a.SubString(1, 0) == L"");
        XL_TEST_ASSERT(a.SubString(1, 1) == L"2");
        XL_TEST_ASSERT(a.SubString(1, 2) == L"23");
        XL_TEST_ASSERT(a.SubString(1, 3) == L"234");
        XL_TEST_ASSERT(a.SubString(1, 4) == L"2345");
        XL_TEST_ASSERT(a.SubString(2, 0) == L"");
        XL_TEST_ASSERT(a.SubString(2, 1) == L"3");
        XL_TEST_ASSERT(a.SubString(2, 2) == L"34");
        XL_TEST_ASSERT(a.SubString(2, 3) == L"345");
        XL_TEST_ASSERT(a.SubString(3, 0) == L"");
        XL_TEST_ASSERT(a.SubString(3, 1) == L"4");
        XL_TEST_ASSERT(a.SubString(3, 2) == L"45");
        XL_TEST_ASSERT(a.SubString(4, 0) == L"");
        XL_TEST_ASSERT(a.SubString(4, 1) == L"5");
        XL_TEST_ASSERT(a.SubString(5, 0) == L"");

        XL_TEST_ASSERT(a.Left(10) == L"12345");
    }

    XL_TEST_CASE()
    {
        String a(L"123abc456abc789");

        XL_TEST_ASSERT(a.IndexOf(L"abc") == 3);
        XL_TEST_ASSERT(a.IndexOf(L"abc", 3) == 3);
        XL_TEST_ASSERT(a.IndexOf(L"abc", 4) == 9);
        XL_TEST_ASSERT(a.IndexOf(L"abc", 9) == 9);
        XL_TEST_ASSERT(a.IndexOf(L"abc", 10) == -1);

        XL_TEST_ASSERT(a.LastIndexOf(L"abc") == 9);
        XL_TEST_ASSERT(a.LastIndexOf(L"abc", 11) == 9);
        XL_TEST_ASSERT(a.LastIndexOf(L"abc", 10) == 3);
        XL_TEST_ASSERT(a.LastIndexOf(L"abc", 5) == 3);
        XL_TEST_ASSERT(a.LastIndexOf(L"abc", 4) == -1);
    }

    XL_TEST_CASE()
    {
        String a(L"123abc456abc789");

        XL_TEST_ASSERT(a.Replace(L"abc", L"") == L"123456789");
        XL_TEST_ASSERT(a.Replace(L"abc", L"@") == L"123@456@789");
        XL_TEST_ASSERT(a.Replace(L"", L"@") == L"123abc456abc789");
        XL_TEST_ASSERT(a.Replace(L"abc", L"@", 1) == L"123@456abc789");
        XL_TEST_ASSERT(a == L"123abc456abc789");
    }

    XL_TEST_CASE()
    {
        String a(L"123|456||789|");

        Array<String> v = a.Split(L"|");

        XL_TEST_ASSERT(v.Size() == 5);
        XL_TEST_ASSERT(v[0] == L"123");
        XL_TEST_ASSERT(v[1] == L"456");
        XL_TEST_ASSERT(v[2] == L"");
        XL_TEST_ASSERT(v[3] == L"789");
        XL_TEST_ASSERT(v[4] == L"");

        v = a.Split(L"|", 3);

        XL_TEST_ASSERT(v.Size() == 3);
        XL_TEST_ASSERT(v[0] == L"123");
        XL_TEST_ASSERT(v[1] == L"456");
        XL_TEST_ASSERT(v[2] == L"|789|");

        String b(L"123|456");

        v = b.Split(L"|", 3);

        XL_TEST_ASSERT(v.Size() == 2);
        XL_TEST_ASSERT(v[0] == L"123");
        XL_TEST_ASSERT(v[1] == L"456");
    }
}
