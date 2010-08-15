//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-08-14
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Containers/xlPair.h>
#include "../UnitTestFrame.h"

using namespace xl;

TEST_CASE(ctor)
{
    Pair<int, int> a(1);
    TEST_ASSERT(a.Key == 1);

    Pair<int, int> b(-1, -2);
    TEST_ASSERT(b.Key == -1);
    TEST_ASSERT(b.Value == -2);

    Pair<int, int> c(b);
    TEST_ASSERT(c.Key == -1);
    TEST_ASSERT(c.Value == -2);

    Pair<int, int> d;
    d = c;
    TEST_ASSERT(d.Key == -1);
    TEST_ASSERT(c.Value == -2);
}

TEST_CASE(operator_compare)
{
    Pair<int, int> a(1, 1), b(1, 2);
    TEST_ASSERT(a == b);
    TEST_ASSERT(!(a != b));
    TEST_ASSERT(!(a < b));
    TEST_ASSERT(!(a > b));
    TEST_ASSERT(a <= b);
    TEST_ASSERT(a >= b);

    a.Key = -1;
    TEST_ASSERT(!(a == b));
    TEST_ASSERT(a != b);
    TEST_ASSERT(a < b);
    TEST_ASSERT(!(a > b));
    TEST_ASSERT(a <= b);
    TEST_ASSERT(!(a >= b));

    a.Key = 2;
    TEST_ASSERT(!(a == b));
    TEST_ASSERT(a != b);
    TEST_ASSERT(!(a < b));
    TEST_ASSERT(a > b);
    TEST_ASSERT(!(a <= b));
    TEST_ASSERT(a >= b);
}

int main()
{
    return 0;
}
