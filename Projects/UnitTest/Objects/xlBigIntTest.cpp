//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlBigIntTest.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/Common/Math/xlBigInt.h"
#include "../../../Include/xl/AppHelper/xlUnitTest.h"

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        BigInt a;
        XL_TEST_ASSERT(a == 0);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(BigInt((char)1) == 1);
        XL_TEST_ASSERT(BigInt((unsigned char)2) == 2);
        XL_TEST_ASSERT(BigInt((short)3) == 3);
        XL_TEST_ASSERT(BigInt((unsigned short)4) == 4);
        XL_TEST_ASSERT(BigInt((int)5) == 5);
        XL_TEST_ASSERT(BigInt((unsigned int)6) == 6);
        XL_TEST_ASSERT(BigInt((long)7) == 7);
        XL_TEST_ASSERT(BigInt((unsigned long)8) == 8);
        XL_TEST_ASSERT(BigInt((long long)9) == 9);
        XL_TEST_ASSERT(BigInt((unsigned long long)10) == 10);

        XL_TEST_ASSERT(BigInt((char)-1) == -1);
        XL_TEST_ASSERT(BigInt((unsigned char)-2) == 0xfe);
        XL_TEST_ASSERT(BigInt((short)-3) == -3);
        XL_TEST_ASSERT(BigInt((unsigned short)-4) == 0xfffc);
        XL_TEST_ASSERT(BigInt((int)-5) == -5);
        XL_TEST_ASSERT(BigInt((unsigned int)-6) == 0xfffffffa);
        XL_TEST_ASSERT(BigInt((long)-7) == -7);
        XL_TEST_ASSERT(BigInt((unsigned long)-8) == 0xfffffff8);
        XL_TEST_ASSERT(BigInt((long long)-9) == -9);
        XL_TEST_ASSERT(BigInt((unsigned long long)-10) == 0xfffffffffffffff6);
    }

    XL_TEST_CASE()
    {
        unsigned char buffer[] =
        {
            0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef,
            0xfe, 0xdc, 0xba, 0x09, 0x87, 0x65, 0x43, 0x21
        };

        XL_TEST_ASSERT(BigInt(buffer, 1) == 0x12);
        XL_TEST_ASSERT(BigInt(buffer, 2) == 0x3412);
        XL_TEST_ASSERT(BigInt(buffer, 3) == 0x563412);
        XL_TEST_ASSERT(BigInt(buffer, 4) == 0x78563412);
        XL_TEST_ASSERT(BigInt(buffer, 5) == 0x9078563412);
        XL_TEST_ASSERT(BigInt(buffer, 6) == 0xab9078563412);
        XL_TEST_ASSERT(BigInt(buffer, 7) == 0xcdab9078563412);
        XL_TEST_ASSERT(BigInt(buffer, 8) == 0xefcdab9078563412);

        BigInt a(buffer, 8);

        BigInt b = 0x1000000000000000;
        b *= 0x10;

        XL_TEST_ASSERT(BigInt(buffer, 9) == a + BigInt(buffer + 8, 1) * b);
        XL_TEST_ASSERT(BigInt(buffer, 10) == a + BigInt(buffer + 8, 2) * b);
        XL_TEST_ASSERT(BigInt(buffer, 11) == a + BigInt(buffer + 8, 3) * b);
        XL_TEST_ASSERT(BigInt(buffer, 12) == a + BigInt(buffer + 8, 4) * b);
        XL_TEST_ASSERT(BigInt(buffer, 13) == a + BigInt(buffer + 8, 5) * b);
        XL_TEST_ASSERT(BigInt(buffer, 14) == a + BigInt(buffer + 8, 6) * b);
        XL_TEST_ASSERT(BigInt(buffer, 15) == a + BigInt(buffer + 8, 7) * b);
        XL_TEST_ASSERT(BigInt(buffer, 16) == a + BigInt(buffer + 8, 8) * b);
    }

    XL_TEST_CASE()
    {
        BigInt a(-1), b(0x1ffffffff), c;
        c = a;
        XL_TEST_ASSERT(c == a);

        c = b;
        XL_TEST_ASSERT(c == b);
    }

    XL_TEST_CASE()
    {
        BigInt a;
        XL_TEST_ASSERT(a.IsPositive() == true);

        BigInt b(1);
        XL_TEST_ASSERT(b.IsPositive() == true);

        BigInt c(-1);
        XL_TEST_ASSERT(c.IsPositive() == false);
    }

    XL_TEST_CASE()
    {
        BigInt a(0xfffffffffffffffe);
        Array<unsigned int> b;
        b.PushBack(0xfffffffe);
        b.PushBack(0xffffffff);

        XL_TEST_ASSERT(a.GetData() == b);
    }

    XL_TEST_CASE()
    {
        BigInt a, b;

        XL_TEST_ASSERT(a == b);
        XL_TEST_ASSERT(!(a != b));
        XL_TEST_ASSERT(!(a < b));
        XL_TEST_ASSERT(a <= b);
        XL_TEST_ASSERT(!(a > b));
        XL_TEST_ASSERT(a >= b);

        a = -1;
        XL_TEST_ASSERT(!(a == b));
        XL_TEST_ASSERT(a != b);
        XL_TEST_ASSERT(a < b);
        XL_TEST_ASSERT(a <= b);
        XL_TEST_ASSERT(!(a > b));
        XL_TEST_ASSERT(!(a >= b));

        a = 1;
        XL_TEST_ASSERT(!(a == b));
        XL_TEST_ASSERT(a != b);
        XL_TEST_ASSERT(!(a < b));
        XL_TEST_ASSERT(!(a <= b));
        XL_TEST_ASSERT(a > b);
        XL_TEST_ASSERT(a >= b);
    }

    XL_TEST_CASE()
    {
        BigInt a(13), b(29);

        XL_TEST_ASSERT(a++ == 13);
        XL_TEST_ASSERT(a == 14);
        XL_TEST_ASSERT(a-- == 14);
        XL_TEST_ASSERT(a == 13);
        XL_TEST_ASSERT(++a == 14);
        XL_TEST_ASSERT(a == 14);
        XL_TEST_ASSERT(--a == 13);
        XL_TEST_ASSERT(a == 13);

        XL_TEST_ASSERT(a + b == 42);
        XL_TEST_ASSERT(a - b == -16);
        XL_TEST_ASSERT(b - a == 16);
        XL_TEST_ASSERT(a * b == 377);
        XL_TEST_ASSERT(a / b == 0);
        XL_TEST_ASSERT(b / a == 2);
        XL_TEST_ASSERT(a % b == 13);
        XL_TEST_ASSERT(b % a == 3);

        XL_TEST_ASSERT((a += 4) == 17);
        XL_TEST_ASSERT(a == 17);
        XL_TEST_ASSERT((a -= 4) == 13);
        XL_TEST_ASSERT(a == 13);
        XL_TEST_ASSERT((a *= 3) == 39);
        XL_TEST_ASSERT(a == 39);
        XL_TEST_ASSERT((a /= 3) == 13);
        XL_TEST_ASSERT(a == 13);
        XL_TEST_ASSERT((a %= 5) == 3);
        XL_TEST_ASSERT(a == 3);

        XL_TEST_ASSERT(a.Exp(3) == 27);
        XL_TEST_ASSERT(a.ExpMod(5, 17) == 5);
    }

    XL_TEST_CASE()
    {
        BigInt a(0x1234567890abcdef);
        a *= 0x10;

        XL_TEST_ASSERT(a.ToChar() == (char)0xf0);
        XL_TEST_ASSERT(a.ToShort() == (short)0xdef0);
        XL_TEST_ASSERT(a.ToInt() == 0x0abcdef0);
        XL_TEST_ASSERT(a.ToLong() == 0x0abcdef0);
        XL_TEST_ASSERT(a.ToLongLong() == 0x234567890abcdef0);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(BigInt(L"1234567890") == 1234567890);
        XL_TEST_ASSERT(BigInt(L"1234567890ABCDEF", 16) == 0x1234567890abcdef);
        XL_TEST_ASSERT(BigInt(L"1234567123", 8) == 01234567123);
        XL_TEST_ASSERT(BigInt(L"12345678", 9) == 6053444);

        XL_TEST_ASSERT(BigInt(L"wertyuiopq", 10, L"qwertyuiop") == 1234567890);
        XL_TEST_ASSERT(BigInt(L"sdfghjklzaxcvbnm", 16, L"asdfghjklzxcvbnm") == 0x1234567890abcdef);
        XL_TEST_ASSERT(BigInt(L"zxcvbnmzxc", 8, L"0zxcvbnm") == 01234567123);
        XL_TEST_ASSERT(BigInt(L"[];',./{", 9, L"}[];',./{") == 6053444);

        XL_TEST_ASSERT(BigInt(L"1234567890").ToString() == String(L"1234567890"));
        XL_TEST_ASSERT(BigInt(L"1234567890").ToString(16) == String(L"499602D2"));
        XL_TEST_ASSERT(BigInt(L"1234567890").ToString(8) == String(L"11145401322"));
        XL_TEST_ASSERT(BigInt(L"1234567890").ToString(2) == String(L"1001001100101100000001011010010"));

        typedef BigIntT<unsigned short> BigIntT16;

        XL_TEST_ASSERT(BigIntT16(L"1234567890") == 1234567890);
        XL_TEST_ASSERT(BigIntT16(L"1234567890ABCDEF", 16) == 0x1234567890abcdef);
        XL_TEST_ASSERT(BigIntT16(L"1234567123", 8) == 01234567123);
        XL_TEST_ASSERT(BigIntT16(L"12345678", 9) == 6053444);

        XL_TEST_ASSERT(BigIntT16(L"wertyuiopq", 10, L"qwertyuiop") == 1234567890);
        XL_TEST_ASSERT(BigIntT16(L"sdfghjklzaxcvbnm", 16, L"asdfghjklzxcvbnm") == 0x1234567890abcdef);
        XL_TEST_ASSERT(BigIntT16(L"zxcvbnmzxc", 8, L"0zxcvbnm") == 01234567123);
        XL_TEST_ASSERT(BigIntT16(L"[];',./{", 9, L"}[];',./{") == 6053444);

        XL_TEST_ASSERT(BigIntT16(L"1234567890").ToString() == String(L"1234567890"));
        XL_TEST_ASSERT(BigIntT16(L"1234567890").ToString(16) == String(L"499602D2"));
        XL_TEST_ASSERT(BigIntT16(L"1234567890").ToString(8) == String(L"11145401322"));
        XL_TEST_ASSERT(BigIntT16(L"1234567890").ToString(2) == String(L"1001001100101100000001011010010"));


        typedef BigIntT<unsigned char> BigIntT8;

        XL_TEST_ASSERT(BigIntT8(L"1234567890") == 1234567890);
        XL_TEST_ASSERT(BigIntT8(L"1234567890ABCDEF", 16) == 0x1234567890abcdef);
        XL_TEST_ASSERT(BigIntT8(L"1234567123", 8) == 01234567123);
        XL_TEST_ASSERT(BigIntT8(L"12345678", 9) == 6053444);

        XL_TEST_ASSERT(BigIntT8(L"wertyuiopq", 10, L"qwertyuiop") == 1234567890);
        XL_TEST_ASSERT(BigIntT8(L"sdfghjklzaxcvbnm", 16, L"asdfghjklzxcvbnm") == 0x1234567890abcdef);
        XL_TEST_ASSERT(BigIntT8(L"zxcvbnmzxc", 8, L"0zxcvbnm") == 01234567123);
        XL_TEST_ASSERT(BigIntT8(L"[];',./{", 9, L"}[];',./{") == 6053444);

        XL_TEST_ASSERT(BigIntT8(L"1234567890").ToString() == String(L"1234567890"));
        XL_TEST_ASSERT(BigIntT8(L"1234567890").ToString(16) == String(L"499602D2"));
        XL_TEST_ASSERT(BigIntT8(L"1234567890").ToString(8) == String(L"11145401322"));
        XL_TEST_ASSERT(BigIntT8(L"1234567890").ToString(2) == String(L"1001001100101100000001011010010"));
    }

