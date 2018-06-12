//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlSHA1Test.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../../Include/xl/AppHelper/xlUnitTest.h"
#include "../../../../Include/xl/Common/Cryption/xlSHA1.h"
#include "../../../../Include/xl/Common/String/xlString.h"
#include <stdio.h>

namespace
{
    xl::StringA SHA1DigestToString(xl::SHA1::Digest digest)
    {
        xl::CharA szDigest[(xl::SHA1::DIGEST_LENGTH * 4 + 1) * 2] = {};

        for (size_t i = 0; i < xl::SHA1::DIGEST_LENGTH; ++i)
        {
            sprintf_s(&szDigest[i * 8], 9, "%08x", digest[i]);
        }

        return szDigest;
    }

    xl::StringA StringSHA1(const xl::StringA &str)
    {
        xl::SHA1::Digest digest;
        xl::SHA1::Calculate(str, str.Length(), digest);

        return SHA1DigestToString(digest);
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(StringSHA1("") == "da39a3ee5e6b4b0d3255bfef95601890afd80709");
        XL_TEST_ASSERT(StringSHA1("a") == "86f7e437faa5a7fce15d1ddcb9eaeaea377667b8");
        XL_TEST_ASSERT(StringSHA1("ab") == "da23614e02469a0d7c7bd1bdab5c9c474b1904dc");
        XL_TEST_ASSERT(StringSHA1("abc") == "a9993e364706816aba3e25717850c26c9cd0d89d");
        XL_TEST_ASSERT(StringSHA1("abcd") == "81fe8bfe87576c3ecb22426f8e57847382917acf");
        XL_TEST_ASSERT(StringSHA1("abcde") == "03de6c570bfe24bfc328ccd7ca46b76eadaf4334");
        XL_TEST_ASSERT(StringSHA1("abcdef") == "1f8ac10f23c5b5bc1167bda84b833e5c057a77d2");
        XL_TEST_ASSERT(StringSHA1("abcdefg") == "2fb5e13419fc89246865e7a324f476ec624e8740");
    }
}
