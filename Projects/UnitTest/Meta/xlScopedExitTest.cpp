//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlScopedExitTest.cpp
//    Author:      Streamlet
//    Create Time: 2012-04-22
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Test/xlUnitTest.h>
#include <xl/Meta/xlScopeExit.h>

namespace
{
    using namespace xl;

    void TestInc(int *p)
    {
        ++*p;
    }

    XL_TEST_CASE()
    {
        int i = 0;

        {
            XL_ON_BLOCK_EXIT(TestInc, &i);
        }

        XL_TEST_ASSERT(i == 1);

        {
            ScopeGuard sg = MakeGuard(Bind(TestInc, &i));
        }

        XL_TEST_ASSERT(i == 2);

        {
            ScopeGuard sg = MakeGuard(Bind(TestInc, &i));
            sg.Dismiss();
        }

        XL_TEST_ASSERT(i == 2);
    }
}
