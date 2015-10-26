//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlRBTreeTest.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/Common/Containers/xlRBTree.h"
#include "../../../Include/xl/AppHelper/xlUnitTest.h"

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        RBTree<int> a;
        XL_TEST_ASSERT(a.Size() == 0);
    }

    XL_TEST_CASE()
    {
        RBTree<int> a;
        XL_TEST_ASSERT(a.Size() == 0);

        RBTree<int> b(a);
        XL_TEST_ASSERT(b.Size() == 0);

        a.Insert(1);
        a.Insert(2);
        RBTree<int> c(a);
        XL_TEST_ASSERT(c.Size() == 2);
        XL_TEST_ASSERT(*c.Begin() == 1);
        XL_TEST_ASSERT(*c.ReverseBegin() == 2);
    }

    XL_TEST_CASE()
    {
        RBTree<int> a;
        XL_TEST_ASSERT(a.Size() == 0);

        RBTree<int> b;
        b = a;
        XL_TEST_ASSERT(b.Size() == 0);

        a.Insert(1);
        a.Insert(2);
        RBTree<int> c;
        c = a;
        XL_TEST_ASSERT(c.Size() == 2);
        XL_TEST_ASSERT(*a.Begin() == 1);
        XL_TEST_ASSERT(*++a.Begin() == 2);
    }

    XL_TEST_CASE()
    {
        RBTree<int> a;
        XL_TEST_ASSERT(a.Size() == 0);

        RBTree<int> b;
        b = a;
        XL_TEST_ASSERT(b == a);
        XL_TEST_ASSERT(!(b != a));

        a.Insert(1);
        a.Insert(2);
        XL_TEST_ASSERT(b != a);
        XL_TEST_ASSERT(!(b == a));

        RBTree<int> c(a);
        XL_TEST_ASSERT(c == a);
        XL_TEST_ASSERT(!(c != a));

        b.Insert(1);
        b.Insert(2);
        XL_TEST_ASSERT(b == a);
        XL_TEST_ASSERT(!(b != a));
        XL_TEST_ASSERT(b == c);
        XL_TEST_ASSERT(!(b != c));
    }

    XL_TEST_CASE()
    {
        RBTree<int> a;
        XL_TEST_ASSERT(a.Size() == 0);
        XL_TEST_ASSERT(a.Empty() == true);

        a.Insert(10);
        XL_TEST_ASSERT(a.Size() == 1);
        XL_TEST_ASSERT(a.Empty() == false);

        a.Insert(20);
        a.Insert(30);
        a.Insert(40);
        a.Insert(50);
        XL_TEST_ASSERT(a.Size() == 5);
        XL_TEST_ASSERT(a.Empty() == false);
    }

    XL_TEST_CASE()
    {
        RBTree<int> a;

        a.Insert(2);
        a.Insert(6);
        a.Insert(4);
        a.Insert(3);
        a.Insert(5);
        a.Insert(1);

        RBTree<int>::Iterator it = a.Begin();

        XL_TEST_ASSERT(*it == 1);

        ++it;
        XL_TEST_ASSERT(*it == 2);

        ++it;
        XL_TEST_ASSERT(*it == 3);

        ++it;
        XL_TEST_ASSERT(*it == 4);

        ++it;
        XL_TEST_ASSERT(*it == 5);

        ++it;
        XL_TEST_ASSERT(*it == 6);

        ++it;
        XL_TEST_ASSERT(it == a.End());
    }

    XL_TEST_CASE()
    {
        RBTree<int> a;

        a.Insert(2);
        a.Insert(6);
        a.Insert(4);
        a.Insert(3);
        a.Insert(5);
        a.Insert(1);

        RBTree<int>::Iterator it = a.Find(5);

        XL_TEST_ASSERT(*it == 5);

        RBTree<int>::Iterator it2 = it;

        ++it2;
        XL_TEST_ASSERT(*it2 == 6);

        ++it2;
        XL_TEST_ASSERT(it2 == a.End());
    }
}
