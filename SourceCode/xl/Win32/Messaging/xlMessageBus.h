//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMessageBus.h
//    Author:      Streamlet
//    Create Time: 2011-11-01
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLMESSAGEBUS_H_AAE36D41_9C3A_48F0_8316_7746219BCC1A_INCLUDED__
#define __XLMESSAGEBUS_H_AAE36D41_9C3A_48F0_8316_7746219BCC1A_INCLUDED__


#include <xl/Meta/xlUtility.h>
#include <xl/Meta/xlFunction.h>
#include <xl/Containers/xlArray.h>
#include <xl/Containers/xlMap.h>
#include <xl/Win32/Memory/xlSafeSmartPtr.h>
#include <xl/Win32/Threads/xlThreadPool.h>
#include <xl/Win32/Threads/xlCriticalSection.h>
#include <xl/Win32/xlWin32Ver.h>
#include <Windows.h>

namespace xl
{
    template <typename MsgType = UINT, typename ParamType = LPVOID>
    class MessageBus : public NonCopyable
    {
    public:
        typedef xl::Function<void (HANDLE, MsgType, ParamType)> HandlerType;

    public:
        MessageBus() : m_bStarted(false)
        {

        }

        ~MessageBus()
        {
            Stop();
        }

    public:
        bool Start(UINT nThreadCount = 4)
        {
            if (m_bStarted)
            {
                return true;
            }

            Stop();

            if (!m_tpTaskDispatcher.Create(nThreadCount))
            {
                return false;
            }

            if (!m_tpTaskExecuter.Create(nThreadCount))
            {
                return false;
            }

            m_bStarted = true;

            return true;
        }

        void Stop()
        {
            m_tpTaskDispatcher.Destroy();
            m_tpTaskExecuter.Destroy();
            m_mapHandlers.Clear();
            m_bStarted = false;
        }

    private:
        struct MessageInfo
        {
            MsgType   message;
            ParamType param;
            int       nPriority;

            MessageInfo(MsgType message = MsgType(), ParamType param = ParamType(), int nPriority = 0) :
                message(message), param(param), nPriority(nPriority)
            {

            }
        };

        struct TaskInfo
        {
            HandlerType handler;
            MsgType     message;
            ParamType   param;

            TaskInfo(HandlerType handler, MsgType message = MsgType(), ParamType param = ParamType()):
                handler(handler), message(message), param(param)
            {

            }
        };

        typedef SafeSharedPtr<MessageInfo> DispatcherThreadPoolParamType;
        typedef SafeSharedPtr<TaskInfo> ExecuterThreadPoolParamType;
        typedef ThreadPool<DispatcherThreadPoolParamType> DispatcherThreadPoolType;
        typedef ThreadPool<ExecuterThreadPoolParamType> ExecuterThreadPoolType;
        typedef Array<HandlerType> HandlerList;
        typedef Map<MsgType, HandlerList>   HandlerMap;

    private:
        DispatcherThreadPoolType m_tpTaskDispatcher;
        ExecuterThreadPoolType   m_tpTaskExecuter;
        bool                     m_bStarted;
        HandlerMap               m_mapHandlers;
        CriticalSection          m_csHandlersLocker;

    public:
        bool Register(MsgType nMessageId, HandlerType fnMessageHandler)
        {
            if (!m_bStarted)
            {
                return false;
            }

            m_csHandlersLocker.Lock();
            m_mapHandlers[nMessageId].PushBack(fnMessageHandler);
            m_csHandlersLocker.UnLock();

            return true;
        }

        bool Unregister(MsgType nMessageId, HandlerType fnMessageHandler)
        {
            if (!m_bStarted)
            {
                return false;
            }

            bool bFound = false;

            m_csHandlersLocker.Lock();

            auto itHandlers = m_mapHandlers.Find(nMessageId);

            if (itHandlers != m_mapHandlers.End())
            {
                for (auto it = itHandlers->Value.Begin(); ir != itHandlers->Value.End(); )
                {
                    if (*it == fnMessageHandler)
                    {
                        it = itHandlers->Value.Delete(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
            }

            m_csHandlersLocker.UnLock();

            return bFound;
        }

    public:
        bool Notify(MsgType message, ParamType param, int nPriority = 0)
        {
            if (!m_bStarted)
            {
                return false;
            }

            m_tpTaskDispatcher.AddTask(DispatcherThreadPoolType::TaskType(this, &MessageBus::Dispatch),
                                       DispatcherThreadPoolParamType(new MessageInfo(message, param, nPriority)),
                                       nPriority);

            return true;
        }

    private:
        void Dispatch(HANDLE hQuit, DispatcherThreadPoolParamType param)
        {
            HandlerList handlers;

            m_csHandlersLocker.Lock();

            auto itHandlers = m_mapHandlers.Find(param->message);

            if (itHandlers != m_mapHandlers.End())
            {
                handlers = itHandlers->Value;
            }

            m_csHandlersLocker.UnLock();

            for (auto it = handlers.Begin(); it != handlers.End(); ++it)
            {
                m_tpTaskExecuter.AddTask(ExecuterThreadPoolType::TaskType(this, &MessageBus::Execute),
                                         ExecuterThreadPoolParamType(new TaskInfo(*it, param->message, param->param)),
                                         param->nPriority);
            }
        }

        void Execute(HANDLE hQuit, ExecuterThreadPoolParamType param)
        {
            param->handler(hQuit, param->message, param->param);
        }

    private:
        static void NullMessageBusHandler(HANDLE, MsgType, ParamType)
        {

        }
    };
}

#endif // #ifndef __XLMESSAGEBUS_H_AAE36D41_9C3A_48F0_8316_7746219BCC1A_INCLUDED__
