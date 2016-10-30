//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlSort.h
//    Author:      Streamlet
//    Create Time: 2013-03-09
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLSORT_H_3810AA26_E81D_4108_9831_D3EBD08B4449_INCLUDED__
#define __XLSORT_H_3810AA26_E81D_4108_9831_D3EBD08B4449_INCLUDED__


#include "../../xlDef.h"
#include "../Memory/xlMemory.h"
#include "../Meta/xlFunction.h"

namespace xl
{
    namespace Sort
    {
        template <typename T>
        bool DirectComparaor(const T &t1, const T &t2)
        {
            return t1 < t2;
        }

        template <typename T>
        bool DereferencingComparaor(const T &t1, const T &t2)
        {
            return *ti < *t2;
        }
    
        template <typename T>
        void BubbleSort(T tData[], size_t nSize, xl::Function<bool (const T &, const T &)> fnComparor = DirectComparaor<T>)
        {
            for (size_t i = 0; i < nSize; ++i)
            {
                bool bExchanged = false;

                for (size_t j = 0; j < nSize - 1 - i; ++j)
                {
                    if (!fnComparor(tData[j],  tData[j + 1]))
                    {
                        Memory::Swap(tData[j], tData[j + 1]);
                        bExchanged = true;
                    }
                }

                if (!bExchanged)
                {
                    break;
                }
            }
        }

        template <typename T>
        void DoubleBubbleSort(T tData[], size_t nSize, xl::Function<bool (const T &, const T &)> fnComparor = DirectComparaor<T>)
        {
            size_t i = 0, j = nSize - 1;

            while (i < j - 1)
            {
                {
                    bool bExchanged = false;

                    for (size_t k = i; k < j; ++k)
                    {
                        if (!fnComparor(tData[k],  tData[k + 1]))
                        {
                            Memory::Swap(tData[k], tData[k + 1]);
                            bExchanged = true;
                        }
                    }

                    --j;

                    if (!bExchanged)
                    {
                        break;
                    }
                }

                {
                    bool bExchanged = false;

                    for (size_t k = j; k > i; --k)
                    {
                        if (!fnComparor(tData[k - 1],  tData[k]))
                        {
                            Memory::Swap(tData[k - 1], tData[k]);
                            bExchanged = true;
                        }
                    }

                    if (!bExchanged)
                    {
                        break;
                    }

                    ++i;
                }
            }
        }

        template <typename T>
        void InsertionSort(T tData[], size_t nSize, xl::Function<bool (const T &, const T &)> fnComparor = DirectComparaor<T>)
        {
            for (size_t i = 1; i < nSize; ++i)
            {
                T t = tData[i];
                size_t j = i;

                while (j > 0 && fnComparor(t, tData[j - 1]))
                {
                    tData[j] = tData[j - 1];
                    --j;
                }

                if (j != i)
                {
                    tData[j] = t;
                }
            }
        }

        template <typename T>
        void SelectionSort(T tData[], size_t nSize, xl::Function<int (const T &, const T &)> fnComparor = DirectComparaor<T>)
        {
            for (size_t i = 0; i < nSize; ++i)
            {
                size_t nMin = i;

                for (size_t j = i + 1; j < nSize; ++j)
                {
                    if (fnComparor(tData[j], tData[nMin]))
                    {
                        nMin = j;
                    }
                }

                if (nMin != i)
                {
                    Memory::Swap(tData[i], tData[nMin]);
                }
            }
        }

        template <typename T>
        void ShellSort(T tData[], size_t nSize, xl::Function<bool (const T &, const T &)> fnComparor = DirectComparaor<T>)
        {
            for (size_t gap = nSize / 2; gap > 0; gap /= 2)
            {
                for (size_t i = gap; i < nSize; ++i)
                {
                    T t = tData[i];
                    size_t j = i;

                    while (fnComparor(t, tData[j - gap]))
                    {
                        tData[j] = tData[j - gap];

                        if (j >= gap)
                        {
                            j -= gap;
                        }
                        else
                        {
                            break;
                        }
                    }

                    if (j != i)
                    {
                        tData[j] = t;
                    }
                }
            }
        }

        template <typename T>
        void HeapSort(T tData[], size_t nSize, xl::Function<bool (const T &, const T &)> fnComparor = DirectComparaor<T>)
        {
            // Build the heap (except the root element)

            for (size_t i = (nSize - 1) / 2; i > 0; --i)
            {
                size_t nMax = i;

                if (2 * i + 1 < nSize && fnComparor(tData[nMax], tData[2 * i + 1]))
                {
                    nMax = 2 * i + 1;
                }

                if (2 * i + 2 < nSize && fnComparor(tData[nMax], tData[2 * i + 2]))
                {
                    nMax = 2 * i + 2;
                }

                if (nMax != i)
                {
                    Memory::Swap(tData[i], tData[nMax]);
                }
            }

            for (size_t n = nSize; n > 1; --n)
            {
                // Adjust the heap

                for (size_t i = 0; i < n; )
                {
                    size_t nMax = i;

                    if (2 * i + 1 < n && fnComparor(tData[nMax], tData[2 * i + 1]))
                    {
                        nMax = 2 * i + 1;
                    }

                    if (2 * i + 2 < n && fnComparor(tData[nMax], tData[2 * i + 2]))
                    {
                        nMax = 2 * i + 2;
                    }

                    if (nMax != i)
                    {
                        Memory::Swap(tData[i], tData[nMax]);
                        i = nMax;
                    }
                    else
                    {
                        break;
                    }
                }
            
                // Move the root element to the last position
                Memory::Swap(tData[0], tData[n - 1]);
            }
        }

        template <typename T>
        void QuickSort(T tData[], size_t nSize, xl::Function<bool (const T &, const T &)> fnComparor = DirectComparaor<T>)
        {
            size_t i = 0, j = nSize - 1,  k = nSize / 2;

            while (i < k || k < j)
            {
                while (i < k)
                {
                    if (fnComparor(tData[k], tData[i]))
                    {
                        Memory::Swap(tData[k], tData[i]);
                        k = i++;
                        break;
                    }

                    ++i;
                }

                while (j > k)
                {
                    if (fnComparor(tData[j], tData[k]))
                    {
                        Memory::Swap(tData[j], tData[k]);
                        k = j--;
                        break;
                    }

                    --j;
                }
            }

            if (k > 1)
            {
                QuickSort(tData, k, fnComparor);
            }
            
            if (k + 2 < nSize)
            {
                QuickSort(tData + k + 1, nSize - k - 1, fnComparor);
            }
        }
    }
}

#endif // #ifndef __XLSORT_H_3810AA26_E81D_4108_9831_D3EBD08B4449_INCLUDED__
