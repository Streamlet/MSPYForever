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


#include <xl/Cryption/xlMD5.h>
#include <xl/String/xlString.h>
#include <cstdio>
#include <tchar.h>

xl::String MD5DigestToString(xl::MD5::Digest digest)
{
    xl::Char szDigest[(xl::MD5::DIGEST_LENGTH + 1) * 2] = {};

    for (size_t i = 0; i < xl::MD5::DIGEST_LENGTH; ++i)
    {
        _stprintf(&szDigest[i * 2], _T("%02x"), digest[i]);
    }

    return szDigest;
}

int main()
{
    xl::MD5::Digest d;
    xl::MD5::Calculate(NULL, 0, d);

    xl::String s = MD5DigestToString(d);

    return 0;
}
