//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMapTest.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../../Include/xl/Common/Containers/xlMap.h"
#include "../../../../Include/xl/AppHelper/xlUnitTest.h"

namespace
{
    using namespace xl;
    typedef Pair<int, int> IntIntPair;

    XL_TEST_CASE()
    {
        Map<int, int> a;
        XL_TEST_ASSERT(a.Size() == 0);
    }

    XL_TEST_CASE()
    {
        Map<int, int> a;
        XL_TEST_ASSERT(a.Size() == 0);

        Map<int, int> b(a);
        XL_TEST_ASSERT(b.Size() == 0);

        a.Insert(1, 10);
        a.Insert(2, 20);
        Map<int, int> c(a);
        XL_TEST_ASSERT(c.Size() == 2);
        XL_TEST_ASSERT(*c.Begin() == IntIntPair(1, 10));
        XL_TEST_ASSERT(*c.ReverseBegin() == IntIntPair(2, 20));
    }

    XL_TEST_CASE()
    {
        Map<int, int> a;
        XL_TEST_ASSERT(a.Size() == 0);

        Map<int, int> b;
        b = a;
        XL_TEST_ASSERT(b.Size() == 0);

        a.Insert(1, 10);
        a.Insert(2, 20);
        Map<int, int> c;
        c = a;
        XL_TEST_ASSERT(c.Size() == 2);
        XL_TEST_ASSERT(*c.Begin() == IntIntPair(1, 10));
        XL_TEST_ASSERT(*c.ReverseBegin() == IntIntPair(2, 20));
    }

    XL_TEST_CASE()
    {
        Map<int, int> a;
        XL_TEST_ASSERT(a.Size() == 0);

        Map<int, int> b;
        b = a;
        XL_TEST_ASSERT(b == a);
        XL_TEST_ASSERT(!(b != a));

        a.Insert(1, 10);
        a.Insert(2, 20);
        XL_TEST_ASSERT(b != a);
        XL_TEST_ASSERT(!(b == a));

        Map<int, int> c(a);
        XL_TEST_ASSERT(c == a);
        XL_TEST_ASSERT(!(c != a));

        b.Insert(1, 10);
        b.Insert(2, 20);
        XL_TEST_ASSERT(b == a);
        XL_TEST_ASSERT(!(b != a));
        XL_TEST_ASSERT(b == c);
        XL_TEST_ASSERT(!(b != c));
    }

    XL_TEST_CASE()
    {
        Map<int, int> a;
        XL_TEST_ASSERT(a.Size() == 0);
        XL_TEST_ASSERT(a.Empty() == true);

        a.Insert(1, 10);
        XL_TEST_ASSERT(a.Size() == 1);
        XL_TEST_ASSERT(a.Empty() == false);

        a.Insert(2, 20);
        a.Insert(3, 30);
        a.Insert(4, 40);
        a.Insert(5, 50);
        XL_TEST_ASSERT(a.Size() == 5);
        XL_TEST_ASSERT(a.Empty() == false);
    }

    XL_TEST_CASE()
    {
        Map<int, int> a;

        a.Insert(2, 20);
        a.Insert(6, 60);
        a.Insert(4, 40);
        a.Insert(3, 30);
        a.Insert(5, 50);
        a.Insert(1, 10);

        Map<int, int>::Iterator it = a.Begin();

        XL_TEST_ASSERT(*it == IntIntPair(1, 10));

        ++it;
        XL_TEST_ASSERT(*it == IntIntPair(2, 20));

        ++it;
        XL_TEST_ASSERT(*it == IntIntPair(3, 30));

        ++it;
        XL_TEST_ASSERT(*it == IntIntPair(4, 40));

        ++it;
        XL_TEST_ASSERT(*it == IntIntPair(5, 50));

        ++it;
        XL_TEST_ASSERT(*it == IntIntPair(6, 60));

        ++it;
        XL_TEST_ASSERT(it == a.End());
    }

    XL_TEST_CASE()
    {
        Map<int, int> a;

        a.Insert(2, 20);
        a.Insert(6, 60);
        a.Insert(4, 40);
        a.Insert(3, 30);
        a.Insert(5, 50);
        a.Insert(1, 10);

        Map<int, int>::Iterator it = a.Find(5);

        XL_TEST_ASSERT(*it == IntIntPair(5, 50));

        Map<int, int>::Iterator it2 = it;

        ++it2;
        XL_TEST_ASSERT(*it2 == IntIntPair(6, 60));

        ++it2;
        XL_TEST_ASSERT(it2 == a.End());
    }
}
