//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-08-14
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include "../UnitTestFrame.h"
#include <xl/Objects/xlString.h>

using namespace xl;

TEST_CASE(ctor)
{
    String a;
    TEST_ASSERT(a == L"");

    String b(L"123");
    TEST_ASSERT(b == L"123");

    String c(b);
    TEST_ASSERT(c == L"123");

    String d(L"123", 3);
    TEST_ASSERT(d == L"123");

    String e(L"123", 4);
    TEST_ASSERT(e == L"123");

    String f(L"1\00023", 3);
    TEST_ASSERT(f.Length() == 3 && f[0] == L'1' && f[1] == L'\0' && f[2] == L'2');
}

TEST_CASE(operator_set)
{
    String a(L"123");
    String b(L"456");

    b = a;
    TEST_ASSERT(b == a);
}

TEST_CASE(operator_compare)
{
    TEST_ASSERT(String(L"") == L"");
    TEST_ASSERT(String(L"123") != L"");
    TEST_ASSERT(String(L"") != L"123");
    TEST_ASSERT(String(L"123") == L"123");
    TEST_ASSERT(String(L"123") <= L"123");
    TEST_ASSERT(String(L"123") >= L"123");
    TEST_ASSERT(String(L"123") < L"223");
    TEST_ASSERT(String(L"123") <= L"223");
    TEST_ASSERT(String(L"123") > L"023");
    TEST_ASSERT(String(L"123") >= L"023");
}

TEST_CASE(operator_cat)
{
    TEST_ASSERT(String(L"") + String(L"") == L"");
    TEST_ASSERT(String(L"a") + String(L"") == L"a");
    TEST_ASSERT(String(L"") + String(L"b") == L"b");
    TEST_ASSERT(String(L"a") + String(L"b") == L"ab");

    TEST_ASSERT((String(L"") += String(L"")) == L"");
    TEST_ASSERT((String(L"a") += String(L"")) == L"a");
    TEST_ASSERT((String(L"") += String(L"b")) == L"b");
    TEST_ASSERT((String(L"a") += String(L"b")) == L"ab");
}

TEST_CASE(operator_index)
{
    String a(L"123");

    TEST_ASSERT(a[0] == L'1');
    TEST_ASSERT(a[1] == L'2');
    TEST_ASSERT(a[2] == L'3');
    TEST_ASSERT(a[3] == L'\0');

    a[0] = L'4';
    a[1] = L'5';
    a[2] = L'6';

    TEST_ASSERT(a[0] == L'4');
    TEST_ASSERT(a[1] == L'5');
    TEST_ASSERT(a[2] == L'6');
}

TEST_CASE(method_GetAddress)
{
    String a(L"123");
    TEST_ASSERT(a.GetAddress() == &a[0]);
}

TEST_CASE(method_Length)
{
    String a;
    TEST_ASSERT(a.Length() == 0);
    TEST_ASSERT(a.Empty());

    a = L"1";
    TEST_ASSERT(a.Length() == 1);
    TEST_ASSERT(!a.Empty());

    a = L"12";
    TEST_ASSERT(a.Length() == 2);
    TEST_ASSERT(!a.Empty());

    a = L"123";
    TEST_ASSERT(a.Length() == 3);
    TEST_ASSERT(!a.Empty());
}

TEST_CASE(method_case)
{
    String a(L"Hello!");

    TEST_ASSERT(a.ToLower() == L"hello!");
    TEST_ASSERT(a.ToUpper() == L"HELLO!");

    TEST_ASSERT(a == L"Hello!");
    a.MakeLower();
    TEST_ASSERT(a == L"hello!");
    a.MakeUpper();
    TEST_ASSERT(a == L"HELLO!");
}

TEST_CASE(method_append)
{
    String a(L"123");

    a.AppendBack(L'a');
    TEST_ASSERT(a == L"123a");

    a.AppendFront(L'a');
    TEST_ASSERT(a == L"a123a");

    a.AppendBack(L'b', 3);
    TEST_ASSERT(a == L"a123abbb");

    a.AppendFront(L'b', 3);
    TEST_ASSERT(a == L"bbba123abbb");

    a.Clear();
    TEST_ASSERT(a == L"");
}

