//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-08-19
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif

#include "../UnitTestFrame.h"
#include <xl/xlDef.h>
#include <xl/Objects/xlQIPtr.h>

using namespace xl;

TEST_CASE(ctor)
{
    QIPtr<int> a;
    TEST_ASSERT(a == nullptr);

    int *pInt = new int;
    *pInt = 123;

    QIPtr<int> b(pInt), c(b);
    TEST_ASSERT(b == pInt);
    TEST_ASSERT(c == pInt);
    TEST_ASSERT(b == c);

    QIPtr<int> d(c);
    TEST_ASSERT(d == c);
    
    QIPtr<int> e;
    TEST_ASSERT(e == nullptr);

    e = d;
    TEST_ASSERT(e == pInt);
}

TEST_CASE(operator_set_compare)
{
    QIPtr<int> a, b;
    TEST_ASSERT(a == nullptr);
    TEST_ASSERT(!(a != nullptr));
    TEST_ASSERT(b == nullptr);
    TEST_ASSERT(!(b != nullptr));

    int *pInt = new int;
    *pInt = 123;

    a = pInt;
    TEST_ASSERT(a == pInt);
    TEST_ASSERT(!(a != pInt));
    TEST_ASSERT(a != b);
    TEST_ASSERT(!(a == b));

    b = a;
    TEST_ASSERT(a == b);
    TEST_ASSERT(!(a != b));

    a = nullptr;
    TEST_ASSERT(a == nullptr);
    TEST_ASSERT(!(a != nullptr));
    TEST_ASSERT(a != b);
    TEST_ASSERT(!(a == b));
}

TEST_CASE(operator_point_ref)
{
    int *pInt = new int;
    *pInt = 123;

    QIPtr<int> a(pInt);
    TEST_ASSERT(*a == 123);

    struct s
    {
        int x;
        int y;
    };

    s *pS = new s;
    pS->x = 1;
    pS->y = 2;

    QIPtr<s> b(pS);
    TEST_ASSERT(pS->x == 1);
    TEST_ASSERT(pS->y == 2);
}

int main()
{
#ifdef _MSC_VER
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    new int;

    QIPtr<int> a(new int[10]);

    return 0;
}

