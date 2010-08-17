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


#include <xl/Containers/xlSet.h>
#include "../UnitTestFrame.h"

using namespace xl;

TEST_CASE(ctor)
{
    Set<int> a;
    TEST_ASSERT(a.Size() == 0);
}

TEST_CASE(ctor_copy)
{
    Set<int> a;
    TEST_ASSERT(a.Size() == 0);

    Set<int> b(a);
    TEST_ASSERT(b.Size() == 0);

    a.Insert(1);
    a.Insert(2);
    Set<int> c(a);
    TEST_ASSERT(c.Size() == 2);
    TEST_ASSERT(*c.Begin() == 1);
    TEST_ASSERT(*c.ReverseBegin() == 2);
}

TEST_CASE(operator_set)
{
    Set<int> a;
    TEST_ASSERT(a.Size() == 0);

    Set<int> b;
    b = a;
    TEST_ASSERT(b.Size() == 0);

    a.Insert(1);
    a.Insert(2);
    Set<int> c;
    c = a;
    TEST_ASSERT(c.Size() == 2);
    TEST_ASSERT(*a.Begin() == 1);
    TEST_ASSERT(*++a.Begin() == 2);
}

TEST_CASE(operator_equal)
{
    Set<int> a;
    TEST_ASSERT(a.Size() == 0);

    Set<int> b;
    b = a;
    TEST_ASSERT(b == a);
    TEST_ASSERT(!(b != a));

    a.Insert(1);
    a.Insert(2);
    TEST_ASSERT(b != a);
    TEST_ASSERT(!(b == a));

    Set<int> c(a);
    TEST_ASSERT(c == a);
    TEST_ASSERT(!(c != a));

    b.Insert(1);
    b.Insert(2);
    TEST_ASSERT(b == a);
    TEST_ASSERT(!(b != a));
    TEST_ASSERT(b == c);
    TEST_ASSERT(!(b != c));
}

TEST_CASE(method_size)
{
    Set<int> a;
    TEST_ASSERT(a.Size() == 0);
    TEST_ASSERT(a.Empty() == true);

    a.Insert(10);
    TEST_ASSERT(a.Size() == 1);
    TEST_ASSERT(a.Empty() == false);

    a.Insert(20);
    a.Insert(30);
    a.Insert(40);
    a.Insert(50);
    TEST_ASSERT(a.Size() == 5);
    TEST_ASSERT(a.Empty() == false);
}

TEST_CASE(method_insert_delete)
{
    Set<int> a;

    a.Insert(2);
    a.Insert(6);
    a.Insert(4);
    a.Insert(3);
    a.Insert(5);
    a.Insert(1);

    Set<int>::Iterator it = a.Begin();

    TEST_ASSERT(*it == 1);

    ++it;
    TEST_ASSERT(*it == 2);

    ++it;
    TEST_ASSERT(*it == 3);

    ++it;
    TEST_ASSERT(*it == 4);

    ++it;
    TEST_ASSERT(*it == 5);

    ++it;
    TEST_ASSERT(*it == 6);

    ++it;
    TEST_ASSERT(it == a.End());
}

TEST_CASE(method_find)
{
    Set<int> a;

    a.Insert(2);
    a.Insert(6);
    a.Insert(4);
    a.Insert(3);
    a.Insert(5);
    a.Insert(1);

    Set<int>::Iterator it = a.Find(5);

    TEST_ASSERT(*it == 5);

    Set<int>::Iterator it2 = it;

    ++it2;
    TEST_ASSERT(*it2 == 6);

    ++it2;
    TEST_ASSERT(it2 == a.End());
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
    printf("Test ends. Time elasped: %lfs.\n", (double)(end_##name - begin_##name) / CLK_TCK)

#include <vector>
using namespace std;

#include <set>

int main()
{
    SECTION_BEGIN(StdSetInsert100000);
    set<int> s1;
    PERFORMANCE_TEST_BEGIN(StdSetInsert100000);
    for (int i = 0; i < 100000; ++i)
    {
        s1.insert(i);
    }
    PERFORMANCE_TEST_END(StdSetInsert100000);
    SECTION_END();

    SECTION_BEGIN(xlSetInsert100000);
    Set<int> a1;
    PERFORMANCE_TEST_BEGIN(xlSetInsert100000);
    for (int i = 0; i < 100000; ++i)
    {
        a1.Insert(i);
    }
    PERFORMANCE_TEST_END(xlSetInsert100000);
    SECTION_END();


    SECTION_BEGIN(StdSetInsert1000000);
    set<int> s2;
    PERFORMANCE_TEST_BEGIN(StdSetInsert1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        s2.insert(i);
    }
    PERFORMANCE_TEST_END(StdSetInsert1000000);
    SECTION_END();

    SECTION_BEGIN(xlSetInsert1000000);
    Set<int> a2;
    PERFORMANCE_TEST_BEGIN(xlSetInsert1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        a2.Insert(i);
    }
    PERFORMANCE_TEST_END(xlSetInsert1000000);
    SECTION_END();


    SECTION_BEGIN(StdSetInsert10000000);
    set<int> s3;
    PERFORMANCE_TEST_BEGIN(StdSetInsert10000000);
    for (int i = 0; i < 10000000; ++i)
    {
        s3.insert(i);
    }
    PERFORMANCE_TEST_END(StdSetInsert10000000);
    SECTION_END();

    SECTION_BEGIN(xlSetInsert10000000);
    Set<int> a3;
    PERFORMANCE_TEST_BEGIN(xlSetInsert10000000);
    for (int i = 0; i < 10000000; ++i)
    {
        a3.Insert(i);
    }
    PERFORMANCE_TEST_END(xlSetInsert10000000);
    SECTION_END();

    return 0;
}
