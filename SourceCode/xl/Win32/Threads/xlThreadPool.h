//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlThreadPool.h
//    Author:      Streamlet
//    Create Time: 2011-11-02
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLTHREADPOOL_H_EF483C0F_09BB_436D_907C_DD8D0444D386_INCLUDED__
#define __XLTHREADPOOL_H_EF483C0F_09BB_436D_907C_DD8D0444D386_INCLUDED__


#include <xl/Meta/xlUtility.h>
#include <xl/Meta/xlFunction.h>
#include <xl/Containers/xlArray.h>
#include <xl/Win32/Threads/xlCriticalSection.h>
#include <xl/Win32/Threads/xlThread.h>

namespace xl
{
    typedef xl::Function<DWORD (HANDLE, LPVOID)> ThreadPoolTask;

    class ThreadPool : public NonCopyable
    {
    public:
        ThreadPool() : m_hEvent(NULL)
        {

        }

        ~ThreadPool()
        {
            Destroy();
        }

    public:
        bool Create(UINT nThreadCount)
        {
            m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

            if (m_hEvent == NULL)
            {
                return false;
            }

            if (!m_arrThreads.Empty())
            {
                return false;
            }

            m_arrThreads.Resize(nThreadCount);

            for (auto it = m_arrThreads.Begin(); it != m_arrThreads.End(); ++it)
            {
                if (!it->Create(ThreadCallback(this, &ThreadPool::ThreadProc), nullptr))
                {
                    Destroy();
                    return false;
                }
            }

            return true;
        }

        void Destroy()
        {
            for (auto it = m_arrThreads.Begin(); it != m_arrThreads.End(); ++it)
            {
                it->NotifyStop();
            }

            for (auto it = m_arrThreads.Begin(); it != m_arrThreads.End(); ++it)
            {
                it->Close();
            }

            m_arrTasks.Clear();
            m_arrThreads.Clear();

            if (m_hEvent != NULL)
            {
                CloseHandle(m_hEvent);
                m_hEvent = NULL;
            }
        }

    private:
        struct TaskInfo
        {
            ThreadPoolTask fnTask;
            LPVOID lpParam;

            TaskInfo(ThreadPoolTask fnTask = NullThreadPoolTask, LPVOID lpParam = nullptr) :
                fnTask(fnTask), lpParam(lpParam)
            {

            }

            TaskInfo(const TaskInfo &that) :
                fnTask(NullThreadPoolTask), lpParam(nullptr)
            {
                *this = that;
            }

            TaskInfo &operator = (const TaskInfo &that)
            {
                if (this == &that)
                {
                    return *this;
                }

                this->fnTask  = that.fnTask;
                this->lpParam = that.lpParam;

                return *this;
            }
        };

    public:
        bool AddTask(ThreadPoolTask fnTask, LPVOID lpParam)
        {
            if (m_hEvent == NULL)
            {
                return false;
            }

            m_csTaskLocker.Lock();
            m_arrTasks.PushBack(TaskInfo(fnTask, lpParam));
            m_csTaskLocker.UnLock();

            SetEvent(m_hEvent);

            return true;
        }

    private:
        DWORD ThreadProc(HANDLE hQuit, LPVOID lpParam)
        {
            DWORD dwRetCode = 0;

            while (true)
            {
                enum ThreadPoolEvents
                {
                    TPE_QUIT,
                    TPE_SIGNAL,
                    TPE_COUNT
                };

                HANDLE hHandles[TPE_COUNT] = { hQuit, m_hEvent };
                DWORD dwWaitResult = WaitForMultipleObjects(TPE_COUNT, hHandles, FALSE, INFINITE) - WAIT_OBJECT_0;

                if (dwWaitResult != TPE_SIGNAL)
                {
                    break;
                }

                m_csTaskLocker.Lock();

                TaskInfo task;

                if (!m_arrTasks.Empty())
                {
                    task = m_arrTasks[0];
                    m_arrTasks.PopFront();

                    if (m_arrTasks.Empty())
                    {
                        ResetEvent(m_hEvent);
                    }
                }

                m_csTaskLocker.UnLock();

                dwRetCode = task.fnTask(hQuit, task.lpParam);
            }

            return dwRetCode;
        }

        static DWORD NullThreadPoolTask(HANDLE hQuit, LPVOID lpParam)
        {
            return 0;
        }

    private:
        Array<Thread>   m_arrThreads;
        Array<TaskInfo> m_arrTasks;
        CriticalSection m_csTaskLocker;
        HANDLE          m_hEvent;
    };

} // namespace xl

#endif // #ifndef __XLTHREADPOOL_H_EF483C0F_09BB_436D_907C_DD8D0444D386_INCLUDED__
