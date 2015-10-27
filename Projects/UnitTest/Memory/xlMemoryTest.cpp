//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMemoryTest.cpp
//    Author:      Streamlet
//    Create Time: 2015-10-26
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/AppHelper/xlUnitTest.h"
#include "../../../Include/xl/xlDef.h"
#include "../../../Include/xl/Common/Memory/xlMemory.h"

namespace
{
    using namespace xl;

    // Memory::Set By KJJ
    XL_TEST_CASE()
    {
        unsigned char *pChar = new unsigned char[17] + 1;
        Memory::Set(pChar, 16, 0);
        for (int i = 0; i < 16; ++i)
        {
            XL_TEST_ASSERT(pChar[i] == 0);
        }

        Memory::Set(pChar, 7, 0x12345678);
        XL_TEST_ASSERT(pChar[0] == 0x78);
        XL_TEST_ASSERT(pChar[1] == 0x56);
        XL_TEST_ASSERT(pChar[2] == 0x34);
        XL_TEST_ASSERT(pChar[3] == 0x12);
        XL_TEST_ASSERT(pChar[4] == 0x78);
        XL_TEST_ASSERT(pChar[5] == 0x56);
        XL_TEST_ASSERT(pChar[6] == 0x34);
        XL_TEST_ASSERT(pChar[7] == 0);

        Memory::Set<unsigned short>(pChar, 5, 0x90ab);
        XL_TEST_ASSERT(pChar[0] == 0xab);
        XL_TEST_ASSERT(pChar[1] == 0x90);
        XL_TEST_ASSERT(pChar[2] == 0xab);
        XL_TEST_ASSERT(pChar[3] == 0x90);
        XL_TEST_ASSERT(pChar[4] == 0xab);
        XL_TEST_ASSERT(pChar[5] == 0x56);
        XL_TEST_ASSERT(pChar[6] == 0x34);
        XL_TEST_ASSERT(pChar[7] == 0);

        Memory::Set<unsigned long long>(pChar, 15, 0x1234567890abcdefull);
        XL_TEST_ASSERT(pChar[0] == 0xef);
        XL_TEST_ASSERT(pChar[1] == 0xcd);
        XL_TEST_ASSERT(pChar[2] == 0xab);
        XL_TEST_ASSERT(pChar[3] == 0x90);
        XL_TEST_ASSERT(pChar[4] == 0x78);
        XL_TEST_ASSERT(pChar[5] == 0x56);
        XL_TEST_ASSERT(pChar[6] == 0x34);
        XL_TEST_ASSERT(pChar[7] == 0x12);
        XL_TEST_ASSERT(pChar[8] == 0xef);
        XL_TEST_ASSERT(pChar[9] == 0xcd);
        XL_TEST_ASSERT(pChar[10] == 0xab);
        XL_TEST_ASSERT(pChar[11] == 0x90);
        XL_TEST_ASSERT(pChar[12] == 0x78);
        XL_TEST_ASSERT(pChar[13] == 0x56);
        XL_TEST_ASSERT(pChar[14] == 0x34);
        XL_TEST_ASSERT(pChar[15] == 0);
    }

