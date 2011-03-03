//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2011-02-24
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Win32/GUI/xlWindow.h>
#include <xl/Win32/GUI/xlStdStatic.h>
#include <xl/Win32/GUI/xlStdButton.h>
#include <xl/Win32/GUI/xlStdEdit.h>
#include <xl/Win32/GUI/xlStdComboBox.h>
#include <xl/Win32/GUI/xlStdListBox.h>

#pragma comment(lib, "Comctl32.lib")

int WINAPI _tWinMain(__in HINSTANCE hInstance,
                     __in_opt HINSTANCE hPrevInstance,
                     __in LPTSTR lpCmdLine,
                     __in int nShowCmd)
{
    INITCOMMONCONTROLSEX iccx = { sizeof(INITCOMMONCONTROLSEX), 0xffffffff };
    InitCommonControlsEx(&iccx);

    xl::Window wnd;
    wnd.Create(360, 300, 300, 240);
    wnd.SetWindowText(_T("MyWindow"));

    xl::StdStatic label;
    label.Create(1, &wnd, 80, 30, 200, 18);
    label.SetWindowText(_T("Please input:"));

    xl::StdEdit edit;
    edit.Create(2, &wnd, 80, 50, 200, 24);

    xl::StdButton button;
    button.Create(3, &wnd, 80, 80, 200, 24);
    button.SetWindowText(_T("Show input"));

    xl::StdComboBox combo;
    combo.Create(4, &wnd, 80, 110, 200, 100);
    combo.AddString(_T("Please select"));
    combo.AddString(_T("Item1"));
    combo.AddString(_T("Item2"));
    combo.AddString(_T("Item3"));
    combo.SetCurSel(0);

    xl::StdListBox list;
    list.Create(5, &wnd, 80, 140, 200, 100);
    list.AddString(_T("ListItem1"));
    list.AddString(_T("ListItem2"));
    list.AddString(_T("ListItem3"));

    wnd.AppendCommandMsgHandler(2, EN_CHANGE, [&label, &edit](HWND hWnd, WORD wID, WORD wCode, HWND hControl) -> LRESULT
    {
        TCHAR szText[MAX_PATH];
        edit.GetWindowText(szText, MAX_PATH);
        label.SetWindowText(szText);        

        return FALSE;
    });

    wnd.AppendCommandMsgHandler(3, [&edit](HWND hWnd, WORD wID, WORD wCode, HWND hControl) -> LRESULT
    {
        TCHAR szText[MAX_PATH];
        edit.GetWindowText(szText, MAX_PATH);

        MessageBox(hWnd, szText, _T("MessageBox"), MB_OK | MB_ICONINFORMATION);

        return FALSE;
    });

    wnd.AppendCommandMsgHandler(4, CBN_SELCHANGE, [&edit, &combo](HWND hWnd, WORD wID, WORD wCode, HWND hControl) ->LRESULT
    {
        TCHAR szText[MAX_PATH];
        combo.GetWindowText(szText, MAX_PATH);
        edit.SetWindowText(szText);

        return FALSE;
    });

    wnd.AppendCommandMsgHandler(5, LBN_SELCHANGE, [&edit, &list](HWND hWnd, WORD wID, WORD wCode, HWND hControl) ->LRESULT
    {
        TCHAR szText[MAX_PATH];
        list.GetText(list.GetCurSel(), szText);
        edit.SetWindowText(szText);

        return FALSE;
    });

    wnd.AppendMsgHandler(WM_DESTROY, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
    {
        PostQuitMessage(0);
        return FALSE;
    });

    wnd.ShowWindow();

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
