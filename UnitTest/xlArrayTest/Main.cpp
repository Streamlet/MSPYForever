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
#include <xl/Test/xlUnitTest.h>

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
    a.InsertBuffer(0, data, 4);
    XL_TEST_ASSERT(a.Size() == 4);
    XL_TEST_ASSERT(a[0] == 1);
    XL_TEST_ASSERT(a[1] == 3);
    XL_TEST_ASSERT(a[2] == 2);
    XL_TEST_ASSERT(a[3] == 4);

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

#include <vector>
using namespace std;

int main()
{
    SECTION_BEGIN(StdVectorPushBack100000);
    vector<int> v1;
    PERFORMANCE_TEST_BEGIN(StdVectorPushBack100000);
    for (int i = 0; i < 100000; ++i)
    {
        v1.push_back(i);
    }
    PERFORMANCE_TEST_END(StdVectorPushBack100000);
    SECTION_END();

    SECTION_BEGIN(xlArrayPushBack100000);
    Array<int> a1;
    PERFORMANCE_TEST_BEGIN(xlArrayPushBack100000);
    for (int i = 0; i < 100000; ++i)
    {
        a1.PushBack(i);
    }
    PERFORMANCE_TEST_END(xlArrayPushBack100000);
    SECTION_END();

    SECTION_BEGIN(xlArrayPushFront100000);
    Array<int> a2;
    PERFORMANCE_TEST_BEGIN(xlArrayPushFront100000);
    for (int i = 0; i < 100000; ++i)
    {
        a2.PushFront(i);
    }
    PERFORMANCE_TEST_END(xlArrayPushFront100000);
    SECTION_END();


    SECTION_BEGIN(StdVectorPushBack1000000);
    vector<int> v2;
    PERFORMANCE_TEST_BEGIN(StdVectorPushBack1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        v2.push_back(i);
    }
    PERFORMANCE_TEST_END(StdVectorPushBack1000000);
    SECTION_END();

    SECTION_BEGIN(xlArrayPushBack1000000);
    Array<int> a3;
    PERFORMANCE_TEST_BEGIN(xlArrayPushBack1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        a3.PushBack(i);
    }
    PERFORMANCE_TEST_END(xlArrayPushBack1000000);
    SECTION_END();

    SECTION_BEGIN(xlArrayPushFront1000000);
    Array<int> a4;
    PERFORMANCE_TEST_BEGIN(xlArrayPushFront1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        a4.PushFront(i);
    }
    PERFORMANCE_TEST_END(xlArrayPushFront1000000);
    SECTION_END();


    SECTION_BEGIN(StdVectorPushBack10000000);
    vector<int> v3;
    PERFORMANCE_TEST_BEGIN(StdVectorPushBack10000000);
    for (int i = 0; i < 10000000; ++i)
    {
        v3.push_back(i);
    }
    PERFORMANCE_TEST_END(StdVectorPushBack10000000);
    SECTION_END();

    SECTION_BEGIN(xlArrayPushBack10000000);
    Array<int> a5;
    PERFORMANCE_TEST_BEGIN(xlArrayPushBack10000000);
    for (int i = 0; i < 10000000; ++i)
    {
        a5.PushBack(i);
    }
    PERFORMANCE_TEST_END(xlArrayPushBack10000000);
    SECTION_END();

    SECTION_BEGIN(xlArrayPushFront10000000);
    Array<int> a6;
    PERFORMANCE_TEST_BEGIN(xlArrayPushFront10000000);
    for (int i = 0; i < 10000000; ++i)
    {
        a6.PushFront(i);
    }
    PERFORMANCE_TEST_END(xlArrayPushFront10000000);
    SECTION_END();

    return 0;
}
