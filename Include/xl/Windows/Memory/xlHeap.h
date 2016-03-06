//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlHeapMgr.h
//    Author:      Streamlet
//    Create Time: 2010-12-20
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLHEAP_H_7B115181_B9FB_4BCD_8E2C_2CDE8814D08A_INCLUDED__
#define __XLHEAP_H_7B115181_B9FB_4BCD_8E2C_2CDE8814D08A_INCLUDED__


#include "../../Common/Meta/xlNonCopyable.h"
#include "../xlHandle.h"
#include "../xlWin32Ver.h"

namespace xl
{
    namespace Windows
    {
        struct HeapDestroyer
        {
            static bool CloseHandle(HANDLE hHandle)
            {
                return !!::HeapDestroy(hHandle);
            }
        };

        template <bool bManaged = true>
        class HeapT : public NonCopyable, public HandleT<bManaged, HeapDestroyer>
        {
        public:
            HeapT(HANDLE hHeap = nullptr) : HandleT(hHeap)
            {

            }

            ~HeapT()
            {

            }

        public:
            bool Create(DWORD dwOptions, DWORD_PTR dwInitialSize = 0, DWORD_PTR dwMaximumSize = 0)
            {
                m_hHeap = HeapCreate(dwOptions, dwInitialSize, dwMaximumSize);
                return IsValid();
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

        typedef HeapT<> Heap;
        typedef HeapT<false> HeapHandle;

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLHEAP_H_7B115181_B9FB_4BCD_8E2C_2CDE8814D08A_INCLUDED__
