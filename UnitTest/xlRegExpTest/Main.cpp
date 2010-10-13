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
#include "../UnitTestFrame.h"

using namespace xl;

TEST_CASE(grammar)
{
    TEST_ASSERT(RegExp().Parse(L"^/d+$"));
}

int main()
{
    return 0;
}
