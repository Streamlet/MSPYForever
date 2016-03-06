//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlThunk.h
//    Author:      Streamlet
//    Create Time: 2010-12-20
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLTHUNK_H_41B69CAE_F597_427A_88C1_193B95C8AB06_INCLUDED__
#define __XLTHUNK_H_41B69CAE_F597_427A_88C1_193B95C8AB06_INCLUDED__


#include "../Memory/xlHeap.h"
#include "../xlWin32Ver.h"

namespace xl
{
    namespace Windows
    {
        template <typename T>
        class Thunk
        {
        private:

#ifdef _WIN64

#pragma pack(push, 1)
            typedef struct _StdCallThunk
            {
                USHORT  m_mov_rcx;  // mov rcx, pThis
                ULONG64 m_this;
                USHORT  m_mov_rax;  // mov rax, target
                ULONG64 m_relproc;
                USHORT  m_jmp;      // jmp target

            } StdCallThunk;
#pragma pack(pop)

#else

#pragma pack(push, 1)
            typedef struct _StdCallThunk
            {
                DWORD   m_mov;      // mov dword ptr [esp+4], pThis
                DWORD   m_this;
                BYTE    m_jmp;      // jmp pWndProc
                DWORD   m_relproc;

            } StdCallThunk;
#pragma pack(pop)

#endif

        private:
            static HANDLE ms_hThunkHeap;
            HeapHandle m_Heap;
            StdCallThunk *m_pThunk;

        public:
            Thunk()
                : m_pThunk(nullptr)
            {
                m_Heap.Attach(ms_hThunkHeap);

                if (!m_Heap.IsValid())
                {
                    m_Heap.Create(HEAP_CREATE_ENABLE_EXECUTE);
                }

                m_pThunk = (StdCallThunk *)m_Heap.Alloc(sizeof(StdCallThunk));

#ifdef _WIN64
                m_pThunk->m_mov_rcx = 0xb948;   // mov rcx, pThis
                m_pThunk->m_this = 0;
                m_pThunk->m_mov_rax = 0xb848;   // mov rax, target
                m_pThunk->m_relproc = 0;
                m_pThunk->m_jmp = 0xe0ff;       // jmp rax
#else
                m_pThunk->m_mov = 0x042444c7;   // mov dword ptr [esp+4], pThis
                m_pThunk->m_this = 0;
                m_pThunk->m_jmp = 0xe9;         // jmp pWndProc
                m_pThunk->m_relproc = 0;
#endif
            }

            ~Thunk()
            {
                if (m_pThunk != nullptr)
                {
                    m_Heap.Free(m_pThunk);
                    m_pThunk = nullptr;
                }

                m_Heap.Detach();
            }

            template <typename U>
            void SetObject(const U *pObject)
            {
#ifdef _WIN64
                m_pThunk->m_this = (ULONG64)pObject;
#else
                m_pThunk->m_this = (DWORD)pObject;
#endif
            }

            void SetRealProc(T pProc)
            {
#ifdef _WIN64
                m_pThunk->m_relproc = (ULONG64)pProc;
#else
                m_pThunk->m_relproc = (ULONG64)pProc - ((ULONG64)m_pThunk + sizeof(StdCallThunk));
#endif
            }

            T GetThunkProc()
            {
                return (T)m_pThunk;
            }
        };

        template <typename T>
        __declspec(selectany) HANDLE Thunk<T>::ms_hThunkHeap = nullptr;

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLTHUNK_H_41B69CAE_F597_427A_88C1_193B95C8AB06_INCLUDED__
