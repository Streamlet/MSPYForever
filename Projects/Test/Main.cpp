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
	b = r.Test(L"aac");
	b = r.Test(L"abc");
	b = r.Test(L"acc");
	b = r.Test(L"a1c");
	b = r.Test(L"a2c");
	b = r.Test(L"a3c");



    return 0;
}
