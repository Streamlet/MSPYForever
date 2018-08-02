//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2012-06-11
//    Description: 
//
//------------------------------------------------------------------------------

#include "../../../Include/xl/AppHelper/xlPerfTest.h"
#include "../../../Include/xl/Common/Parser/xlRegExp.h"
#include <regex>

int main()
{
    XL_BEGIN_PERF_TEST(StdRegExParseAndMatch)
    {
        for (int i = 0; i < 1000; ++i)
        {
            std::wregex r;
            r.assign(L"http://([a-zA-Z0-9\\-]+.)+[a-zA-Z]+/");
            regex_match(L"http://w-1.w-2.w-3.streamlet.org/", r);
        }
    }
    XL_END_PERF_TEST()

    XL_BEGIN_PERF_TEST(xlRegExpParseAndMatch)
    {
        for (int i = 0; i < 1000; ++i)
        {
            xl::RegExp r;
            r.Parse(L"http://([a-zA-Z0-9\\-]+.)+[a-zA-Z]+/");
            r.Match(L"http://w-1.w-2.w-3.streamlet.org/");
        }
    }
    XL_END_PERF_TEST()

    return 0;
}
