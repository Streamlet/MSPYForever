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


#include "../PerformanceTest.h"
#include <xl/Containers/xlArray.h>
#include <vector>

int main()
{
    using namespace std;
    using namespace xl;

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
