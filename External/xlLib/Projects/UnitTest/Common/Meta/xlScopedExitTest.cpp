//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlScopedExitTest.cpp
//    Author:      Streamlet
//    Create Time: 2012-04-22
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/AppHelper/xlUnitTest.h"
#include "../../../Include/xl/Common/Meta/xlScopeExit.h"

namespace
{
    using namespace xl;

    void TestInc(int *p)
    {
        ++*p;
    }

    XL_TEST_CASE()
    {
        int i = 0;

        {
            XL_ON_BLOCK_EXIT(TestInc, &i);
        }

        XL_TEST_ASSERT(i == 1);

        {
            ScopeGuard sg = MakeGuard(Bind(TestInc, &i));
        }

        XL_TEST_ASSERT(i == 2);

        {
            ScopeGuard sg = MakeGuard(Bind(TestInc, &i));
            sg.Dismiss();
        }

        XL_TEST_ASSERT(i == 2);
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

    XL_TEST_CASE()
    {
        {
            XL_ON_BLOCK_EXIT(cdecl0);
        }
        {
            XL_ON_BLOCK_EXIT(cdecl1, 1);
        }
        {
            XL_ON_BLOCK_EXIT(cdecl2, 1, 2);
        }
        {
            XL_ON_BLOCK_EXIT(cdecl3, 1, 2, 3);
        }
    }

    XL_TEST_CASE()
    {
        {
            XL_ON_BLOCK_EXIT(stdcall0);
        }
        {
            XL_ON_BLOCK_EXIT(stdcall1, 1);
        }
        {
            XL_ON_BLOCK_EXIT(stdcall2, 1, 2);
        }
        {
            XL_ON_BLOCK_EXIT(stdcall3, 1, 2, 3);
        }
    }

    XL_TEST_CASE()
    {
        {
            XL_ON_BLOCK_EXIT(fastcall0);
        }
        {
            XL_ON_BLOCK_EXIT(fastcall1, 1);
        }
        {
            XL_ON_BLOCK_EXIT(fastcall2, 1, 2);
        }
        {
            XL_ON_BLOCK_EXIT(fastcall3, 1, 2, 3);
        }
    }

    XL_TEST_CASE()
    {
        {
            XL_ON_BLOCK_EXIT(&s, &S::cdecl0);
        }
        {
            XL_ON_BLOCK_EXIT(&s, &S::cdecl1, 1);
        }
        {
            XL_ON_BLOCK_EXIT(&s, &S::cdecl2, 1, 2);
        }
        {
            XL_ON_BLOCK_EXIT(&s, &S::cdecl3, 1, 2, 3);
        }
    }

    XL_TEST_CASE()
    {
        {
            XL_ON_BLOCK_EXIT(&s, &S::stdcall0);
        }
        {
            XL_ON_BLOCK_EXIT(&s, &S::stdcall1, 1);
        }
        {
            XL_ON_BLOCK_EXIT(&s, &S::stdcall2, 1, 2);
        }
        {
            XL_ON_BLOCK_EXIT(&s, &S::stdcall3, 1, 2, 3);
        }
    }

    XL_TEST_CASE()
    {
        {
            XL_ON_BLOCK_EXIT(&s, &S::fastcall0);
        }
        {
            XL_ON_BLOCK_EXIT(&s, &S::fastcall1, 1);
        }
        {
            XL_ON_BLOCK_EXIT(&s, &S::fastcall2, 1, 2);
        }
        {
            XL_ON_BLOCK_EXIT(&s, &S::fastcall3, 1, 2, 3);
        }
    }

    XL_TEST_CASE()
    {
        {
            XL_ON_BLOCK_EXIT(&s, &S::thiscall0);
        }
        {
            XL_ON_BLOCK_EXIT(&s, &S::thiscall1, 1);
        }
        {
            XL_ON_BLOCK_EXIT(&s, &S::thiscall2, 1, 2);
        }
        {
            XL_ON_BLOCK_EXIT(&s, &S::thiscall3, 1, 2, 3);
        }
    }

    XL_TEST_CASE()
    {
        {
            XL_ON_BLOCK_EXIT(Function<int ()>(f));
        }
        {
            XL_ON_BLOCK_EXIT(Function<int (int)>(f), 1);
        }
        {
            XL_ON_BLOCK_EXIT(Function<int (int, int)>(f), 1, 2);
        }
        {
            XL_ON_BLOCK_EXIT(Function<int (int, int, int)>(f), 1, 2, 3);
        }
    }

    XL_TEST_CASE()
    {
        {
            XL_ON_BLOCK_EXIT(test_const, 0);
        }
#ifdef __XL_CPP11
        {
            int i = 0;
            xl::Bind(test_ref, (int &)i)();
            XL_ON_BLOCK_EXIT(test_ref, (int &)i);
        }
        {
            XL_ON_BLOCK_EXIT(test_const_ref, 0);
        }
        {
            XL_ON_BLOCK_EXIT(test_r_ref, 0);
        }
        {
            XL_ON_BLOCK_EXIT(test_const_r_ref, 0);
        }
#endif
    }
}


                             