//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlSmartPtrTest.cpp
//    Author:      Streamlet
//    Create Time: 2011-05-21
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../../Include/xl/AppHelper/xlUnitTest.h"
#include "../../../../Include/xl/Common/Memory/xlSmartPtr.h"

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        SharedPtr<int> a;
        XL_TEST_ASSERT(a == nullptr);

        int *pInt = new int;
        *pInt = 123;

        SharedPtr<int> b(pInt), c(b);
        XL_TEST_ASSERT(b == pInt);
        XL_TEST_ASSERT(c == pInt);
        XL_TEST_ASSERT(b == c);

        SharedPtr<int> d(c);
        XL_TEST_ASSERT(d == c);

        SharedPtr<int> e;
        XL_TEST_ASSERT(e == nullptr);

        e = d;
        XL_TEST_ASSERT(e == pInt);
    }

    XL_TEST_CASE()
    {
        SharedPtr<int> a, b;
        XL_TEST_ASSERT(a == nullptr);
        XL_TEST_ASSERT(!(a != nullptr));
        XL_TEST_ASSERT(b == nullptr);
        XL_TEST_ASSERT(!(b != nullptr));

        int *pInt = new int;
        *pInt = 123;

        a = pInt;
        XL_TEST_ASSERT(a == pInt);
        XL_TEST_ASSERT(!(a != pInt));
        XL_TEST_ASSERT(a != b);
        XL_TEST_ASSERT(!(a == b));

        b = a;
        XL_TEST_ASSERT(a == b);
        XL_TEST_ASSERT(!(a != b));

        a = nullptr;
        XL_TEST_ASSERT(a == nullptr);
        XL_TEST_ASSERT(!(a != nullptr));
        XL_TEST_ASSERT(a != b);
        XL_TEST_ASSERT(!(a == b));
    }

    XL_TEST_CASE()
    {
        int *pInt = new int;
        *pInt = 123;

        SharedPtr<int> a(pInt);
        XL_TEST_ASSERT(*a == 123);

        struct s
        {
            int x;
            int y;
        };

        s *pS = new s;
        pS->x = 1;
        pS->y = 2;

        SharedPtr<s> b(pS);
        XL_TEST_ASSERT(b->x == 1);
        XL_TEST_ASSERT(b->y == 2);
    }
}


