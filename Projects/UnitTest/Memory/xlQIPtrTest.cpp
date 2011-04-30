//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlQIPtrTest.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Test/xlUnitTest.h>
#include <xl/xlDef.h>
#include <xl/Memory/xlQIPtr.h>

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        QIPtr<int> a;
        XL_TEST_ASSERT(a == nullptr);

        int *pInt = new int;
        *pInt = 123;

        QIPtr<int> b(pInt), c(b);
        XL_TEST_ASSERT(b == pInt);
        XL_TEST_ASSERT(c == pInt);
        XL_TEST_ASSERT(b == c);

        QIPtr<int> d(c);
        XL_TEST_ASSERT(d == c);

        QIPtr<int> e;
        XL_TEST_ASSERT(e == nullptr);

        e = d;
        XL_TEST_ASSERT(e == pInt);
    }

    XL_TEST_CASE()
    {
        QIPtr<int> a, b;
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

        QIPtr<int> a(pInt);
        XL_TEST_ASSERT(*a == 123);

        struct s
        {
            int x;
            int y;
        };

        s *pS = new s;
        pS->x = 1;
        pS->y = 2;

        QIPtr<s> b(pS);
        XL_TEST_ASSERT(b->x == 1);
        XL_TEST_ASSERT(b->y == 2);
    }
}
