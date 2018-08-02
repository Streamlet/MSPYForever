//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlListTest.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../../Include/xl/Common/Containers/xlList.h"
#include "../../../../Include/xl/AppHelper/xlUnitTest.h"

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        List<int> a;
        XL_TEST_ASSERT(a.Size() == 0);
    }

    XL_TEST_CASE()
    {
        List<int> a;

        a.PushBack(1);
        a.PushBack(2);

        List<int> b(a);

        XL_TEST_ASSERT(b == a);

        List<int>::Iterator it = b.Begin();
        XL_TEST_ASSERT(*it == 1);
        ++it;
        XL_TEST_ASSERT(*it == 2);
    }

    XL_TEST_CASE()
    {
        List<int> a;

        a.PushBack(10);
        a.PushBack(9);

        List<int> b;

        b = a;

        XL_TEST_ASSERT(b == a);

        List<int>::Iterator it = b.Begin();
        XL_TEST_ASSERT(*it == 10);
        ++it;
        XL_TEST_ASSERT(*it == 9);
    }

    XL_TEST_CASE()
    {
        List<int> a, b;

        a.PushBack(11);
        a.PushBack(22);

        b = a;
        XL_TEST_ASSERT(b == a);

        ++*b.Begin();
        XL_TEST_ASSERT(b != a);

        --*b.Begin();
        XL_TEST_ASSERT(b == a);

        a.PushBack(100);
        XL_TEST_ASSERT(b != a);

        a.PopBack();
        XL_TEST_ASSERT(b == a);
    }

    XL_TEST_CASE()
    {
        List<int> a;
        XL_TEST_ASSERT(a.Empty() == true);

        a.PushBack(0);
        XL_TEST_ASSERT(a.Empty() == false);

        a.PopBack();
        XL_TEST_ASSERT(a.Empty() == true);

        a.PushFront(1);
        a.PushFront(0);
        XL_TEST_ASSERT(a.Size() == 2);

        a.Clear();
        XL_TEST_ASSERT(a.Size() == 0);
    }

    XL_TEST_CASE()
    {
        List<int> a;
        XL_TEST_ASSERT(a.Empty() == true);

        a.Insert(a.Begin(), -1);
        XL_TEST_ASSERT(a.Size() == 1);
        XL_TEST_ASSERT(*a.Begin() == -1);

        a.PushBack(15);
        XL_TEST_ASSERT(a.Size() == 2);
        XL_TEST_ASSERT(*a.ReverseBegin() == 15);

        a.PushFront(20);
        XL_TEST_ASSERT(a.Size() == 3);
        XL_TEST_ASSERT(*a.Begin() == 20);

        a.Delete(a.Begin());
        XL_TEST_ASSERT(a.Size() == 2);
        XL_TEST_ASSERT(*a.Begin() == -1);
        XL_TEST_ASSERT(*(++a.Begin()) == 15);

        a.PopBack();
        XL_TEST_ASSERT(a.Size() == 1);
        XL_TEST_ASSERT(*a.Begin() == -1);

        a.Clear();
        XL_TEST_ASSERT(a.Size() == 0);
        XL_TEST_ASSERT(a.Empty() == true);
    }
}
