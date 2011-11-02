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
    typedef xl::Function<DWORD (HANDLE, LPVOID)> ThreadCallback;

    class Thread : public NonCopyable
    {
    public:
        Thread() : m_hEventQuit(NULL), m_hThread(NULL), m_lpParam(nullptr)
        {

        }

        ~Thread()
        {
            Close();
        }

    public:
        bool Create(ThreadCallback fnThreadCallback, LPVOID lpParam)
        {
            if (m_hEventQuit != NULL)
            {
                return false;
            }

            m_hEventQuit = CreateEvent(NULL, TRUE, FALSE, NULL);

            if (m_hEventQuit == NULL)
            {
                return false;
            }

            m_hThread = (HANDLE)_beginthreadex(NULL, 0, StaticThreadProc, this, CREATE_SUSPENDED, NULL);

            if (m_hThread == NULL)
            {
                CloseHandle(m_hEventQuit);
                m_hEventQuit = NULL;

                return false;
            }

            m_fnThread = fnThreadCallback;
            m_lpParam = lpParam;

            ResumeThread(m_hThread);

            return true;
        }

        void NotifyStop()
        {
            if (m_hEventQuit == NULL)
            {
                return;
            }

            SetEvent(m_hEventQuit);
        }

        bool Wait(DWORD dwTimeout = INFINITE)
        {
            if (m_hEventQuit == NULL)
            {
                return true;
            }

            if (WaitForSingleObject(m_hThread, dwTimeout) != WAIT_OBJECT_0)
            {
                return false;
            }

            return true;
        }

        void Close()
        {
            if (!Wait())
            {
                return;
            }

            CloseHandle(m_hThread);
            CloseHandle(m_hEventQuit);

            m_fnThread = ThreadCallback(NullThreadProc);
            m_lpParam = nullptr;
            m_hThread = NULL;
            m_hEventQuit = NULL;
        }

    private:
        static UINT CALLBACK StaticThreadProc(LPVOID lpParam)
        {
            return ((Thread *)lpParam)->ThreadProc();
        }

        DWORD ThreadProc()
        {
            return m_fnThread(m_hEventQuit, m_lpParam);
        }

        static DWORD NullThreadProc(HANDLE hQuit, LPVOID lpParam)
        {
            return 0;
        }

    private:
        HANDLE m_hEventQuit;
        HANDLE m_hThread;
        ThreadCallback m_fnThread;
        LPVOID m_lpParam;
    };

} // namespace xl

#endif // #ifndef __XLTHREAD_H_7019B92A_520D_4235_8B24_9334EF47B92A_INCLUDED__
