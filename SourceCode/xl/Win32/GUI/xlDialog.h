//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlDialog.h
//    Author:      Streamlet
//    Create Time: 2011-03-12
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLDIALOG_H_FB784537_F2A1_43D5_B337_1882AB81D19F_INCLUDED__
#define __XLDIALOG_H_FB784537_F2A1_43D5_B337_1882AB81D19F_INCLUDED__


#include <xl/Win32/GUI/xlWindow.h>

namespace xl
{
    class Dialog : public Window
    {
    public:
        Dialog() :
            m_bInModal(false),
            m_nModalResult(-1)
        {
            AppendMsgHandler(WM_CREATE,       MsgHandler(this, &Dialog::OnMsgCreate));
            AppendMsgHandler(WM_INITDIALOG,   MsgHandler(this, &Dialog::OnMsgInitDialog));
            AppendMsgHandler(WM_ERASEBKGND,   MsgHandler(this, &Dialog::OnMsgEraseBackground));
            AppendMsgHandler(WM_CLOSE,        MsgHandler(this, &Dialog::OnMsgClose));

            AppendCommandMsgHandler(IDOK,     CommandMsgHandler(this, &Dialog::OnMsgOK));
            AppendCommandMsgHandler(IDCANCEL, CommandMsgHandler(this, &Dialog::OnMsgCancel));
        }

        Dialog(HWND hWnd) :
            Window(hWnd),
            m_bInModal(false),
            m_nModalResult(-1)
        {
            AppendMsgHandler(WM_CREATE,       MsgHandler(this, &Dialog::OnMsgCreate));
            AppendMsgHandler(WM_INITDIALOG,   MsgHandler(this, &Dialog::OnMsgInitDialog));
            AppendMsgHandler(WM_ERASEBKGND,   MsgHandler(this, &Dialog::OnMsgEraseBackground));
            AppendMsgHandler(WM_CLOSE,        MsgHandler(this, &Dialog::OnMsgClose));

            AppendCommandMsgHandler(IDOK,     CommandMsgHandler(this, &Dialog::OnMsgOK));
            AppendCommandMsgHandler(IDCANCEL, CommandMsgHandler(this, &Dialog::OnMsgCancel));
        }

        ~Dialog()
        {

        }

    private:
        Dialog(const Dialog &);
        Dialog &operator =(const Dialog &);

    protected:
        static LPCTSTR GetClassName()
        {
            return _T("xlDialog");
        }
        
    public:
        bool Create(int nWidth = CW_USEDEFAULT,
                    int nHeight = CW_USEDEFAULT,
                    Window *pParent = nullptr,
                    LPCTSTR lpszClassName = GetClassName(),
                    DWORD dwStyle = WS_POPUPWINDOW | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                    DWORD dwExStyle = WS_EX_CONTROLPARENT,
                    HMENU hMenu = nullptr,
                    HINSTANCE hInstance = nullptr)
        {
            RECT rect = {};

            if (pParent != nullptr)
            {
                pParent->GetWindowRect(&rect);
            }
            else
            {
                rect.right  = GetSystemMetrics(SM_CXSCREEN);
                rect.bottom = GetSystemMetrics(SM_CYSCREEN);
            }

            int x = (rect.left + rect.right - nWidth)  / 2;
            int y = (rect.top + rect.bottom - nHeight) / 2;

            if (!Window::Create(x,
                                y,
                                nWidth,
                                nHeight,
                                pParent,
                                lpszClassName,
                                dwStyle,
                                dwExStyle,
                                hMenu,
                                hInstance))
            {
                return false;
            }

            return true;
        }

    public:

        INT_PTR DoModal()
        {
            HWND hOwner = GetWindow(GW_OWNER);

            if (hOwner != nullptr)
            {
                ::EnableWindow(hOwner, FALSE);
            }

            ShowWindow(SW_SHOW);

            INT_PTR nModalResult = RunModalLoop();

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

    private:

        INT_PTR RunModalLoop()
        {
            m_nModalResult = -1;
            m_bInModal = true;

            MSG msg = {};

            while (m_bInModal)
            {
                do
                {
                    if (!::GetMessage(&msg, NULL, NULL, NULL))
                    {
                        EndDialog(-1);
                    }

                    if (!IsDialogMessage(m_hWnd, &msg))
                    {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }

                } while (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE));
            }

            return m_nModalResult;
        }

    private:
        bool    m_bInModal;
        INT_PTR m_nModalResult;

    private:

        LRESULT OnMsgCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            OnCreate();

            HWND hCtrl = ::GetNextDlgTabItem(hWnd, NULL, FALSE);

            if (::SendMessage(hWnd, WM_INITDIALOG, (WPARAM)hCtrl, 0))
            {
                ::SetFocus(hCtrl);
            }

            return TRUE;
        }

        LRESULT OnMsgInitDialog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            if (!OnInitDialog())
            {
                return FALSE;
            }

            return TRUE;
        }

        LRESULT OnMsgEraseBackground(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            HDC hDC = (HDC)wParam;

            RECT rect;
            GetClientRect(&rect);

            SetDCBrushColor(hDC, GetSysColor(COLOR_3DFACE));
            HBRUSH hBrush = (HBRUSH)GetStockObject(DC_BRUSH);

            FillRect(hDC, &rect, hBrush);

            return TRUE;
        }

        LRESULT OnMsgClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            if (OnCancel())
            {
                EndDialog(IDCANCEL);
            }

            return 0;
        }

        LRESULT OnMsgOK(HWND hWnd, WORD wID, WORD wCode, HWND hControl)
        {
            if (OnOK())
            {
                EndDialog(IDOK);
            }

            return 0;
        }

        LRESULT OnMsgCancel(HWND hWnd, WORD wID, WORD wCode, HWND hControl)
        {
            if (OnCancel())
            {
                EndDialog(IDCANCEL);
            }

            return 0;
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

} // namespace xl

#endif // #ifndef __XLDIALOG_H_FB784537_F2A1_43D5_B337_1882AB81D19F_INCLUDED__
