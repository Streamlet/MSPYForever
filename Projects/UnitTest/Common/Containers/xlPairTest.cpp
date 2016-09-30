//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlPairTest.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/Common/Containers/xlPair.h"
#include "../../../Include/xl/AppHelper/xlUnitTest.h"

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        Pair<int, int> a(1);
        XL_TEST_ASSERT(a.Key == 1);

        Pair<int, int> b(-1, -2);
        XL_TEST_ASSERT(b.Key == -1);
        XL_TEST_ASSERT(b.Value == -2);

        Pair<int, int> c(b);
        XL_TEST_ASSERT(c.Key == -1);
        XL_TEST_ASSERT(c.Value == -2);

        Pair<int, int> d;
        d = c;
        XL_TEST_ASSERT(d.Key == -1);
        XL_TEST_ASSERT(c.Value == -2);
    }

    XL_TEST_CASE()
    {
        Pair<int, int> a(1, 1), b(1, 2);
        XL_TEST_ASSERT(a == b);
        XL_TEST_ASSERT(!(a != b));
        XL_TEST_ASSERT(!(a < b));
        XL_TEST_ASSERT(!(a > b));
        XL_TEST_ASSERT(a <= b);
        XL_TEST_ASSERT(a >= b);

        a.Key = -1;
        XL_TEST_ASSERT(!(a == b));
        XL_TEST_ASSERT(a != b);
        XL_TEST_ASSERT(a < b);
        XL_TEST_ASSERT(!(a > b));
        XL_TEST_ASSERT(a <= b);
        XL_TEST_ASSERT(!(a >= b));

        a.Key = 2;
        XL_TEST_ASSERT(!(a == b));
        XL_TEST_ASSERT(a != b);
        XL_TEST_ASSERT(!(a < b));
        XL_TEST_ASSERT(a > b);
        XL_TEST_ASSERT(!(a <= b));
        XL_TEST_ASSERT(a >= b);
    }
}
