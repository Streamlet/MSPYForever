//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlRegExpTest.cpp
//    Author:      Streamlet
//    Create Time: 2012-06-02
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/Common/Parser/xlRegExp.h"
#include "../../../Include/xl/AppHelper/xlUnitTest.h"

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        RegExp r;

        XL_TEST_ASSERT(!r.Parse(L""));
        XL_TEST_ASSERT(!r.Parse(L"||"));
        XL_TEST_ASSERT(!r.Parse(L"()"));
        XL_TEST_ASSERT(!r.Parse(L"|"));
        XL_TEST_ASSERT(!r.Parse(L"(|)"));
        XL_TEST_ASSERT(!r.Parse(L"(||)"));
        XL_TEST_ASSERT(!r.Parse(L"()|()"));
        XL_TEST_ASSERT(!r.Parse(L"("));
        XL_TEST_ASSERT(!r.Parse(L")"));
    }

    XL_TEST_CASE()
    {
        RegExp r;
        int nPos = 0;
        
        XL_TEST_ASSERT(r.Parse(L"a"));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"ab"));
        XL_TEST_ASSERT(r.Match(L"ab", &nPos) && nPos == 1);
        XL_TEST_ASSERT(!r.Match(L"b"));

        XL_TEST_ASSERT(r.Parse(L"(a)"));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"ab"));
        XL_TEST_ASSERT(r.Match(L"ab", &nPos) && nPos == 1);
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

        //XL_TEST_ASSERT(r.Parse(L"\\"));
        //XL_TEST_ASSERT(r.Match(L"\\"));

        XL_TEST_ASSERT(r.Parse(L"\\|(\\(|\\))"));
        XL_TEST_ASSERT(r.Match(L"|("));
        XL_TEST_ASSERT(r.Match(L"|)"));
    }

    XL_TEST_CASE()
    {
        RegExp r;
        int nPos = 0;

        // an integer from 0 to 255
        // 3 digit:
        //   0-199: (0|1)(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)
        // 200-249: 2(0|1|2|3|4)(0|1|2|3|4|5|6|7|8|9)
        // 250-255: 25(0|1|2|3|4|5)
        // 2 digit: (0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)
        // 1 digit: (0|1|2|3|4|5|6|7|8|9)
        XL_TEST_ASSERT(r.Parse(L"(0|1)(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"2(0|1|2|3|4)(0|1|2|3|4|5|6|7|8|9)|"
                               L"25(0|1|2|3|4|5)|"
                               L"(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1|2|3|4|5|6|7|8|9)"));
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
        XL_TEST_ASSERT(r.Match(L"256", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"260", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"300", &nPos) && nPos == 2);

        // IPv4 address
        XL_TEST_ASSERT(r.Parse(L"("
                               L"(0|1)(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"2(0|1|2|3|4)(0|1|2|3|4|5|6|7|8|9)|"
                               L"25(0|1|2|3|4|5)|"
                               L"(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1|2|3|4|5|6|7|8|9)"
                               L")\\.("
                               L"(0|1)(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"2(0|1|2|3|4)(0|1|2|3|4|5|6|7|8|9)|"
                               L"25(0|1|2|3|4|5)|"
                               L"(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1|2|3|4|5|6|7|8|9)"
                               L")\\.("
                               L"(0|1)(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"2(0|1|2|3|4)(0|1|2|3|4|5|6|7|8|9)|"
                               L"25(0|1|2|3|4|5)|"
                               L"(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1|2|3|4|5|6|7|8|9)"
                               L")\\.("
                               L"(0|1)(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"2(0|1|2|3|4)(0|1|2|3|4|5|6|7|8|9)|"
                               L"25(0|1|2|3|4|5)|"
                               L"(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)|"
                               L"(0|1|2|3|4|5|6|7|8|9)"
                               L")"));
        XL_TEST_ASSERT(r.Match(L"192.168.1.1"));
        XL_TEST_ASSERT(r.Match(L"0.0.0.0"));
        XL_TEST_ASSERT(r.Match(L"255.255.255.255"));
        XL_TEST_ASSERT(!r.Match(L"0.0.0.256"));
        XL_TEST_ASSERT(r.Match(L"0.0.0.256", &nPos) && nPos == 8);
    }

    XL_TEST_CASE()
    {
        RegExp r;
        XL_TEST_ASSERT(!r.Parse(L"[]"));
        XL_TEST_ASSERT(!r.Parse(L"[^]"));
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
        int nPos = 0;

        // an integer from 0 to 255
        // 3 digit:
        //   0-199: [01][0-9][0-9]
        // 200-249: 2[0-4][0-9]
        // 250-255: 25[0-5]
        // 2 digit: [0-9][0-9]
        // 1 digit: [0-9]
        XL_TEST_ASSERT(r.Parse(L"[01][0-9][0-9]|2[0-4][0-9]|25[0-5]|[0-9][0-9]|[0-9]"));
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
        XL_TEST_ASSERT(r.Match(L"256", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"260", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"300", &nPos) && nPos == 2);

        // IPv4 address
        XL_TEST_ASSERT(r.Parse(L"("
                               L"[01][0-9][0-9]|2[0-4][0-9]|25[0-5]|[0-9][0-9]|[0-9]"
                               L")\\.("
                               L"[01][0-9][0-9]|2[0-4][0-9]|25[0-5]|[0-9][0-9]|[0-9]"
                               L")\\.("
                               L"[01][0-9][0-9]|2[0-4][0-9]|25[0-5]|[0-9][0-9]|[0-9]"
                               L")\\.("
                               L"[01][0-9][0-9]|2[0-4][0-9]|25[0-5]|[0-9][0-9]|[0-9]"
                               L")"));
        XL_TEST_ASSERT(r.Match(L"192.168.1.1"));
        XL_TEST_ASSERT(r.Match(L"0.0.0.0"));
        XL_TEST_ASSERT(r.Match(L"255.255.255.255"));
        XL_TEST_ASSERT(!r.Match(L"0.0.0.256"));
        XL_TEST_ASSERT(r.Match(L"0.0.0.256", &nPos) && nPos == 8);
    }

    XL_TEST_CASE()
    {
        RegExp r;
        int nPos = 0;

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
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 1);

        XL_TEST_ASSERT(r.Parse(L"a??"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"aa"));
        XL_TEST_ASSERT(r.Parse(L"a??"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 0);

        XL_TEST_ASSERT(r.Parse(L"a+"));
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
        XL_TEST_ASSERT(!r.Match(L"", &nPos));
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 3);

        XL_TEST_ASSERT(r.Parse(L"a+?"));
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
        XL_TEST_ASSERT(!r.Match(L"", &nPos));
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 1);

        XL_TEST_ASSERT(r.Parse(L"a*"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 3);

        XL_TEST_ASSERT(r.Parse(L"a*?"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 0);

        XL_TEST_ASSERT(r.Parse(L"w1+"));
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(!r.Match(L"w"));
        XL_TEST_ASSERT(r.Match(L"w1"));
        XL_TEST_ASSERT(r.Match(L"w11"));
        XL_TEST_ASSERT(r.Match(L"w111"));
        XL_TEST_ASSERT(r.Match(L"w1111"));
        XL_TEST_ASSERT(r.Match(L"w11111"));
        XL_TEST_ASSERT(!r.Match(L"", &nPos));
        XL_TEST_ASSERT(!r.Match(L"w", &nPos));
        XL_TEST_ASSERT(r.Match(L"w1", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"w11", &nPos) && nPos == 3);
        XL_TEST_ASSERT(r.Match(L"w111", &nPos) && nPos == 4);
        XL_TEST_ASSERT(r.Match(L"w1111", &nPos) && nPos == 5);
        XL_TEST_ASSERT(r.Match(L"w11111", &nPos) && nPos == 6);

        XL_TEST_ASSERT(r.Parse(L"w1+?"));
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(!r.Match(L"w"));
        XL_TEST_ASSERT(r.Match(L"w1"));
        XL_TEST_ASSERT(r.Match(L"w11"));
        XL_TEST_ASSERT(r.Match(L"w111"));
        XL_TEST_ASSERT(r.Match(L"w1111"));
        XL_TEST_ASSERT(r.Match(L"w11111"));
        XL_TEST_ASSERT(!r.Match(L"", &nPos));
        XL_TEST_ASSERT(!r.Match(L"w", &nPos));
        XL_TEST_ASSERT(r.Match(L"w1", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"w11", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"w111", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"w1111", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"w11111", &nPos) && nPos == 2);
    }

    XL_TEST_CASE()
    {
        RegExp r;
        int nPos = 0;

        XL_TEST_ASSERT(!r.Parse(L"{0,1}"));
        XL_TEST_ASSERT(!r.Parse(L"{,1}"));
        XL_TEST_ASSERT(!r.Parse(L"{1,}"));
        XL_TEST_ASSERT(!r.Parse(L"{0,}"));

        XL_TEST_ASSERT(r.Parse(L"a{0,1}"));  // Equal to a?
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 1);


        XL_TEST_ASSERT(r.Parse(L"a{,1}"));   // Equal to a?
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 1);

        XL_TEST_ASSERT(r.Parse(L"a{0,1}?"));  // Equal to a??
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"aa"));
        XL_TEST_ASSERT(r.Parse(L"a??"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 0);

        XL_TEST_ASSERT(r.Parse(L"a{,1}?"));   // Equal to a??
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"aa"));
        XL_TEST_ASSERT(r.Parse(L"a??"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 0);



        XL_TEST_ASSERT(r.Parse(L"a{1,}"));   // Equal to a+
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
        XL_TEST_ASSERT(!r.Match(L"", &nPos));
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 3);

        XL_TEST_ASSERT(r.Parse(L"a{1,}?"));   // Equal to a+?
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
        XL_TEST_ASSERT(!r.Match(L"", &nPos));
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 1);

        
        XL_TEST_ASSERT(r.Parse(L"a{0,}"));   // Equal to a*
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 3);

        XL_TEST_ASSERT(r.Parse(L"a{,}"));   // Equal to a*
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 3);

        XL_TEST_ASSERT(r.Parse(L"a{0,}?"));   // Equal to a*?
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 0);

        XL_TEST_ASSERT(r.Parse(L"a{,}?"));   // Equal to a*?
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 0);
    }

    XL_TEST_CASE()
    {
        RegExp r;
        int nPos = 0;

        XL_TEST_ASSERT(r.Parse(L"a{1,2}"));
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(!r.Match(L"", &nPos));
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 2);

        XL_TEST_ASSERT(r.Parse(L"a{1,2}?"));
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(!r.Match(L"", &nPos));
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 1);

        XL_TEST_ASSERT(r.Parse(L"a{0,2}"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 2);

        XL_TEST_ASSERT(r.Parse(L"a{0,2}?"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 0);

        XL_TEST_ASSERT(r.Parse(L"a{,2}"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 1);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 2);

        XL_TEST_ASSERT(r.Parse(L"a{,2}?"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 0);

        XL_TEST_ASSERT(r.Parse(L"a{2,}"));
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
        XL_TEST_ASSERT(!r.Match(L"", &nPos));
        XL_TEST_ASSERT(!r.Match(L"a", &nPos));
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 3);

        XL_TEST_ASSERT(r.Parse(L"a{2,}?"));
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(r.Match(L"aaa"));
        XL_TEST_ASSERT(!r.Match(L"", &nPos));
        XL_TEST_ASSERT(!r.Match(L"a", &nPos));
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 2);

        XL_TEST_ASSERT(r.Parse(L"a{2,2}"));
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(!r.Match(L"", &nPos));
        XL_TEST_ASSERT(!r.Match(L"a", &nPos));
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 2);

        XL_TEST_ASSERT(r.Parse(L"a{2,2}?"));
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(!r.Match(L"", &nPos));
        XL_TEST_ASSERT(!r.Match(L"a", &nPos));
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 2);

        XL_TEST_ASSERT(r.Parse(L"a{2}"));
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(!r.Match(L"", &nPos));
        XL_TEST_ASSERT(!r.Match(L"a", &nPos));
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 2);

        XL_TEST_ASSERT(r.Parse(L"a{2}?"));
        XL_TEST_ASSERT(!r.Match(L""));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(!r.Match(L"", &nPos));
        XL_TEST_ASSERT(!r.Match(L"a", &nPos));
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 2);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 2);

        XL_TEST_ASSERT(r.Parse(L"a{0,0}"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 0);

        XL_TEST_ASSERT(r.Parse(L"a{0,0}?"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 0);

        XL_TEST_ASSERT(r.Parse(L"a{0}"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 0);

        XL_TEST_ASSERT(r.Parse(L"a{0}?"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 0);

        XL_TEST_ASSERT(r.Parse(L"a{}"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 0);

        XL_TEST_ASSERT(r.Parse(L"a{}?"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"aa"));
        XL_TEST_ASSERT(!r.Match(L"aaa"));
        XL_TEST_ASSERT(r.Match(L"", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"a", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aa", &nPos) && nPos == 0);
        XL_TEST_ASSERT(r.Match(L"aaa", &nPos) && nPos == 0);

        // IPv4 address
        XL_TEST_ASSERT(r.Parse(L"(([01][0-9][0-9]|2[0-4][0-9]|25[0-5]|[0-9][0-9]|[0-9])\\.){3}"
                               L"([01][0-9][0-9]|2[0-4][0-9]|25[0-5]|[0-9][0-9]|[0-9])"));
        XL_TEST_ASSERT(r.Match(L"192.168.1.1"));
        XL_TEST_ASSERT(r.Match(L"0.0.0.0"));
        XL_TEST_ASSERT(r.Match(L"255.255.255.255"));
        XL_TEST_ASSERT(!r.Match(L"0.0.0.256"));
        XL_TEST_ASSERT(r.Match(L"0.0.0.256", &nPos) && nPos == 8);
    }

    XL_TEST_CASE()
    {
        RegExp r;

        XL_TEST_ASSERT(r.Parse(L"."));
        XL_TEST_ASSERT(!r.Match(L"\n"));
        XL_TEST_ASSERT(r.Match(L"."));
        XL_TEST_ASSERT(r.Match(L"\r"));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"A"));
        XL_TEST_ASSERT(r.Match(L"0"));

        XL_TEST_ASSERT(r.Parse(L".*"));
        XL_TEST_ASSERT(r.Match(L""));
        XL_TEST_ASSERT(r.Match(L"1234567890"));
        XL_TEST_ASSERT(r.Match(L"abcdefg"));
        XL_TEST_ASSERT(!r.Match(L"\n"));
        XL_TEST_ASSERT(!r.Match(L"1234567890\n"));
        XL_TEST_ASSERT(!r.Match(L"abcdefg\n"));

        XL_TEST_ASSERT(r.Parse(L"[.\n]"));
        XL_TEST_ASSERT(r.Match(L"\n"));
        XL_TEST_ASSERT(r.Match(L"."));
        XL_TEST_ASSERT(r.Match(L"\r"));
        XL_TEST_ASSERT(r.Match(L"a"));
        XL_TEST_ASSERT(r.Match(L"A"));
        XL_TEST_ASSERT(r.Match(L"0"));

        XL_TEST_ASSERT(r.Parse(L"[^.\n]"));
        XL_TEST_ASSERT(!r.Match(L"\n"));
        XL_TEST_ASSERT(!r.Match(L"."));
        XL_TEST_ASSERT(!r.Match(L"\r"));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"A"));
        XL_TEST_ASSERT(!r.Match(L"0"));

        XL_TEST_ASSERT(r.Parse(L"[^.]"));
        XL_TEST_ASSERT(r.Match(L"\n"));
        XL_TEST_ASSERT(!r.Match(L"."));
        XL_TEST_ASSERT(!r.Match(L"\r"));
        XL_TEST_ASSERT(!r.Match(L"a"));
        XL_TEST_ASSERT(!r.Match(L"A"));
        XL_TEST_ASSERT(!r.Match(L"0"));
    }

    XL_TEST_CASE()
    {
        RegExp r;

        // \d \D \f \n \r \s \S \t \v \w\ W

        XL_TEST_ASSERT(r.Parse(L"\\d*"));
        XL_TEST_ASSERT(r.Match(L"0123456789"));
        XL_TEST_ASSERT(!r.Match(L"\x29"));
        XL_TEST_ASSERT(!r.Match(L"\x3a"));
        XL_TEST_ASSERT(r.Parse(L"[\\d]*"));
        XL_TEST_ASSERT(r.Match(L"0123456789"));
        XL_TEST_ASSERT(!r.Match(L"\x29"));
        XL_TEST_ASSERT(!r.Match(L"\x3a"));
        XL_TEST_ASSERT(r.Parse(L"[^\\D]*"));
        XL_TEST_ASSERT(r.Match(L"0123456789"));
        XL_TEST_ASSERT(!r.Match(L"\x29"));
        XL_TEST_ASSERT(!r.Match(L"\x3a"));

        XL_TEST_ASSERT(r.Parse(L"\\t"));
        XL_TEST_ASSERT(r.Match(L"\x09"));
        XL_TEST_ASSERT(!r.Match(L"\x08"));
        XL_TEST_ASSERT(!r.Match(L"\x0a"));
        XL_TEST_ASSERT(r.Parse(L"\\n"));
        XL_TEST_ASSERT(r.Match(L"\x0a"));
        XL_TEST_ASSERT(!r.Match(L"\x09"));
        XL_TEST_ASSERT(!r.Match(L"\x0b"));
        XL_TEST_ASSERT(r.Parse(L"\\v"));
        XL_TEST_ASSERT(r.Match(L"\x0b"));
        XL_TEST_ASSERT(!r.Match(L"\x0a"));
        XL_TEST_ASSERT(!r.Match(L"\x0c"));
        XL_TEST_ASSERT(r.Parse(L"\\f"));
        XL_TEST_ASSERT(r.Match(L"\x0c"));
        XL_TEST_ASSERT(!r.Match(L"\x0b"));
        XL_TEST_ASSERT(!r.Match(L"\x0d"));
        XL_TEST_ASSERT(r.Parse(L"\\r"));
        XL_TEST_ASSERT(r.Match(L"\x0d"));
        XL_TEST_ASSERT(!r.Match(L"\x0c"));
        XL_TEST_ASSERT(!r.Match(L"\x0e"));

        XL_TEST_ASSERT(r.Parse(L"\\s*"));
        XL_TEST_ASSERT(r.Match(L"\x09\x0a\x0b\x0c\x0d"));
        XL_TEST_ASSERT(!r.Match(L"\x08"));
        XL_TEST_ASSERT(!r.Match(L"\x0e"));
        XL_TEST_ASSERT(r.Parse(L"[^\\S]*"));
        XL_TEST_ASSERT(r.Match(L"\x09\x0a\x0b\x0c\x0d"));
        XL_TEST_ASSERT(!r.Match(L"\x08"));
        XL_TEST_ASSERT(!r.Match(L"\x0e"));
        XL_TEST_ASSERT(r.Parse(L"\\w*"));
        XL_TEST_ASSERT(r.Match(L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"));
        XL_TEST_ASSERT(!r.Match(L"\x60"));
        XL_TEST_ASSERT(!r.Match(L"\x7b"));
        XL_TEST_ASSERT(!r.Match(L"\x40"));
        XL_TEST_ASSERT(!r.Match(L"\x5b"));
        XL_TEST_ASSERT(!r.Match(L"\x29"));
        XL_TEST_ASSERT(!r.Match(L"\x3a"));
        XL_TEST_ASSERT(!r.Match(L"\x5e"));
        XL_TEST_ASSERT(!r.Match(L"\x60"));
        XL_TEST_ASSERT(r.Parse(L"[^\\W]*"));
        XL_TEST_ASSERT(r.Match(L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"));
        XL_TEST_ASSERT(!r.Match(L"\x60"));
        XL_TEST_ASSERT(!r.Match(L"\x7b"));
        XL_TEST_ASSERT(!r.Match(L"\x40"));
        XL_TEST_ASSERT(!r.Match(L"\x5b"));
        XL_TEST_ASSERT(!r.Match(L"\x29"));
        XL_TEST_ASSERT(!r.Match(L"\x3a"));
        XL_TEST_ASSERT(!r.Match(L"\x5e"));
        XL_TEST_ASSERT(!r.Match(L"\x60"));
    }

    XL_TEST_CASE()
    {
        RegExp r;

        // \xHH \uHHHH

        XL_TEST_ASSERT(!r.Parse(L"\\x"));
        XL_TEST_ASSERT(!r.Parse(L"\\x4"));
        XL_TEST_ASSERT(r.Parse(L"\\x41"));
        XL_TEST_ASSERT(r.Parse(L"\\x413"));
        XL_TEST_ASSERT(r.Match(L"A3"));

        XL_TEST_ASSERT(r.Parse(L"\\x41\\x42\\x43\\x44\\x45\\x46\\x47"));
        XL_TEST_ASSERT(r.Match(L"ABCDEFG"));

        XL_TEST_ASSERT(r.Parse(L"[\\x41\\x42]"));
        XL_TEST_ASSERT(r.Match(L"A"));
        XL_TEST_ASSERT(r.Match(L"B"));
        XL_TEST_ASSERT(!r.Match(L"C"));

        XL_TEST_ASSERT(!r.Parse(L"\\u"));
        XL_TEST_ASSERT(!r.Parse(L"\\u5"));
        XL_TEST_ASSERT(!r.Parse(L"\\u59"));
        XL_TEST_ASSERT(!r.Parse(L"\\u597"));
        XL_TEST_ASSERT(r.Parse(L"\\u597d"));
        XL_TEST_ASSERT(r.Parse(L"\\u597de"));
        XL_TEST_ASSERT(r.Match(L"ºÃe"));

        XL_TEST_ASSERT(r.Parse(L"\\u4f60\\u597d"));
        XL_TEST_ASSERT(r.Match(L"ÄãºÃ"));

        XL_TEST_ASSERT(r.Parse(L"[\\u4f60\\u597d]"));
        XL_TEST_ASSERT(r.Match(L"Äã"));
        XL_TEST_ASSERT(r.Match(L"ºÃ"));
        XL_TEST_ASSERT(!r.Match(L"Éµ"));
    }

    XL_TEST_CASE()
    {
        RegExp r;

        XL_TEST_ASSERT(r.Parse(L"(a)"));
        XL_TEST_ASSERT(r.Parse(L"(?:a)"));
        XL_TEST_ASSERT(r.Parse(L"(?=a)"));
        XL_TEST_ASSERT(r.Parse(L"(?!a)"));
        XL_TEST_ASSERT(r.Parse(L"(?<=a)"));
        XL_TEST_ASSERT(r.Parse(L"(?<!a)"));
        XL_TEST_ASSERT(r.Parse(L"(?<a>a)"));
    }

    XL_TEST_CASE()
    {
        RegExp r;

        XL_TEST_ASSERT(r.Parse(L"http://([a-zA-Z0-9\\-]+\\.)+[a-zA-Z]+/"));
        XL_TEST_ASSERT(r.Match(L"http://streamlet.org/"));
        XL_TEST_ASSERT(r.Match(L"http://w-1.streamlet.org/"));
        XL_TEST_ASSERT(r.Match(L"http://w-1.w-2.streamlet.org/"));
        XL_TEST_ASSERT(r.Match(L"http://w-1.w-2.w-3.streamlet.org/"));
        XL_TEST_ASSERT(!r.Match(L"http://org/"));
        XL_TEST_ASSERT(!r.Match(L"http://streamlet.o-g/"));
    }
}