    // Memory::Copy By KJJ
    XL_TEST_CASE()
    {
        unsigned char *pChar1 = new unsigned char[19] + 3;
        unsigned char *pChar2 = new unsigned char[19] + 3;

        Memory::Set(pChar1, 16, 0x1234567890abcdefull);
        XL_TEST_ASSERT(pChar1[0] == 0xef);
        XL_TEST_ASSERT(pChar1[1] == 0xcd);
        XL_TEST_ASSERT(pChar1[2] == 0xab);
        XL_TEST_ASSERT(pChar1[3] == 0x90);
        XL_TEST_ASSERT(pChar1[4] == 0x78);
        XL_TEST_ASSERT(pChar1[5] == 0x56);
        XL_TEST_ASSERT(pChar1[6] == 0x34);
        XL_TEST_ASSERT(pChar1[7] == 0x12);
        XL_TEST_ASSERT(pChar1[8] == 0xef);
        XL_TEST_ASSERT(pChar1[9] == 0xcd);
        XL_TEST_ASSERT(pChar1[10] == 0xab);
        XL_TEST_ASSERT(pChar1[11] == 0x90);
        XL_TEST_ASSERT(pChar1[12] == 0x78);
        XL_TEST_ASSERT(pChar1[13] == 0x56);
        XL_TEST_ASSERT(pChar1[14] == 0x34);
        XL_TEST_ASSERT(pChar1[15] == 0x12);

        Memory::Set(pChar2, 16, 0);
        for (int i = 0; i < 16; ++i)
        {
            XL_TEST_ASSERT(pChar2[i] == 0);
        }

        Memory::Copy(pChar2, pChar1, 16);
        XL_TEST_ASSERT(pChar2[0] == 0xef);
        XL_TEST_ASSERT(pChar2[1] == 0xcd);
        XL_TEST_ASSERT(pChar2[2] == 0xab);
        XL_TEST_ASSERT(pChar2[3] == 0x90);
        XL_TEST_ASSERT(pChar2[4] == 0x78);
        XL_TEST_ASSERT(pChar2[5] == 0x56);
        XL_TEST_ASSERT(pChar2[6] == 0x34);
        XL_TEST_ASSERT(pChar2[7] == 0x12);
        XL_TEST_ASSERT(pChar2[8] == 0xef);
        XL_TEST_ASSERT(pChar2[9] == 0xcd);
        XL_TEST_ASSERT(pChar2[10] == 0xab);
        XL_TEST_ASSERT(pChar2[11] == 0x90);
        XL_TEST_ASSERT(pChar2[12] == 0x78);
        XL_TEST_ASSERT(pChar2[13] == 0x56);
        XL_TEST_ASSERT(pChar2[14] == 0x34);
        XL_TEST_ASSERT(pChar2[15] == 0x12);

        Memory::Copy(pChar1, pChar1 + 1 , 15);
        XL_TEST_ASSERT(pChar1[0] == 0xcd);
        XL_TEST_ASSERT(pChar1[1] == 0xab);
        XL_TEST_ASSERT(pChar1[2] == 0x90);
        XL_TEST_ASSERT(pChar1[3] == 0x78);
        XL_TEST_ASSERT(pChar1[4] == 0x56);
        XL_TEST_ASSERT(pChar1[5] == 0x34);
        XL_TEST_ASSERT(pChar1[6] == 0x12);
        XL_TEST_ASSERT(pChar1[7] == 0xef);
        XL_TEST_ASSERT(pChar1[8] == 0xcd);
        XL_TEST_ASSERT(pChar1[9] == 0xab);
        XL_TEST_ASSERT(pChar1[10] == 0x90);
        XL_TEST_ASSERT(pChar1[11] == 0x78);
        XL_TEST_ASSERT(pChar1[12] == 0x56);
        XL_TEST_ASSERT(pChar1[13] == 0x34);
        XL_TEST_ASSERT(pChar1[14] == 0x12);
        XL_TEST_ASSERT(pChar1[15] == 0x12);

        Memory::Copy(pChar2 + 1, pChar2, 15);
        XL_TEST_ASSERT(pChar2[0] == 0xef);
        XL_TEST_ASSERT(pChar2[1] == 0xef);
        XL_TEST_ASSERT(pChar2[2] == 0xcd);
        XL_TEST_ASSERT(pChar2[3] == 0xab);
        XL_TEST_ASSERT(pChar2[4] == 0x90);
        XL_TEST_ASSERT(pChar2[5] == 0x78);
        XL_TEST_ASSERT(pChar2[6] == 0x56);
        XL_TEST_ASSERT(pChar2[7] == 0x34);
        XL_TEST_ASSERT(pChar2[8] == 0x12);
        XL_TEST_ASSERT(pChar2[9] == 0xef);
        XL_TEST_ASSERT(pChar2[10] == 0xcd);
        XL_TEST_ASSERT(pChar2[11] == 0xab);
        XL_TEST_ASSERT(pChar2[12] == 0x90);
        XL_TEST_ASSERT(pChar2[13] == 0x78);
        XL_TEST_ASSERT(pChar2[14] == 0x56);
        XL_TEST_ASSERT(pChar2[15] == 0x34);
    }

    // Memory::Zero/Copy By KJJ
    XL_TEST_CASE()
    {
        char c[] = { '\x12', '\x34', '\x56', '\x78', '\xab' };
        Memory::Zero(c);
        XL_TEST_ASSERT(c[0] == 0);
        XL_TEST_ASSERT(c[1] == 0);
        XL_TEST_ASSERT(c[2] == 0);
        XL_TEST_ASSERT(c[3] == 0);
        XL_TEST_ASSERT(c[4] == 0);

        char d[] = { '\x12', '\x34', '\x56', '\x78', '\xab' };
        Memory::Copy(c, d);
        XL_TEST_ASSERT(d[0] == '\x12');
        XL_TEST_ASSERT(d[1] == '\x34');
        XL_TEST_ASSERT(d[2] == '\x56');
        XL_TEST_ASSERT(d[3] == '\x78');
        XL_TEST_ASSERT(d[4] == '\xab');
    }

    // Memory::Move/Swap By KJJ
    XL_TEST_CASE()
    {

        struct S
        {
            int iCount = 0;

            S()
            {

            }

            S(const S &that) : iCount(that.iCount + 1)
            {

            }

            S(const S &&that)
            {

            }
        };

        S x;
        S y = x;
        S z = Memory::Move(x);
        XL_TEST_ASSERT(y.iCount == 1);
        XL_TEST_ASSERT(z.iCount == 0);

        int a = 1, b = 2;
        Memory::Swap(a, b);
        XL_TEST_ASSERT(a == 2);
        XL_TEST_ASSERT(b == 1);
    }

    // Memory::Set By WYN
    XL_TEST_CASE()
    {
        char *pChar = new char[3];
        Memory::Set(pChar, 3, 0x12345678);
        XL_TEST_ASSERT(pChar[0] == 0x78);
        XL_TEST_ASSERT(pChar[1] == 0x56);
        XL_TEST_ASSERT(pChar[2] == 0x34);
    }
}
