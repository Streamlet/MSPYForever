//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-08-13
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Containers/xlRBTree.h>
#include "../UnitTestFrame.h"

using namespace xl;

TEST_CASE(ctor)
{
    RBTree<int> a;
    TEST_ASSERT(a.Size() == 0);
}

int main()
{
    return 0;
}

