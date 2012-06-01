//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIntervalTest.cpp
//    Author:      Streamlet
//    Create Time: 2012-06-01
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Math/xlInterval.h>
#include <xl/Test/xlUnitTest.h>

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        Interval<int> a;
        XL_TEST_ASSERT(a.left == 0);
        XL_TEST_ASSERT(a.right == 0);
        XL_TEST_ASSERT(!a.bIncludeLeft);
        XL_TEST_ASSERT(!a.bIncludeRight);

        Interval<int> b(1, 2, true, false);
        XL_TEST_ASSERT(b.left == 1);
        XL_TEST_ASSERT(b.right == 2);
        XL_TEST_ASSERT(b.bIncludeLeft);
        XL_TEST_ASSERT(!b.bIncludeRight);

        Interval<int> c(2, 1, false, true);
        XL_TEST_ASSERT(c.left == 2);
        XL_TEST_ASSERT(c.right == 1);
        XL_TEST_ASSERT(!c.bIncludeLeft);
        XL_TEST_ASSERT(c.bIncludeRight);

        Interval<int> d(c);
        XL_TEST_ASSERT(d == c);
        XL_TEST_ASSERT(!(d != c));
        d = b;
        XL_TEST_ASSERT(d != c);
        XL_TEST_ASSERT(!(d == c));
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Interval<int>(0, 0, false, false).IsEmpty());
        XL_TEST_ASSERT(Interval<int>(0, 0, false, true).IsEmpty());
        XL_TEST_ASSERT(Interval<int>(0, 0, true, false).IsEmpty());
        XL_TEST_ASSERT(!Interval<int>(0, 0, true, true).IsEmpty());

        XL_TEST_ASSERT(!Interval<int>(1, 2, false, false).IsEmpty());
        XL_TEST_ASSERT(!Interval<int>(1, 2, false, true).IsEmpty());
        XL_TEST_ASSERT(!Interval<int>(1, 2, true, false).IsEmpty());
        XL_TEST_ASSERT(!Interval<int>(1, 2, true, true).IsEmpty());

        XL_TEST_ASSERT(Interval<int>(2, 1, false, false).IsEmpty());
        XL_TEST_ASSERT(Interval<int>(2, 1, false, true).IsEmpty());
        XL_TEST_ASSERT(Interval<int>(2, 1, true, false).IsEmpty());
        XL_TEST_ASSERT(Interval<int>(2, 1, true, true).IsEmpty());
    }

    XL_TEST_CASE()
    {
        Interval<int> empty;
        XL_TEST_ASSERT(!empty.Contains(0));
        XL_TEST_ASSERT(!empty.Contains(1));
        XL_TEST_ASSERT(!empty.Contains(2));
        XL_TEST_ASSERT(!empty.Contains(3));
        XL_TEST_ASSERT(!empty.Contains(4));

        Interval<int> loro(1, 3, false, false);
        XL_TEST_ASSERT(!loro.Contains(0));
        XL_TEST_ASSERT(!loro.Contains(1));
        XL_TEST_ASSERT(loro.Contains(2));
        XL_TEST_ASSERT(!loro.Contains(3));
        XL_TEST_ASSERT(!loro.Contains(4));

        Interval<int> lorc(1, 3, false, true);
        XL_TEST_ASSERT(!lorc.Contains(0));
        XL_TEST_ASSERT(!lorc.Contains(1));
        XL_TEST_ASSERT(lorc.Contains(2));
        XL_TEST_ASSERT(lorc.Contains(3));
        XL_TEST_ASSERT(!lorc.Contains(4));

        Interval<int> lcro(1, 3, true, false);
        XL_TEST_ASSERT(!lcro.Contains(0));
        XL_TEST_ASSERT(lcro.Contains(1));
        XL_TEST_ASSERT(lcro.Contains(2));
        XL_TEST_ASSERT(!lcro.Contains(3));
        XL_TEST_ASSERT(!lcro.Contains(4));

        Interval<int> lcrc(1, 3, true, true);
        XL_TEST_ASSERT(!lcrc.Contains(0));
        XL_TEST_ASSERT(lcrc.Contains(1));
        XL_TEST_ASSERT(lcrc.Contains(2));
        XL_TEST_ASSERT(lcrc.Contains(3));
        XL_TEST_ASSERT(!lcrc.Contains(4));
    }

    XL_TEST_CASE()
    {
        Interval<int> empty;
        Interval<int> loro(1, 3, false, false);
        Interval<int> lorc(1, 3, false, true);
        Interval<int> lcro(1, 3, true, false);
        Interval<int> lcrc(1, 3, true, true);

        XL_TEST_ASSERT(empty.Contains(empty));
        XL_TEST_ASSERT(!empty.Contains(loro));
        XL_TEST_ASSERT(!empty.Contains(lorc));
        XL_TEST_ASSERT(!empty.Contains(lcro));
        XL_TEST_ASSERT(!empty.Contains(lcrc));
        XL_TEST_ASSERT(loro.Contains(empty));
        XL_TEST_ASSERT(lorc.Contains(empty));
        XL_TEST_ASSERT(lcro.Contains(empty));
        XL_TEST_ASSERT(lcrc.Contains(empty));
        XL_TEST_ASSERT(lcrc.Contains(empty));
    }
}
