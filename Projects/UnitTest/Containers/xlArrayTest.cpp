//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlArrayTest.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/Common/Containers/xlArray.h"
#include "../../../Include/xl/AppHelper/xlUnitTest.h"

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        Array<int> a;
        XL_TEST_ASSERT(a.Size() == 0);
    }

    XL_TEST_CASE()
    {
        Array<int> a(3);
        XL_TEST_ASSERT(a.Size() == 3);
    }

    XL_TEST_CASE()
    {
        Array<int> a(5, 10);
        XL_TEST_ASSERT(a.Size() == 5);

        for (size_t i = 0; i < a.Size(); ++i)
        {
            XL_TEST_ASSERT(a[i] == 10);
        }
    }

    XL_TEST_CASE()
    {
        Array<int> a(10, 100), b(a);

        XL_TEST_ASSERT(b.Size() == 10);

        for (size_t i = 0; i < b.Size(); ++i)
        {
            XL_TEST_ASSERT(b[i] == 100);
        }
    }

    XL_TEST_CASE()
    {
        Array<int> a(10, 100), b;

        b = a;

        XL_TEST_ASSERT(b.Size() == 10);

        for (size_t i = 0; i < b.Size(); ++i)
        {
            XL_TEST_ASSERT(b[i] == 100);
        }
    }

    XL_TEST_CASE()
    {
        Array<int> a(10, 100), b;

        b = a;
        XL_TEST_ASSERT(b == a);

        ++b[3];
        XL_TEST_ASSERT(b != a);

        --b[3];
        XL_TEST_ASSERT(b == a);

        a.PushBack(100);
        XL_TEST_ASSERT(b != a);

        a.PopFront();
        XL_TEST_ASSERT(b == a);
    }

    XL_TEST_CASE()
    {
        Array<int> a;
        XL_TEST_ASSERT(a.Empty() == true);

        a.PushBack(0);
        XL_TEST_ASSERT(a.Empty() == false);

        a.PopBack();
        XL_TEST_ASSERT(a.Empty() == true);

        a.PushFront(1);
        a.PushFront(0);
        XL_TEST_ASSERT(a.Size() == 2);

        a.Resize(5);
        XL_TEST_ASSERT(a.Size() == 5);
    }

    XL_TEST_CASE()
    {
        Array<int> a;
        XL_TEST_ASSERT(a.Empty() == true);

        a.Insert(0, 5, 3);
        XL_TEST_ASSERT(a.Size() == 3);
        XL_TEST_ASSERT(a[0] == 5);
        XL_TEST_ASSERT(a[1] == 5);
        XL_TEST_ASSERT(a[2] == 5);

        a.Clear();
        XL_TEST_ASSERT(a.Empty() == true);

        int data[4] = { 1, 3, 2, 4 };
        a.Insert(0, data, 4);
        XL_TEST_ASSERT(a.Size() == 4);
        XL_TEST_ASSERT(a[0] == 1);
        XL_TEST_ASSERT(a[1] == 3);
        XL_TEST_ASSERT(a[2] == 2);
        XL_TEST_ASSERT(a[3] == 4);

        Array<int>::Iterator it = a.Begin();
        XL_TEST_ASSERT(*it == 1);
        ++it;
        XL_TEST_ASSERT(*it == 3);
        ++it;
        XL_TEST_ASSERT(*it == 2);
        ++it;
        XL_TEST_ASSERT(*it == 4);

        a.Insert(2, 10);
        XL_TEST_ASSERT(a.Size() == 5);
        XL_TEST_ASSERT(a[0] == 1);
        XL_TEST_ASSERT(a[1] == 3);
        XL_TEST_ASSERT(a[2] == 10);
        XL_TEST_ASSERT(a[3] == 2);
        XL_TEST_ASSERT(a[4] == 4);

        a.PushBack(15);
        XL_TEST_ASSERT(a.Size() == 6);
        XL_TEST_ASSERT(a[0] == 1);
        XL_TEST_ASSERT(a[1] == 3);
        XL_TEST_ASSERT(a[2] == 10);
        XL_TEST_ASSERT(a[3] == 2);
        XL_TEST_ASSERT(a[4] == 4);
        XL_TEST_ASSERT(a[5] == 15);

        a.PushFront(20);
        XL_TEST_ASSERT(a.Size() == 7);
        XL_TEST_ASSERT(a[0] == 20);
        XL_TEST_ASSERT(a[1] == 1);
        XL_TEST_ASSERT(a[2] == 3);
        XL_TEST_ASSERT(a[3] == 10);
        XL_TEST_ASSERT(a[4] == 2);
        XL_TEST_ASSERT(a[5] == 4);
        XL_TEST_ASSERT(a[6] == 15);

        a.Delete(2, 3);
        XL_TEST_ASSERT(a.Size() == 4);
        XL_TEST_ASSERT(a[0] == 20);
        XL_TEST_ASSERT(a[1] == 1);
        XL_TEST_ASSERT(a[2] == 4);
        XL_TEST_ASSERT(a[3] == 15);

        a.Delete(1);
        XL_TEST_ASSERT(a.Size() == 3);
        XL_TEST_ASSERT(a[0] == 20);
        XL_TEST_ASSERT(a[1] == 4);
        XL_TEST_ASSERT(a[2] == 15);

        a.PopFront();
        XL_TEST_ASSERT(a.Size() == 2);
        XL_TEST_ASSERT(a[0] == 4);
        XL_TEST_ASSERT(a[1] == 15);

        a.PopBack();
        XL_TEST_ASSERT(a.Size() == 1);
        XL_TEST_ASSERT(a[0] == 4);

        a.Resize(100);
        a[99] = 1001;
        XL_TEST_ASSERT(a.Size() == 100);
        XL_TEST_ASSERT(a[99] == 1001);

        a.Clear();
        XL_TEST_ASSERT(a.Size() == 0);
    }

    XL_TEST_CASE()
    {
        Array<char> a;
        a.PushBack('k');
        a.PushFront('s');

        XL_TEST_ASSERT(a[0] == 's');
        XL_TEST_ASSERT(a[1] == 'k');

        Array<char>::Iterator it = a.Begin();
        XL_TEST_ASSERT(*it == 's');
        ++it;
        XL_TEST_ASSERT(*it == 'k');
    }
}
