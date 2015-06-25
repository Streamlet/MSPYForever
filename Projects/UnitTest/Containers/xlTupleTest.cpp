//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlTupleTest.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Containers/xlTuple.h>
#include <xl/Test/xlUnitTest.h>

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        Tuple<int, int> a(1, 2);
        XL_TEST_ASSERT(a.At<0>() == 1);
        XL_TEST_ASSERT(a.At<1>() == 2);

        Tuple<int, int> b(3, 4);
        XL_TEST_ASSERT(b.At<0>() == 3);
        XL_TEST_ASSERT(b.At<1>() == 4);

        Tuple<int, int> c(b);
        XL_TEST_ASSERT(c.At<0>() == 3);
        XL_TEST_ASSERT(c.At<1>() == 4);

        Tuple<int, int> d;
        d = c;
        XL_TEST_ASSERT(d.At<0>() == 3);
        XL_TEST_ASSERT(c.At<1>() == 4);
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
        b = a;

        a = a2;
    }
}
