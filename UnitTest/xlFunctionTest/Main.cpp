//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2011-01-15
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Test/xlUnitTest.h>
#include <xl/Meta/xlFunction.h>
#include <stdio.h>

using namespace xl;

void voidfun0()
{
    printf("%s invoked\n", __FUNCTION__);
}

void voidfun1(int)
{
    printf("%s invoked\n", __FUNCTION__);
}

int intfun0()
{
    printf("%s invoked\n", __FUNCTION__);
    return -1;
}

int intfun1(int n)
{
    printf("%s invoked\n", __FUNCTION__);
    return n + 1;
}

struct _voidfunctor0
{
    void operator()()
    {
        printf("%s invoked\n", __FUNCTION__);
    }

} voidfunctor0;

struct _voidfunctor1
{
    void operator()(int)
    {
        printf("%s invoked\n", __FUNCTION__);
    }

} voidfunctor1;

struct _intfunctor0
{
    int operator()()
    {
        printf("%s invoked\n", __FUNCTION__);
        return -2;
    }

} intfunctor0;

struct _intfunctor1
{
    int operator()(int n)
    {
        printf("%s invoked\n", __FUNCTION__);
        return n + 2;
    }

} intfunctor1;

struct Test
{
    void voidmem0()
    {
        printf("%s invoked\n", __FUNCTION__);
    }

    void voidmem1(int)
    {
        printf("%s invoked\n", __FUNCTION__);
    }

    int intmem0()
    {
        printf("%s invoked\n", __FUNCTION__);
        return -3;
    }

    int intmem1(int n)
    {
        printf("%s invoked\n", __FUNCTION__);
        return n + 3;
    }

} test;

XL_TEST_CASE()
{
    Function<void ()>    void0_fun(&voidfun0);
    Function<void ()>    void0_fun_(voidfun0);
    Function<void ()>    void0_functor(voidfunctor0);
    Function<void ()>    void0_memfun(&test, &Test::voidmem0);
    Function<void (int)> void1_fun(&voidfun1);
    Function<void (int)> void1_fun_(voidfun1);
    Function<void (int)> void1_functor(voidfunctor1);
    Function<void (int)> void1_memfun(&test, &Test::voidmem1);
    Function<int  ()>    int0_fun(&intfun0);
    Function<int  ()>    int0_fun_(intfun0);
    Function<int  ()>    int0_functor(intfunctor0);
    Function<int  ()>    int0_memfun(&test, &Test::intmem0);
    Function<int  (int)> int1_fun(&intfun1);
    Function<int  (int)> int1_fun_(intfun1);
    Function<int  (int)> int1_functor(intfunctor1);
    Function<int  (int)> int1_memfun(&test, &Test::intmem1);

    void0_fun();
    void0_fun_();
    void0_functor();
    void0_memfun();
    void1_fun(0);
    void1_fun_(0);
    void1_functor(0);
    void1_memfun(0);
    XL_TEST_ASSERT(int0_fun() == -1);
    XL_TEST_ASSERT(int0_fun_() == -1);
    XL_TEST_ASSERT(int0_functor() == -2);
    XL_TEST_ASSERT(int0_memfun() == -3);
    XL_TEST_ASSERT(int1_fun(0) == 1);
    XL_TEST_ASSERT(int1_fun_(0) == 1);
    XL_TEST_ASSERT(int1_functor(0) == 2);
    XL_TEST_ASSERT(int1_memfun(0) == 3);

}

void __cdecl f1(int)
{

}

void __stdcall f2(int)
{

}

template<typename F>
void call(F f ) { return f(); }

void __cdecl f() { printf("cdecl\n"); }
void __stdcall g() { printf("stdcall\n"); }

int main()
{
    call(&f);
    call(&g);

    return 0;
}
