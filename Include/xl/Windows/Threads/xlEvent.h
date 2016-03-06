//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlEvent.h
//    Author:      Streamlet
//    Create Time: 2013-05-15
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLEVENT_H_7BC8461C_EA45_496E_B383_023E9D4FFCD7_INCLUDED__
#define __XLEVENT_H_7BC8461C_EA45_496E_B383_023E9D4FFCD7_INCLUDED__


#include "../xlHandle.h"
#include "../xlWin32Ver.h"

namespace xl
{
    namespace Windows
    {
        class Event : public Handle
        {
        public:
            Event()
            {

            }

            ~Event()
            {

            }

        public:
            bool Create(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCTSTR lpName)
            {
                m_hHandle = CreateEvent(lpEventAttributes, bManualReset, bInitialState, lpName);

                if (m_hHandle == nullptr)
                {
                    return false;
                }

                return true;
            }

            bool Open(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCTSTR lpName)
            {
                m_hHandle = OpenEvent(dwDesiredAccess, bInheritHandle, lpName);

                if (m_hHandle == nullptr)
                {
                    return false;
                }

                return true;
            }

            bool Reset()
            {
                if (!ResetEvent(m_hHandle))
                {
                    return false;
                }

                return true;
            }

            bool Set()
            {
                if (!SetEvent(m_hHandle))
                {
                    return false;
                }

                return true;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLEVENT_H_7BC8461C_EA45_496E_B383_023E9D4FFCD7_INCLUDED__
