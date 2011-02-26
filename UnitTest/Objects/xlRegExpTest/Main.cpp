//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-10-12
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Objects/xlRegExp.h>
#include <xl/Test/xlUnitTest.h>

using namespace xl;

XL_TEST_CASE()
{
    XL_TEST_ASSERT(RegExp().Parse(L"^/d+$"));
}

int main()
{
    return 0;
}
