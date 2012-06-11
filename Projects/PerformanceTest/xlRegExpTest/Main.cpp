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
#include <xl/Parser/xlRegExp.h>
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

    return 0;
}
