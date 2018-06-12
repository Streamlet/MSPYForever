//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlBase64Test.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../../Include/xl/AppHelper/xlUnitTest.h"
#include "../../../../Include/xl/Common/String/xlBase64.h"

namespace
{
    XL_TEST_CASE()
    {
        xl::String str;
        xl::Array<unsigned char> arr;

        xl::Base64::Encode("", 0, &str);
        xl::Base64::Decode(str, &arr);
        arr.PushBack(0);
        XL_TEST_ASSERT(str == L"");
        XL_TEST_ASSERT(xl::StringA((const char *)&arr[0]) == "");

        xl::Base64::Encode("a", 1, &str);
        xl::Base64::Decode(str, &arr);
        arr.PushBack(0);
        XL_TEST_ASSERT(str == L"YQ==");
        XL_TEST_ASSERT(xl::StringA((const char *)&arr[0]) == "a");

        xl::Base64::Encode("ab", 2, &str);
        xl::Base64::Decode(str, &arr);
        arr.PushBack(0);
        XL_TEST_ASSERT(str == L"YWI=");
        XL_TEST_ASSERT(xl::StringA((const char *)&arr[0]) == "ab");

        xl::Base64::Encode("abc", 3, &str);
        xl::Base64::Decode(str, &arr);
        arr.PushBack(0);
        XL_TEST_ASSERT(str == L"YWJj");
        XL_TEST_ASSERT(xl::StringA((const char *)&arr[0]) == "abc");

        xl::Base64::Encode("abcd", 4, &str);
        xl::Base64::Decode(str, &arr);
        arr.PushBack(0);
        XL_TEST_ASSERT(str == L"YWJjZA==");
        XL_TEST_ASSERT(xl::StringA((const char *)&arr[0]) == "abcd");

        xl::Base64::Encode("abcde", 5, &str);
        xl::Base64::Decode(str, &arr);
        arr.PushBack(0);
        XL_TEST_ASSERT(str == L"YWJjZGU=");
        XL_TEST_ASSERT(xl::StringA((const char *)&arr[0]) == "abcde");

        xl::Base64::Encode("abcdef", 6, &str);
        xl::Base64::Decode(str, &arr);
        arr.PushBack(0);
        XL_TEST_ASSERT(str == L"YWJjZGVm");
        XL_TEST_ASSERT(xl::StringA((const char *)&arr[0]) == "abcdef");

        xl::Base64::Encode("abcdefg", 7, &str);
        xl::Base64::Decode(str, &arr);
        arr.PushBack(0);
        XL_TEST_ASSERT(str == L"YWJjZGVmZw==");
        XL_TEST_ASSERT(xl::StringA((const char *)&arr[0]) == "abcdefg");
    }
}
