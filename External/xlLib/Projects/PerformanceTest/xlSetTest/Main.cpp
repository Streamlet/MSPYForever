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


#include "../../../Include/xl/AppHelper/xlPerfTest.h"
#include "../../../Include/xl/Common/Containers/xlSet.h"
#include <set>

int main()
{
    XL_BEGIN_PERF_TEST(StdSetInsert)
    {
        std::set<int> s;
        for (int i = 0; i < 10000000; ++i)
        {
            s.insert(i);
        }
    }
    XL_END_PERF_TEST()

    XL_BEGIN_PERF_TEST(xlSetInsert)
    {
        xl::Set<int> a;
        for (int i = 0; i < 10000000; ++i)
        {
            a.Insert(i);
        }
    }
    XL_END_PERF_TEST()

    return 0;
}
