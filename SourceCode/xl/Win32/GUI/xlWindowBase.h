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


#include "../../Containers/xlList.h"
#include "../../Containers/xlMap.h"
#include "../../Meta/xlFunction.h"
#include "../../Meta/xlUtility.h"
#include "../Threads/xlCriticalSection.h"
#include "../Threads/xlTls.h"
#include "../xlWin32Ver.h"
#include "xlThunk.h"
#include <Windows.h>
#include <CommCtrl.h>
#include <tchar.h>

namespace xl
{
    class WindowBase : public NonCopyable
    {
    public:
        // MsgHandler Parameters:
        // HWND:   hWnd
        // UINT:   uMsg
        // WPARAM: wParam
        // LPARAM: lParam
        // BOOL &: bHandled
        typedef Function<LRESULT (HWND, UINT, WPARAM, LPARAM, BOOL &)> MsgHandler;

    public:
        WindowBase() :
            m_hWnd(nullptr), m_fnDefaultProc(DefWindowProc)
        {

        }

        WindowBase(HWND hWnd) :
            m_hWnd(nullptr), m_fnDefaultProc(DefWindowProc)
        {
            Attach(hWnd);
        }

        ~WindowBase()
        {
            Destroy();
            Detach();
        }

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

            WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
            bool bStdControl = !!GetClassInfoEx(nullptr, lpClassName, &wcex);

            if (!bStdControl)
            {
                ZeroMemory(&wcex, sizeof(WNDCLASSEX));
                wcex.cbSize        = sizeof(WNDCLASSEX);
                wcex.lpfnWndProc   = StartWndProc;
                wcex.hInstance     = hInstance;
                wcex.lpszClassName = lpClassName;
                wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
                wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);

                RegisterClassEx(&wcex);

                ms_Tls.Set((LPVOID)this);
            }


            HWND hWnd = CreateWindowEx(dwExStyle,
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

            if (hWnd == nullptr)
            {
                return false;
            }

            if (bStdControl)
            {
                Attach(hWnd);
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

    public:
        bool Attach(HWND hWnd)
        {
            if (m_hWnd != nullptr)
            {
                return false;
            }

            ms_Tls.Set((LPVOID)this);

#ifdef _WIN64
            m_fnDefaultProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)StartWndProc);
#else
            m_fnDefaultProc = (WNDPROC)::SetWindowLong(hWnd, GWL_WNDPROC, (LONG)StartWndProc);
#endif

            // Force the StartWndProc to be called:
            ::SendMessage(hWnd, WM_NULL, 0, 0);

            return true;
        }

        HWND Detach()
        {
            HWND hWnd = m_hWnd;

            if (m_hWnd != nullptr)
            {
#ifdef _WIN64
                ::SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)m_fnDefaultProc);
#else
                ::SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)m_fnDefaultProc);
#endif
                m_hWnd = nullptr;
            }

            return hWnd;
        }

    protected:
        HWND          m_hWnd;
        WNDPROC       m_fnDefaultProc;

    private:
        Thunk<WNDPROC> m_thunk;

    private:
        static LRESULT CALLBACK StartWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            WindowBase *pThis = (WindowBase *)ms_Tls.Get();

            pThis->m_thunk.SetObject(pThis);
            pThis->m_thunk.SetRealProc(&WindowBase::StaticWndProc);

            pThis->m_hWnd = hWnd;

            WNDPROC pWndProc = pThis->m_thunk.GetThunkProc();

#ifdef _WIN64
            SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)pWndProc);
#else
            SetWindowLong(hWnd, GWL_WNDPROC, (LONG)pWndProc);
#endif

            return pWndProc(hWnd, uMsg, wParam, lParam);
        }

        static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            return ((WindowBase *)hWnd)->WndProc(uMsg, wParam, lParam);
        }

    private:
        static Tls  ms_Tls;

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
            m_MsgMap[uMsg].PushBack(pMsgHandler);
            m_csMsgMap.UnLock();
        }

    private:
        LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            m_csMsgMap.Lock();

            MsgHandlerList *pMsgHandlers = nullptr;
            MsgMap::Iterator itMsgMap = m_MsgMap.Find(uMsg);

            if (itMsgMap != m_MsgMap.End())
            {
                pMsgHandlers = &itMsgMap->Value;
            }

            m_csMsgMap.UnLock();

            if (pMsgHandlers != nullptr)
            {
                LRESULT lResult = 0;
                BOOL bHandled = TRUE;

                for (MsgHandlerList::Iterator it = pMsgHandlers->Begin(); it != pMsgHandlers->End(); ++it)
                {
                    lResult = (*it)(m_hWnd, uMsg, wParam, lParam, bHandled);
                }

                if (bHandled)
                {
                    return lResult;
                }
            }

            if (m_fnDefaultProc == nullptr)
            {
                return 0;
            }

            return m_fnDefaultProc(m_hWnd, uMsg, wParam, lParam);
        }
    };

    __declspec(selectany) Tls  WindowBase::ms_Tls;

} // namespace xl

#endif // #ifndef __XLWINDOWBASE_H_93972CEE_2D67_4A8B_927D_E327BDE8D4A4_INCLUDED__
