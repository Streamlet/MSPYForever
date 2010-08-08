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

int main()
{
    return 0;
}
