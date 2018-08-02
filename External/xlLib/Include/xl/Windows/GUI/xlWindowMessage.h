//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlWindowBaseEx.h
//    Author:      Streamlet
//    Create Time: 2011-03-02
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLWINDOWMESSAGE_H_AC4BA307_1739_4573_90E1_B080A8D1AB1E_INCLUDED__
#define __XLWINDOWMESSAGE_H_AC4BA307_1739_4573_90E1_B080A8D1AB1E_INCLUDED__


#include "../../Common/Meta/xlFunction.h"
#include "../../Common/Meta/xlTuple.h"
#include "../../Common/Containers/xlList.h"
#include "../../Common/Containers/xlMap.h"
#include "xlCommCtrlInitializer.h"

namespace xl
{
    namespace Windows
    {
        class WindowMessage
        {
        public:
            // MsgHandler Parameters:
            // HWND:   hWnd
            // UINT:   uMsg
            // WPARAM: wParam
            // LPARAM: lParam
            // BOOL &: bHandled
            typedef Function<LRESULT(HWND, UINT, WPARAM, LPARAM, BOOL &)> MsgHandler;

            // CommandMsgHandler Parameters:
            // HWND: hWnd
            // WORD: wID
            // WORD: wCode
            //           For menus, it will always be 0;
            //           for accelerators, it will always be 1;
            //           for controls, it depends on the very control.
            // HWND: hControl
            //           For controls, it will be the HWND of the control,
            //           otherwise, it will be 0.
            // BOOL &: bHandled
            typedef Function<LRESULT(HWND, WORD, WORD, HWND, BOOL &)> CommandMsgHandler;

            // NotifyMsgHandler Parameters:
            // HWND:     hWnd
            // LPNMHDR:  lpNMHDR
            // BOOL &:   bHandled
            typedef Function<LRESULT(HWND, LPNMHDR, BOOL &)> NotifyMsgHandler;

        public:
            WindowMessage()
            {
                AppendMsgHandler(WM_COMMAND, MsgHandler(this, &WindowMessage::OnCommand));
                AppendMsgHandler(WM_NOTIFY, MsgHandler(this, &WindowMessage::OnNotify));
            }

            ~WindowMessage()
            {

            }

            // Command message maps

        private:
            typedef Tuple<WORD, WORD> CommandMsgFinder;

            inline CommandMsgFinder MakeCommandMsgFinder(WORD wID, WORD wCode)
            {
                return CommandMsgFinder(wID, wCode);
            }

            typedef Tuple<UINT_PTR, UINT> NotifyMsgFinder;

            inline NotifyMsgFinder MakeNotifyMsgFinder(UINT_PTR uID, UINT uCode)
            {
                return NotifyMsgFinder(uID, uCode);
            }

        private:
            typedef List<MsgHandler> MsgHandlerList;
            typedef Map<UINT, MsgHandlerList> MsgMap;
            MsgMap m_MsgMap;

            typedef List<CommandMsgHandler> CommandMsgHandlerList;
            typedef Map<CommandMsgFinder, CommandMsgHandlerList> CommandMsgMap;
            CommandMsgMap m_CommandMsgMap;

            typedef List<NotifyMsgHandler> NotifyMsgHandlerList;
            typedef Map<NotifyMsgFinder, NotifyMsgHandlerList> NotifyMsgMap;
            NotifyMsgMap   m_NotifyMsgMap;

        public:
            void AppendMsgHandler(UINT uMsg, MsgHandler pMsgHandler)
            {
                m_MsgMap[uMsg].PushBack(pMsgHandler);
            }

            void AppendCommandMsgHandler(WORD wID, WORD wCode, CommandMsgHandler pMsgHandler)
            {
                m_CommandMsgMap[MakeCommandMsgFinder(wID, wCode)].PushBack(pMsgHandler);
            }

            void AppendMenuCommandMsgHandler(WORD wID, CommandMsgHandler pMsgHandler)
            {
                AppendCommandMsgHandler(wID, 0, pMsgHandler);
            }

