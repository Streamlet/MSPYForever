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


#include "../PerformanceTest.h"
#include "../../../Include/xl/Containers/xlList.h"
#include <list>

int main()
{
    using namespace std;
    using namespace xl;

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
