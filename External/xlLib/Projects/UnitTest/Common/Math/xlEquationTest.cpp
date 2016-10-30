//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlEquationTest.cpp
//    Author:      Streamlet
//    Create Time: 2015-08-25
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------


#include "../../../Include/xl/Common/Math/xlEquation.h"
#include "../../../Include/xl/AppHelper/xlUnitTest.h"

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        int c[1][2] =
        {
            { 1, 1 },   // x = 1
        };

        int s[1] = {};
        bool r = Equation::LinearSystem::Solve(c, s);
        XL_TEST_ASSERT(r);
        XL_TEST_ASSERT(s[0] == 1);  // x == 1
    }

    XL_TEST_CASE()
    {
        int c[1][2] =
        {
            { 0, 1 },   // 0x = 1
        };

        int s[1] = { 0x19851204 };
        bool r = Equation::LinearSystem::Solve(c, s);
        XL_TEST_ASSERT(!r);
        XL_TEST_ASSERT(s[0] == 0x19851204);
    }

    XL_TEST_CASE()
    {
        int c[2][3] =
        {
            { 1,  1, 3 },   // x + y = 3
            { 1, -1, 1 },   // x - y = 1
        };

        int s[2] = {};
        bool r = Equation::LinearSystem::Solve(c, s);
        XL_TEST_ASSERT(r);
        XL_TEST_ASSERT(s[0] == 2);  // x == 2
        XL_TEST_ASSERT(s[1] == 1);  // y == 1
    }

    XL_TEST_CASE()
    {
        int c[2][3] =
        {
            { 0, 1, 1 },    //     y = 1
            { 1, 1, 3 },    // x + y = 3
        };

        int s[2] = { 0x19851204, 0x19851205 };
        bool r = Equation::LinearSystem::Solve(c, s);
        XL_TEST_ASSERT(r);
        XL_TEST_ASSERT(s[0] == 2);  // x == 2
        XL_TEST_ASSERT(s[1] == 1);  // y == 1
    }

    XL_TEST_CASE()
    {
        int c[2][3] =
        {
            { 1, 1, 3 },    //  x +  y = 3
            { 2, 2, 6 },    // 2x + 2y = 6
        };

        int s[2] = { 0x19851204, 0x19851205 };
        bool r = Equation::LinearSystem::Solve(c, s);
        XL_TEST_ASSERT(!r);
        XL_TEST_ASSERT(s[0] == 0x19851204);
        XL_TEST_ASSERT(s[1] == 0x19851205);
    }

    XL_TEST_CASE()
    {
        int c[3][4] =
        {
            { 1,  2, 3, 29 },   // x + 2y + 3z = 29
            { 1, -1, 1,  8 },   // x -  y +  z = 8
            { 1, -3, 9, 22 },   // x - 3y + 9z = 22
        };

        int s[3] = {};
        bool r = Equation::LinearSystem::Solve(c, s);
        XL_TEST_ASSERT(r);
        XL_TEST_ASSERT(s[0] == 10); // x == 10
        XL_TEST_ASSERT(s[1] == 5);  // y == 5
        XL_TEST_ASSERT(s[2] == 3);  // z == 3
    }

    XL_TEST_CASE()
    {
        int c[3][4] =
        {
            { 0, 0, 3, 27 },    //          3z = 27
            { 0, 3, 2, 21 },    //     3y + 2z = 21
            { 1, 2, 9, 99 },    // x + 2y + 9z = 99
        };

        int s[3] = {};
        bool r = Equation::LinearSystem::Solve(c, s);
        XL_TEST_ASSERT(r);
        XL_TEST_ASSERT(s[0] == 16); // x == 16
        XL_TEST_ASSERT(s[1] == 1);  // y == 1
        XL_TEST_ASSERT(s[2] == 9);  // z == 9
    }

    XL_TEST_CASE()
    {
        int c[3][4] =
        {
            { 1,  2,  3, 29  }, // x + 2y + 3z = 29
            { 1, -1,  1,  8  }, // x -  y +  z = 8
            { 1, -7, -3, -34 }, // x - 7y - 3z = -34
        };

        int s[3] = { 0x19851204, 0x19851205, 0x19851206 };
        bool r = Equation::LinearSystem::Solve(c, s);
        XL_TEST_ASSERT(!r);
        XL_TEST_ASSERT(s[0] == 0x19851204);
        XL_TEST_ASSERT(s[1] == 0x19851205);
        XL_TEST_ASSERT(s[2] == 0x19851206);
    }
}
