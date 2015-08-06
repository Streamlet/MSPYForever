//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlSortTest.cpp
//    Author:      Streamlet
//    Create Time: 2013-03-09
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------


#include "../../../Include/xl/Common/Algorithm/xlSort.h"
#include "../../../Include/xl/AppHelper/xlUnitTest.h"

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        int a[] = { 1, 3, 4, 2, 6, 7, 8, 5, 0, 9 };
        Sort::BubbleSort(a, 10);
        XL_TEST_ASSERT(a[0] <= a[1]);
        XL_TEST_ASSERT(a[1] <= a[2]);
        XL_TEST_ASSERT(a[2] <= a[3]);
        XL_TEST_ASSERT(a[3] <= a[4]);
        XL_TEST_ASSERT(a[4] <= a[5]);
        XL_TEST_ASSERT(a[5] <= a[6]);
        XL_TEST_ASSERT(a[6] <= a[7]);
        XL_TEST_ASSERT(a[7] <= a[8]);
        XL_TEST_ASSERT(a[8] <= a[9]);
    }

    XL_TEST_CASE()
    {
        int a[] = { 1, 3, 4, 2, 6, 7, 8, 5, 0, 9 };
        Sort::DoubleBubbleSort(a, 10);
        XL_TEST_ASSERT(a[0] <= a[1]);
        XL_TEST_ASSERT(a[1] <= a[2]);
        XL_TEST_ASSERT(a[2] <= a[3]);
        XL_TEST_ASSERT(a[3] <= a[4]);
        XL_TEST_ASSERT(a[4] <= a[5]);
        XL_TEST_ASSERT(a[5] <= a[6]);
        XL_TEST_ASSERT(a[6] <= a[7]);
        XL_TEST_ASSERT(a[7] <= a[8]);
        XL_TEST_ASSERT(a[8] <= a[9]);
    }

    XL_TEST_CASE()
    {
        int a[] = { 1, 3, 4, 2, 6, 7, 8, 5, 0, 9 };
        Sort::InsertionSort(a, 10);
        XL_TEST_ASSERT(a[0] <= a[1]);
        XL_TEST_ASSERT(a[1] <= a[2]);
        XL_TEST_ASSERT(a[2] <= a[3]);
        XL_TEST_ASSERT(a[3] <= a[4]);
        XL_TEST_ASSERT(a[4] <= a[5]);
        XL_TEST_ASSERT(a[5] <= a[6]);
        XL_TEST_ASSERT(a[6] <= a[7]);
        XL_TEST_ASSERT(a[7] <= a[8]);
        XL_TEST_ASSERT(a[8] <= a[9]);
    }

    XL_TEST_CASE()
    {
        int a[] = { 1, 3, 4, 2, 6, 7, 8, 5, 0, 9 };
        Sort::SelectionSort(a, 10);
        XL_TEST_ASSERT(a[0] <= a[1]);
        XL_TEST_ASSERT(a[1] <= a[2]);
        XL_TEST_ASSERT(a[2] <= a[3]);
        XL_TEST_ASSERT(a[3] <= a[4]);
        XL_TEST_ASSERT(a[4] <= a[5]);
        XL_TEST_ASSERT(a[5] <= a[6]);
        XL_TEST_ASSERT(a[6] <= a[7]);
        XL_TEST_ASSERT(a[7] <= a[8]);
        XL_TEST_ASSERT(a[8] <= a[9]);
    }

    XL_TEST_CASE()
    {
        int a[] = { 1, 3, 4, 2, 6, 7, 8, 5, 0, 9 };
        Sort::ShellSort(a, 10);
        XL_TEST_ASSERT(a[0] <= a[1]);
        XL_TEST_ASSERT(a[1] <= a[2]);
        XL_TEST_ASSERT(a[2] <= a[3]);
        XL_TEST_ASSERT(a[3] <= a[4]);
        XL_TEST_ASSERT(a[4] <= a[5]);
        XL_TEST_ASSERT(a[5] <= a[6]);
        XL_TEST_ASSERT(a[6] <= a[7]);
        XL_TEST_ASSERT(a[7] <= a[8]);
        XL_TEST_ASSERT(a[8] <= a[9]);
    }
 
    XL_TEST_CASE()
    {
        int a[] = { 1, 3, 4, 2, 6, 7, 8, 5, 0, 9 };
        Sort::HeapSort(a, 10);
        XL_TEST_ASSERT(a[0] <= a[1]);
        XL_TEST_ASSERT(a[1] <= a[2]);
        XL_TEST_ASSERT(a[2] <= a[3]);
        XL_TEST_ASSERT(a[3] <= a[4]);
        XL_TEST_ASSERT(a[4] <= a[5]);
        XL_TEST_ASSERT(a[5] <= a[6]);
        XL_TEST_ASSERT(a[6] <= a[7]);
        XL_TEST_ASSERT(a[7] <= a[8]);
        XL_TEST_ASSERT(a[8] <= a[9]);
    }
    
    XL_TEST_CASE()
    {
        int a[] = { 1, 3, 4, 2, 6, 7, 8, 5, 0, 9 };
        Sort::QuickSort(a, 10);
        XL_TEST_ASSERT(a[0] <= a[1]);
        XL_TEST_ASSERT(a[1] <= a[2]);
        XL_TEST_ASSERT(a[2] <= a[3]);
        XL_TEST_ASSERT(a[3] <= a[4]);
        XL_TEST_ASSERT(a[4] <= a[5]);
        XL_TEST_ASSERT(a[5] <= a[6]);
        XL_TEST_ASSERT(a[6] <= a[7]);
        XL_TEST_ASSERT(a[7] <= a[8]);
        XL_TEST_ASSERT(a[8] <= a[9]);
    }
}
