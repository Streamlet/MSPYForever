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
#include <xl/Containers/xlSet.h>
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

            m_setTasks.Clear();
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
            static UINT ms_nCount;

            ThreadPoolTask fnTask;
            LPVOID         lpParam;
            HANDLE         hComplete;
            int    nPriority;
            UINT   nCount;

            TaskInfo(ThreadPoolTask fnTask = NullThreadPoolTask, LPVOID lpParam = nullptr, HANDLE hComplete = NULL, int nPriority = 0) :
                fnTask(fnTask), lpParam(lpParam), hComplete(hComplete), nPriority(nPriority), nCount(++ms_nCount)
            {

            }

            TaskInfo(const TaskInfo &that) :
                fnTask(NullThreadPoolTask), lpParam(nullptr), hComplete(NULL), nPriority(that.nPriority), nCount(++ms_nCount)
            {
                *this = that;
            }

            TaskInfo &operator = (const TaskInfo &that)
            {
                if (this == &that)
                {
                    return *this;
                }

                this->fnTask    = that.fnTask;
                this->lpParam   = that.lpParam;
                this->hComplete = that.hComplete;
                this->nPriority = that.nPriority;

                return *this;
            }

            bool operator == (const TaskInfo &that) const
            {
                if (this == &that)
                {
                    return true;
                }

                return false;
            }

            bool operator != (const TaskInfo &that) const
            {
                if (this == &that)
                {
                    return false;
                }

                return true;
            }

            bool operator < (const TaskInfo &that) const
            {
                if (this == &that)
                {
                    return false;
                }

                if (this->nPriority > that.nPriority)
                {
                    return true;
                }

                if (this->nCount < that.nCount)
                {
                    return true;
                }
                
                return false;
            }

            bool operator > (const TaskInfo &that) const
            {
                if (this == &that)
                {
                    return false;
                }

                if (this->nPriority < that.nPriority)
                {
                    return true;
                }

                if (this->nCount > that.nCount)
                {
                    return true;
                }

                return false;
            }

            bool operator <= (const TaskInfo &that) const
            {
                if (this == &that)
                {
                    return true;
                }

                if (this->nPriority > that.nPriority)
                {
                    return true;
                }

                if (this->nCount < that.nCount)
                {
                    return true;
                }

                return false;
            }

            bool operator >= (const TaskInfo &that) const
            {
                if (this == &that)
                {
                    return true;
                }

                if (this->nPriority < that.nPriority)
                {
                    return true;
                }

                if (this->nCount > that.nCount)
                {
                    return true;
                }

                return false;
            }
        };

    public:
        bool AddTask(ThreadPoolTask fnTask, LPVOID lpParam, int nPriority = 0, HANDLE hCompleteEvent = NULL)
        {
            if (m_hEvent == NULL)
            {
                return false;
            }

            m_csTaskLocker.Lock();
            m_setTasks.Insert(TaskInfo(fnTask, lpParam, hCompleteEvent, nPriority));
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

                if (!m_setTasks.Empty())
                {
                    auto it = m_setTasks.Begin();
                    task = *it;
                    m_setTasks.Delete(it);

                    if (m_setTasks.Empty())
                    {
                        ResetEvent(m_hEvent);
                    }
                }

                m_csTaskLocker.UnLock();

                if (task.hComplete != NULL)
                {
                    ResetEvent(task.hComplete);
                }

                dwRetCode = task.fnTask(hQuit, task.lpParam);

                if (task.hComplete != NULL)
                {
                    SetEvent(task.hComplete);
                }
            }

            return dwRetCode;
        }

        static DWORD NullThreadPoolTask(HANDLE hQuit, LPVOID lpParam)
        {
            return 0;
        }

    private:
        Array<Thread>   m_arrThreads;
        Set<TaskInfo>   m_setTasks;
        CriticalSection m_csTaskLocker;
        HANDLE          m_hEvent;
    };

    __declspec(selectany) UINT ThreadPool::TaskInfo::ms_nCount = 0;

} // namespace xl

#endif // #ifndef __XLTHREADPOOL_H_EF483C0F_09BB_436D_907C_DD8D0444D386_INCLUDED__
