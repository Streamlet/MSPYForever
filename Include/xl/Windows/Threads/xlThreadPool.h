//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlThreadPool.h
//    Author:      Streamlet
//    Create Time: 2011-11-02
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLTHREADPOOL_H_EF483C0F_09BB_436D_907C_DD8D0444D386_INCLUDED__
#define __XLTHREADPOOL_H_EF483C0F_09BB_436D_907C_DD8D0444D386_INCLUDED__


#include "../../Common/Containers/xlArray.h"
#include "../../Common/Containers/xlSet.h"
#include "../../Common/Meta/xlFunction.h"
#include "../../Common/Meta/xlNonCopyable.h"
#include "xlCriticalSection.h"
#include "xlThread.h"

namespace xl
{
    namespace Windows
    {
        template <typename ParamType = LPVOID>
        class ThreadPool : public NonCopyable
        {
        public:
            typedef Function<void(HANDLE, ParamType)> TaskType;

        public:
            ThreadPool() : m_bCreated(false), m_hEvent(NULL)
            {

            }

            ~ThreadPool()
            {
                Destroy();
            }

        public:
            bool Create(UINT nThreadCount = 4)
            {
                if (m_bCreated)
                {
                    return true;
                }

                Destroy();

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
                    if (!it->Create(Thread<>::ProcType(this, &ThreadPool::ThreadProc), nullptr))
                    {
                        return false;
                    }
                }

                m_bCreated = true;

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
                    it->Destroy();
                }

                m_csTaskLocker.Lock();
                m_setTasks.Clear();
                m_csTaskLocker.UnLock();

                m_arrThreads.Clear();

                if (m_hEvent != NULL)
                {
                    CloseHandle(m_hEvent);
                    m_hEvent = NULL;
                }

                m_bCreated = false;
            }

        private:
            struct TaskInfo
            {
                static UINT ms_nNextTaskInfoId;

                TaskType  fnTask;
                ParamType param;
                int       nPriority;
                HANDLE    hComplete;
                UINT      nTaskInfoId;

                TaskInfo(TaskType fnTask = NullThreadPoolTask,
                         ParamType param = ParamType(),
                         int nPriority = 0,
                         HANDLE hComplete = NULL) :
                         fnTask(fnTask),
                         param(param),
                         nPriority(nPriority),
                         hComplete(hComplete),
                         nTaskInfoId(ms_nNextTaskInfoId++)
                {

                }

                TaskInfo(const TaskInfo &that) :
                    fnTask(NullThreadPoolTask),
                    hComplete(NULL),
                    param(),
                    nPriority(that.nPriority),
                    nTaskInfoId(ms_nNextTaskInfoId++)
                {
                    *this = that;
                }

                TaskInfo &operator = (const TaskInfo &that)
                {
                    if (this == &that)
                    {
                        return *this;
                    }

                    this->fnTask = that.fnTask;
                    this->param = that.param;
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

                    if (this->nTaskInfoId < that.nTaskInfoId)
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

                    if (this->nTaskInfoId > that.nTaskInfoId)
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

                    if (this->nTaskInfoId < that.nTaskInfoId)
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

                    if (this->nTaskInfoId > that.nTaskInfoId)
                    {
                        return true;
                    }

                    return false;
                }
            };

        public:
            bool AddTask(TaskType fnTask, ParamType param, int nPriority = 0, HANDLE hCompleteEvent = NULL)
            {
                if (!m_bCreated)
                {
                    return false;
                }

                m_csTaskLocker.Lock();
                m_setTasks.Insert(TaskInfo(fnTask, param, nPriority, hCompleteEvent));
                m_csTaskLocker.UnLock();

                SetEvent(m_hEvent);

                return true;
            }

            bool RemoveTask(TaskType fnTask, ParamType param, int nPriority = 0, HANDLE hCompleteEvent = NULL)
            {
                if (!m_bCreated)
                {
                    return false;
                }

                bool bFound = false;

                m_csTaskLocker.Lock();

                for (auto it = m_setTasks.Begin(); it != m_setTasks.End(); )
                {
                    if (it->fnTask == fnTask
                        && it->param == param
                        && it->nPriority == nPriority
                        && it->hComplete == hCompleteEvent)
                    {
                        bFound = true;

                        it = m_setTasks.Delete(it);
                    }
                    else
                    {
                        ++it;
                    }
                }

                m_csTaskLocker.UnLock();

                return bFound;
            }

        private:
            DWORD ThreadProc(HANDLE hQuit, LPVOID lpParam)
            {
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

                    task.fnTask(hQuit, task.param);

                    if (task.hComplete != NULL)
                    {
                        SetEvent(task.hComplete);
                    }
                }

                return 0;
            }

            static void NullThreadPoolTask(HANDLE hQuit, ParamType param)
            {

            }

        private:
            Array<Thread<>> m_arrThreads;
            Set<TaskInfo>   m_setTasks;
            CriticalSection m_csTaskLocker;
            HANDLE          m_hEvent;
            bool            m_bCreated;
        };

        template <typename ParamType>
        __declspec(selectany) UINT ThreadPool<ParamType>::TaskInfo::ms_nNextTaskInfoId = 0;

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLTHREADPOOL_H_EF483C0F_09BB_436D_907C_DD8D0444D386_INCLUDED__
