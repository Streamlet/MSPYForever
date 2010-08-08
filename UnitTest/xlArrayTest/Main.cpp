//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-08-08
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Containers/xlArray.h>
#include "../UnitTestFrame.h"

using namespace xl;

TEST_CASE(ctor)
{
    Array<int> a;
    TEST_ASSERT(a.Size() == 0);
}

TEST_CASE(ctor_int)
{
    Array<int> a(3);
    TEST_ASSERT(a.Size() == 3);
}

TEST_CASE(ctor_int_t)
{
    Array<int> a(5, 10);
    TEST_ASSERT(a.Size() == 5);

    for (size_t i = 0; i < a.Size(); ++i)
    {
        TEST_ASSERT(a[i] == 10);
    }
}

TEST_CASE(ctor_copy)
{
    Array<int> a(10, 100), b(a);

    TEST_ASSERT(b.Size() == 10);

    for (size_t i = 0; i < b.Size(); ++i)
    {
        TEST_ASSERT(b[i] == 100);
    }
}

TEST_CASE(ctor_op_set)
{
    Array<int> a(10, 100), b;

    b = a;

    TEST_ASSERT(b.Size() == 10);

    for (size_t i = 0; i < b.Size(); ++i)
    {
        TEST_ASSERT(b[i] == 100);
    }
}

TEST_CASE(ctor_op_equal)
{
    Array<int> a(10, 100), b;

    b = a;
    TEST_ASSERT(b == a);

    ++b[3];
    TEST_ASSERT(b != a);

    --b[3];
    TEST_ASSERT(b == a);

    a.PushBack(100);
    TEST_ASSERT(b != a);

    a.PopFront();
    TEST_ASSERT(b == a);
}

// TODO...

int main()
{
    return 0;
}
