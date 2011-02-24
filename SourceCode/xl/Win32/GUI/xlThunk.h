//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlThunk.h
//    Author:      Streamlet
//    Create Time: 2010-12-20
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLTHUNK_H_41B69CAE_F597_427A_88C1_193B95C8AB06_INCLUDED__
#define __XLTHUNK_H_41B69CAE_F597_427A_88C1_193B95C8AB06_INCLUDED__


#include <Windows.h>
#include <xl/Win32/Memory/xlHeap.h>

namespace xl
{

    class Thunk
    {
    private:
#pragma pack(push,1)
        typedef struct _StdCallThunk
        {
            DWORD   m_mov;
            DWORD   m_this;
            BYTE    m_jmp;
            DWORD   m_relproc;

        } StdCallThunk;
#pragma pack(pop)

    private:
        static Heap m_sHeap;
        StdCallThunk *m_pThunk;

    public:
        Thunk()
            : m_pThunk(nullptr)
        {
            m_pThunk = (StdCallThunk *)m_sHeap.Alloc(sizeof(StdCallThunk));
            m_pThunk->m_mov     = 0x042444c7;
            m_pThunk->m_jmp     = 0xe9;
            m_pThunk->m_this    = 0;
            m_pThunk->m_relproc = 0;
        }

        ~Thunk()
        {
            if (m_pThunk != nullptr)
            {
                m_sHeap.Free(m_pThunk);
                m_pThunk = nullptr;
            }
        }

        template <typename T>
        void SetObject(const T *pObject)
        {
            m_pThunk->m_this = (DWORD)pObject;
        }

        void SetRealWndProc(WNDPROC pWndProc)
        {
            m_pThunk->m_relproc = (DWORD)pWndProc - ((DWORD)m_pThunk + sizeof(StdCallThunk));
        }

        WNDPROC GetThunkWndProc()
        {
            return (WNDPROC)m_pThunk;
        }
    };

    __declspec(selectany) Heap Thunk::m_sHeap;

} // namespace xl

#endif // #ifndef __XLTHUNK_H_41B69CAE_F597_427A_88C1_193B95C8AB06_INCLUDED__
