//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlWindowBase.h
//    Author:      Streamlet
//    Create Time: 2010-12-20
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLWINDOWBASE_H_93972CEE_2D67_4A8B_927D_E327BDE8D4A4_INCLUDED__
#define __XLWINDOWBASE_H_93972CEE_2D67_4A8B_927D_E327BDE8D4A4_INCLUDED__


#include <xl/Win32/xlWin32Ver.h>
#include <xl/Containers/xlMap.h>
#include <xl/Containers/xlList.h>
#include <xl/Meta/xlFunction.h>
#include <xl/Win32/GUI/xlThunk.h>
#include <xl/Win32/Threads/xlTls.h>
#include <xl/Win32/Threads/xlCriticalSection.h>
#include <Windows.h>
#include <tchar.h>
#include <CommCtrl.h>

namespace xl
{

// Standard class names accepted by CreateWindow/CreateWindowEx
#define STD_CONTROL_CLASSNAME_STATIC        _T("STATIC")    // WC_STATIC
#define STD_CONTROL_CLASSNAME_BUTTON        _T("BUTTON")    // WC_BUTTON
#define STD_CONTROL_CLASSNAME_EDIT          _T("EDIT")      // WC_EDIT
#define STD_CONTROL_CLASSNAME_COMBOBOX      _T("COMBOBOX")  // WC_COMBOBOX
#define STD_CONTROL_CLASSNAME_LISTBOX       _T("LISTBOX")   // WC_LISTBOX
#define STD_CONTROL_CLASSNAME_SCROLLBAR     _T("SCROLLBAR") // WC_SCROLLBAR
#define STD_CONTROL_CLASSNAME_RICHEDIT1     _T("RichEdit")
#define STD_CONTROL_CLASSNAME_RICHEDIT2     _T("RICHEDIT_CLASS")
#define STD_CONTROL_CLASSNAME_MDICLIENT     _T("MDICLIENT")

// Controls defined in CommCtrl.h
#define STD_CONTROL_CLASSNAME_HEADER        WC_HEADER
#define STD_CONTROL_CLASSNAME_LINK          WC_LINK
#define STD_CONTROL_CLASSNAME_LISTVIEW      WC_LISTVIEW
#define STD_CONTROL_CLASSNAME_TREEVIEW      WC_TREEVIEW
#define STD_CONTROL_CLASSNAME_COMBOBOXEX    WC_COMBOBOXEX
#define STD_CONTROL_CLASSNAME_TABCONTROL    WC_TABCONTROL
#define STD_CONTROL_CLASSNAME_IPADDRESS     WC_IPADDRESS
#define STD_CONTROL_CLASSNAME_PAGESCROLLER  WC_PAGESCROLLER
#define STD_CONTROL_CLASSNAME_NATIVEFONTCTL WC_NATIVEFONTCTL

    class WindowBase
    {
    protected:
        // MsgHandler Parameters:
        // UINT:   uMsg
        // WPARAM: wParam
        // LPARAM: lParam
        typedef Function<LRESULT (UINT, WPARAM, LPARAM)> MsgHandler;

        // CommandMsgHandler Parameters:
        // WORD: wID
        // WORD: wCode
        //           For menus, it will always be 0;
        //           for accelerators, it will always be 1;
        //           for controls, it depends on the very control.
        // HWND: hControl
        //           For controls, it will be the HWND of the control,
        //           otherwise, it will be 0.
        typedef Function<LRESULT (WORD, WORD, HWND)> CommandMsgHandler;

        // MsgHandler Parameters:
        // UINT: wID
        // UINT: uCode
        // HWND: hControl
        typedef Function<LRESULT (UINT, UINT, HWND)> NotifyMsgHandler;

    private:
        inline UINT MakeMsgFinder(UINT uMsg)
        {
            return uMsg;
        }

        inline UINT MakeCommandMsgFinder(WORD wID, WORD wCode)
        {
            return ((UINT)wID | ((UINT)wCode << 16));
        }

        inline ULONGLONG MakeNotifyMsgFinder(UINT uID, UINT uCode)
        {
            return ((ULONGLONG)uID | ((ULONGLONG)uCode << 32));
        }

    public:
        WindowBase() :
            m_hWnd(nullptr), m_fnDefaultProc(DefWindowProc)
        {
            AppendMsgHandler(WM_COMMAND, MsgHandler(this, &WindowBase::OnCommand));
            AppendMsgHandler(WM_NOTIFY,  MsgHandler(this, &WindowBase::OnNotify));
        }

        ~WindowBase()
        {
            Destroy();
        }

    private:
        WindowBase(const WindowBase &);
        WindowBase &operator =(const WindowBase &);

    protected:
        bool Create(LPCTSTR lpClassName,
                    LPCTSTR lpWindowName,
                    DWORD dwStyle,
                    DWORD dwExStyle,
                    int x,
                    int y,
                    int nWidth,
                    int nHeight,
                    const WindowBase *pParent,
                    HMENU hMenu,
                    HINSTANCE hInstance,
                    LPVOID lpParam)
        {
            if (m_hWnd != nullptr)
            {
                return false;
            }

            bool bStdControl = false;

            if (lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_STATIC       ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_BUTTON       ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_EDIT         ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_COMBOBOX     ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_LISTBOX      ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_SCROLLBAR    ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_RICHEDIT1    ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_RICHEDIT2    ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_MDICLIENT    ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_HEADER       ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_LINK         ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_LISTVIEW     ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_TREEVIEW     ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_COMBOBOXEX   ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_TABCONTROL   ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_IPADDRESS    ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_PAGESCROLLER ) == 0 ||
                lstrcmpi(lpClassName, STD_CONTROL_CLASSNAME_NATIVEFONTCTL) == 0)
            {
                bStdControl = true;
            }

