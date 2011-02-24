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




#include <Windows.h>
#include <tchar.h>
#include <xl/Win32/GUI/xlWindow.h>
#include <xl/Win32/GUI/xlStdStatic.h>
#include <xl/Win32/GUI/xlStdButton.h>

class MyWindow : public xl::Window
{
public:
    MyWindow()
    {
        AppendMsgHandler(WM_DESTROY, MsgHandler(this, &MyWindow::OnDestroy));
        AppendCommandMsgHandler(2, CommandMsgHandler(this, &MyWindow::OnButton2));
    }

protected:
    LRESULT OnButton2(WORD wID, WORD wCode, HWND hControl)
    {
        MessageBox(_T("Hello, world!"), _T("MessageBox"), MB_OK | MB_ICONINFORMATION);

        return FALSE;
    }

    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        PostQuitMessage(0);
        return FALSE;
    }
};

int WINAPI _tWinMain(__in HINSTANCE hInstance,
                     __in_opt HINSTANCE hPrevInstance,
                     __in LPTSTR lpCmdLine,
                     __in int nShowCmd)
{
    MyWindow wnd;
    wnd.Create(360, 300, 300, 240);
    wnd.SetWindowText(_T("MyWindow"));

    xl::StdStatic label;
    label.Create(1, &wnd, 100, 100, 100, 18, WS_CHILD | WS_VISIBLE | SS_CENTER);
    label.SetWindowText(_T("Hello, world!"));

    xl::StdButton button;
    button.Create(2, &wnd, 100, 120, 100, 24, WS_CHILD | WS_VISIBLE);
    button.SetWindowText(_T("Click Me"));

    wnd.ShowWindow();

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	return 0;
}



