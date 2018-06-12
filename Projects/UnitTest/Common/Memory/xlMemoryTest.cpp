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


#include "../../../../Include/xl/AppHelper/xlUnitTest.h"
#include "../../../../Include/xl/Common/Memory/xlMemory.h"
#include "../../../../Include/xl/Common/Meta/xlCountOf.h"

namespace
{
    using namespace xl;

    // Memory::Set By KJJ
    XL_TEST_CASE()
    {
        unsigned char *pBuf = new unsigned char[17];
        unsigned char *pChar = pBuf + 1;

        Memory::Set(pChar, 0, 16);
        for (int i = 0; i < 16; ++i)
        {
            XL_TEST_ASSERT(pChar[i] == 0);
        }

        Memory::Set(pChar, 0x12345678, 7);
        XL_TEST_ASSERT(pChar[0] == 0x78);
        XL_TEST_ASSERT(pChar[1] == 0x78);
        XL_TEST_ASSERT(pChar[2] == 0x78);
        XL_TEST_ASSERT(pChar[3] == 0x78);
        XL_TEST_ASSERT(pChar[4] == 0x78);
        XL_TEST_ASSERT(pChar[5] == 0x78);
        XL_TEST_ASSERT(pChar[6] == 0x78);
        XL_TEST_ASSERT(pChar[7] == 0);

        Memory::Set(pChar, 0x90abcdef, 5);
        XL_TEST_ASSERT(pChar[0] == 0xef);
        XL_TEST_ASSERT(pChar[1] == 0xef);
        XL_TEST_ASSERT(pChar[2] == 0xef);
        XL_TEST_ASSERT(pChar[3] == 0xef);
        XL_TEST_ASSERT(pChar[4] == 0xef);
        XL_TEST_ASSERT(pChar[5] == 0x78);
        XL_TEST_ASSERT(pChar[6] == 0x78);
        XL_TEST_ASSERT(pChar[7] == 0);

        Memory::Set(pChar, 0x98765432, 15);
        XL_TEST_ASSERT(pChar[0] == 0x32);
        XL_TEST_ASSERT(pChar[1] == 0x32);
        XL_TEST_ASSERT(pChar[2] == 0x32);
        XL_TEST_ASSERT(pChar[3] == 0x32);
        XL_TEST_ASSERT(pChar[4] == 0x32);
        XL_TEST_ASSERT(pChar[5] == 0x32);
        XL_TEST_ASSERT(pChar[6] == 0x32);
        XL_TEST_ASSERT(pChar[7] == 0x32);
        XL_TEST_ASSERT(pChar[8] == 0x32);
        XL_TEST_ASSERT(pChar[9] == 0x32);
        XL_TEST_ASSERT(pChar[10] == 0x32);
        XL_TEST_ASSERT(pChar[11] == 0x32);
        XL_TEST_ASSERT(pChar[12] == 0x32);
        XL_TEST_ASSERT(pChar[13] == 0x32);
        XL_TEST_ASSERT(pChar[14] == 0x32);
        XL_TEST_ASSERT(pChar[15] == 0);

        delete[] pBuf;
    }

