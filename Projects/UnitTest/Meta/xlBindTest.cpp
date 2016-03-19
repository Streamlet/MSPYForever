//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlBindTest.cpp
//    Author:      Streamlet
//    Create Time: 2012-04-22
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/AppHelper/xlUnitTest.h"
#include "../../../Include/xl/Common/Meta/xlBind.h"
#include "../../../Include/xl/Windows/Threads/xlThread.h"

namespace
{
    using namespace xl;
    using namespace xl::Windows;

    int __cdecl cdecl0()
    {
        return 0;
    }

    int __cdecl cdecl1(int a)
    {
        return a;
    }

    int __cdecl cdecl2(int a, int b)
    {
        return a * 10 + b;
    }

    int __cdecl cdecl3(int a, int b, int c)
    {
        return a * 100 + b * 10 + c;
    }

    int __stdcall stdcall0()
    {
        return 0;
    }

    int __stdcall stdcall1(int a)
    {
        return a;
    }

    int __stdcall stdcall2(int a, int b)
    {
        return a * 10 + b;
    }

    int __stdcall stdcall3(int a, int b, int c)
    {
        return a * 100 + b * 10 + c;
    }

    int __fastcall fastcall0()
    {
        return 0;
    }

    int __fastcall fastcall1(int a)
    {
        return a;
    }

    int __fastcall fastcall2(int a, int b)
    {
        return a * 10 + b;
    }

    int __fastcall fastcall3(int a, int b, int c)
    {
        return a * 100 + b * 10 + c;
    }

    struct S
    {
        int __cdecl cdecl0()
        {
            return 0;
        }

        int __cdecl cdecl1(int a)
        {
            return a;
        }

        int __cdecl cdecl2(int a, int b)
        {
            return a * 10 + b;
        }

        int __cdecl cdecl3(int a, int b, int c)
        {
            return a * 100 + b * 10 + c;
        }

        int __stdcall stdcall0()
        {
            return 0;
        }

        int __stdcall stdcall1(int a)
        {
            return a;
        }

        int __stdcall stdcall2(int a, int b)
        {
            return a * 10 + b;
        }

        int __stdcall stdcall3(int a, int b, int c)
        {
            return a * 100 + b * 10 + c;
        }

        int __fastcall fastcall0()
        {
            return 0;
        }

        int __fastcall fastcall1(int a)
        {
            return a;
        }

        int __fastcall fastcall2(int a, int b)
        {
            return a * 10 + b;
        }

        int __fastcall fastcall3(int a, int b, int c)
        {
            return a * 100 + b * 10 + c;
        }

        int __thiscall thiscall0()
        {
            return 0;
        }

        int __thiscall thiscall1(int a)
        {
            return a;
        }

        int __thiscall thiscall2(int a, int b)
        {
            return a * 10 + b;
        }

        int __thiscall thiscall3(int a, int b, int c)
        {
            return a * 100 + b * 10 + c;
        }

    } s;

    struct F
    {
        int operator()()
        {
            return 0;
        }

        int operator()(int a)
        {
            return a;
        }

        int operator()(int a, int b)
        {
            return a * 10 + b;
        }

        int operator()(int a, int b, int c)
        {
            return a * 100 + b * 10 + c;
        }

    } f;

    int test_const(const int i)
    {
        return i;
    }

    int test_ref(int &i)
    {
        return ++i;
    }

    int test_const_ref(const int &i)
    {
        return i;
    }

#ifdef __XL_CPP11

    int test_r_ref(int &&i)
    {
        return i;
    }

    int test_const_r_ref(const int &&i)
    {
        return i;
    }

#endif

    DWORD test_const_thread(HANDLE hQuitEvent, LPVOID pParam, const int i)
    {
        return i;
    }

    DWORD test_ref_thread(HANDLE hQuitEvent, LPVOID pParam, int &i)
    {
        return ++i;
    }

    DWORD test_const_ref_thread(HANDLE hQuitEvent, LPVOID pParam, const int &i)
    {
        return i;
    }

#ifdef __XL_CPP11

    DWORD test_r_ref_thread(HANDLE hQuitEvent, LPVOID pParam, int &&i)
    {
        return i;
    }

