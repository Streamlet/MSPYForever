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

TEST_CASE(ctor_copy)
{
    RBTree<int> a;
    TEST_ASSERT(a.Size() == 0);

    RBTree<int> b(a);
    TEST_ASSERT(b.Size() == 0);

    a.Insert(1);
    a.Insert(2);
    RBTree<int> c(a);
    TEST_ASSERT(c.Size() == 2);
    TEST_ASSERT(*c.Begin() == 1);
    TEST_ASSERT(*c.ReverseBegin() == 2);
}

TEST_CASE(operator_set)
{
    RBTree<int> a;
    TEST_ASSERT(a.Size() == 0);

    RBTree<int> b;
    b = a;
    TEST_ASSERT(b.Size() == 0);

    a.Insert(1);
    a.Insert(2);
    RBTree<int> c;
    c = a;
    TEST_ASSERT(c.Size() == 2);
    TEST_ASSERT(*a.Begin() == 1);
    TEST_ASSERT(*++a.Begin() == 2);
}

TEST_CASE(operator_equal)
{
    RBTree<int> a;
    TEST_ASSERT(a.Size() == 0);

    RBTree<int> b;
    b = a;
    TEST_ASSERT(b == a);
    TEST_ASSERT(!(b != a));

    a.Insert(1);
    a.Insert(2);
    TEST_ASSERT(b != a);
    TEST_ASSERT(!(b == a));

    RBTree<int> c(a);
    TEST_ASSERT(c == a);
    TEST_ASSERT(!(c != a));

    b.Insert(1);
    b.Insert(2);
    TEST_ASSERT(b == a);
    TEST_ASSERT(!(b != a));
    TEST_ASSERT(b == c);
    TEST_ASSERT(!(b != c));
}

TEST_CASE(method_size)
{
    RBTree<int> a;
    TEST_ASSERT(a.Size() == 0);
    TEST_ASSERT(a.Empty() == true);

    a.Insert(10);
    TEST_ASSERT(a.Size() == 1);
    TEST_ASSERT(a.Empty() == false);

    a.Insert(20);
    a.Insert(30);
    a.Insert(40);
    a.Insert(50);
    TEST_ASSERT(a.Size() == 5);
    TEST_ASSERT(a.Empty() == false);
}

TEST_CASE(method_insert_delete)
{
    RBTree<int> a;
    
    a.Insert(2);
    a.Insert(6);
    a.Insert(4);
    a.Insert(3);
    a.Insert(5);
    a.Insert(1);

    RBTree<int>::Iterator it = a.Begin();

    TEST_ASSERT(*it == 1);

    ++it;
    TEST_ASSERT(*it == 2);

    ++it;
    TEST_ASSERT(*it == 3);

    ++it;
    TEST_ASSERT(*it == 4);

    ++it;
    TEST_ASSERT(*it == 5);

    ++it;
    TEST_ASSERT(*it == 6);

    ++it;
    TEST_ASSERT(it == a.End());
}

TEST_CASE(method_find)
{
    RBTree<int> a;

    a.Insert(2);
    a.Insert(6);
    a.Insert(4);
    a.Insert(3);
    a.Insert(5);
    a.Insert(1);

    RBTree<int>::Iterator it = a.Find(5);

    TEST_ASSERT(*it == 5);

    RBTree<int>::Iterator it2 = it;

    ++it2;
    TEST_ASSERT(*it2 == 6);

    ++it2;
    TEST_ASSERT(it2 == a.End());
}

int main()
{
    return 0;
}

