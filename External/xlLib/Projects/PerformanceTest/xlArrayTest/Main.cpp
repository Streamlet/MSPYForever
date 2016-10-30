//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-08-08
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/AppHelper/xlPerfTest.h"
#include "../../../Include/xl/Common/Containers/xlArray.h"
#include <vector>
#include <deque>

int main()
{
    XL_BEGIN_PERF_TEST(StdVectorPushBack)
    {
        std::vector<int> v;
        for (int i = 0; i < 50000000; ++i)
        {
            v.push_back(i);
        }
    }
    XL_END_PERF_TEST()

    XL_BEGIN_PERF_TEST(xlVectorPushBack)
    {
        xl::Vector<int> v;
        for (int i = 0; i < 50000000; ++i)
        {
            v.PushBack(i);
        }
    }
    XL_END_PERF_TEST()

    XL_BEGIN_PERF_TEST(xlArrayPushBack)
    {
        xl::Array<int> a;
        for (int i = 0; i < 50000000; ++i)
        {
            a.PushBack(i);
        }
    }
    XL_END_PERF_TEST()

    XL_BEGIN_PERF_TEST(xlArrayPushFront)
    {
        xl::Array<int> a;
        for (int i = 0; i < 50000000; ++i)
        {
            a.PushFront(i);
        }
    }
    XL_END_PERF_TEST()

    XL_BEGIN_PERF_TEST(xlStackPushFront)
    {
        xl::Stack<int> s;
        for (int i = 0; i < 50000000; ++i)
        {
            s.PushFront(i);
        }
    }
    XL_END_PERF_TEST()

    XL_BEGIN_PERF_TEST(StdDequePushFront)
    {
        std::deque<int> d;
        for (int i = 0; i < 50000000; ++i)
        {
            d.push_front(i);
        }
    }
    XL_END_PERF_TEST()

    return 0;
}
