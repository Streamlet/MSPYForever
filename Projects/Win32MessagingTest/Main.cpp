//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2011-11-06
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/String/xlString.h>
#include <xl/Win32/GUI/xlWindow.h>
#include <xl/Win32/GUI/xlStdButton.h>
#include <xl/Win32/GUI/xlStdEdit.h>
#include <xl/Win32/Memory/xlSafeSmartPtr.h>
#include <xl/Win32/Messaging/xlMessageBus.h>

enum
{
    ID_MSGBUS_TEXT_COMING,
    ID_MSGBUS_CLOSE,
    ID_MSGBUS_QUIT,
};
typedef xl::SafeSharedPtr<xl::String> StringPtr;
typedef xl::MessageBus<UINT, StringPtr> MsgBus;

MsgBus g_msgbus;
UINT   g_nWindows = 0;

class DemoWindow : public xl::Window
{
public:
    DemoWindow()
    {
        AppendMsgHandler(WM_CREATE,  MsgHandler(this, &DemoWindow::OnCreate));
        AppendMsgHandler(WM_DESTROY, MsgHandler(this, &DemoWindow::OnDestroy));
    }

private:
    enum
    {
        ID_START = 100,
        ID_EDIT_TEXT,
        ID_EDIT_INPUT,
        ID_BUTTON_SEND,
        ID_BUTTON_CLOSE_ALL,
    };

private:
    xl::StdEdit m_editText;
    xl::StdEdit m_editInput;
    xl::StdButton m_buttonSend;
    xl::StdButton m_buttonCloseAll;

private:
    LRESULT OnCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
    {
        InterlockedIncrement(&g_nWindows);

        m_editText.Create(ID_EDIT_TEXT,   this, 10,  10,  200, 120, WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL | ES_AUTOHSCROLL | ES_MULTILINE | ES_READONLY);
        m_editInput.Create(ID_EDIT_INPUT,  this, 10,  140, 120, 20);
        m_buttonSend.Create(ID_BUTTON_SEND, this, 140, 138, 40,  24);
        m_buttonCloseAll.Create(ID_BUTTON_CLOSE_ALL, this, 190, 138, 24,  24);
        m_editInput.SetLimitText(MAX_PATH - 1);
        m_buttonSend.SetWindowText(_T("Send"));
        m_buttonCloseAll.SetWindowText(_T("X"));

        AppendCommandMsgHandler(ID_BUTTON_SEND, CommandMsgHandler(this, &DemoWindow::OnButtonSendClick));
        AppendCommandMsgHandler(ID_BUTTON_CLOSE_ALL, CommandMsgHandler(this, &DemoWindow::OnButtonCloseAllClick));

        g_msgbus.Register(ID_MSGBUS_TEXT_COMING,  MsgBus::HandlerType(this, &DemoWindow::OnMessageTextComing));
        g_msgbus.Register(ID_MSGBUS_QUIT,  MsgBus::HandlerType(this, &DemoWindow::OnMessageQuit));

        return 0;
    }

    LRESULT OnDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
    {
        g_msgbus.Unregister(ID_MSGBUS_QUIT,  MsgBus::HandlerType(this, &DemoWindow::OnMessageQuit));
        g_msgbus.Unregister(ID_MSGBUS_TEXT_COMING,  MsgBus::HandlerType(this, &DemoWindow::OnMessageTextComing));

        if (InterlockedDecrement(&g_nWindows) == 0)
        {
            PostQuitMessage(0);
        }

        return 0;
    }

    LRESULT OnButtonSendClick(HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled)
    {
        TCHAR szText[MAX_PATH] = {};
        m_editInput.GetWindowText(szText, MAX_PATH);
        m_editInput.SetWindowText(_T(""));
        g_msgbus.Notify(ID_MSGBUS_TEXT_COMING, StringPtr(new xl::String(szText)));

        return 0;
    }

    LRESULT OnButtonCloseAllClick(HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled)
    {
        g_msgbus.Notify(ID_MSGBUS_QUIT, StringPtr());
        return 0;
    }

private:
    void OnMessageTextComing(HANDLE hQuit, UINT nMessageId, StringPtr pMsgParam)
    {
        m_editText.AppendText(pMsgParam ->GetAddress());
        m_editText.AppendText(_T("\r\n"));
    }

    void OnMessageQuit(HANDLE hQuit, UINT nMessageId, StringPtr pMsgParam)
    {
        SendMessage(WM_CLOSE, 0, 0);
    }
};


int WINAPI _tWinMain(__in HINSTANCE hInstance,
                     __in_opt HINSTANCE hPrevInstance,
                     __in LPTSTR lpCmdLine,
                     __in int nShowCmd)
{
    g_msgbus.Start();

    const UINT WINDOW_MAX = 12;
    DemoWindow *pWindows = new DemoWindow[WINDOW_MAX];

    const int WIDTH  = 230;
    const int HEIGHT = 200;
    const int SPACE = 20;
    const int START = 100;

    int nScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
    int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    int nLeft = START;
    int nTop  = START;

    for (UINT i = 0; i < WINDOW_MAX; ++i)
    {
        if (nLeft + WIDTH > nScreenWidth)
        {
            nTop += HEIGHT + SPACE;
            nLeft = START;
        }

        if (nTop + HEIGHT > nScreenHeight)
        {
            break;
        }

        pWindows[i].Create(nLeft, nTop, WIDTH, HEIGHT);
        pWindows[i].SetWindowText(_T("Messaging Test Window"));
        pWindows[i].ShowWindow();

        nLeft += WIDTH + SPACE;
    }

    MSG msg = {};

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    delete[] pWindows;

    g_msgbus.Stop();

    return 0;
}
