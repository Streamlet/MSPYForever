//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2011-02-26
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/String/xlBase64.h>

int main()
{
    xl::String base64;
    xl::Base64::Encode("abcd", 4, &base64);

    xl::Array<unsigned char> arr;
    xl::Base64::Decode(base64, &arr);

    return 0;
}
