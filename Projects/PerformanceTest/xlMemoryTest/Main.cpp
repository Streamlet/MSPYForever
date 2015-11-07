//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2015-10-27
//    Description: 
//
//------------------------------------------------------------------------------


#include "../PerformanceTest.h"
#include "../../../Include/xl/Common/Memory/xlMemory.h"

int main()
{
    int *p = new int[10];
    int *q = new int[10];
    memcpy(p, q, 10);

    using namespace std;
    using namespace xl;

    int *p1 = new int[1025];
    int *p2 = new int[1025];
    p1 = (int *)((char *)p1 + 1);
    p2 = (int *)((char *)p2 + 1);
    memset(p1, 0, 1024 * sizeof(int));

    SECTION_BEGIN(xlMemCopy1000000);
    PERFORMANCE_TEST_BEGIN(xlMemCopy1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        Memory::Copy(p2, p1, 1024 * sizeof(int));
    }
    PERFORMANCE_TEST_END(xlMemCopy1000000);
    SECTION_END();

    SECTION_BEGIN(memcpy1000000);
    PERFORMANCE_TEST_BEGIN(memcpy1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        memmove(p2, p1, 1024 * sizeof(int));
    }
    PERFORMANCE_TEST_END(memcpy1000000);
    SECTION_END();

    return 0;
}