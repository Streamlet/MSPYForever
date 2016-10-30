//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlDialog.h
//    Author:      Streamlet
//    Create Time: 2011-03-12
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLDIALOG_H_FB784537_F2A1_43D5_B337_1882AB81D19F_INCLUDED__
#define __XLDIALOG_H_FB784537_F2A1_43D5_B337_1882AB81D19F_INCLUDED__


#include "xlWindow.h"

namespace xl
{
    namespace Windows
    {
        class Dialog : public Window
        {
        public:
            Dialog() :
                m_bInModal(false),
                m_nModalResult(-1)
            {
                AppendMsgHandler(WM_CREATE, MsgHandler(this, &Dialog::OnMsgCreate));
                AppendMsgHandler(WM_INITDIALOG, MsgHandler(this, &Dialog::OnMsgInitDialog));
                AppendMsgHandler(WM_ERASEBKGND, MsgHandler(this, &Dialog::OnMsgEraseBackground));
                AppendMsgHandler(WM_CLOSE, MsgHandler(this, &Dialog::OnMsgClose));

                AppendCommandMsgHandler(IDOK, CommandMsgHandler(this, &Dialog::OnMsgOK));
                AppendCommandMsgHandler(IDCANCEL, CommandMsgHandler(this, &Dialog::OnMsgCancel));
            }

            Dialog(HWND hWnd) :
                Window(hWnd),
                m_bInModal(false),
                m_nModalResult(-1)
            {
                AppendMsgHandler(WM_CREATE, MsgHandler(this, &Dialog::OnMsgCreate));
                AppendMsgHandler(WM_INITDIALOG, MsgHandler(this, &Dialog::OnMsgInitDialog));
                AppendMsgHandler(WM_ERASEBKGND, MsgHandler(this, &Dialog::OnMsgEraseBackground));
                AppendMsgHandler(WM_CLOSE, MsgHandler(this, &Dialog::OnMsgClose));

                AppendCommandMsgHandler(IDOK, CommandMsgHandler(this, &Dialog::OnMsgOK));
                AppendCommandMsgHandler(IDCANCEL, CommandMsgHandler(this, &Dialog::OnMsgCancel));
            }

            ~Dialog()
            {

            }

            bool Create(HWND hOwner,
                        int nWidth,
                        int nHeight,
                        DWORD dwStyle = WS_POPUPWINDOW | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                        DWORD dwExStyle = WS_EX_CONTROLPARENT,
                        LPCTSTR lpszClassName = L"xlDialog",
                        LPCTSTR lpWindowName = nullptr,
                        HMENU hMenu = nullptr,
                        HINSTANCE hInstance = nullptr)
            {
                RECT rect = {};

                if (hOwner != nullptr)
                {
                    ::GetWindowRect(hOwner, &rect);
                }
                else
                {
                    rect.right = GetSystemMetrics(SM_CXSCREEN);
                    rect.bottom = GetSystemMetrics(SM_CYSCREEN);
                }

                int x = (rect.left + rect.right - nWidth) / 2;
                int y = (rect.top + rect.bottom - nHeight) / 2;

                if (!Window::Create(hOwner,
                                    x,
                                    y,
                                    nWidth,
                                    nHeight,
                                    dwStyle,
                                    dwExStyle,
                                    lpszClassName,
                                    lpWindowName,
                                    hMenu,
                                    hInstance))
                {
                    return false;
                }

                return true;
            }

        public:

            INT_PTR DoModal(int nCmdShow = SW_SHOW, bool bProcessDialogMessage = true)
            {
                HWND hOwner = GetWindow(GW_OWNER);

                if (hOwner != nullptr)
                {
                    ::EnableWindow(hOwner, FALSE);
                }

                ShowWindow(nCmdShow);

                INT_PTR nModalResult = RunModalLoop(bProcessDialogMessage);

                Destroy();

                if (hOwner != nullptr)
                {
                    ::EnableWindow(hOwner, TRUE);
                    ::BringWindowToTop(hOwner);
                }

                return nModalResult;
            }

            void EndDialog(INT_PTR nModulResult)
            {
                m_nModalResult = nModulResult;
                m_bInModal = false;
            }

        protected:

            INT_PTR RunModalLoop(bool bProcessDialogMessage = true)
            {
                m_nModalResult = -1;
                m_bInModal = true;

                MSG msg = {};

                while (m_bInModal)
                {
                    while (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
                    {
                        if (msg.message == WM_QUIT)
                        {
                            EndDialog(IDCANCEL);
                            break;
                        }

                        if (!::GetMessage(&msg, NULL, NULL, NULL))
                        {
                            EndDialog(IDCANCEL);
                            break;
                        }

                        if (!bProcessDialogMessage || !IsDialogMessage(m_hWnd, &msg))
                        {
                            TranslateMessage(&msg);
                            DispatchMessage(&msg);
                        }
                    }

                    Sleep(0);
                }

                return m_nModalResult;
            }

        protected:
            bool    m_bInModal;
            INT_PTR m_nModalResult;

        protected:

            LRESULT OnMsgCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
            {
                OnCreate();

                HWND hCtrl = ::GetNextDlgTabItem(hWnd, NULL, FALSE);

                if (::SendMessage(hWnd, WM_INITDIALOG, (WPARAM)hCtrl, 0))
                {
                    ::SetFocus(hCtrl);
                }

                return TRUE;
            }

            LRESULT OnMsgInitDialog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
            {
                if (!OnInitDialog())
                {
                    return FALSE;
                }

                return TRUE;
            }

            LRESULT OnMsgEraseBackground(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
            {
                HDC hDC = (HDC)wParam;

                RECT rect;
                GetClientRect(&rect);

                SetDCBrushColor(hDC, GetSysColor(COLOR_3DFACE));
                HBRUSH hBrush = (HBRUSH)GetStockObject(DC_BRUSH);

                FillRect(hDC, &rect, hBrush);

                return TRUE;
            }

            LRESULT OnMsgClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
            {
                if (OnCancel())
                {
                    EndDialog(IDCANCEL);
                }

                return TRUE;
            }

            LRESULT OnMsgOK(HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled)
            {
                if (OnOK())
                {
                    EndDialog(IDOK);
                }

                return TRUE;
            }

            LRESULT OnMsgCancel(HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled)
            {
                if (OnCancel())
                {
                    EndDialog(IDCANCEL);
                }

                return TRUE;
            }

        protected:

            virtual bool OnCreate()
            {
                return true;
            }

            virtual bool OnInitDialog()
            {
                return true;
            }

            virtual bool OnOK()
            {
                return true;
            }

            virtual bool OnCancel()
            {
                return true;
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLDIALOG_H_FB784537_F2A1_43D5_B337_1882AB81D19F_INCLUDED__