            if (!bStdControl)
            {
                WNDCLASSEX wcex    = { sizeof(WNDCLASSEX) };
                wcex.lpfnWndProc   = StartWndProc;
                wcex.hInstance     = hInstance;
                wcex.lpszClassName = lpClassName;
                wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
                wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);

                RegisterClassEx(&wcex);
            }

            m_sTls.Set((LPVOID)this);

            m_hWnd = CreateWindowEx(dwExStyle,
                                    lpClassName,
                                    lpWindowName,
                                    dwStyle,
                                    x,
                                    y,
                                    nWidth,
                                    nHeight,
                                    pParent == nullptr ? nullptr : pParent->m_hWnd,
                                    hMenu,
                                    hInstance,
                                    lpParam);

            if (m_hWnd == nullptr)
            {
                return false;
            }

            if (bStdControl)
            {
                m_fnDefaultProc = (WNDPROC)GetWindowLong(m_hWnd, GWL_WNDPROC);
                SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)StartWndProc);
            }

            return true;
        }

        bool Destroy()
        {
            if (m_hWnd == nullptr)
            {
                return false;
            }

            if (!DestroyWindow(m_hWnd))
            {
                return false;
            }

            return true;
        }

    protected:
        HWND          m_hWnd;
        WNDPROC       m_fnDefaultProc;

    private:
        Thunk m_thunk;

    private:
        static LRESULT CALLBACK StartWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            WindowBase *pThis = (WindowBase *)m_sTls.Get();

            pThis->m_thunk.SetObject(pThis);
            pThis->m_thunk.SetRealWndProc(&WindowBase::StaticWndProc);

            pThis->m_hWnd = hWnd;

            WNDPROC pWndProc = pThis->m_thunk.GetThunkWndProc();

            SetWindowLong(hWnd, GWL_WNDPROC, (LONG)pWndProc);

            return pWndProc(hWnd, uMsg, wParam, lParam);
        }

        static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            return ((WindowBase *)hWnd)->WndProc(uMsg, wParam, lParam);
        }

    private:
        static Tls  m_sTls;

    // Message maps

    protected:
        typedef List<MsgHandler> MsgHandlerList;
        typedef Map<UINT, MsgHandlerList> MsgMap;

    private:
        MsgMap          m_MsgMap;
        CriticalSection m_csMsgMap;

    public:
        void AppendMsgHandler(UINT uMsg, MsgHandler pMsgHandler)
        {
            m_csMsgMap.Lock();
            m_MsgMap[MakeMsgFinder(uMsg)].PushBack(pMsgHandler);
            m_csMsgMap.UnLock();
        }

    private:
        LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            m_csMsgMap.Lock();

            MsgHandlerList *pMsgHandlers = nullptr;
            MsgMap::Iterator itMsgMap = m_MsgMap.Find(MakeMsgFinder(uMsg));

            if (itMsgMap != m_MsgMap.End())
            {
                pMsgHandlers = &itMsgMap->Value;
            }

            m_csMsgMap.UnLock();

            if (pMsgHandlers != nullptr)
            {
                LRESULT lResult = 0;

                for (MsgHandlerList::Iterator it = pMsgHandlers->Begin(); it != pMsgHandlers->End(); ++it)
                {
                    lResult = (*it)(uMsg, wParam, lParam);
                }

                if (uMsg != WM_COMMAND && uMsg != WM_NOTIFY)
                {
                    return lResult;
                }
            }

            return m_fnDefaultProc(m_hWnd, uMsg, wParam, lParam);
        }

    // Command message maps

    private:
        typedef List<CommandMsgHandler> CommandMsgHandlerList;
        typedef Map<WPARAM, CommandMsgHandlerList> CommandMsgMap;

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
        LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
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
                    lResult = (*it)(wID, wCode, (HWND)lParam);
                }

                return lResult;
            }
            else
            {
                return FALSE;
            }
        }

    // Notify message maps

    private:
        typedef List<NotifyMsgHandler> NotifyMsgHandlerList;
        typedef Map<ULONGLONG, NotifyMsgHandlerList> NotifyMsgMap;

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
        LRESULT OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            m_csNotifyMsgMap.Lock();

            LPNMHDR pNMHDR = (LPNMHDR)lParam;
            UINT uID = pNMHDR->idFrom;
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
                    lResult = (*it)(uID, uCode, pNMHDR->hwndFrom);
                }

                return lResult;
            }
            else
            {
                return FALSE;
            }
        }
    };

    __declspec(selectany) Tls  WindowBase::m_sTls;

} // namespace xl

#endif // #ifndef __XLWINDOWBASE_H_93972CEE_2D67_4A8B_927D_E327BDE8D4A4_INCLUDED__
