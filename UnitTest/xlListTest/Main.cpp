//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-08-10
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Containers/xlList.h>
#include "../UnitTestFrame.h"

using namespace xl;

TEST_CASE(ctor)
{
    List<int> a;
    TEST_ASSERT(a.Size() == 0);
}

TEST_CASE(ctor_copy)
{
    List<int> a;

    a.PushBack(1);
    a.PushBack(2);

    List<int> b(a);

    TEST_ASSERT(b == a);

    List<int>::Iterator it = b.Begin();
    TEST_ASSERT(*it == 1);
    ++it;
    TEST_ASSERT(*it == 2);
}

TEST_CASE(operator_set)
{
    List<int> a;

    a.PushBack(10);
    a.PushBack(9);

    List<int> b;

    b = a;

    TEST_ASSERT(b == a);

    List<int>::Iterator it = b.Begin();
    TEST_ASSERT(*it == 10);
    ++it;
    TEST_ASSERT(*it == 9);
}

TEST_CASE(operator_equal)
{
    List<int> a, b;

    a.PushBack(11);
    a.PushBack(22);

    b = a;
    TEST_ASSERT(b == a);

    ++*b.Begin();
    TEST_ASSERT(b != a);

    --*b.Begin();
    TEST_ASSERT(b == a);

    a.PushBack(100);
    TEST_ASSERT(b != a);

    a.PopBack();
    TEST_ASSERT(b == a);
}

TEST_CASE(method_size)
{
    List<int> a;
    TEST_ASSERT(a.Empty() == true);

    a.PushBack(0);
    TEST_ASSERT(a.Empty() == false);

    a.PopBack();
    TEST_ASSERT(a.Empty() == true);

    a.PushFront(1);
    a.PushFront(0);
    TEST_ASSERT(a.Size() == 2);

    a.Clear();
    TEST_ASSERT(a.Size() == 0);
}

TEST_CASE(method_insert_delete)
{
    List<int> a;
    TEST_ASSERT(a.Empty() == true);

//     int data[4] = { 1, 3, 2, 4 };
//     a.Insert(0, data, 4);
//     TEST_ASSERT(a.Size() == 4);
//     TEST_ASSERT(a[0] == 1);
//     TEST_ASSERT(a[1] == 3);
//     TEST_ASSERT(a[2] == 2);
//     TEST_ASSERT(a[3] == 4);
// 
//     a.Insert(2, 10);
//     TEST_ASSERT(a.Size() == 5);
//     TEST_ASSERT(a[0] == 1);
//     TEST_ASSERT(a[1] == 3);
//     TEST_ASSERT(a[2] == 10);
//     TEST_ASSERT(a[3] == 2);
//     TEST_ASSERT(a[4] == 4);
// 
//     a.PushBack(15);
//     TEST_ASSERT(a.Size() == 6);
//     TEST_ASSERT(a[0] == 1);
//     TEST_ASSERT(a[1] == 3);
//     TEST_ASSERT(a[2] == 10);
//     TEST_ASSERT(a[3] == 2);
//     TEST_ASSERT(a[4] == 4);
//     TEST_ASSERT(a[5] == 15);
// 
//     a.PushFront(20);
//     TEST_ASSERT(a.Size() == 7);
//     TEST_ASSERT(a[0] == 20);
//     TEST_ASSERT(a[1] == 1);
//     TEST_ASSERT(a[2] == 3);
//     TEST_ASSERT(a[3] == 10);
//     TEST_ASSERT(a[4] == 2);
//     TEST_ASSERT(a[5] == 4);
//     TEST_ASSERT(a[6] == 15);
// 
//     a.Delete(2, 3);
//     TEST_ASSERT(a.Size() == 4);
//     TEST_ASSERT(a[0] == 20);
//     TEST_ASSERT(a[1] == 1);
//     TEST_ASSERT(a[2] == 4);
//     TEST_ASSERT(a[3] == 15);
// 
//     a.Delete(1);
//     TEST_ASSERT(a.Size() == 3);
//     TEST_ASSERT(a[0] == 20);
//     TEST_ASSERT(a[1] == 4);
//     TEST_ASSERT(a[2] == 15);
// 
//     a.PopFront();
//     TEST_ASSERT(a.Size() == 2);
//     TEST_ASSERT(a[0] == 4);
//     TEST_ASSERT(a[1] == 15);
// 
//     a.PopBack();
//     TEST_ASSERT(a.Size() == 1);
//     TEST_ASSERT(a[0] == 4);
// 
//     a.Resize(100);
//     a[99] = 1001;
//     TEST_ASSERT(a.Size() == 100);
//     TEST_ASSERT(a[0] == 4);
//     TEST_ASSERT(a[99] == 1001);

    a.Clear();
    TEST_ASSERT(a.Size() == 0);
}

int main()
{
    return 0;
}
