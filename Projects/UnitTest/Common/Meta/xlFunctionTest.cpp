//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlFunctionTest.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../../Include/xl/AppHelper/xlUnitTest.h"
#include "../../../../Include/xl/Common/Meta/xlFunction.h"

namespace
{
    using namespace xl;

    void __cdecl voidcdecl0()
    {

    }

    void __cdecl voidcdecl1(int a)
    {

    }

    void __cdecl voidcdecl2(int a, int b)
    {

    }

    void __cdecl voidcdecl3(int a, int b, int c)
    {

    }

    void __stdcall voidstdcall0()
    {

    }

    void __stdcall voidstdcall1(int a)
    {

    }

    void __stdcall voidstdcall2(int a, int b)
    {

    }

    void __stdcall voidstdcall3(int a, int b, int c)
    {

    }

    void __fastcall voidfastcall0()
    {

    }

    void __fastcall voidfastcall1(int a)
    {

    }

    void __fastcall voidfastcall2(int a, int b)
    {

    }

    void __fastcall voidfastcall3(int a, int b, int c)
    {

    }

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
        void __cdecl voidcdecl0()
        {

        }

        void __cdecl voidcdecl1(int a)
        {

        }

        void __cdecl voidcdecl2(int a, int b)
        {

        }

        void __cdecl voidcdecl3(int a, int b, int c)
        {

        }

        void __stdcall voidstdcall0()
        {

        }

        void __stdcall voidstdcall1(int a)
        {

        }

        void __stdcall voidstdcall2(int a, int b)
        {

        }

        void __stdcall voidstdcall3(int a, int b, int c)
        {

        }

        void __fastcall voidfastcall0()
        {

        }

        void __fastcall voidfastcall1(int a)
        {

        }

        void __fastcall voidfastcall2(int a, int b)
        {

        }

        void __fastcall voidfastcall3(int a, int b, int c)
        {

        }

        void __thiscall voidthiscall0()
        {

        }

        void __thiscall voidthiscall1(int a)
        {

        }

        void __thiscall voidthiscall2(int a, int b)
        {

        }

        void __thiscall voidthiscall3(int a, int b, int c)
        {

        }

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

    struct VOIDF
    {
        void operator()()
        {

        }

        void operator()(int a)
        {

        }

        void operator()(int a, int b)
        {

        }

        void operator()(int a, int b, int c)
        {

        }

    } voidf;

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

    XL_TEST_CASE()
    {
        Function<void ()>             void0(voidcdecl0);
        Function<void (int)>          void1(voidcdecl1);
        Function<void (int, int)>     void2(voidcdecl2);
        Function<void (int, int, int)>void3(voidcdecl3);
    }

    XL_TEST_CASE()
    {
        Function<void ()>             void0(voidstdcall0);
        Function<void (int)>          void1(voidstdcall1);
        Function<void (int, int)>     void2(voidstdcall2);
        Function<void (int, int, int)>void3(voidstdcall3);
    }

    XL_TEST_CASE()
    {
        Function<void ()>             void0(voidfastcall0);
        Function<void (int)>          void1(voidfastcall1);
        Function<void (int, int)>     void2(voidfastcall2);
        Function<void (int, int, int)>void3(voidfastcall3);
    }

    XL_TEST_CASE()
    {
        Function<void ()>             void0(&s, &S::voidcdecl0);
        Function<void (int)>          void1(&s, &S::voidcdecl1);
        Function<void (int, int)>     void2(&s, &S::voidcdecl2);
        Function<void (int, int, int)>void3(&s, &S::voidcdecl3);
    }

    XL_TEST_CASE()
    {
        Function<void ()>             void0(&s, &S::voidstdcall0);
        Function<void (int)>          void1(&s, &S::voidstdcall1);
        Function<void (int, int)>     void2(&s, &S::voidstdcall2);
        Function<void (int, int, int)>void3(&s, &S::voidstdcall3);
    }

    XL_TEST_CASE()
    {
        Function<void ()>             void0(&s, &S::voidfastcall0);
        Function<void (int)>          void1(&s, &S::voidfastcall1);
        Function<void (int, int)>     void2(&s, &S::voidfastcall2);
        Function<void (int, int, int)>void3(&s, &S::voidfastcall3);
    }