TEST_CASE(method_substring)
{
    String a(L"12345");

    TEST_ASSERT(a.Left(0) == L"");
    TEST_ASSERT(a.Left(1) == L"1");
    TEST_ASSERT(a.Left(2) == L"12");
    TEST_ASSERT(a.Left(3) == L"123");
    TEST_ASSERT(a.Left(4) == L"1234");
    TEST_ASSERT(a.Left(5) == L"12345");
    TEST_ASSERT(a.Right(0) == L"");
    TEST_ASSERT(a.Right(1) == L"5");
    TEST_ASSERT(a.Right(2) == L"45");
    TEST_ASSERT(a.Right(3) == L"345");
    TEST_ASSERT(a.Right(4) == L"2345");
    TEST_ASSERT(a.Right(5) == L"12345");
    TEST_ASSERT(a.SubString(0, 0) == L"");
    TEST_ASSERT(a.SubString(0, 1) == L"1");
    TEST_ASSERT(a.SubString(0, 2) == L"12");
    TEST_ASSERT(a.SubString(0, 3) == L"123");
    TEST_ASSERT(a.SubString(0, 4) == L"1234");
    TEST_ASSERT(a.SubString(0, 5) == L"12345");
    TEST_ASSERT(a.SubString(1, 0) == L"");
    TEST_ASSERT(a.SubString(1, 1) == L"2");
    TEST_ASSERT(a.SubString(1, 2) == L"23");
    TEST_ASSERT(a.SubString(1, 3) == L"234");
    TEST_ASSERT(a.SubString(1, 4) == L"2345");
    TEST_ASSERT(a.SubString(2, 0) == L"");
    TEST_ASSERT(a.SubString(2, 1) == L"3");
    TEST_ASSERT(a.SubString(2, 2) == L"34");
    TEST_ASSERT(a.SubString(2, 3) == L"345");
    TEST_ASSERT(a.SubString(3, 0) == L"");
    TEST_ASSERT(a.SubString(3, 1) == L"4");
    TEST_ASSERT(a.SubString(3, 2) == L"45");
    TEST_ASSERT(a.SubString(4, 0) == L"");
    TEST_ASSERT(a.SubString(4, 1) == L"5");
    TEST_ASSERT(a.SubString(5, 0) == L"");

    TEST_ASSERT(a.Left(10) == L"12345");
}

TEST_CASE(method_find)
{
    String a(L"123abc456abc789");

    TEST_ASSERT(a.IndexOf(L"abc") == 3);
    TEST_ASSERT(a.IndexOf(L"abc", 3) == 3);
    TEST_ASSERT(a.IndexOf(L"abc", 4) == 9);
    TEST_ASSERT(a.IndexOf(L"abc", 9) == 9);
    TEST_ASSERT(a.IndexOf(L"abc", 10) == -1);

    TEST_ASSERT(a.LastIndexOf(L"abc") == 9);
    TEST_ASSERT(a.LastIndexOf(L"abc", 11) == 9);
    TEST_ASSERT(a.LastIndexOf(L"abc", 10) == 3);
    TEST_ASSERT(a.LastIndexOf(L"abc", 5) == 3);
    TEST_ASSERT(a.LastIndexOf(L"abc", 4) == -1);
}

TEST_CASE(method_replace)
{
    String a(L"123abc456abc789");

    TEST_ASSERT(a.Replace(L"abc", L"") == L"123456789");
    TEST_ASSERT(a.Replace(L"abc", L"@") == L"123@456@789");
    TEST_ASSERT(a.Replace(L"", L"@") == L"123abc456abc789");
    TEST_ASSERT(a.Replace(L"abc", L"@", 1) == L"123@456abc789");
    TEST_ASSERT(a == L"123abc456abc789");
}

TEST_CASE(method_split)
{
    String a(L"123|456||789|");

    Array<String> v = a.Split(L"|");

    TEST_ASSERT(v.Size() == 5);
    TEST_ASSERT(v[0] == L"123");
    TEST_ASSERT(v[1] == L"456");
    TEST_ASSERT(v[2] == L"");
    TEST_ASSERT(v[3] == L"789");
    TEST_ASSERT(v[4] == L"");

    v = a.Split(L"|", 3);

    TEST_ASSERT(v.Size() == 3);
    TEST_ASSERT(v[0] == L"123");
    TEST_ASSERT(v[1] == L"456");
    TEST_ASSERT(v[2] == L"|789|");
    
    String b(L"123|456");

    v = b.Split(L"|", 3);

    TEST_ASSERT(v.Size() == 2);
    TEST_ASSERT(v[0] == L"123");
    TEST_ASSERT(v[1] == L"456");
}

int main()
{
    return 0;
}
