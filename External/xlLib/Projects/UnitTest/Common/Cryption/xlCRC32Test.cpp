//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlCRC32Test.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/AppHelper/xlUnitTest.h"
#include "../../../Include/xl/Common/Cryption/xlCRC32.h"
#include "../../../Include/xl/Common/String/xlString.h"

namespace
{
    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(xl::CRC32::Calculate(nullptr, 0) == 0);
        XL_TEST_ASSERT(xl::CRC32::Calculate("a", 1) == 0xe8b7be43);
        XL_TEST_ASSERT(xl::CRC32::Calculate("ab", 2) == 0x9e83486d);
        XL_TEST_ASSERT(xl::CRC32::Calculate("abc", 3) == 0x352441c2);
        XL_TEST_ASSERT(xl::CRC32::Calculate("abcd", 4) == 0xed82cd11);
        XL_TEST_ASSERT(xl::CRC32::Calculate("abcde", 5) == 0x8587d865);
        XL_TEST_ASSERT(xl::CRC32::Calculate("abcdef", 6) == 0x4b8e39ef);
        XL_TEST_ASSERT(xl::CRC32::Calculate("abcdefg", 7) == 0x312a6aa6);
    }
}