    DWORD test_const_r_ref_thread(HANDLE hQuitEvent, LPVOID pParam, const int &&i)
    {
        return i;
    }

#endif

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Bind(cdecl0)() == 0);
        XL_TEST_ASSERT(Bind(cdecl1, _1)(1) == 1);
        XL_TEST_ASSERT(Bind(cdecl1, 2)() == 2);
        XL_TEST_ASSERT(Bind(cdecl2, _1, _2)(1, 2) == 12);
        XL_TEST_ASSERT(Bind(cdecl2, _2, _1)(1, 2) == 21);
        XL_TEST_ASSERT(Bind(cdecl2, _1, _2)(2, 1) == 21);
        XL_TEST_ASSERT(Bind(cdecl2, _2, _1)(2, 1) == 12);
        XL_TEST_ASSERT(Bind(cdecl2, _1, 2)(1) == 12);
        XL_TEST_ASSERT(Bind(cdecl2, 2, _1)(1) == 21);
        XL_TEST_ASSERT(Bind(cdecl2, 1, 2)() == 12);
        XL_TEST_ASSERT(Bind(cdecl2, 2, 1)() == 21);
        XL_TEST_ASSERT(Bind(cdecl3, _1, _2, _3)(1, 2, 3) == 123);
        XL_TEST_ASSERT(Bind(cdecl3, _1, _3, _2)(1, 2, 3) == 132);
        XL_TEST_ASSERT(Bind(cdecl3, _2, _1, _3)(1, 2, 3) == 213);
        XL_TEST_ASSERT(Bind(cdecl3, _2, _3, _1)(1, 2, 3) == 231);
        XL_TEST_ASSERT(Bind(cdecl3, _3, _1, _2)(1, 2, 3) == 312);
        XL_TEST_ASSERT(Bind(cdecl3, _3, _2, _1)(1, 2, 3) == 321);
        XL_TEST_ASSERT(Bind(cdecl3, _1, _2, _3)(1, 3, 2) == 132);
        XL_TEST_ASSERT(Bind(cdecl3, _1, _2, _3)(2, 1, 3) == 213);
        XL_TEST_ASSERT(Bind(cdecl3, _1, _2, _3)(2, 3, 1) == 231);
        XL_TEST_ASSERT(Bind(cdecl3, _1, _2, _3)(3, 1, 2) == 312);
        XL_TEST_ASSERT(Bind(cdecl3, _1, _2, _3)(3, 2, 1) == 321);
        XL_TEST_ASSERT(Bind(cdecl3, _1, _2, 3)(1, 2) == 123);
        XL_TEST_ASSERT(Bind(cdecl3, _2, _1, 3)(1, 2) == 213);
        XL_TEST_ASSERT(Bind(cdecl3, _1, _2, 3)(2, 1) == 213);
        XL_TEST_ASSERT(Bind(cdecl3, _2, _1, 3)(2, 1) == 123);
        XL_TEST_ASSERT(Bind(cdecl3, _1, 3, _2)(1, 2) == 132);
        XL_TEST_ASSERT(Bind(cdecl3, _2, 3, _1)(1, 2) == 231);
        XL_TEST_ASSERT(Bind(cdecl3, _1, 3, _2)(2, 1) == 231);
        XL_TEST_ASSERT(Bind(cdecl3, _2, 3, _1)(2, 1) == 132);
        XL_TEST_ASSERT(Bind(cdecl3, 3, _1, _2)(1, 2) == 312);
        XL_TEST_ASSERT(Bind(cdecl3, 3, _2, _1)(1, 2) == 321);
        XL_TEST_ASSERT(Bind(cdecl3, 3, _1, _2)(2, 1) == 321);
        XL_TEST_ASSERT(Bind(cdecl3, 3, _2, _1)(2, 1) == 312);
        XL_TEST_ASSERT(Bind(cdecl3, _1, 2, 3)(1) == 123);
        XL_TEST_ASSERT(Bind(cdecl3, _1, 3, 2)(1) == 132);
        XL_TEST_ASSERT(Bind(cdecl3, 2, _1, 3)(1) == 213);
        XL_TEST_ASSERT(Bind(cdecl3, 3, _1, 2)(1) == 312);
        XL_TEST_ASSERT(Bind(cdecl3, 2, 3, _1)(1) == 231);
        XL_TEST_ASSERT(Bind(cdecl3, 3, 2, _1)(1) == 321);
        XL_TEST_ASSERT(Bind(cdecl3, 1, 2, 3)() == 123);
        XL_TEST_ASSERT(Bind(cdecl3, 1, 3, 2)() == 132);
        XL_TEST_ASSERT(Bind(cdecl3, 2, 1, 3)() == 213);
        XL_TEST_ASSERT(Bind(cdecl3, 2, 3, 1)() == 231);
        XL_TEST_ASSERT(Bind(cdecl3, 3, 1, 2)() == 312);
        XL_TEST_ASSERT(Bind(cdecl3, 3, 2, 1)() == 321);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Bind(stdcall0)() == 0);
        XL_TEST_ASSERT(Bind(stdcall1, _1)(1) == 1);
        XL_TEST_ASSERT(Bind(stdcall1, 2)() == 2);
        XL_TEST_ASSERT(Bind(stdcall2, _1, _2)(1, 2) == 12);
        XL_TEST_ASSERT(Bind(stdcall2, _2, _1)(1, 2) == 21);
        XL_TEST_ASSERT(Bind(stdcall2, _1, _2)(2, 1) == 21);
        XL_TEST_ASSERT(Bind(stdcall2, _2, _1)(2, 1) == 12);
        XL_TEST_ASSERT(Bind(stdcall2, _1, 2)(1) == 12);
        XL_TEST_ASSERT(Bind(stdcall2, 2, _1)(1) == 21);
        XL_TEST_ASSERT(Bind(stdcall2, 1, 2)() == 12);
        XL_TEST_ASSERT(Bind(stdcall2, 2, 1)() == 21);
        XL_TEST_ASSERT(Bind(stdcall3, _1, _2, _3)(1, 2, 3) == 123);
        XL_TEST_ASSERT(Bind(stdcall3, _1, _3, _2)(1, 2, 3) == 132);
        XL_TEST_ASSERT(Bind(stdcall3, _2, _1, _3)(1, 2, 3) == 213);
        XL_TEST_ASSERT(Bind(stdcall3, _2, _3, _1)(1, 2, 3) == 231);
        XL_TEST_ASSERT(Bind(stdcall3, _3, _1, _2)(1, 2, 3) == 312);
        XL_TEST_ASSERT(Bind(stdcall3, _3, _2, _1)(1, 2, 3) == 321);
        XL_TEST_ASSERT(Bind(stdcall3, _1, _2, _3)(1, 3, 2) == 132);
        XL_TEST_ASSERT(Bind(stdcall3, _1, _2, _3)(2, 1, 3) == 213);
        XL_TEST_ASSERT(Bind(stdcall3, _1, _2, _3)(2, 3, 1) == 231);
        XL_TEST_ASSERT(Bind(stdcall3, _1, _2, _3)(3, 1, 2) == 312);
        XL_TEST_ASSERT(Bind(stdcall3, _1, _2, _3)(3, 2, 1) == 321);
        XL_TEST_ASSERT(Bind(stdcall3, _1, _2, 3)(1, 2) == 123);
        XL_TEST_ASSERT(Bind(stdcall3, _2, _1, 3)(1, 2) == 213);
        XL_TEST_ASSERT(Bind(stdcall3, _1, _2, 3)(2, 1) == 213);
        XL_TEST_ASSERT(Bind(stdcall3, _2, _1, 3)(2, 1) == 123);
        XL_TEST_ASSERT(Bind(stdcall3, _1, 3, _2)(1, 2) == 132);
        XL_TEST_ASSERT(Bind(stdcall3, _2, 3, _1)(1, 2) == 231);
        XL_TEST_ASSERT(Bind(stdcall3, _1, 3, _2)(2, 1) == 231);
        XL_TEST_ASSERT(Bind(stdcall3, _2, 3, _1)(2, 1) == 132);
        XL_TEST_ASSERT(Bind(stdcall3, 3, _1, _2)(1, 2) == 312);
        XL_TEST_ASSERT(Bind(stdcall3, 3, _2, _1)(1, 2) == 321);
        XL_TEST_ASSERT(Bind(stdcall3, 3, _1, _2)(2, 1) == 321);
        XL_TEST_ASSERT(Bind(stdcall3, 3, _2, _1)(2, 1) == 312);
        XL_TEST_ASSERT(Bind(stdcall3, _1, 2, 3)(1) == 123);
        XL_TEST_ASSERT(Bind(stdcall3, _1, 3, 2)(1) == 132);
        XL_TEST_ASSERT(Bind(stdcall3, 2, _1, 3)(1) == 213);
        XL_TEST_ASSERT(Bind(stdcall3, 3, _1, 2)(1) == 312);
        XL_TEST_ASSERT(Bind(stdcall3, 2, 3, _1)(1) == 231);
        XL_TEST_ASSERT(Bind(stdcall3, 3, 2, _1)(1) == 321);
        XL_TEST_ASSERT(Bind(stdcall3, 1, 2, 3)() == 123);
        XL_TEST_ASSERT(Bind(stdcall3, 1, 3, 2)() == 132);
        XL_TEST_ASSERT(Bind(stdcall3, 2, 1, 3)() == 213);
        XL_TEST_ASSERT(Bind(stdcall3, 2, 3, 1)() == 231);
        XL_TEST_ASSERT(Bind(stdcall3, 3, 1, 2)() == 312);
        XL_TEST_ASSERT(Bind(stdcall3, 3, 2, 1)() == 321);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Bind(fastcall0)() == 0);
        XL_TEST_ASSERT(Bind(fastcall1, _1)(1) == 1);
        XL_TEST_ASSERT(Bind(fastcall1, 2)() == 2);
        XL_TEST_ASSERT(Bind(fastcall2, _1, _2)(1, 2) == 12);
        XL_TEST_ASSERT(Bind(fastcall2, _2, _1)(1, 2) == 21);
        XL_TEST_ASSERT(Bind(fastcall2, _1, _2)(2, 1) == 21);
        XL_TEST_ASSERT(Bind(fastcall2, _2, _1)(2, 1) == 12);
        XL_TEST_ASSERT(Bind(fastcall2, _1, 2)(1) == 12);
        XL_TEST_ASSERT(Bind(fastcall2, 2, _1)(1) == 21);
        XL_TEST_ASSERT(Bind(fastcall2, 1, 2)() == 12);
        XL_TEST_ASSERT(Bind(fastcall2, 2, 1)() == 21);
        XL_TEST_ASSERT(Bind(fastcall3, _1, _2, _3)(1, 2, 3) == 123);
        XL_TEST_ASSERT(Bind(fastcall3, _1, _3, _2)(1, 2, 3) == 132);
        XL_TEST_ASSERT(Bind(fastcall3, _2, _1, _3)(1, 2, 3) == 213);
        XL_TEST_ASSERT(Bind(fastcall3, _2, _3, _1)(1, 2, 3) == 231);
        XL_TEST_ASSERT(Bind(fastcall3, _3, _1, _2)(1, 2, 3) == 312);
        XL_TEST_ASSERT(Bind(fastcall3, _3, _2, _1)(1, 2, 3) == 321);
        XL_TEST_ASSERT(Bind(fastcall3, _1, _2, _3)(1, 3, 2) == 132);
        XL_TEST_ASSERT(Bind(fastcall3, _1, _2, _3)(2, 1, 3) == 213);
        XL_TEST_ASSERT(Bind(fastcall3, _1, _2, _3)(2, 3, 1) == 231);
        XL_TEST_ASSERT(Bind(fastcall3, _1, _2, _3)(3, 1, 2) == 312);
        XL_TEST_ASSERT(Bind(fastcall3, _1, _2, _3)(3, 2, 1) == 321);
        XL_TEST_ASSERT(Bind(fastcall3, _1, _2, 3)(1, 2) == 123);
        XL_TEST_ASSERT(Bind(fastcall3, _2, _1, 3)(1, 2) == 213);
        XL_TEST_ASSERT(Bind(fastcall3, _1, _2, 3)(2, 1) == 213);
        XL_TEST_ASSERT(Bind(fastcall3, _2, _1, 3)(2, 1) == 123);
        XL_TEST_ASSERT(Bind(fastcall3, _1, 3, _2)(1, 2) == 132);
        XL_TEST_ASSERT(Bind(fastcall3, _2, 3, _1)(1, 2) == 231);
        XL_TEST_ASSERT(Bind(fastcall3, _1, 3, _2)(2, 1) == 231);
        XL_TEST_ASSERT(Bind(fastcall3, _2, 3, _1)(2, 1) == 132);
        XL_TEST_ASSERT(Bind(fastcall3, 3, _1, _2)(1, 2) == 312);
        XL_TEST_ASSERT(Bind(fastcall3, 3, _2, _1)(1, 2) == 321);
        XL_TEST_ASSERT(Bind(fastcall3, 3, _1, _2)(2, 1) == 321);
        XL_TEST_ASSERT(Bind(fastcall3, 3, _2, _1)(2, 1) == 312);
        XL_TEST_ASSERT(Bind(fastcall3, _1, 2, 3)(1) == 123);
        XL_TEST_ASSERT(Bind(fastcall3, _1, 3, 2)(1) == 132);
        XL_TEST_ASSERT(Bind(fastcall3, 2, _1, 3)(1) == 213);
        XL_TEST_ASSERT(Bind(fastcall3, 3, _1, 2)(1) == 312);
        XL_TEST_ASSERT(Bind(fastcall3, 2, 3, _1)(1) == 231);
        XL_TEST_ASSERT(Bind(fastcall3, 3, 2, _1)(1) == 321);
        XL_TEST_ASSERT(Bind(fastcall3, 1, 2, 3)() == 123);
        XL_TEST_ASSERT(Bind(fastcall3, 1, 3, 2)() == 132);
        XL_TEST_ASSERT(Bind(fastcall3, 2, 1, 3)() == 213);
        XL_TEST_ASSERT(Bind(fastcall3, 2, 3, 1)() == 231);
        XL_TEST_ASSERT(Bind(fastcall3, 3, 1, 2)() == 312);
        XL_TEST_ASSERT(Bind(fastcall3, 3, 2, 1)() == 321);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Bind(&s, &S::cdecl0)() == 0);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl1, _1)(1) == 1);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl1, 2)() == 2);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl2, _1, _2)(1, 2) == 12);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl2, _2, _1)(1, 2) == 21);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl2, _1, _2)(2, 1) == 21);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl2, _2, _1)(2, 1) == 12);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl2, _1, 2)(1) == 12);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl2, 2, _1)(1) == 21);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl2, 1, 2)() == 12);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl2, 2, 1)() == 21);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _1, _2, _3)(1, 2, 3) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _1, _3, _2)(1, 2, 3) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _2, _1, _3)(1, 2, 3) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _2, _3, _1)(1, 2, 3) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _3, _1, _2)(1, 2, 3) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _3, _2, _1)(1, 2, 3) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _1, _2, _3)(1, 3, 2) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _1, _2, _3)(2, 1, 3) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _1, _2, _3)(2, 3, 1) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _1, _2, _3)(3, 1, 2) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _1, _2, _3)(3, 2, 1) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _1, _2, 3)(1, 2) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _2, _1, 3)(1, 2) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _1, _2, 3)(2, 1) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _2, _1, 3)(2, 1) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _1, 3, _2)(1, 2) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _2, 3, _1)(1, 2) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _1, 3, _2)(2, 1) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _2, 3, _1)(2, 1) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, 3, _1, _2)(1, 2) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, 3, _2, _1)(1, 2) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, 3, _1, _2)(2, 1) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, 3, _2, _1)(2, 1) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _1, 2, 3)(1) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, _1, 3, 2)(1) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, 2, _1, 3)(1) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, 3, _1, 2)(1) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, 2, 3, _1)(1) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, 3, 2, _1)(1) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, 1, 2, 3)() == 123);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, 1, 3, 2)() == 132);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, 2, 1, 3)() == 213);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, 2, 3, 1)() == 231);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, 3, 1, 2)() == 312);
        XL_TEST_ASSERT(Bind(&s, &S::cdecl3, 3, 2, 1)() == 321);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Bind(&s, &S::stdcall0)() == 0);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall1, _1)(1) == 1);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall1, 2)() == 2);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall2, _1, _2)(1, 2) == 12);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall2, _2, _1)(1, 2) == 21);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall2, _1, _2)(2, 1) == 21);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall2, _2, _1)(2, 1) == 12);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall2, _1, 2)(1) == 12);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall2, 2, _1)(1) == 21);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall2, 1, 2)() == 12);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall2, 2, 1)() == 21);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _1, _2, _3)(1, 2, 3) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _1, _3, _2)(1, 2, 3) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _2, _1, _3)(1, 2, 3) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _2, _3, _1)(1, 2, 3) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _3, _1, _2)(1, 2, 3) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _3, _2, _1)(1, 2, 3) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _1, _2, _3)(1, 3, 2) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _1, _2, _3)(2, 1, 3) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _1, _2, _3)(2, 3, 1) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _1, _2, _3)(3, 1, 2) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _1, _2, _3)(3, 2, 1) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _1, _2, 3)(1, 2) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _2, _1, 3)(1, 2) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _1, _2, 3)(2, 1) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _2, _1, 3)(2, 1) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _1, 3, _2)(1, 2) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _2, 3, _1)(1, 2) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _1, 3, _2)(2, 1) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _2, 3, _1)(2, 1) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, 3, _1, _2)(1, 2) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, 3, _2, _1)(1, 2) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, 3, _1, _2)(2, 1) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, 3, _2, _1)(2, 1) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _1, 2, 3)(1) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, _1, 3, 2)(1) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, 2, _1, 3)(1) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, 3, _1, 2)(1) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, 2, 3, _1)(1) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, 3, 2, _1)(1) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, 1, 2, 3)() == 123);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, 1, 3, 2)() == 132);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, 2, 1, 3)() == 213);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, 2, 3, 1)() == 231);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, 3, 1, 2)() == 312);
        XL_TEST_ASSERT(Bind(&s, &S::stdcall3, 3, 2, 1)() == 321);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Bind(&s, &S::fastcall0)() == 0);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall1, _1)(1) == 1);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall1, 2)() == 2);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall2, _1, _2)(1, 2) == 12);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall2, _2, _1)(1, 2) == 21);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall2, _1, _2)(2, 1) == 21);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall2, _2, _1)(2, 1) == 12);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall2, _1, 2)(1) == 12);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall2, 2, _1)(1) == 21);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall2, 1, 2)() == 12);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall2, 2, 1)() == 21);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _1, _2, _3)(1, 2, 3) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _1, _3, _2)(1, 2, 3) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _2, _1, _3)(1, 2, 3) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _2, _3, _1)(1, 2, 3) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _3, _1, _2)(1, 2, 3) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _3, _2, _1)(1, 2, 3) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _1, _2, _3)(1, 3, 2) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _1, _2, _3)(2, 1, 3) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _1, _2, _3)(2, 3, 1) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _1, _2, _3)(3, 1, 2) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _1, _2, _3)(3, 2, 1) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _1, _2, 3)(1, 2) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _2, _1, 3)(1, 2) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _1, _2, 3)(2, 1) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _2, _1, 3)(2, 1) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _1, 3, _2)(1, 2) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _2, 3, _1)(1, 2) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _1, 3, _2)(2, 1) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _2, 3, _1)(2, 1) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, 3, _1, _2)(1, 2) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, 3, _2, _1)(1, 2) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, 3, _1, _2)(2, 1) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, 3, _2, _1)(2, 1) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _1, 2, 3)(1) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, _1, 3, 2)(1) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, 2, _1, 3)(1) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, 3, _1, 2)(1) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, 2, 3, _1)(1) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, 3, 2, _1)(1) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, 1, 2, 3)() == 123);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, 1, 3, 2)() == 132);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, 2, 1, 3)() == 213);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, 2, 3, 1)() == 231);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, 3, 1, 2)() == 312);
        XL_TEST_ASSERT(Bind(&s, &S::fastcall3, 3, 2, 1)() == 321);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Bind(&s, &S::thiscall0)() == 0);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall1, _1)(1) == 1);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall1, 2)() == 2);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall2, _1, _2)(1, 2) == 12);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall2, _2, _1)(1, 2) == 21);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall2, _1, _2)(2, 1) == 21);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall2, _2, _1)(2, 1) == 12);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall2, _1, 2)(1) == 12);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall2, 2, _1)(1) == 21);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall2, 1, 2)() == 12);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall2, 2, 1)() == 21);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _1, _2, _3)(1, 2, 3) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _1, _3, _2)(1, 2, 3) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _2, _1, _3)(1, 2, 3) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _2, _3, _1)(1, 2, 3) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _3, _1, _2)(1, 2, 3) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _3, _2, _1)(1, 2, 3) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _1, _2, _3)(1, 3, 2) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _1, _2, _3)(2, 1, 3) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _1, _2, _3)(2, 3, 1) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _1, _2, _3)(3, 1, 2) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _1, _2, _3)(3, 2, 1) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _1, _2, 3)(1, 2) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _2, _1, 3)(1, 2) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _1, _2, 3)(2, 1) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _2, _1, 3)(2, 1) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _1, 3, _2)(1, 2) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _2, 3, _1)(1, 2) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _1, 3, _2)(2, 1) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _2, 3, _1)(2, 1) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, 3, _1, _2)(1, 2) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, 3, _2, _1)(1, 2) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, 3, _1, _2)(2, 1) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, 3, _2, _1)(2, 1) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _1, 2, 3)(1) == 123);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, _1, 3, 2)(1) == 132);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, 2, _1, 3)(1) == 213);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, 3, _1, 2)(1) == 312);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, 2, 3, _1)(1) == 231);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, 3, 2, _1)(1) == 321);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, 1, 2, 3)() == 123);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, 1, 3, 2)() == 132);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, 2, 1, 3)() == 213);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, 2, 3, 1)() == 231);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, 3, 1, 2)() == 312);
        XL_TEST_ASSERT(Bind(&s, &S::thiscall3, 3, 2, 1)() == 321);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Bind(Function<int ()>(f))() == 0);
        XL_TEST_ASSERT(Bind(Function<int (int)>(f), _1)(1) == 1);
        XL_TEST_ASSERT(Bind(Function<int (int)>(f), 2)() == 2);
        XL_TEST_ASSERT(Bind(Function<int (int, int)>(f), _1, _2)(1, 2) == 12);
        XL_TEST_ASSERT(Bind(Function<int (int, int)>(f), _2, _1)(1, 2) == 21);
        XL_TEST_ASSERT(Bind(Function<int (int, int)>(f), _1, _2)(2, 1) == 21);
        XL_TEST_ASSERT(Bind(Function<int (int, int)>(f), _2, _1)(2, 1) == 12);
        XL_TEST_ASSERT(Bind(Function<int (int, int)>(f), _1, 2)(1) == 12);
        XL_TEST_ASSERT(Bind(Function<int (int, int)>(f), 2, _1)(1) == 21);
        XL_TEST_ASSERT(Bind(Function<int (int, int)>(f), 1, 2)() == 12);
        XL_TEST_ASSERT(Bind(Function<int (int, int)>(f), 2, 1)() == 21);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _1, _2, _3)(1, 2, 3) == 123);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _1, _3, _2)(1, 2, 3) == 132);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _2, _1, _3)(1, 2, 3) == 213);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _2, _3, _1)(1, 2, 3) == 231);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _3, _1, _2)(1, 2, 3) == 312);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _3, _2, _1)(1, 2, 3) == 321);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _1, _2, _3)(1, 3, 2) == 132);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _1, _2, _3)(2, 1, 3) == 213);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _1, _2, _3)(2, 3, 1) == 231);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _1, _2, _3)(3, 1, 2) == 312);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _1, _2, _3)(3, 2, 1) == 321);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _1, _2, 3)(1, 2) == 123);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _2, _1, 3)(1, 2) == 213);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _1, _2, 3)(2, 1) == 213);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _2, _1, 3)(2, 1) == 123);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _1, 3, _2)(1, 2) == 132);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _2, 3, _1)(1, 2) == 231);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _1, 3, _2)(2, 1) == 231);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _2, 3, _1)(2, 1) == 132);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), 3, _1, _2)(1, 2) == 312);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), 3, _2, _1)(1, 2) == 321);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), 3, _1, _2)(2, 1) == 321);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), 3, _2, _1)(2, 1) == 312);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _1, 2, 3)(1) == 123);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), _1, 3, 2)(1) == 132);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), 2, _1, 3)(1) == 213);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), 3, _1, 2)(1) == 312);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), 2, 3, _1)(1) == 231);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), 3, 2, _1)(1) == 321);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), 1, 2, 3)() == 123);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), 1, 3, 2)() == 132);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), 2, 1, 3)() == 213);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), 2, 3, 1)() == 231);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), 3, 1, 2)() == 312);
        XL_TEST_ASSERT(Bind(Function<int (int, int, int)>(f), 3, 2, 1)() == 321);
    }

    XL_TEST_CASE()
    {
        int i = 0;

        XL_TEST_ASSERT(Bind(test_const, _1)(i) == 0);
        XL_TEST_ASSERT(Bind(test_const, i)() == 0);
#ifdef __XL_CPP11
        XL_TEST_ASSERT(Bind(test_ref, _1)(i) == 1);
#endif
        XL_TEST_ASSERT(i == 1);

#ifdef __XL_CPP11
        XL_TEST_ASSERT(Bind(test_ref, i)() == 2);
#endif
        XL_TEST_ASSERT(i == 2);
#ifdef __XL_CPP11
        i = 0;
        XL_TEST_ASSERT(Bind(test_const_ref, _1)(i) == 0);
        XL_TEST_ASSERT(Bind(test_r_ref, _1)(0) == 0);
        XL_TEST_ASSERT(Bind(test_const_r_ref, _1)(0) == 0);
#endif
    }

    XL_TEST_CASE()
    {
        int i = 0;

        {
            Thread<> t;
            t.Create(xl::Bind(test_const_thread, _1, _2, i), nullptr);
            t.Wait(INFINITE);
            XL_TEST_ASSERT(i == 0);

            DWORD dwExitCode = 0;
            t.GetExitCode(&dwExitCode);
            XL_TEST_ASSERT(dwExitCode == 0);
        }

#ifdef __XL_CPP11

        {
            Thread<> t;
            t.Create(xl::Bind(test_ref_thread, _1, _2, i), nullptr);
            t.Wait(INFINITE);
            XL_TEST_ASSERT(i == 1);

            DWORD dwExitCode = 0;
            t.GetExitCode(&dwExitCode);
            XL_TEST_ASSERT(dwExitCode == 1);
            i = 0;
        }

        {
            int *p = new int;
            *p = 0;
            Thread<> t;
            t.Create(xl::Bind(test_ref_thread, _1, _2, *p), nullptr);
            t.Wait(INFINITE);
            XL_TEST_ASSERT(*p == 1);

            DWORD dwExitCode = 0;
            t.GetExitCode(&dwExitCode);
            XL_TEST_ASSERT(dwExitCode == 1);
            delete p;
        }


        {
            Thread<> t;
            t.Create(xl::Bind(test_const_ref_thread, _1, _2, i), nullptr);
            t.Wait(INFINITE);
            XL_TEST_ASSERT(i == 0);

            DWORD dwExitCode = 0;
            t.GetExitCode(&dwExitCode);
            XL_TEST_ASSERT(dwExitCode == 0);
        }

        {
            Thread<> t;
            t.Create(xl::Bind(test_r_ref_thread, _1, _2, 0), nullptr);
            t.Wait(INFINITE);

            DWORD dwExitCode = 0;
            t.GetExitCode(&dwExitCode);
            XL_TEST_ASSERT(dwExitCode == 0);
        }

        {
            Thread<> t;
            t.Create(xl::Bind(test_const_r_ref_thread, _1, _2, 0), nullptr);
            t.Wait(INFINITE);

            DWORD dwExitCode = 0;
            t.GetExitCode(&dwExitCode);
            XL_TEST_ASSERT(dwExitCode == 0);
        }

#endif

    }
}
