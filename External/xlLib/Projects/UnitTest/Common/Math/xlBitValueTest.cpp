//------------------------------------------------------------------------------
//
//    Copyright (C) YourName. All rights reserved.
//
//    File Name:   xlBitValueTest.cpp
//    Author:      YourName
//    Create Time: 2016-02-26
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/Common/Math/xlBitValue.h"
#include "../../../Include/xl/AppHelper/xlUnitTest.h"

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        XL_ASSERT(BitValue::Eval(0x12345678,  0, 32) == 0x12345678);

        XL_ASSERT(BitValue::Eval(0x12345678,  1, 31) == 0x12345678);
        XL_ASSERT(BitValue::Eval(0x12345678,  2, 30) == 0x12345678);
        XL_ASSERT(BitValue::Eval(0x12345678,  3, 29) == 0x12345678);
        XL_ASSERT(BitValue::Eval(0x12345678,  4, 28) == 0x02345678);
        XL_ASSERT(BitValue::Eval(0x12345678,  5, 27) == 0x02345678);
        XL_ASSERT(BitValue::Eval(0x12345678,  6, 26) == 0x02345678);
        XL_ASSERT(BitValue::Eval(0x12345678,  7, 25) == 0x00345678);
        XL_ASSERT(BitValue::Eval(0x12345678,  8, 24) == 0x00345678);
        XL_ASSERT(BitValue::Eval(0x12345678,  9, 23) == 0x00345678);
        XL_ASSERT(BitValue::Eval(0x12345678, 10, 22) == 0x00345678);
        XL_ASSERT(BitValue::Eval(0x12345678, 11, 21) == 0x00145678);
        XL_ASSERT(BitValue::Eval(0x12345678, 12, 20) == 0x00045678);
        XL_ASSERT(BitValue::Eval(0x12345678, 13, 19) == 0x00045678);
        XL_ASSERT(BitValue::Eval(0x12345678, 14, 18) == 0x00005678);
        XL_ASSERT(BitValue::Eval(0x12345678, 15, 17) == 0x00005678);
        XL_ASSERT(BitValue::Eval(0x12345678, 16, 16) == 0x00005678);
        XL_ASSERT(BitValue::Eval(0x12345678, 17, 15) == 0x00005678);
        XL_ASSERT(BitValue::Eval(0x12345678, 18, 14) == 0x00001678);
        XL_ASSERT(BitValue::Eval(0x12345678, 19, 13) == 0x00001678);
        XL_ASSERT(BitValue::Eval(0x12345678, 20, 12) == 0x00000678);
        XL_ASSERT(BitValue::Eval(0x12345678, 21, 11) == 0x00000678);
        XL_ASSERT(BitValue::Eval(0x12345678, 22, 10) == 0x00000278);
        XL_ASSERT(BitValue::Eval(0x12345678, 23,  9) == 0x00000078);
        XL_ASSERT(BitValue::Eval(0x12345678, 24,  8) == 0x00000078);
        XL_ASSERT(BitValue::Eval(0x12345678, 25,  7) == 0x00000078);
        XL_ASSERT(BitValue::Eval(0x12345678, 26,  6) == 0x00000038);
        XL_ASSERT(BitValue::Eval(0x12345678, 27,  5) == 0x00000018);
        XL_ASSERT(BitValue::Eval(0x12345678, 28,  4) == 0x00000008);
        XL_ASSERT(BitValue::Eval(0x12345678, 29,  3) == 0x00000000);
        XL_ASSERT(BitValue::Eval(0x12345678, 30,  2) == 0x00000000);
        XL_ASSERT(BitValue::Eval(0x12345678, 31,  1) == 0x00000000);

        XL_ASSERT(BitValue::Eval(0x12345678, 0, 31) == 0x91A2B3C);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 30) == 0x48D159E);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 29) == 0x2468ACF);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 28) == 0x1234567);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 27) == 0x91A2B3);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 26) == 0x48D159);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 25) == 0x2468AC);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 24) == 0x123456);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 23) == 0x91A2B);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 22) == 0x48D15);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 21) == 0x2468A);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 20) == 0x12345);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 19) == 0x91A2);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 18) == 0x48D1);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 17) == 0x2468);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 16) == 0x1234);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 15) == 0x91A);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 14) == 0x48D);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 13) == 0x246);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 12) == 0x123);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 11) == 0x91);
        XL_ASSERT(BitValue::Eval(0x12345678, 0, 10) == 0x48);
        XL_ASSERT(BitValue::Eval(0x12345678, 0,  9) == 0x24);
        XL_ASSERT(BitValue::Eval(0x12345678, 0,  8) == 0x12);
        XL_ASSERT(BitValue::Eval(0x12345678, 0,  7) == 0x9);
        XL_ASSERT(BitValue::Eval(0x12345678, 0,  6) == 0x4);
        XL_ASSERT(BitValue::Eval(0x12345678, 0,  5) == 0x2);
        XL_ASSERT(BitValue::Eval(0x12345678, 0,  4) == 0x1);
        XL_ASSERT(BitValue::Eval(0x12345678, 0,  3) == 0);
        XL_ASSERT(BitValue::Eval(0x12345678, 0,  2) == 0);
        XL_ASSERT(BitValue::Eval(0x12345678, 0,  1) == 0);
    }

    XL_TEST_CASE()
    {
        XL_ASSERT(BitValue::Eval(0x87654321, 0, 32) == 0x87654321);
        XL_ASSERT(BitValue::Eval(0x87654321, 1, 31) == 0x07654321);
        XL_ASSERT(BitValue::Eval(0x87654321, 0, 31) == 0x43B2A190);
    }

    XL_TEST_CASE()
    {
        int x[] = { (int)0x12345678, (int)0x90abcdef };
        XL_ASSERT(BitValue::Eval(x,  0, 32) == 0x12345678);
        XL_ASSERT(BitValue::Eval(x,  1, 32) == 0x2468ACF1);
        XL_ASSERT(BitValue::Eval(x,  2, 32) == 0x48D159E2);
        XL_ASSERT(BitValue::Eval(x,  3, 32) == 0x91A2B3C4);
        XL_ASSERT(BitValue::Eval(x,  4, 32) == 0x23456789);
        XL_ASSERT(BitValue::Eval(x,  5, 32) == 0x468ACF12);
        XL_ASSERT(BitValue::Eval(x,  6, 32) == 0x8D159E24);
        XL_ASSERT(BitValue::Eval(x,  7, 32) == 0x1A2B3C48);
        XL_ASSERT(BitValue::Eval(x,  8, 32) == 0x34567890);
        XL_ASSERT(BitValue::Eval(x,  9, 32) == 0x68ACF121);
        XL_ASSERT(BitValue::Eval(x, 10, 32) == 0xD159E242);
        XL_ASSERT(BitValue::Eval(x, 11, 32) == 0xA2B3C485);
        XL_ASSERT(BitValue::Eval(x, 12, 32) == 0x4567890A);
        XL_ASSERT(BitValue::Eval(x, 13, 32) == 0x8ACF1215);
        XL_ASSERT(BitValue::Eval(x, 14, 32) == 0x159E242A);
        XL_ASSERT(BitValue::Eval(x, 15, 32) == 0x2B3C4855);
        XL_ASSERT(BitValue::Eval(x, 16, 32) == 0x567890AB);
        XL_ASSERT(BitValue::Eval(x, 17, 32) == 0xACF12157);
        XL_ASSERT(BitValue::Eval(x, 18, 32) == 0x59E242AF);
        XL_ASSERT(BitValue::Eval(x, 19, 32) == 0xB3C4855E);
        XL_ASSERT(BitValue::Eval(x, 20, 32) == 0x67890ABC);
        XL_ASSERT(BitValue::Eval(x, 21, 32) == 0xCF121579);
        XL_ASSERT(BitValue::Eval(x, 22, 32) == 0x9E242AF3);
        XL_ASSERT(BitValue::Eval(x, 23, 32) == 0x3C4855E6);
        XL_ASSERT(BitValue::Eval(x, 24, 32) == 0x7890ABCD);
        XL_ASSERT(BitValue::Eval(x, 25, 32) == 0xF121579B);
        XL_ASSERT(BitValue::Eval(x, 26, 32) == 0xE242AF37);
        XL_ASSERT(BitValue::Eval(x, 27, 32) == 0xC4855E6F);
        XL_ASSERT(BitValue::Eval(x, 28, 32) == 0x890ABCDE);
        XL_ASSERT(BitValue::Eval(x, 29, 32) == 0x121579BD);
        XL_ASSERT(BitValue::Eval(x, 30, 32) == 0x242AF37B);
        XL_ASSERT(BitValue::Eval(x, 31, 32) == 0x4855E6F7);
    }
}
