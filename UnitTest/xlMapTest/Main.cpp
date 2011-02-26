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


#include <xl/Containers/xlMap.h>
#include <xl/Test/xlUnitTest.h>

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

// Performance Test

#include <stdio.h>
#include <time.h>

#define SECTION_BEGIN(name) \
    printf("Testing \"" #name "\"...\n")
#define SECTION_END()   \
    printf("\n")
#define PERFORMANCE_TEST_BEGIN(name)    \
    printf("Test begins.\n");   \
    clock_t begin_##name = clock()
#define PERFORMANCE_TEST_END(name)  \
    clock_t end_##name = clock();   \
    printf("Test ends. Time elasped: %lfs.\n", (double)(end_##name - begin_##name) / CLOCKS_PER_SEC)

#include <map>
using namespace std;


int main()
{
    SECTION_BEGIN(StdMapInsert100000);
    map<int, int> m1;
    PERFORMANCE_TEST_BEGIN(StdMapInsert100000);
    for (int i = 0; i < 100000; ++i)
    {
        m1.insert(std::make_pair((i % 2 == 0 ? i : -i), i));
    }
    PERFORMANCE_TEST_END(StdMapInsert100000);
    SECTION_END();

    SECTION_BEGIN(xlMapInsert100000);
    Map<int, int> a1;
    PERFORMANCE_TEST_BEGIN(xlMapInsert100000);
    for (int i = 0; i < 100000; ++i)
    {
        a1.Insert((i % 2 == 0 ? i : -i), i);
    }
    PERFORMANCE_TEST_END(xlMapInsert100000);
    SECTION_END();


    SECTION_BEGIN(StdMapInsert1000000);
    map<int, int> m2;
    PERFORMANCE_TEST_BEGIN(StdMapInsert1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        m2.insert(std::make_pair((i % 2 == 0 ? i : -i), i));
    }
    PERFORMANCE_TEST_END(StdMapInsert1000000);
    SECTION_END();

    SECTION_BEGIN(xlMapInsert1000000);
    Map<int, int> a2;
    PERFORMANCE_TEST_BEGIN(xlMapInsert1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        a2.Insert((i % 2 == 0 ? i : -i), i);
    }
    PERFORMANCE_TEST_END(xlMapInsert1000000);
    SECTION_END();


    SECTION_BEGIN(StdMapInsert10000000);
    map<int, int> m3;
    PERFORMANCE_TEST_BEGIN(StdMapInsert10000000);
    for (int i = 0; i < 10000000; ++i)
    {
        m3.insert(std::make_pair((i % 2 == 0 ? i : -i), i));
    }
    PERFORMANCE_TEST_END(StdMapInsert10000000);
    SECTION_END();

    SECTION_BEGIN(xlMapInsert10000000);
    Map<int, int> a3;
    PERFORMANCE_TEST_BEGIN(xlMapInsert10000000);
    for (int i = 0; i < 10000000; ++i)
    {
        a3.Insert((i % 2 == 0 ? i : -i), i);
    }
    PERFORMANCE_TEST_END(xlMapInsert10000000);
    SECTION_END();

    return 0;
}
