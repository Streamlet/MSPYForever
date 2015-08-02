//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2012-06-11
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#include "../PerformanceTest.h"
#include "../../../Include/xl/Parser/xlRegExp.h"
#include <regex>

int main()
{
    using namespace std;
    using namespace xl;

    SECTION_BEGIN(StdRegExParse100000);
    PERFORMANCE_TEST_BEGIN(StdRegExParse100000);
    for (int i = 0; i < 100000; ++i)
    {
        wregex r;
        r.assign(L"http://([a-zA-Z0-9\\-]+.)+[a-zA-Z]+/");
    }
    PERFORMANCE_TEST_END(StdRegExParse100000);
    SECTION_END();

    SECTION_BEGIN(xlRegExpParse100000);
    PERFORMANCE_TEST_BEGIN(xlRegExpParse100000);
    for (int i = 0; i < 100000; ++i)
    {
        RegExp r;
        r.Parse(L"http://([a-zA-Z0-9\\-]+.)+[a-zA-Z]+/");
    }
    PERFORMANCE_TEST_END(xlRegExpParse100000);
    SECTION_END();

    SECTION_BEGIN(StdRegExMatch100000);
    {
        wregex r;
        r.assign(L"http://([a-zA-Z0-9\\-]+.)+[a-zA-Z]+/");
        PERFORMANCE_TEST_BEGIN(StdRegExMatch100000);
        for (int i = 0; i < 100000; ++i)
        {
            regex_match(L"http://w-1.w-2.w-3.streamlet.org/", r);
        }
        PERFORMANCE_TEST_END(StdRegExMatch100000);
    }
    SECTION_END();

    SECTION_BEGIN(xlRegExpMatch100000);
    {
        RegExp r;
        r.Parse(L"http://([a-zA-Z0-9\\-]+.)+[a-zA-Z]+/");
        PERFORMANCE_TEST_BEGIN(xlRegExpMatch100000);
        for (int i = 0; i < 100000; ++i)
        {
            r.Match(L"http://w-1.w-2.w-3.streamlet.org/");
        }
        PERFORMANCE_TEST_END(xlRegExpMatch100000);
    }
    SECTION_END();

    return 0;
}
