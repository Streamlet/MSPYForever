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
        XL_TEST_ASSERT(!r.Match(L"a"));

        XL_TEST_ASSERT(r.Parse(L"a"));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"ab"));
        XL_TEST_ASSERT(!r.Match(L"b"));

        XL_TEST_ASSERT(r.Parse(L"(a)"));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"ab"));
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

    XL_TEST_CASE()
    {
        RegExp r;

        XL_TEST_ASSERT(r.Parse(L"\\|"));
        XL_TEST_ASSERT(r.Match(L"|"));

        XL_TEST_ASSERT(r.Parse(L"\\("));
        XL_TEST_ASSERT(r.Match(L"("));

        XL_TEST_ASSERT(r.Parse(L"\\)"));
        XL_TEST_ASSERT(r.Match(L")"));

        XL_TEST_ASSERT(r.Parse(L"\\\\"));
        XL_TEST_ASSERT(r.Match(L"\\"));

        XL_TEST_ASSERT(r.Parse(L"\\"));
        XL_TEST_ASSERT(r.Match(L"\\"));

        XL_TEST_ASSERT(r.Parse(L"\\|(\\(|\\))"));
        XL_TEST_ASSERT(r.Match(L"|("));
        XL_TEST_ASSERT(r.Match(L"|)"));
    }

    XL_TEST_CASE()
    {
        RegExp r;
        // an integer from 0 to 255
        // 1 digit: (0|1|2|3|4|5|6|7|8|9)
        // 2 digit: (0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)
        // 3 digit:
        //   0-199: (0|1)(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)
        // 200-249: 2(0|1|2|3|4)(0|1|2|3|4|5|6|7|8|9)
        // 250-255: 25(0|1|2|3|4|5)
        XL_TEST_ASSERT(r.Parse(L"(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1)(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"2(0|1|2|3|4)(0|1|2|3|4|5|6|7|8|9)|"
                               L"25(0|1|2|3|4|5)"));
        XL_TEST_ASSERT(r.Match(L"0"));
        XL_TEST_ASSERT(r.Match(L"1"));
        XL_TEST_ASSERT(r.Match(L"2"));
        XL_TEST_ASSERT(r.Match(L"3"));
        XL_TEST_ASSERT(r.Match(L"4"));
        XL_TEST_ASSERT(r.Match(L"5"));
        XL_TEST_ASSERT(r.Match(L"6"));
        XL_TEST_ASSERT(r.Match(L"7"));
        XL_TEST_ASSERT(r.Match(L"8"));
        XL_TEST_ASSERT(r.Match(L"9"));
        XL_TEST_ASSERT(r.Match(L"10"));
        XL_TEST_ASSERT(r.Match(L"20"));
        XL_TEST_ASSERT(r.Match(L"30"));
        XL_TEST_ASSERT(r.Match(L"40"));
        XL_TEST_ASSERT(r.Match(L"50"));
        XL_TEST_ASSERT(r.Match(L"60"));
        XL_TEST_ASSERT(r.Match(L"70"));
        XL_TEST_ASSERT(r.Match(L"80"));
        XL_TEST_ASSERT(r.Match(L"90"));
        XL_TEST_ASSERT(r.Match(L"100"));
        XL_TEST_ASSERT(r.Match(L"199"));
        XL_TEST_ASSERT(r.Match(L"200"));
        XL_TEST_ASSERT(r.Match(L"249"));
        XL_TEST_ASSERT(r.Match(L"250"));
        XL_TEST_ASSERT(r.Match(L"251"));
        XL_TEST_ASSERT(r.Match(L"252"));
        XL_TEST_ASSERT(r.Match(L"253"));
        XL_TEST_ASSERT(r.Match(L"254"));
        XL_TEST_ASSERT(r.Match(L"255"));
        XL_TEST_ASSERT(!r.Match(L"256"));
        XL_TEST_ASSERT(!r.Match(L"260"));
        XL_TEST_ASSERT(!r.Match(L"300"));

        // IPv4 address
        XL_TEST_ASSERT(r.Parse(L"("
                               L"(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1)(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"2(0|1|2|3|4)(0|1|2|3|4|5|6|7|8|9)|"
                               L"25(0|1|2|3|4|5)"
                               L").("
                               L"(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1)(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"2(0|1|2|3|4)(0|1|2|3|4|5|6|7|8|9)|"
                               L"25(0|1|2|3|4|5)"
                               L").("
                               L"(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1)(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"2(0|1|2|3|4)(0|1|2|3|4|5|6|7|8|9)|"
                               L"25(0|1|2|3|4|5)"
                               L").("
                               L"(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1)(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"2(0|1|2|3|4)(0|1|2|3|4|5|6|7|8|9)|"
                               L"25(0|1|2|3|4|5)"
                               L")"));
        XL_TEST_ASSERT(r.Match(L"192.168.1.1"));
        XL_TEST_ASSERT(r.Match(L"0.0.0.0"));
        XL_TEST_ASSERT(r.Match(L"255.255.255.255"));
        XL_TEST_ASSERT(!r.Match(L"0.0.0.256"));
    }

    XL_TEST_CASE()
    {
        RegExp r;
        XL_TEST_ASSERT(r.Parse(L"[]"));
        XL_TEST_ASSERT(r.Parse(L"[^]"));
        XL_TEST_ASSERT(!r.Parse(L"[(]"));
        XL_TEST_ASSERT(!r.Parse(L"[|]"));

        XL_TEST_ASSERT(r.Parse(L"[1-3a]"));
        XL_TEST_ASSERT(r.Match(L"1"));
        XL_TEST_ASSERT(r.Match(L"2"));
        XL_TEST_ASSERT(r.Match(L"3"));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"0"));
        XL_TEST_ASSERT(!r.Match(L"4"));
        XL_TEST_ASSERT(!r.Match(L"b"));

        XL_TEST_ASSERT(r.Parse(L"[^1-3a]"));
        XL_TEST_ASSERT(!r.Match(L"1"));
        XL_TEST_ASSERT(!r.Match(L"2"));
        XL_TEST_ASSERT(!r.Match(L"3"));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"0"));
        XL_TEST_ASSERT(r.Match(L"4"));
        XL_TEST_ASSERT(r.Match(L"b"));
    }

    XL_TEST_CASE()
    {
        RegExp r;
        // an integer from 0 to 255
        // 1 digit: [0-9]
        // 2 digit: [0-9][0-9]
        // 3 digit:
        //   0-199: [01][0-9][0-9]
        // 200-249: 2[0-4][0-9]
        // 250-255: 25[0-5]
        XL_TEST_ASSERT(r.Parse(L"[0-9]|[0-9][0-9]|[01][0-9][0-9]|2[0-4][0-9]|25[0-5]"));
        XL_TEST_ASSERT(r.Match(L"0"));
        XL_TEST_ASSERT(r.Match(L"1"));
        XL_TEST_ASSERT(r.Match(L"2"));
        XL_TEST_ASSERT(r.Match(L"3"));
        XL_TEST_ASSERT(r.Match(L"4"));
        XL_TEST_ASSERT(r.Match(L"5"));
        XL_TEST_ASSERT(r.Match(L"6"));
        XL_TEST_ASSERT(r.Match(L"7"));
        XL_TEST_ASSERT(r.Match(L"8"));
        XL_TEST_ASSERT(r.Match(L"9"));
        XL_TEST_ASSERT(r.Match(L"10"));
        XL_TEST_ASSERT(r.Match(L"20"));
        XL_TEST_ASSERT(r.Match(L"30"));
        XL_TEST_ASSERT(r.Match(L"40"));
        XL_TEST_ASSERT(r.Match(L"50"));
        XL_TEST_ASSERT(r.Match(L"60"));
        XL_TEST_ASSERT(r.Match(L"70"));
        XL_TEST_ASSERT(r.Match(L"80"));
        XL_TEST_ASSERT(r.Match(L"90"));
        XL_TEST_ASSERT(r.Match(L"100"));
        XL_TEST_ASSERT(r.Match(L"199"));
        XL_TEST_ASSERT(r.Match(L"200"));
        XL_TEST_ASSERT(r.Match(L"249"));
        XL_TEST_ASSERT(r.Match(L"250"));
        XL_TEST_ASSERT(r.Match(L"251"));
        XL_TEST_ASSERT(r.Match(L"252"));
        XL_TEST_ASSERT(r.Match(L"253"));
        XL_TEST_ASSERT(r.Match(L"254"));
        XL_TEST_ASSERT(r.Match(L"255"));
        XL_TEST_ASSERT(!r.Match(L"256"));
        XL_TEST_ASSERT(!r.Match(L"260"));
        XL_TEST_ASSERT(!r.Match(L"300"));

        // IPv4 address
        XL_TEST_ASSERT(r.Parse(L"("
                               L"[0-9]|[0-9][0-9]|[01][0-9][0-9]|2[0-4][0-9]|25[0-5]"
                               L").("
                               L"[0-9]|[0-9][0-9]|[01][0-9][0-9]|2[0-4][0-9]|25[0-5]"
                               L").("
                               L"[0-9]|[0-9][0-9]|[01][0-9][0-9]|2[0-4][0-9]|25[0-5]"
                               L").("
                               L"[0-9]|[0-9][0-9]|[01][0-9][0-9]|2[0-4][0-9]|25[0-5]"
                               L")"));
        XL_TEST_ASSERT(r.Match(L"192.168.1.1"));
        XL_TEST_ASSERT(r.Match(L"0.0.0.0"));
        XL_TEST_ASSERT(r.Match(L"255.255.255.255"));
        XL_TEST_ASSERT(!r.Match(L"0.0.0.256"));
    }

    XL_TEST_CASE()
    {
        RegExp r;

        XL_TEST_ASSERT(!r.Parse(L"?"));
        XL_TEST_ASSERT(!r.Parse(L"+"));
        XL_TEST_ASSERT(!r.Parse(L"*"));
        XL_TEST_ASSERT(!r.Parse(L"??"));
        XL_TEST_ASSERT(!r.Parse(L"+?"));
        XL_TEST_ASSERT(!r.Parse(L"*?"));

        XL_TEST_ASSERT(r.Parse(L"a?"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"aa"));
        XL_TEST_ASSERT(r.Parse(L"a??"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"aa"));

        XL_TEST_ASSERT(r.Parse(L"a+"));
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Parse(L"a+?"));
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));

        XL_TEST_ASSERT(r.Parse(L"a*"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Parse(L"a*?"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
    }

    XL_TEST_CASE()
    {
        RegExp r;

        XL_TEST_ASSERT(r.Parse(L"http://([a-zA-Z0-9\\-]+.)+[a-zA-Z]+/"));
        XL_TEST_ASSERT(r.Match(L"http://streamlet.org/"));
        XL_TEST_ASSERT(r.Match(L"http://w-1.streamlet.org/"));
        XL_TEST_ASSERT(r.Match(L"http://w-1.w-2.streamlet.org/"));
        XL_TEST_ASSERT(r.Match(L"http://w-1.w-2.w-3.streamlet.org/"));
        XL_TEST_ASSERT(!r.Match(L"http://org/"));
        XL_TEST_ASSERT(!r.Match(L"http://streamlet.o-g/"));
    }
}