    // Memory::Copy By KJJ
    XL_TEST_CASE()
    {
        unsigned char *pBuf1 = new unsigned char[19];
        unsigned char *pBuf2 = new unsigned char[19];
        unsigned char *pChar1 = pBuf1 + 3;
        unsigned char *pChar2 = pBuf2 + 3;

        Memory::Set(pChar1, 0x12, 16);
        pChar1[0] = 0x01;
        pChar1[1] = 0x02;
        pChar1[2] = 0x03;
        pChar1[3] = 0x04;
        pChar1[4] = 0x05;
        pChar1[5] = 0x06;
        pChar1[6] = 0x07;
        pChar1[7] = 0x08;
        pChar1[8] = 0x09;
        pChar1[9] = 0x0a;
        pChar1[10] = 0x0b;
        pChar1[11] = 0x0c;
        pChar1[12] = 0x0d;
        pChar1[13] = 0x0e;
        pChar1[14] = 0x0f;
        pChar1[15] = 0x10;

        Memory::Set(pChar2, 0, 16);
        for (int i = 0; i < 16; ++i)
        {
            XL_TEST_ASSERT(pChar2[i] == 0);
        }

        Memory::Copy(pChar2, pChar1, 16);
        XL_TEST_ASSERT(pChar2[0] == 0x01);
        XL_TEST_ASSERT(pChar2[1] == 0x02);
        XL_TEST_ASSERT(pChar2[2] == 0x03);
        XL_TEST_ASSERT(pChar2[3] == 0x04);
        XL_TEST_ASSERT(pChar2[4] == 0x05);
        XL_TEST_ASSERT(pChar2[5] == 0x06);
        XL_TEST_ASSERT(pChar2[6] == 0x07);
        XL_TEST_ASSERT(pChar2[7] == 0x08);
        XL_TEST_ASSERT(pChar2[8] == 0x09);
        XL_TEST_ASSERT(pChar2[9] == 0x0a);
        XL_TEST_ASSERT(pChar2[10] == 0x0b);
        XL_TEST_ASSERT(pChar2[11] == 0x0c);
        XL_TEST_ASSERT(pChar2[12] == 0x0d);
        XL_TEST_ASSERT(pChar2[13] == 0x0e);
        XL_TEST_ASSERT(pChar2[14] == 0x0f);
        XL_TEST_ASSERT(pChar2[15] == 0x10);

        Memory::Copy(pChar1, pChar1 + 1 , 15);
        XL_TEST_ASSERT(pChar1[0] == 0x02);
        XL_TEST_ASSERT(pChar1[1] == 0x03);
        XL_TEST_ASSERT(pChar1[2] == 0x04);
        XL_TEST_ASSERT(pChar1[3] == 0x05);
        XL_TEST_ASSERT(pChar1[4] == 0x06);
        XL_TEST_ASSERT(pChar1[5] == 0x07);
        XL_TEST_ASSERT(pChar1[6] == 0x08);
        XL_TEST_ASSERT(pChar1[7] == 0x09);
        XL_TEST_ASSERT(pChar1[8] == 0x0a);
        XL_TEST_ASSERT(pChar1[9] == 0x0b);
        XL_TEST_ASSERT(pChar1[10] == 0x0c);
        XL_TEST_ASSERT(pChar1[11] == 0x0d);
        XL_TEST_ASSERT(pChar1[12] == 0x0e);
        XL_TEST_ASSERT(pChar1[13] == 0x0f);
        XL_TEST_ASSERT(pChar1[14] == 0x10);
        XL_TEST_ASSERT(pChar1[15] == 0x10);

        Memory::Copy(pChar2 + 1, pChar2, 15);
        XL_TEST_ASSERT(pChar2[0] == 0x01);
        XL_TEST_ASSERT(pChar2[1] == 0x01);
        XL_TEST_ASSERT(pChar2[2] == 0x02);
        XL_TEST_ASSERT(pChar2[3] == 0x03);
        XL_TEST_ASSERT(pChar2[4] == 0x04);
        XL_TEST_ASSERT(pChar2[5] == 0x05);
        XL_TEST_ASSERT(pChar2[6] == 0x06);
        XL_TEST_ASSERT(pChar2[7] == 0x07);
        XL_TEST_ASSERT(pChar2[8] == 0x08);
        XL_TEST_ASSERT(pChar2[9] == 0x09);
        XL_TEST_ASSERT(pChar2[10] == 0x0a);
        XL_TEST_ASSERT(pChar2[11] == 0x0b);
        XL_TEST_ASSERT(pChar2[12] == 0x0c);
        XL_TEST_ASSERT(pChar2[13] == 0x0d);
        XL_TEST_ASSERT(pChar2[14] == 0x0e);
        XL_TEST_ASSERT(pChar2[15] == 0x0f);

        delete[] pBuf2;
        delete[] pBuf1;
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
        Memory::Copy(c, d, XL_COUNT_OF(c));
        XL_TEST_ASSERT(d[0] == '\x12');
        XL_TEST_ASSERT(d[1] == '\x34');
        XL_TEST_ASSERT(d[2] == '\x56');
        XL_TEST_ASSERT(d[3] == '\x78');
        XL_TEST_ASSERT(d[4] == '\xab');
    }

    // Memory::Move/Swap By KJJ
    XL_TEST_CASE()
    {
#ifdef __XL_CPP11

        struct S
        {
            int iCount;

            S() : iCount(0)
            {

            }

            S(const S &that) : iCount(that.iCount + 1)
            {

            }

            S(const S &&that) : iCount(-1)
            {

            }
        };

        S x;
        S y = x;
        S z = Memory::Move(x);
        XL_TEST_ASSERT(y.iCount == 1);
        XL_TEST_ASSERT(z.iCount == -1);

#endif

        int a = 1, b = 2;
        Memory::Swap(a, b);
        XL_TEST_ASSERT(a == 2);
        XL_TEST_ASSERT(b == 1);
    }
}
