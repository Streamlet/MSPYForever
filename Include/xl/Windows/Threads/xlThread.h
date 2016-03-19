//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlThread.h
//    Author:      Streamlet
//    Create Time: 2011-11-02
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLTHREAD_H_7019B92A_520D_4235_8B24_9334EF47B92A_INCLUDED__
#define __XLTHREAD_H_7019B92A_520D_4235_8B24_9334EF47B92A_INCLUDED__


#include "../../Common/Meta/xlFunction.h"
#include "../../Common/Meta/xlAssert.h"
#include "../xlWin32Ver.h"
#include "xlCriticalSection.h"
#include <process.h>

namespace xl
{
    namespace Windows
    {
        template <typename ParamType = LPVOID>
        class Thread 
        {
        public:
            typedef Function<DWORD(HANDLE, ParamType)> ProcType;

        public:
            Thread() : m_hEventQuit(nullptr), m_hThread(nullptr), m_param()
            {
                m_hEventQuit = CreateEvent(nullptr, TRUE, FALSE, nullptr);
                m_hEventStopped = CreateEvent(nullptr, TRUE, TRUE, nullptr);
            }

            Thread(const Thread &that)
            {
                XL_ASSERT(false);
            }

#ifdef __XL_CPP11
            Thread(Thread &&that)
            {
                XL_ASSERT(false);
            }
#endif

            ~Thread()
            {
                Destroy();

                CloseHandle(m_hEventStopped);
                CloseHandle(m_hEventQuit);
            }

            Thread &operator = (const Thread &that)
            {
                XL_ASSERT(false);
                return *this;
            }

#ifdef __XL_CPP11
            Thread &operator = (Thread &&that)
            {
                XL_ASSERT(false);
                return *this;
            }
#endif

        public:
            bool Create(ProcType fnThreadProc, ParamType param, bool bSuspend = false)
            {
                XL_SCOPED_CRITICAL_SECTION(m_cs);

                Destroy();

                m_fnThreadProc = fnThreadProc;
                m_param = param;

                ResetEvent(m_hEventQuit);
                ResetEvent(m_hEventStopped);

                m_hThread = (HANDLE)_beginthreadex(nullptr, 0, StaticThreadProc, this, bSuspend ? CREATE_SUSPENDED : 0, nullptr);

                if (m_hThread == nullptr)
                {
                    SetEvent(m_hEventStopped);
                    return false;
                }

                return true;
            }

            bool Suspend()
            {
                XL_SCOPED_CRITICAL_SECTION(m_cs);

                if (m_hThread == nullptr)
                {
                    return false;
                }

                if (SuspendThread(m_hThread) == -1)
                {
                    return false;
                }

                return true;
            }

            bool Resume()
            {
                XL_SCOPED_CRITICAL_SECTION(m_cs);

                if (m_hThread == nullptr)
                {
                    return false;
                }

                if (ResumeThread(m_hThread) == -1)
                {
                    return false;
                }

                return true;
            }

            void NotifyStop()
            {
                SetEvent(m_hEventQuit);
            }

            bool Wait(DWORD dwTimeout = INFINITE)
            {
                DWORD dwTickCount = GetTickCount();

                if (WaitForSingleObject(m_hEventStopped, dwTimeout) != WAIT_OBJECT_0)
                {
                    return false;
                }

                DWORD dwTimeUsed = GetTickCount() - dwTickCount;

                if (dwTimeout != 0 && dwTimeout != INFINITE)
                {
                    if (dwTimeUsed < dwTimeout)
                    {
                        dwTimeout -= dwTimeUsed;
                    }
                    else
                    {
                        dwTimeout = 0;
                    }
                }

                if (WaitForSingleObject(m_hThread, dwTimeout) != WAIT_OBJECT_0)
                {
                    return false;
                }

                return true;
            }

            bool GetExitCode(DWORD *lpExitCode)
            {
                if (lpExitCode == nullptr)
                {
                    return false;
                }

                if (!GetExitCodeThread(m_hThread, lpExitCode))
                {
                    return false;
                }

                return true;
            }

            void Destroy()
            {
                NotifyStop();

                if (!Wait())
                {
                    return;
                }

                XL_SCOPED_CRITICAL_SECTION(m_cs);

                if (m_hThread == nullptr)
                {
                    CloseHandle(m_hThread);
                }

                m_fnThreadProc = NULL;
                m_param = ParamType();
            }

        private:
            static UINT CALLBACK StaticThreadProc(LPVOID lpParam)
            {
                return ((Thread *)lpParam)->ThreadProc();
            }

            DWORD ThreadProc()
            {
                DWORD dwResult = m_fnThreadProc(m_hEventQuit, m_param);
                SetEvent(m_hEventStopped);

                return dwResult;
            }

        private:
            HANDLE    m_hEventQuit;
            HANDLE    m_hEventStopped;

            CriticalSection m_cs;
            HANDLE    m_hThread;

            ProcType  m_fnThreadProc;
            ParamType m_param;
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLTHREAD_H_7019B92A_520D_4235_8B24_9334EF47B92A_INCLUDED__
