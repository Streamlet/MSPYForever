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


#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#include <xl/Win32/GUI/xlWindow.h>
#include <xl/Win32/GUI/xlStdStatic.h>
#include <xl/Win32/GUI/xlStdButton.h>
#include <xl/Win32/GUI/xlStdEdit.h>

int WINAPI _tWinMain(__in HINSTANCE hInstance,
                     __in_opt HINSTANCE hPrevInstance,
                     __in LPTSTR lpCmdLine,
                     __in int nShowCmd)
{
    xl::Window wnd;
    wnd.Create(360, 300, 300, 240);
    wnd.SetWindowText(_T("MyWindow"));

    xl::StdStatic label;
    label.Create(1, &wnd, 80, 60, 200, 18);
    label.SetWindowText(_T("Please input:"));

    xl::StdEdit edit;
    edit.Create(2, &wnd, 80, 80, 200, 24);

    xl::StdButton button;
    button.Create(3, &wnd, 80, 120, 200, 24);
    button.SetWindowText(_T("Show input"));

    wnd.AppendCommandMsgHandler(2, EN_CHANGE, [&label, &edit](WORD wID, WORD wCode, HWND hControl) -> LRESULT
    {
        TCHAR szText[MAX_PATH];
        edit.GetWindowText(szText, MAX_PATH);
        label.SetWindowText(szText);        

        return FALSE;
    });

    wnd.AppendCommandMsgHandler(3, [&wnd, &edit](WORD wID, WORD wCode, HWND hControl) -> LRESULT
    {
        TCHAR szText[MAX_PATH];
        edit.GetWindowText(szText, MAX_PATH);

        wnd.MessageBox(szText, _T("MessageBox"), MB_OK | MB_ICONINFORMATION);

        return FALSE;

    });

    wnd.AppendMsgHandler(WM_DESTROY, [](UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
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