#define P_512   L"BF273099C31081FA8F32819C4D5C219579A9430B5B594FB3825F5929B77D1813"
#define Q_512   L"D91F81D4F71454D277E31C9C0B487D3A4CC490792ECCEC81CAA84603AE75716B"
#define N_512   L"A21FBEE2FD67561826B9562CEE35334692D5049EA832ECEB89E2191E1F0BAFDAD9262266E5083D6BE0E7F853E4369B84ABCE72E773312914D4820B2FD39872F1"
#define D_512   L"83711584574AC6A48210D56B4C1DD9DAA80508DFD122A8AF36751744328B7920BCD5EAA3DBB1CE6B8FD259B7E76A8EE5E2EA798EE9BE2FD9F2AF308EAF734A59"
#define E_512   L"10001"

#define P_1024  L"D840E5A3749A9149421578A8F5D9D6E1C8C7D22A2DA83B81C78EEEBD99834007C1270BDC1422324B5374A99C5A1082F32A981EEEB6785426FF65BA2D85780F4B"
#define Q_1024  L"BE4596D7818C4313F457A19EF8BABC1F30EE43EDF4180F82457AFD2E784209DDAF4E813B66C523E7ED0B3B8CC8849659F4546F2CFE642133C3C8C4E00FBBD1EB"
#define N_1024  L"A0BAF3594816F7F5D1340C6E6ADF482CD564FCB9D503F9A42029E532D6A89E6BA2F9BC0B47AF5D942745041699B4C06CFD369E360C38187D01C1B785A8E52FBEE350B4176D8587D96F97F502E7CC1E65010CD3FFD39739C1A97736E893E532AF3882640880416B7CF0C16752EEA583807F087E1D6E94CDEDF1CE66F91A7B44D9"
#define D_1024  L"430BF93B031161BA0EDC915AF605D20BB1B080A3DC31DE4F1283A7723F8CF3189F516199AAFB8223AD05E320B2596DF388E4E1B655FE88688CF50BE31B830F18FE115485565E10ACFF03DB5E275B7E2FE9C7CB4BFD2955498F19203098EF4AA1F16B39B62CAF5935F5EA3DABC5CE0B1F07366035B80D2815AD5B52D9322D8769"
#define E_1024  L"10001"

