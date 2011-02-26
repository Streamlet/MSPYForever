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


#include <xl/Cryption/xlCRC32.h>
#include <xl/String/xlString.h>
#include <cstdio>
#include <tchar.h>

xl::String CRC32ChecksumToString(unsigned int checksum)
{
    xl::Char szDigest[9] = {};

    _stprintf(szDigest, _T("%08x"), checksum);

    return szDigest;
}

int main()
{
    unsigned int c = xl::CRC32::Calculate("a", 1);

    xl::String s = CRC32ChecksumToString(c);

    return 0;
}