            void AppendAcceleratorCommandMsgHandler(WORD wID, CommandMsgHandler pMsgHandler)
            {
                AppendCommandMsgHandler(wID, 1, pMsgHandler);
            }

            void AppendCommandMsgHandler(WORD wID, CommandMsgHandler pMsgHandler)
            {
                AppendCommandMsgHandler(wID, 0, pMsgHandler);
            }

            void AppendNotifyMsgHandler(UINT_PTR uID, UINT uCode, NotifyMsgHandler pMsgHandler)
            {
                m_NotifyMsgMap[MakeNotifyMsgFinder(uID, uCode)].PushBack(pMsgHandler);
            }

            LRESULT ProcessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
            {
                return OnMessage(hWnd, uMsg, wParam, lParam, bHandled);
            }

        private:
            LRESULT OnMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
            {
                bHandled = FALSE;

                MsgHandlerList *pMsgHandlers = nullptr;
                MsgMap::Iterator itMsgMap = m_MsgMap.Find(uMsg);

                if (itMsgMap != m_MsgMap.End())
                {
                    pMsgHandlers = &itMsgMap->Value;
                }

                if (pMsgHandlers != nullptr)
                {
                    LRESULT lResult = 0;
                    bHandled = TRUE;

                    for (MsgHandlerList::Iterator it = pMsgHandlers->Begin(); it != pMsgHandlers->End(); ++it)
                    {
                        lResult = (*it)(hWnd, uMsg, wParam, lParam, bHandled);

                        if (bHandled)
                        {
                            break;
                        }
                    }

                    if (bHandled)
                    {
                        return lResult;
                    }
                }

                return 0;
            }

            LRESULT OnCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
            {
                bHandled = FALSE;

                WORD wID = LOWORD(wParam);
                WORD wCode = HIWORD(wParam);

                CommandMsgHandlerList *pCommandMsgHandlers = nullptr;
                CommandMsgMap::Iterator itCommandMsgMap = m_CommandMsgMap.Find(MakeCommandMsgFinder(wID, wCode));

                if (itCommandMsgMap != m_CommandMsgMap.End())
                {
                    pCommandMsgHandlers = &itCommandMsgMap->Value;
                }

                if (pCommandMsgHandlers != nullptr)
                {
                    LRESULT lResult = 0;
                    bHandled = TRUE;

                    for (CommandMsgHandlerList::Iterator it = pCommandMsgHandlers->Begin(); it != pCommandMsgHandlers->End(); ++it)
                    {
                        lResult = (*it)(hWnd, wID, wCode, (HWND)lParam, bHandled);

                        if (bHandled)
                        {
                            break;
                        }
                    }

                    if (bHandled)
                    {
                        return lResult;
                    }
                }

                return 0;
            }

            LRESULT OnNotify(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
            {
                bHandled = FALSE;

                LPNMHDR pNMHDR = (LPNMHDR)lParam;
                UINT_PTR uID = pNMHDR->idFrom;
                UINT uCode = pNMHDR->code;

                NotifyMsgHandlerList *pNotifyMsgHandlers = nullptr;
                NotifyMsgMap::Iterator itNotifyMsgMap = m_NotifyMsgMap.Find(MakeNotifyMsgFinder(uID, uCode));

                if (itNotifyMsgMap != m_NotifyMsgMap.End())
                {
                    pNotifyMsgHandlers = &itNotifyMsgMap->Value;
                }

                if (pNotifyMsgHandlers != nullptr)
                {
                    LRESULT lResult = 0;
                    bHandled = TRUE;

                    for (NotifyMsgHandlerList::Iterator it = pNotifyMsgHandlers->Begin(); it != pNotifyMsgHandlers->End(); ++it)
                    {
                        lResult = (*it)(hWnd, pNMHDR, bHandled);

                        if (bHandled)
                        {
                            break;
                        }
                    }

                    if (bHandled)
                    {
                        return lResult;
                    }
                }

                return 0;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLWINDOWMESSAGE_H_AC4BA307_1739_4573_90E1_B080A8D1AB1E_INCLUDED__
