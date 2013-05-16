//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlHandle.h
//    Author:      Streamlet
//    Create Time: 2013-05-15
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLHANDLE_H_39C0A466_0EB3_4D32_879B_1984722D3AED_INCLUDED__
#define __XLHANDLE_H_39C0A466_0EB3_4D32_879B_1984722D3AED_INCLUDED__


#include <Windows.h>

namespace xl
{
    template <bool bManaged = true>
    class HandleT
    {
    public:
        HandleT(HANDLE hHandle = nullptr) :
            m_hHandle(hHandle)
        {
        
        }

        ~HandleT()
        {
            if (bManaged)
            {
                Close();
            }
            else
            {
                Detach();
            }
        }

    public:
        HANDLE Attach(HANDLE hHandle)
        {
            HINTERNET hPrevious = m_hHandle;
            m_hHandle = hHandle;
            return hPrevious;
        }

        HANDLE Detach()
        {
            return Attach(nullptr);
        }

        bool Close()
        {
            if (m_hHandle == nullptr)
            {
                return true;
            }

            if (!CloseHandle(m_hHandle))
            {
                return false;
            }

            m_hHandle = nullptr;

            return true;
        }

    public:
        operator HANDLE() const
        {
            return m_hHandle;
        }

    
    protected:
        HANDLE m_hHandle;
    };

    typedef HandleT<> Handle;

} // namespace xl

#endif // #ifndef __XLHANDLE_H_39C0A466_0EB3_4D32_879B_1984722D3AED_INCLUDED__
