//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlRegExpTest.cpp
//    Author:      Streamlet
//    Create Time: 2012-06-02
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Parser/xlRegExp.h>
#include <xl/Test/xlUnitTest.h>

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        RegExp r;
        XL_TEST_ASSERT(r.Parse(L""));
        XL_TEST_ASSERT(r.Parse(L"||"));
        XL_TEST_ASSERT(r.Parse(L"()"));
        XL_TEST_ASSERT(r.Parse(L"|"));
        XL_TEST_ASSERT(r.Parse(L"(|)"));
        XL_TEST_ASSERT(r.Parse(L"(||)"));
        XL_TEST_ASSERT(r.Parse(L"()|()"));
        XL_TEST_ASSERT(!r.Parse(L"("));
        XL_TEST_ASSERT(!r.Parse(L")"));
    }

    XL_TEST_CASE()
    {
        RegExp r;

        XL_TEST_ASSERT(r.Parse(L""));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));

        XL_TEST_ASSERT(r.Parse(L"a"));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"ab"));
        XL_TEST_ASSERT(!r.Match(L"b"));

        XL_TEST_ASSERT(r.Parse(L"(a)"));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"ab"));
        XL_TEST_ASSERT(!r.Match(L"b"));

        XL_TEST_ASSERT(r.Parse(L"ab|c"));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"b"));
        XL_TEST_ASSERT(r.Match(L"c"));
        XL_TEST_ASSERT(r.Match(L"ab"));
        XL_TEST_ASSERT(!r.Match(L"bc"));
        XL_TEST_ASSERT(!r.Match(L"ac"));

        XL_TEST_ASSERT(r.Parse(L"a(b|c)"));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"b"));
        XL_TEST_ASSERT(!r.Match(L"c"));
        XL_TEST_ASSERT(r.Match(L"ab"));
        XL_TEST_ASSERT(r.Match(L"ac"));
        XL_TEST_ASSERT(!r.Match(L"bc"));
    }
}
