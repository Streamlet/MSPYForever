//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlThread.h
//    Author:      Streamlet
//    Create Time: 2011-11-02
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLTHREAD_H_7019B92A_520D_4235_8B24_9334EF47B92A_INCLUDED__
#define __XLTHREAD_H_7019B92A_520D_4235_8B24_9334EF47B92A_INCLUDED__


#include <xl/Meta/xlUtility.h>
#include <xl/Meta/xlFunction.h>
#include <xl/Win32/xlWin32Ver.h>
#include <Windows.h>
#include <process.h>

namespace xl
{
    template <typename ParamType = LPVOID>
    class Thread : public NonCopyable
    {
    public:
        typedef xl::Function<DWORD (HANDLE, ParamType)> ProcType;

    public:
        Thread() : m_hEventQuit(NULL), m_hThread(NULL), m_bCreated(false), m_param()
        {

        }

        ~Thread()
        {
            Destroy();
        }

    public:
        bool Create(ProcType fnThreadProc, ParamType param)
        {
            if (m_bCreated)
            {
                return true;
            }

            Destroy();

            m_hEventQuit = CreateEvent(NULL, TRUE, FALSE, NULL);

            if (m_hEventQuit == NULL)
            {
                return false;
            }

            m_fnThreadProc = fnThreadProc;
            m_param        = param;

            m_hThread = (HANDLE)_beginthreadex(NULL, 0, StaticThreadProc, this, 0, NULL);

            if (m_hThread == NULL)
            {
                return false;
            }

            return true;
        }

        void NotifyStop()
        {
            if (m_bCreated)
            {
                SetEvent(m_hEventQuit);
            }
        }

        bool Wait(DWORD dwTimeout = INFINITE)
        {
            if (!m_bCreated)
            {
                return true;
            }

            if (WaitForSingleObject(m_hThread, dwTimeout) != WAIT_OBJECT_0)
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

            CloseHandle(m_hThread);
            CloseHandle(m_hEventQuit);

            m_fnThreadProc = NullThreadProc;
            m_param        = nullptr;
            m_hThread      = NULL;
            m_hEventQuit   = NULL;
            m_bCreated     = false;
        }

    private:
        static UINT CALLBACK StaticThreadProc(LPVOID lpParam)
        {
            return ((Thread *)lpParam)->ThreadProc();
        }

        DWORD ThreadProc()
        {
            return m_fnThreadProc(m_hEventQuit, m_param);
        }

        static DWORD NullThreadProc(HANDLE hQuit, ParamType param)
        {
            return 0;
        }

    private:
        HANDLE    m_hEventQuit;
        HANDLE    m_hThread;
        bool      m_bCreated;
        ProcType  m_fnThreadProc;
        ParamType m_param;
    };

} // namespace xl

#endif // #ifndef __XLTHREAD_H_7019B92A_520D_4235_8B24_9334EF47B92A_INCLUDED__
