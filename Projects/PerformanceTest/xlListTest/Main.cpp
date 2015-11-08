//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-08-10
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/AppHelper/xlPerfTest.h"
#include "../../../Include/xl/Common/Containers/xlList.h"
#include <list>

int main()
{
    XL_BEGIN_PERF_TEST(StdListPushBack)
    {
        std::list<int> l;
        for (int i = 0; i < 10000000; ++i)
        {
            l.push_back(i);
        }
    }
    XL_END_PERF_TEST()

    XL_BEGIN_PERF_TEST(xlListPushBack)
    {
        xl::List<int> a;
        for (int i = 0; i < 10000000; ++i)
        {
            a.PushBack(i);
        }
    }
    XL_END_PERF_TEST()

    XL_BEGIN_PERF_TEST(StdListPushFront)
    {
        std::list<int> l;
        for (int i = 0; i < 10000000; ++i)
        {
            l.push_front(i);
        }
    }
    XL_END_PERF_TEST()

    XL_BEGIN_PERF_TEST(xlListPushFront)
    {
        xl::List<int> a;
        for (int i = 0; i < 10000000; ++i)
        {
            a.PushFront(i);
        }
    }
    XL_END_PERF_TEST()

    return 0;
}
