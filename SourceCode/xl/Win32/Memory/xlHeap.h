//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlHeapMgr.h
//    Author:      Streamlet
//    Create Time: 2010-12-20
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLHEAP_H_7B115181_B9FB_4BCD_8E2C_2CDE8814D08A_INCLUDED__
#define __XLHEAP_H_7B115181_B9FB_4BCD_8E2C_2CDE8814D08A_INCLUDED__


#include <Windows.h>

namespace xl
{
    class Heap
    {
    public:
        Heap() :
            m_hHeap(NULL)
        {
            m_hHeap = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 0, 0);
        }

        ~Heap()
        {
            if (m_hHeap != NULL)
            {
                HeapDestroy(m_hHeap);
                m_hHeap = NULL;
            }
        }

    public:
        LPVOID Alloc(size_t nSize)
        {
            if (m_hHeap == NULL)
            {
                return NULL;
            }

            return HeapAlloc(m_hHeap, 0, nSize);
       }

        BOOL Free(LPVOID pMem)
        {
            if (m_hHeap == NULL)
            {
                return FALSE;
            }

            return HeapFree(m_hHeap, 0, pMem);
        }

    private:
        HANDLE m_hHeap;
    };

} // namespace xl

#endif // #ifndef __XLHEAP_H_7B115181_B9FB_4BCD_8E2C_2CDE8814D08A_INCLUDED__
