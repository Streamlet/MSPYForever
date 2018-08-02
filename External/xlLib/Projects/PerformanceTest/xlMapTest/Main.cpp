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
#include "../../../Include/xl/Common/Containers/xlMap.h"
#include <map>

int main()
{
    XL_BEGIN_PERF_TEST(StdMapInsert)
    {
        std::map<int, int> m;
        for (int i = 0; i < 10000000; ++i)
        {
            m.insert(std::make_pair((i % 2 == 0 ? i : -i), i));
        }
    }
    XL_END_PERF_TEST()

    XL_BEGIN_PERF_TEST(xlMapInsert)
    {
        xl::Map<int, int> a;
        for (int i = 0; i < 10000000; ++i)
        {
            a.Insert((i % 2 == 0 ? i : -i), i);
        }
    }
    XL_END_PERF_TEST()

    return 0;
}
