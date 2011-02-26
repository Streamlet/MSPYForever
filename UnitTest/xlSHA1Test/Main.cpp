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


#include <xl/Cryption/xlSHA1.h>
#include <xl/Objects/xlString.h>
#include <cstdio>
#include <tchar.h>

xl::String SHA1DigestToString(xl::SHA1::Digest digest)
{
    xl::Char szDigest[(xl::SHA1::DIGEST_LENGTH * 4 + 1) * 2] = {};

    for (size_t i = 0; i < xl::SHA1::DIGEST_LENGTH; ++i)
    {
        _stprintf(&szDigest[i * 8], _T("%08x"), digest[i]);
    }

    return szDigest;
}

int main()
{
    xl::SHA1::Digest d;
    xl::SHA1::Calculate(NULL, 0, d);

    xl::String s = SHA1DigestToString(d);

    return 0;
}
