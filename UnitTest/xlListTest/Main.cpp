//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-08-10
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Containers/xlList.h>
#include "../UnitTestFrame.h"

using namespace xl;

TEST_CASE(ctor)
{
    List<int> a;
    TEST_ASSERT(a.Size() == 0);
}

int main()
{
    return 0;
}
