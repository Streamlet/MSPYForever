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


#include "../PerformanceTest.h"
#include "../../../Include/xl/Containers/xlMap.h"
#include <map>

int main()
{
    using namespace std;
    using namespace xl;

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
