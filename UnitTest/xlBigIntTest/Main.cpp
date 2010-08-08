//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-08-08
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Objects/xlBigInt.h>
#include "../UnitTestFrame.h"

using namespace xl;

TEST_CASE(ctor)
{
    BigInt a;
    TEST_ASSERT(a == 0);
}

TEST_CASE(ctor_number)
{
    TEST_ASSERT(BigInt((char)1) == 1);
    TEST_ASSERT(BigInt((unsigned char)2) == 2);
    TEST_ASSERT(BigInt((short)3) == 3);
    TEST_ASSERT(BigInt((unsigned short)4) == 4);
    TEST_ASSERT(BigInt((int)5) == 5);
    TEST_ASSERT(BigInt((unsigned int)6) == 6);
    TEST_ASSERT(BigInt((long)7) == 7);
    TEST_ASSERT(BigInt((unsigned long)8) == 8);
    TEST_ASSERT(BigInt((long long)9) == 9);
    TEST_ASSERT(BigInt((unsigned long long)10) == 10);

    TEST_ASSERT(BigInt((char)-1) == -1);
    TEST_ASSERT(BigInt((unsigned char)-2) == 0xfe);
    TEST_ASSERT(BigInt((short)-3) == -3);
    TEST_ASSERT(BigInt((unsigned short)-4) == 0xfffc);
    TEST_ASSERT(BigInt((int)-5) == -5);
    TEST_ASSERT(BigInt((unsigned int)-6) == 0xfffffffa);
    TEST_ASSERT(BigInt((long)-7) == -7);
    TEST_ASSERT(BigInt((unsigned long)-8) == 0xfffffff8);
    TEST_ASSERT(BigInt((long long)-9) == -9);
    TEST_ASSERT(BigInt((unsigned long long)-10) == 0xfffffffffffffff6);
}

TEST_CASE(ctor_buffer)
{
    unsigned char buffer[] =
    {
        0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef,
        0xfe, 0xdc, 0xba, 0x09, 0x87, 0x65, 0x43, 0x21
    };

    TEST_ASSERT(BigInt(buffer, 1) == 0x12);
    TEST_ASSERT(BigInt(buffer, 2) == 0x3412);
    TEST_ASSERT(BigInt(buffer, 3) == 0x563412);
    TEST_ASSERT(BigInt(buffer, 4) == 0x78563412);
    TEST_ASSERT(BigInt(buffer, 5) == 0x9078563412);
    TEST_ASSERT(BigInt(buffer, 6) == 0xab9078563412);
    TEST_ASSERT(BigInt(buffer, 7) == 0xcdab9078563412);
    TEST_ASSERT(BigInt(buffer, 8) == 0xefcdab9078563412);

    BigInt a(buffer, 8);

    BigInt b = 0x1000000000000000;
    b *= 0x10;

    TEST_ASSERT(BigInt(buffer, 9) == a + BigInt(buffer + 8, 1) * b);
    TEST_ASSERT(BigInt(buffer, 10) == a + BigInt(buffer + 8, 2) * b);
    TEST_ASSERT(BigInt(buffer, 11) == a + BigInt(buffer + 8, 3) * b);
    TEST_ASSERT(BigInt(buffer, 12) == a + BigInt(buffer + 8, 4) * b);
    TEST_ASSERT(BigInt(buffer, 13) == a + BigInt(buffer + 8, 5) * b);
    TEST_ASSERT(BigInt(buffer, 14) == a + BigInt(buffer + 8, 6) * b);
    TEST_ASSERT(BigInt(buffer, 15) == a + BigInt(buffer + 8, 7) * b);
    TEST_ASSERT(BigInt(buffer, 16) == a + BigInt(buffer + 8, 8) * b);
}

int main()
{
    return 0;
}
