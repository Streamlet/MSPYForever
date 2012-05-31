//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Parser/xlRegExp.h>
using namespace xl;

int main()
{
    RegExp r;
    bool b = false;

    r.Parse(L"a[^1b2]c");
    b = r.Match(L"aac");
    b = r.Match(L"abc");
    b = r.Match(L"acc");
    b = r.Match(L"a1c");
    b = r.Match(L"a2c");
    b = r.Match(L"a3c");



    return 0;
}
