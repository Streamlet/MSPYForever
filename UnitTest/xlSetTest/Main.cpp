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
#include <xl/Test/xlUnitTest.h>

using namespace xl;

XL_TEST_CASE()
{
    Set<int> a;
    XL_TEST_ASSERT(a.Size() == 0);
}

XL_TEST_CASE()
{
    Set<int> a;
    XL_TEST_ASSERT(a.Size() == 0);

    Set<int> b(a);
    XL_TEST_ASSERT(b.Size() == 0);

    a.Insert(1);
    a.Insert(2);
    Set<int> c(a);
    XL_TEST_ASSERT(c.Size() == 2);
    XL_TEST_ASSERT(*c.Begin() == 1);
    XL_TEST_ASSERT(*c.ReverseBegin() == 2);
}

XL_TEST_CASE()
{
    Set<int> a;
    XL_TEST_ASSERT(a.Size() == 0);

    Set<int> b;
    b = a;
    XL_TEST_ASSERT(b.Size() == 0);

    a.Insert(1);
    a.Insert(2);
    Set<int> c;
    c = a;
    XL_TEST_ASSERT(c.Size() == 2);
    XL_TEST_ASSERT(*a.Begin() == 1);
    XL_TEST_ASSERT(*++a.Begin() == 2);
}

XL_TEST_CASE()
{
    Set<int> a;
    XL_TEST_ASSERT(a.Size() == 0);

    Set<int> b;
    b = a;
    XL_TEST_ASSERT(b == a);
    XL_TEST_ASSERT(!(b != a));

    a.Insert(1);
    a.Insert(2);
    XL_TEST_ASSERT(b != a);
    XL_TEST_ASSERT(!(b == a));

    Set<int> c(a);
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
    Set<int> a;
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
    Set<int> a;

    a.Insert(2);
    a.Insert(6);
    a.Insert(4);
    a.Insert(3);
    a.Insert(5);
    a.Insert(1);

    Set<int>::Iterator it = a.Begin();

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
    Set<int> a;

    a.Insert(2);
    a.Insert(6);
    a.Insert(4);
    a.Insert(3);
    a.Insert(5);
    a.Insert(1);

    Set<int>::Iterator it = a.Find(5);

    XL_TEST_ASSERT(*it == 5);

    Set<int>::Iterator it2 = it;

    ++it2;
    XL_TEST_ASSERT(*it2 == 6);

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

#include <set>
using namespace std;


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
