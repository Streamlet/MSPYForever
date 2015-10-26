//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMD5Test.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../Include/xl/AppHelper/xlUnitTest.h"
#include "../../../Include/xl/Common/Cryption/xlMD5.h"
#include "../../../Include/xl/Common/String/xlString.h"
#include <stdio.h>

namespace
{
    xl::StringA MD5DigestToString(xl::MD5::Digest digest)
    {
        xl::CharA szDigest[(xl::MD5::DIGEST_LENGTH + 1) * 2] = {};

        for (size_t i = 0; i < xl::MD5::DIGEST_LENGTH; ++i)
        {
            sprintf_s(&szDigest[i * 2], 3, "%02x", digest[i]);
        }

        return szDigest;
    }

    xl::StringA StringMD5(const xl::StringA &str)
    {
        xl::MD5::Digest digest;
        xl::MD5::Calculate(str, str.Length(), digest);

        return MD5DigestToString(digest);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(StringMD5("") == "d41d8cd98f00b204e9800998ecf8427e");
        XL_TEST_ASSERT(StringMD5("a") == "0cc175b9c0f1b6a831c399e269772661");
        XL_TEST_ASSERT(StringMD5("ab") == "187ef4436122d1cc2f40dc2b92f0eba0");
        XL_TEST_ASSERT(StringMD5("abc") == "900150983cd24fb0d6963f7d28e17f72");
        XL_TEST_ASSERT(StringMD5("abcd") == "e2fc714c4727ee9395f324cd2e7f331f");
        XL_TEST_ASSERT(StringMD5("abcde") == "ab56b4d92b40713acc5af89985d4b786");
        XL_TEST_ASSERT(StringMD5("abcdef") == "e80b5017098950fc58aad83c8c14978e");
        XL_TEST_ASSERT(StringMD5("abcdefg") == "7ac66c0f148de9519b8bd264312c4d64");
    }
}
