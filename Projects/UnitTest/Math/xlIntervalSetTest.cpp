//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIntervalSetTest.cpp
//    Author:      Streamlet
//    Create Time: 2012-06-01
//    Description: 
//
//------------------------------------------------------------------------------



#include "../../../Include/xl/Common/Math/xlIntervalSet.h"
#include "../../../Include/xl/AppHelper/xlUnitTest.h"

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        IntervalSet<int> s;
        XL_TEST_ASSERT(s.IsEmpty());

        Interval<int> a(0, 5);
        Interval<int> b(6, 8);

        s.Union(a);
        s.Union(b);
        Set<Interval<int>> x = s.GetIntervals();
        XL_TEST_ASSERT(*x.Begin() == a);
        XL_TEST_ASSERT(*x.ReverseBegin() == b);

        IntervalSet<int> t;
        XL_TEST_ASSERT(t.IsEmpty());
        t.Union(Interval<int>(4, 7));

        IntervalSet<int> u = s.Intersection(t);
        x = u.GetIntervals();
        XL_TEST_ASSERT(x.Size() == 2);
        XL_TEST_ASSERT(*x.Begin() == Interval<int>(4, 5));
        XL_TEST_ASSERT(*x.ReverseBegin() == Interval<int>(6, 7));

        u = s.Union(t);
        x = u.GetIntervals();
        XL_TEST_ASSERT(x.Size() == 1);
        XL_TEST_ASSERT(*x.Begin() == Interval<int>(0, 8));

        u = s.Exclude(t);
        x = u.GetIntervals();
        XL_TEST_ASSERT(x.Size() == 2);
        XL_TEST_ASSERT(*x.Begin() == Interval<int>(0, 4, true, false));
        XL_TEST_ASSERT(*x.ReverseBegin() == Interval<int>(7, 8, false, true));
    }
}




