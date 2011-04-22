//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlWindowBaseEx.h
//    Author:      Streamlet
//    Create Time: 2011-03-02
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLWINDOWBASEEX_H_AC4BA307_1739_4573_90E1_B080A8D1AB1E_INCLUDED__
#define __XLWINDOWBASEEX_H_AC4BA307_1739_4573_90E1_B080A8D1AB1E_INCLUDED__


#include <xl/Containers/xlTuple.h>
#include <xl/Win32/GUI/xlWindowBase.h>

namespace xl
{
    class WindowBaseEx : public WindowBase
    {
    protected:
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
        typedef Function<LRESULT (HWND, WORD, WORD, HWND, BOOL &)> CommandMsgHandler;

        // MsgHandler Parameters:
        // HWND:     hWnd
        // UINT_PTR: wID
        // UINT:     uCode
        // HWND:     hControl
        // BOOL &:   bHandled
        typedef Function<LRESULT (HWND, UINT_PTR, UINT, HWND, BOOL &)> NotifyMsgHandler;

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

    public:
        WindowBaseEx()
        {
            AppendMsgHandler(WM_COMMAND, MsgHandler(this, &WindowBaseEx::OnCommand));
            AppendMsgHandler(WM_NOTIFY,  MsgHandler(this, &WindowBaseEx::OnNotify));
        }

        WindowBaseEx(HWND hWnd) :
            WindowBase(hWnd)
        {
            AppendMsgHandler(WM_COMMAND, MsgHandler(this, &WindowBaseEx::OnCommand));
            AppendMsgHandler(WM_NOTIFY,  MsgHandler(this, &WindowBaseEx::OnNotify));
        }

        ~WindowBaseEx()
        {

        }

    private:
        WindowBaseEx(const WindowBase &);
        WindowBaseEx &operator =(const WindowBase &);

    // Command message maps

    private:
        typedef List<CommandMsgHandler> CommandMsgHandlerList;
        typedef Map<CommandMsgFinder, CommandMsgHandlerList> CommandMsgMap;

    private:
        CommandMsgMap   m_CommandMsgMap;
        CriticalSection m_csCommandMsgMap;
    
    public:
        void AppendCommandMsgHandler(WORD wID, WORD wCode, CommandMsgHandler pMsgHandler)
        {
            m_csCommandMsgMap.Lock();
            m_CommandMsgMap[MakeCommandMsgFinder(wID, wCode)].PushBack(pMsgHandler);
            m_csCommandMsgMap.UnLock();
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

    private:
        LRESULT OnCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
        {
            bHandled = FALSE;

            m_csCommandMsgMap.Lock();

            WORD wID = LOWORD(wParam);
            WORD wCode = HIWORD(wParam);

            CommandMsgHandlerList *pCommandMsgHandlers = nullptr;
            CommandMsgMap::Iterator itCommandMsgMap = m_CommandMsgMap.Find(MakeCommandMsgFinder(wID, wCode));

            if (itCommandMsgMap != m_CommandMsgMap.End())
            {
                pCommandMsgHandlers = &itCommandMsgMap->Value;
            }

            m_csCommandMsgMap.UnLock();

            if (pCommandMsgHandlers != nullptr)
            {
                LRESULT lResult = 0;

                for (CommandMsgHandlerList::Iterator it = pCommandMsgHandlers->Begin(); it != pCommandMsgHandlers->End(); ++it)
                {
                    lResult = (*it)(m_hWnd, wID, wCode, (HWND)lParam, bHandled);
                }

                if (bHandled)
                {
                    return lResult;
                }
            }

            return FALSE;
        }

    // Notify message maps

    private:
        typedef List<NotifyMsgHandler> NotifyMsgHandlerList;
        typedef Map<NotifyMsgFinder, NotifyMsgHandlerList> NotifyMsgMap;

    private:
        NotifyMsgMap   m_NotifyMsgMap;
        CriticalSection m_csNotifyMsgMap;

    public:
        void AppendNotifyMsgHandler(UINT_PTR uID, UINT uCode, NotifyMsgHandler pMsgHandler)
        {
            m_csNotifyMsgMap.Lock();
            m_NotifyMsgMap[MakeNotifyMsgFinder(uID, uCode)].PushBack(pMsgHandler);
            m_csNotifyMsgMap.UnLock();
        }

    private:
        LRESULT OnNotify(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
        {
            bHandled = FALSE;

            m_csNotifyMsgMap.Lock();

            LPNMHDR pNMHDR = (LPNMHDR)lParam;
            UINT_PTR uID = pNMHDR->idFrom;
            UINT uCode = pNMHDR->code;

            NotifyMsgHandlerList *pNotifyMsgHandlers = nullptr;
            NotifyMsgMap::Iterator itNotifyMsgMap = m_NotifyMsgMap.Find(MakeNotifyMsgFinder(uID, uCode));

            if (itNotifyMsgMap != m_NotifyMsgMap.End())
            {
                pNotifyMsgHandlers = &itNotifyMsgMap->Value;
            }

            m_csNotifyMsgMap.UnLock();

            if (pNotifyMsgHandlers != nullptr)
            {
                LRESULT lResult = 0;

                for (NotifyMsgHandlerList::Iterator it = pNotifyMsgHandlers->Begin(); it != pNotifyMsgHandlers->End(); ++it)
                {
                    lResult = (*it)(m_hWnd, uID, uCode, pNMHDR->hwndFrom, bHandled);
                }

                if (bHandled)
                {
                    return lResult;
                }
            }

            return FALSE;
        }
    };

} // namespace xl


#endif // #ifndef __XLWINDOWBASEEX_H_AC4BA307_1739_4573_90E1_B080A8D1AB1E_INCLUDED__
