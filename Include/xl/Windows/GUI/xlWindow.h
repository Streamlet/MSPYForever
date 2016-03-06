//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlWindow.h
//    Author:      Streamlet
//    Create Time: 2010-12-20
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLWINDOW_H_93972CEE_2D67_4A8B_927D_E327BDE8D4A4_INCLUDED__
#define __XLWINDOW_H_93972CEE_2D67_4A8B_927D_E327BDE8D4A4_INCLUDED__


#include "../../Common/Meta/xlNonCopyable.h"
#include "../Threads/xlTls.h"
#include "../xlWin32Ver.h"
#include "xlThunk.h"
#include "xlWindowMessage.h"
#include "xlWindowHelper.h"
#include <CommCtrl.h>

namespace xl
{
    namespace Windows
    {
        class Window : public NonCopyable, public WindowMessage, public WindowHelper
        {
        public:
            Window() :
                WindowHelper(nullptr), m_fnDefaultProc(::DefWindowProc)
            {

            }

            Window(HWND hWnd) :
                WindowHelper(nullptr), m_fnDefaultProc(::DefWindowProc)
            {
                Attach(hWnd);
            }

            ~Window()
            {
                Destroy();
                Detach();
            }

            bool Create(HWND hParent,
                        int x,
                        int y,
                        int nWidth,
                        int nHeight,
                        DWORD dwStyle,
                        DWORD dwExStyle = 0,
                        LPCTSTR lpClassName = L"xlWindow",
                        LPCTSTR lpWindowName = nullptr,
                        HMENU hMenu = nullptr,
                        HINSTANCE hInstance = nullptr,
                        LPVOID lpParam = nullptr)
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
                    wcex.cbSize = sizeof(WNDCLASSEX);
                    wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
                    wcex.lpfnWndProc = StartWndProc;
                    wcex.hInstance = hInstance;
                    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
                    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
                    wcex.lpszClassName = lpClassName;

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
                                           hParent,
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

                if (ms_hFont == nullptr)
                {
                    NONCLIENTMETRICS m_tagNONCLIENTMETRICSW = { sizeof(m_tagNONCLIENTMETRICSW) };
                    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &m_tagNONCLIENTMETRICSW, 0);

                    ms_hFont = CreateFontIndirect(&m_tagNONCLIENTMETRICSW.lfMessageFont);
                }

                SetFont(ms_hFont, FALSE);

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

            LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
            {
                LRESULT lResult = 0;
                bHandled = FALSE;

                if (m_fnDefaultProc != nullptr)
                {
                    bHandled = true;
                    lResult = m_fnDefaultProc(m_hWnd, uMsg, wParam, lParam);
                }

                return lResult;
            }

        private:
            static LRESULT CALLBACK StartWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
            {
                Window *pThis = (Window *)ms_Tls.Get();

                pThis->m_thunk.SetObject(pThis);
                pThis->m_thunk.SetRealProc(&Window::StaticWndProc);

                pThis->m_hWnd = hWnd;

                WNDPROC pWndProc = pThis->m_thunk.GetThunkProc();

#ifdef _WIN64
                pThis->SetWindowLongPtr(GWLP_WNDPROC, (LONG_PTR)pWndProc);
#else
                pThis->SetWindowLong(GWL_WNDPROC, (LONG)pWndProc);
#endif

                return pWndProc(hWnd, uMsg, wParam, lParam);
            }

            static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
            {
                BOOL bHandled = TRUE;
                Window *pThis = (Window *)hWnd;
                LRESULT lResult = pThis->ProcessMessage(pThis->m_hWnd, uMsg, wParam, lParam, bHandled);

                if (!bHandled)
                {
                    lResult = pThis->DefWindowProc(uMsg, wParam, lParam, bHandled);
                }

                if (uMsg == WM_NCDESTROY)
                {
                    pThis->m_hWnd = nullptr;
                }

                return lResult;
            }

        private:
            WNDPROC        m_fnDefaultProc;
            Thunk<WNDPROC> m_thunk;

            CommCtrlInitializer ms_cci;

            static Tls     ms_Tls;
            static HFONT   ms_hFont;
        };

        __declspec(selectany) Tls  Window::ms_Tls;
        __declspec(selectany) HFONT Window::ms_hFont = nullptr;

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLWINDOW_H_93972CEE_2D67_4A8B_927D_E327BDE8D4A4_INCLUDED__