#define P_2048  L"83836EC1603C4CF01E29DEC07179B0E25A275783CA1E80009B695C6B2DDEBAF9B1E0C65C00F86D594C24F5E41D37AAECE62DDC4D667266E8A28CDA9584E466A9032DC544DD3417FEA5C4D57A1A9A639B9835069F555292D128083FE337E68E31B8D69CCCCCA80092284E71BFB950DADE37AE531D8CBAD5A1EEC16397B256C43B"
#define Q_2048  L"977537C427DC631986871CE1A2C4B05AB652B48286CCE1B80AE0C8CB5769D61B37ED463AF3CC284CDBDAD7FE268881E8CD56EB20147EF30868F903C7B93E971BA6BF1109EA7D4FA748D86D4C870DD93DC56E0793B9554F9F4F976B865F5944D6670A1DA11F67834174E51C11779C9B4BDE27AC87707CDC4040D28D55534ED363"
#define N_2048  L"4DCEBE0BB00B226702D9AB9BBCFC3991D37E0E0FB335FFE72557C7B14C5727FEECEDD7AD4D39820057B60897180DE3F599CE4148CC073B1140D3E4D20B3790E481C0EE93DE6FF6FC5F8A9FF785D5DEC4B4702F89042F4F929F8FD3A3343C9F80834E329570DE93EFB613C5C52A42BBBA731F5B78A0918D20A77D3C34E186223E21D6E73FC3BE3F04D2CA81DB02B038C712E288F34A3FD435F3F0CB15532AA019EECF62A2C1582D3490A5F92E3E78B00607E24602B950142A54108F645E1B3A889EF3E0FFB8ED20379D9CDBAF0DE9C56E911DAB670326690932A320415ACA458B839E8EAB3F202697B2282410868A31485ECC00976E12E532FA33AA4D664483D1"
#define D_2048  L"26B732B55A19903AB59E5DD79687E2957F2900122BD838C7693B6E6FF84E7DE6493A67D121D5F5ABF9F8E7F956CCC29B58B6DAA14074709DBB26347B977D44A98F2ED307DCECD576EA8B6DE19A44BB1E21B298D492B27FE3B365BBA73FBCD298FDBD114A6EE931AF5B6827465E2AEA8271FA2E67AD6DFF4D3A4A0485439A9CBAC50A1E270CBAEA946D71E1E9BE2C0355F6B0CB48971FC0003D7D2897DED6172726406DF25D0F2BA07ECE0049442E3F88F2D1BAC4C44E1A579A92F857553F0DED6BA4DF5B000DF95EF436D67D0030F3A75A002EECC54197F3B34A9AFF299B6033A493B661F54D17D07DA4DE86113175A23227C67CDC4F160FA3632AB89C1B37E9"
#define E_2048  L"10001"

    XL_TEST_CASE()
    {
        BigInt p, q, n, d, e;

        p.FromString(P_512, 16);
        q.FromString(Q_512, 16);
        n.FromString(N_512, 16);
        d.FromString(D_512, 16);
        e.FromString(E_512, 16);

        XL_TEST_ASSERT(p * q == n);
        XL_TEST_ASSERT(d * e % ((p - 1) * (q - 1)) == 1);

        p.FromString(P_1024, 16);
        q.FromString(Q_1024, 16);
        n.FromString(N_1024, 16);
        d.FromString(D_1024, 16);
        e.FromString(E_1024, 16);

        XL_TEST_ASSERT(p * q == n);
        XL_TEST_ASSERT(d * e % ((p - 1) * (q - 1)) == 1);

        p.FromString(P_2048, 16);
        q.FromString(Q_2048, 16);
        n.FromString(N_2048, 16);
        d.FromString(D_2048, 16);
        e.FromString(E_2048, 16);

        XL_TEST_ASSERT(p * q == n);
        XL_TEST_ASSERT(d * e % ((p - 1) * (q - 1)) == 1);


        BigIntT<unsigned short> p1, q1, n1, d1, e1;

        p1.FromString(P_512, 16);
        q1.FromString(Q_512, 16);
        n1.FromString(N_512, 16);
        d1.FromString(D_512, 16);
        e1.FromString(E_512, 16);

        XL_TEST_ASSERT(p1 * q1 == n1);
        XL_TEST_ASSERT(d1 * e1 % ((p1 - 1) * (q1 - 1)) == 1);

        p1.FromString(P_1024, 16);
        q1.FromString(Q_1024, 16);
        n1.FromString(N_1024, 16);
        d1.FromString(D_1024, 16);
        e1.FromString(E_1024, 16);

        XL_TEST_ASSERT(p1 * q1 == n1);
        XL_TEST_ASSERT(d1 * e1 % ((p1 - 1) * (q1 - 1)) == 1);

        p1.FromString(P_2048, 16);
        q1.FromString(Q_2048, 16);
        n1.FromString(N_2048, 16);
        d1.FromString(D_2048, 16);
        e1.FromString(E_2048, 16);

        XL_TEST_ASSERT(p1 * q1 == n1);
        XL_TEST_ASSERT(d1 * e1 % ((p1 - 1) * (q1 - 1)) == 1);

        BigIntT<unsigned char> p2, q2, n2, d2, e2;

        p2.FromString(P_512, 16);
        q2.FromString(Q_512, 16);
        n2.FromString(N_512, 16);
        d2.FromString(D_512, 16);
        e2.FromString(E_512, 16);

        XL_TEST_ASSERT(p2 * q2 == n2);
        XL_TEST_ASSERT(d2 * e2 % ((p2 - 1) * (q2 - 1)) == 1);

        p2.FromString(P_1024, 16);
        q2.FromString(Q_1024, 16);
        n2.FromString(N_1024, 16);
        d2.FromString(D_1024, 16);
        e2.FromString(E_1024, 16);

        XL_TEST_ASSERT(p2 * q2 == n2);
        XL_TEST_ASSERT(d2 * e2 % ((p2 - 1) * (q2 - 1)) == 1);

        p2.FromString(P_2048, 16);
        q2.FromString(Q_2048, 16);
        n2.FromString(N_2048, 16);
        d2.FromString(D_2048, 16);
        e2.FromString(E_2048, 16);

        XL_TEST_ASSERT(p2 * q2 == n2);
        XL_TEST_ASSERT(d2 * e2 % ((p2- 1) * (q2 - 1)) == 1);
    }
}
