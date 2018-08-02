//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMessageBus.h
//    Author:      Streamlet
//    Create Time: 2011-11-01
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLMESSAGEBUS_H_AAE36D41_9C3A_48F0_8316_7746219BCC1A_INCLUDED__
#define __XLMESSAGEBUS_H_AAE36D41_9C3A_48F0_8316_7746219BCC1A_INCLUDED__


#include "../../Common/Containers/xlArray.h"
#include "../../Common/Containers/xlMap.h"
#include "../../Common/Meta/xlFunction.h"
#include "../../Common/Meta/xlNonCopyable.h"
#include "../Memory/xlSafeSmartPtr.h"
#include "../Threads/xlCriticalSection.h"
#include "../Threads/xlThreadPool.h"
#include "../xlWin32Ver.h"

namespace xl
{
    namespace Windows
    {
        template <typename MsgType = UINT, typename ParamType = LPVOID>
        class MessageBus : public NonCopyable
        {
        public:
            typedef Function<void(HANDLE, MsgType, ParamType)> HandlerType;

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

                if (!m_tpTaskDispatcher.Create())
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

                m_csHandlersLocker.Lock();

                for (auto itMsg = m_mapHandlers.Begin(); itMsg != m_mapHandlers.End(); ++itMsg)
                {
                    for (auto itHandler = itMsg->Value.Begin(); itHandler != itMsg->Value.End(); ++itHandler)
                    {
                        CloseHandle(itHandler->hEvent);
                    }
                }

                m_mapHandlers.Clear();

                m_csHandlersLocker.UnLock();

                m_bStarted = false;
            }

        private:
            struct HandlerInfo
            {
                HandlerType fnHandler;
                HANDLE hEvent;

                HandlerInfo(HandlerType fnHandler = NullMessageBusHandler, HANDLE hEvent = NULL) :
                    fnHandler(fnHandler), hEvent(hEvent)
                {

                }
            };

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
                HandlerInfo handler;
                MsgType     message;
                ParamType   param;

                TaskInfo(HandlerInfo handler, MsgType message = MsgType(), ParamType param = ParamType()) :
                    handler(handler), message(message), param(param)
                {

                }
            };

            typedef SafeSharedPtr<MessageInfo> DispatcherThreadPoolParamType;
            typedef SafeSharedPtr<TaskInfo> ExecuterThreadPoolParamType;
            typedef ThreadPool<DispatcherThreadPoolParamType> DispatcherThreadPoolType;
            typedef ThreadPool<ExecuterThreadPoolParamType> ExecuterThreadPoolType;
            typedef Array<HandlerInfo> HandlerList;
            typedef Map<MsgType, HandlerList> HandlerMap;

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

                HANDLE hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

                if (hEvent == NULL)
                {
                    return false;
                }

                m_csHandlersLocker.Lock();
                m_mapHandlers[nMessageId].PushBack(HandlerInfo(fnMessageHandler, hEvent));
                m_csHandlersLocker.UnLock();

                return true;
            }

            bool Unregister(MsgType nMessageId, HandlerType fnMessageHandler, bool bWait = true)
            {
                if (!m_bStarted)
                {
                    return false;
                }

                bool bFound = false;
                HANDLE hEvent = NULL;

                m_csHandlersLocker.Lock();

                auto itHandlers = m_mapHandlers.Find(nMessageId);

                if (itHandlers != m_mapHandlers.End())
                {
                    for (auto it = itHandlers->Value.Begin(); it != itHandlers->Value.End(); )
                    {
                        if (it->fnHandler == fnMessageHandler)
                        {
                            hEvent = it->hEvent;
                            it = itHandlers->Value.Delete(it);
                        }
                        else
                        {
                            ++it;
                        }
                    }
                }

                m_csHandlersLocker.UnLock();

                if (hEvent != NULL)
                {
                    if (bWait)
                    {
                        WaitForSingleObject(hEvent, INFINITE);
                    }

                    CloseHandle(hEvent);
                }

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
                        param->nPriority,
                        it->hEvent);
                }
            }

            void Execute(HANDLE hQuit, ExecuterThreadPoolParamType param)
            {
                param->handler.fnHandler(hQuit, param->message, param->param);
            }

        private:
            static void NullMessageBusHandler(HANDLE hQuit, MsgType message, ParamType param)
            {

            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLMESSAGEBUS_H_AAE36D41_9C3A_48F0_8316_7746219BCC1A_INCLUDED__
