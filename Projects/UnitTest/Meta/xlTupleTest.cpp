//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlTupleTest.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/Common/Meta/xlTuple.h"
#include "../../../Include/xl/AppHelper/xlUnitTest.h"

namespace
{
    using namespace xl;

    // Size
    XL_TEST_CASE()
    {
        Tuple<> a;
        XL_TEST_ASSERT(a.Size == 0);

        Tuple<int> b;
        XL_TEST_ASSERT(b.Size == 1);

        Tuple<int, int> c;
        XL_TEST_ASSERT(c.Size == 2);

        Tuple<int, int, int> d;
        XL_TEST_ASSERT(d.Size == 3);

        Tuple<int, int, int, int, int, int, int, int, int, int> e;
        XL_TEST_ASSERT(e.Size == 10);
    }

    // Assign
    XL_TEST_CASE()
    {
        Tuple<int> a;
        XL_TEST_ASSERT(a.At<0>() == 0);
        XL_TEST_ASSERT(a.Get<0>() == 0);
        a.Set<0>(1);
        XL_TEST_ASSERT(a.At<0>() == 1);
        XL_TEST_ASSERT(a.Get<0>() == 1);

        Tuple<double, double> b(a);
        XL_TEST_ASSERT(b.At<0>() == 1.0);
        XL_TEST_ASSERT(b.Get<0>() == 1.0);
        XL_TEST_ASSERT(b.At<1>() == 0.0);
        XL_TEST_ASSERT(b.Get<1>() == 0.0);

        Tuple<float> c;
        c = b;
        XL_TEST_ASSERT(c.At<0>() == 1.0);
        XL_TEST_ASSERT(c.Get<0>() == 1.0);

    }

    XL_TEST_CASE()
    {
        Tuple<int, int> a(1, 1), b(1, 1);
        XL_TEST_ASSERT(a == b);
        XL_TEST_ASSERT(!(a != b));
        XL_TEST_ASSERT(!(a < b));
        XL_TEST_ASSERT(!(a > b));
        XL_TEST_ASSERT(a <= b);
        XL_TEST_ASSERT(a >= b);

        a.At<0>() = -1;
        XL_TEST_ASSERT(!(a == b));
        XL_TEST_ASSERT(a != b);
        XL_TEST_ASSERT(a < b);
        XL_TEST_ASSERT(!(a > b));
        XL_TEST_ASSERT(a <= b);
        XL_TEST_ASSERT(!(a >= b));

        a.At<0>() = 2;
        XL_TEST_ASSERT(!(a == b));
        XL_TEST_ASSERT(a != b);
        XL_TEST_ASSERT(!(a < b));
        XL_TEST_ASSERT(a > b);
        XL_TEST_ASSERT(!(a <= b));
        XL_TEST_ASSERT(a >= b);
    }

    XL_TEST_CASE()
    {
        Tuple<int, int> a(1, 1);
        Tuple<double, double> b(1.0, 1.0);
        XL_TEST_ASSERT(a == b);
        XL_TEST_ASSERT(!(a != b));
        XL_TEST_ASSERT(!(a < b));
        XL_TEST_ASSERT(!(a > b));
        XL_TEST_ASSERT(a <= b);
        XL_TEST_ASSERT(a >= b);

        a.At<0>() = -1;
        XL_TEST_ASSERT(!(a == b));
        XL_TEST_ASSERT(a != b);
        XL_TEST_ASSERT(a < b);
        XL_TEST_ASSERT(!(a > b));
        XL_TEST_ASSERT(a <= b);
        XL_TEST_ASSERT(!(a >= b));

        a.At<0>() = 2;
        XL_TEST_ASSERT(!(a == b));
        XL_TEST_ASSERT(a != b);
        XL_TEST_ASSERT(!(a < b));
        XL_TEST_ASSERT(a > b);
        XL_TEST_ASSERT(!(a <= b));
        XL_TEST_ASSERT(a >= b);
    }

    XL_TEST_CASE()
    {
        Tuple<int, int> a(1, 1);
        Tuple<int, int, int> a2(1, 1, 1);
        Tuple<double, double> b(1.0, 1.0);

//         a = b;  // warning
//         b = a;
// 
//         a = a2;
    }
}