    XL_TEST_CASE()
    {
        Function<void ()>             void0(&s, &S::voidthiscall0);
        Function<void (int)>          void1(&s, &S::voidthiscall1);
        Function<void (int, int)>     void2(&s, &S::voidthiscall2);
        Function<void (int, int, int)>void3(&s, &S::voidthiscall3);
    }

    XL_TEST_CASE()
    {
        Function<void ()>             void0(voidf);
        Function<void (int)>          void1(voidf);
        Function<void (int, int)>     void2(voidf);
        Function<void (int, int, int)>void3(voidf);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Function<int ()>             (cdecl0)() == 0);
        XL_TEST_ASSERT(Function<int (int)>          (cdecl1)(1) == 1);
        XL_TEST_ASSERT(Function<int (int, int)>     (cdecl2)(1, 2) == 12);
        XL_TEST_ASSERT(Function<int (int, int, int)>(cdecl3)(1, 2, 3) == 123);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Function<int ()>             (stdcall0)() == 0);
        XL_TEST_ASSERT(Function<int (int)>          (stdcall1)(1) == 1);
        XL_TEST_ASSERT(Function<int (int, int)>     (stdcall2)(1, 2) == 12);
        XL_TEST_ASSERT(Function<int (int, int, int)>(stdcall3)(1, 2, 3) == 123);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Function<int ()>             (fastcall0)() == 0);
        XL_TEST_ASSERT(Function<int (int)>          (fastcall1)(1) == 1);
        XL_TEST_ASSERT(Function<int (int, int)>     (fastcall2)(1, 2) == 12);
        XL_TEST_ASSERT(Function<int (int, int, int)>(fastcall3)(1, 2, 3) == 123);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Function<int ()>             (&s, &S::cdecl0)() == 0);
        XL_TEST_ASSERT(Function<int (int)>          (&s, &S::cdecl1)(1) == 1);
        XL_TEST_ASSERT(Function<int (int, int)>     (&s, &S::cdecl2)(1, 2) == 12);
        XL_TEST_ASSERT(Function<int (int, int, int)>(&s, &S::cdecl3)(1, 2, 3) == 123);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Function<int ()>             (&s, &S::stdcall0)() == 0);
        XL_TEST_ASSERT(Function<int (int)>          (&s, &S::stdcall1)(1) == 1);
        XL_TEST_ASSERT(Function<int (int, int)>     (&s, &S::stdcall2)(1, 2) == 12);
        XL_TEST_ASSERT(Function<int (int, int, int)>(&s, &S::stdcall3)(1, 2, 3) == 123);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Function<int ()>             (&s, &S::fastcall0)() == 0);
        XL_TEST_ASSERT(Function<int (int)>          (&s, &S::fastcall1)(1) == 1);
        XL_TEST_ASSERT(Function<int (int, int)>     (&s, &S::fastcall2)(1, 2) == 12);
        XL_TEST_ASSERT(Function<int (int, int, int)>(&s, &S::fastcall3)(1, 2, 3) == 123);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Function<int ()>             (&s, &S::thiscall0)() == 0);
        XL_TEST_ASSERT(Function<int (int)>          (&s, &S::thiscall1)(1) == 1);
        XL_TEST_ASSERT(Function<int (int, int)>     (&s, &S::thiscall2)(1, 2) == 12);
        XL_TEST_ASSERT(Function<int (int, int, int)>(&s, &S::thiscall3)(1, 2, 3) == 123);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Function<int ()>             (f)() == 0);
        XL_TEST_ASSERT(Function<int (int)>          (f)(1) == 1);
        XL_TEST_ASSERT(Function<int (int, int)>     (f)(1, 2) == 12);
        XL_TEST_ASSERT(Function<int (int, int, int)>(f)(1, 2, 3) == 123);
    }

    XL_TEST_CASE()
    {
        int i = 0;

        XL_TEST_ASSERT(Function<int (const int)>(test_const)(i) == 0);
        XL_TEST_ASSERT(Function<int (int &)>(test_ref)(i) == 1);
        XL_TEST_ASSERT(i == 1);
        --i;
        XL_TEST_ASSERT(Function<int (const int &)>(test_const_ref)(i) == 0);

#ifdef __XL_CPP11
        XL_TEST_ASSERT(Function<int (int &&)>(test_r_ref)(0) == 0);
        XL_TEST_ASSERT(Function<int (const int &&)>(test_const_r_ref)(0) == 0);
#endif
    }
}
