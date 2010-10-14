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

    a.Insert(a.Begin(), -1);
    TEST_ASSERT(a.Size() == 1);
    TEST_ASSERT(*a.Begin() == -1);

    a.PushBack(15);
    TEST_ASSERT(a.Size() == 2);
    TEST_ASSERT(*a.ReverseBegin() == 15);

    a.PushFront(20);
    TEST_ASSERT(a.Size() == 3);
    TEST_ASSERT(*a.Begin() == 20);
    
    a.Delete(a.Begin());
    TEST_ASSERT(a.Size() == 2);
    TEST_ASSERT(*a.Begin() == -1);
    TEST_ASSERT(*(++a.Begin()) == 15);

    a.PopBack();
    TEST_ASSERT(a.Size() == 1);
    TEST_ASSERT(*a.Begin() == -1);

    a.Clear();
    TEST_ASSERT(a.Size() == 0);
    TEST_ASSERT(a.Empty() == true);
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

#include <list>
using namespace std;

int main()
{
    SECTION_BEGIN(StdListPushBack100000);
    list<int> l1;
    PERFORMANCE_TEST_BEGIN(StdListPushBack100000);
    for (int i = 0; i < 100000; ++i)
    {
        l1.push_back(i);
    }
    PERFORMANCE_TEST_END(StdListPushBack100000);
    SECTION_END();

    SECTION_BEGIN(xlListPushBack100000);
    List<int> a1;
    PERFORMANCE_TEST_BEGIN(xlListPushBack100000);
    for (int i = 0; i < 100000; ++i)
    {
        a1.PushBack(i);
    }
    PERFORMANCE_TEST_END(xlListPushBack100000);
    SECTION_END();

    SECTION_BEGIN(StdListPushFront100000);
    list<int> l2;
    PERFORMANCE_TEST_BEGIN(StdListPushFront100000);
    for (int i = 0; i < 100000; ++i)
    {
        l2.push_back(i);
    }
    PERFORMANCE_TEST_END(StdListPushFront100000);
    SECTION_END();

    SECTION_BEGIN(xlListPushFront100000);
    List<int> a2;
    PERFORMANCE_TEST_BEGIN(xlListPushFront100000);
    for (int i = 0; i < 100000; ++i)
    {
        a2.PushFront(i);
    }
    PERFORMANCE_TEST_END(xlListPushFront100000);
    SECTION_END();


    SECTION_BEGIN(StdListPushBack1000000);
    list<int> l3;
    PERFORMANCE_TEST_BEGIN(StdListPushBack1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        l3.push_back(i);
    }
    PERFORMANCE_TEST_END(StdListPushBack1000000);
    SECTION_END();

    SECTION_BEGIN(xlListPushBack1000000);
    List<int> a3;
    PERFORMANCE_TEST_BEGIN(xlListPushBack1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        a3.PushBack(i);
    }
    PERFORMANCE_TEST_END(xlListPushBack1000000);
    SECTION_END();

    SECTION_BEGIN(StdListPushFront1000000);
    list<int> l4;
    PERFORMANCE_TEST_BEGIN(StdListPushFront1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        l4.push_back(i);
    }
    PERFORMANCE_TEST_END(StdListPushFront1000000);
    SECTION_END();

    SECTION_BEGIN(xlListPushFront1000000);
    List<int> a4;
    PERFORMANCE_TEST_BEGIN(xlListPushFront1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        a4.PushFront(i);
    }
    PERFORMANCE_TEST_END(xlListPushFront1000000);
    SECTION_END();


    SECTION_BEGIN(StdListPushBack10000000);
    list<int> l5;
    PERFORMANCE_TEST_BEGIN(StdListPushBack10000000);
    for (int i = 0; i < 10000000; ++i)
    {
        l5.push_back(i);
    }
    PERFORMANCE_TEST_END(StdListPushBack10000000);
    SECTION_END();

    SECTION_BEGIN(xlListPushBack10000000);
    List<int> a5;
    PERFORMANCE_TEST_BEGIN(xlListPushBack10000000);
    for (int i = 0; i < 10000000; ++i)
    {
        a5.PushBack(i);
    }
    PERFORMANCE_TEST_END(xlListPushBack10000000);
    SECTION_END();

    SECTION_BEGIN(StdListPushFront10000000);
    list<int> l6;
    PERFORMANCE_TEST_BEGIN(StdListPushFront10000000);
    for (int i = 0; i < 10000000; ++i)
    {
        l6.push_back(i);
    }
    PERFORMANCE_TEST_END(StdListPushFront10000000);
    SECTION_END();

    SECTION_BEGIN(xlListPushFront10000000);
    List<int> a6;
    PERFORMANCE_TEST_BEGIN(xlListPushFront10000000);
    for (int i = 0; i < 10000000; ++i)
    {
        a6.PushFront(i);
    }
    PERFORMANCE_TEST_END(xlListPushFront10000000);
    SECTION_END();

    return 0;
}
