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

TEST_CASE(operator_set)
{
    BigInt a(-1), b(0x1ffffffff), c;
    c = a;
    TEST_ASSERT(c == a);

    c = b;
    TEST_ASSERT(c == b);
}

TEST_CASE(method_IsPositive)
{
    BigInt a;
    TEST_ASSERT(a.IsPositive() == true);

    BigInt b(1);
    TEST_ASSERT(b.IsPositive() == true);

    BigInt c(-1);
    TEST_ASSERT(c.IsPositive() == false);
}

TEST_CASE(method_GetData)
{
    BigInt a(0xfffffffffffffffe);
    Array<unsigned int> b;
    b.PushBack(0xfffffffe);
    b.PushBack(0xffffffff);

    TEST_ASSERT(a.GetData() == b);
}

TEST_CASE(operator_lt_gt)
{
    BigInt a, b;

    TEST_ASSERT(a == b);
    TEST_ASSERT(!(a != b));
    TEST_ASSERT(!(a < b));
    TEST_ASSERT(a <= b);
    TEST_ASSERT(!(a > b));
    TEST_ASSERT(a >= b);

    a = -1;
    TEST_ASSERT(!(a == b));
    TEST_ASSERT(a != b);
    TEST_ASSERT(a < b);
    TEST_ASSERT(a <= b);
    TEST_ASSERT(!(a > b));
    TEST_ASSERT(!(a >= b));

    a = 1;
    TEST_ASSERT(!(a == b));
    TEST_ASSERT(a != b);
    TEST_ASSERT(!(a < b));
    TEST_ASSERT(!(a <= b));
    TEST_ASSERT(a > b);
    TEST_ASSERT(a >= b);
}

TEST_CASE(operator_math)
{
    BigInt a(13), b(29);

    TEST_ASSERT(a++ == 13);
    TEST_ASSERT(a == 14);
    TEST_ASSERT(a-- == 14);
    TEST_ASSERT(a == 13);
    TEST_ASSERT(++a == 14);
    TEST_ASSERT(a == 14);
    TEST_ASSERT(--a == 13);
    TEST_ASSERT(a == 13);

    TEST_ASSERT(a + b == 42);
    TEST_ASSERT(a - b == -16);
    TEST_ASSERT(b - a == 16);
    TEST_ASSERT(a * b == 377);
    TEST_ASSERT(a / b == 0);
    TEST_ASSERT(b / a == 2);
    TEST_ASSERT(a % b == 13);
    TEST_ASSERT(b % a == 3);

    TEST_ASSERT((a += 4) == 17);
    TEST_ASSERT(a == 17);
    TEST_ASSERT((a -= 4) == 13);
    TEST_ASSERT(a == 13);
    TEST_ASSERT((a *= 3) == 39);
    TEST_ASSERT(a == 39);
    TEST_ASSERT((a /= 3) == 13);
    TEST_ASSERT(a == 13);
    TEST_ASSERT((a %= 5) == 3);
    TEST_ASSERT(a == 3);

    TEST_ASSERT(a.Exp(3) == 27);
    TEST_ASSERT(a.ExpMod(5, 17) == 5);
}

TEST_CASE(method_to_number)
{
    BigInt a(0x1234567890abcdef);
    a *= 0x10;

    TEST_ASSERT(a.ToChar() == (char)0xf0);
    TEST_ASSERT(a.ToShort() == (short)0xdef0);
    TEST_ASSERT(a.ToInt() == 0x0abcdef0);
    TEST_ASSERT(a.ToLong() == 0x0abcdef0);
    TEST_ASSERT(a.ToLongLong() == 0x234567890abcdef0);
}

TEST_CASE(method_string)
{
    TEST_ASSERT(BigInt(L"1234567890") == 1234567890);
    TEST_ASSERT(BigInt(L"1234567890ABCDEF", 16) == 0x1234567890abcdef);
    TEST_ASSERT(BigInt(L"1234567123", 8) == 01234567123);
    TEST_ASSERT(BigInt(L"12345678", 9) == 6053444);

    TEST_ASSERT(BigInt(L"wertyuiopq", 10, L"qwertyuiop") == 1234567890);
    TEST_ASSERT(BigInt(L"sdfghjklzaxcvbnm", 16, L"asdfghjklzxcvbnm") == 0x1234567890abcdef);
    TEST_ASSERT(BigInt(L"zxcvbnmzxc", 8, L"0zxcvbnm") == 01234567123);
    TEST_ASSERT(BigInt(L"[];',./{", 9, L"}[];',./{") == 6053444);

    TEST_ASSERT(BigInt(L"1234567890").ToString() == String(L"1234567890"));
    TEST_ASSERT(BigInt(L"1234567890").ToString(16) == String(L"499602D2"));
    TEST_ASSERT(BigInt(L"1234567890").ToString(8) == String(L"11145401322"));
    TEST_ASSERT(BigInt(L"1234567890").ToString(2) == String(L"1001001100101100000001011010010"));
}

int main()
{
    return 0;
}
