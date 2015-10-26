//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-08-14
//    Description: 
//
//------------------------------------------------------------------------------


#include "../PerformanceTest.h"
#include "../../../Include/xl/Common/Containers/xlSet.h"
#include <set>

int main()
{
    using namespace std;
    using namespace xl;

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
