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
#include <xl/Win32/GUI/xlMenu.h>
#include <xl/Win32/GUI/xlDialog.h>
#include <xl/Win32/GUI/xlStdStatic.h>
#include <xl/Win32/GUI/xlStdButton.h>
#include <xl/Win32/GUI/xlStdEdit.h>
#include <xl/Win32/GUI/xlStdComboBox.h>
#include <xl/Win32/GUI/xlStdListBox.h>
#include <xl/Win32/GUI/xlStdScrollBar.h>
#include <xl/Win32/GUI/xlStdListView.h>
#include <xl/Win32/GUI/xlStdLink.h>
#include <xl/Win32/GUI/xlStdProgressBar.h>

int WINAPI _tWinMain(__in HINSTANCE hInstance,
                     __in_opt HINSTANCE hPrevInstance,
                     __in LPTSTR lpCmdLine,
                     __in int nShowCmd)
{
    xl::Menu popupMenu;
    popupMenu.CreatePopup();
    popupMenu.AppendMenu(MF_POPUP | MF_STRING, 103, _T("&New"));
    popupMenu.AppendMenu(MF_POPUP | MF_STRING, 104, _T("&Open"));
    popupMenu.AppendMenu(MF_POPUP | MF_SEPARATOR, 0, nullptr);
    popupMenu.AppendMenu(MF_POPUP | MF_STRING, 105, _T("&Quit"));

    xl::Menu mainMenu;
    mainMenu.Create();
    mainMenu.AppendMenu(MF_POPUP, (UINT_PTR)popupMenu.GetHMENU(), _T("&File"));
    mainMenu.AppendMenu(MF_STRING, 101, _T("&Edit"));
    mainMenu.AppendMenu(MF_SEPARATOR, 0, nullptr);
    mainMenu.AppendMenu(MF_STRING, 102, _T("&Help"));

    xl::Window wnd;
    wnd.Create(nullptr, 300, 240, 500, 400, WS_OVERLAPPEDWINDOW, 0);
    wnd.SetWindowText(_T("MyWindow"));
    wnd.SetMenu(mainMenu.GetHMENU());

    xl::StdStatic label;
    label.Create(wnd, 1, 80, 30, 200, 18);
    label.SetWindowText(_T("Please input:"));

    xl::StdEdit edit;
    edit.Create(wnd, 2, 80, 50, 200, 24);

    xl::StdButton button;
    button.Create(wnd, 3, 80, 80, 200, 24);
    button.SetWindowText(_T("Show Dialog"));

    xl::StdComboBox combo;
    combo.Create(wnd, 4, 80, 110, 200, 100);
    combo.AddString(_T("Please select"));
    combo.AddString(_T("Item1"));
    combo.AddString(_T("Item2"));
    combo.AddString(_T("Item3"));
    combo.SetCurSel(0);

    xl::StdListBox list;
    list.Create(wnd, 5, 80, 140, 200, 100);
    list.AddString(_T("ListItem1"));
    list.AddString(_T("ListItem2"));
    list.AddString(_T("ListItem3"));

    xl::StdScrollBar scroll;
    scroll.Create(wnd, 6, 474, 0, 20, 372);
    scroll.SetScrollRange(0, 100);

    xl::StdListView listview;
    listview.Create(wnd, 7, 300, 30, 160, 150);
    listview.AddColumn(_T("Column0"), 0);
    listview.AddColumn(_T("Column1"), 1);
    listview.AddItem(0, 0, _T("R0C0"));
    listview.AddItem(0, 1, _T("R0C1"));
    listview.AddItem(1, 0, _T("R1C0"));
    listview.AddItem(1, 1, _T("R1C1"));
    listview.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT);

    xl::StdLink link;
    link.Create(wnd, 8, 300, 200, 160, 20);
    link.SetWindowText(_T("<a href=\"http://www.streamlet.org/\">·ÃÎÊÏªÁ÷ÍøÕ¾</a>"));

    xl::StdProgressBar progressbar;
    progressbar.Create(wnd, 9, 300, 240, 160, 20);
    progressbar.OffsetPos(60);

    wnd.AppendMsgHandler(WM_RBUTTONUP, [&popupMenu](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) -> LRESULT
    {
        POINT point = {};
        GetCursorPos(&point);
        popupMenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, hWnd);

        return FALSE;
    });

    wnd.AppendMenuCommandMsgHandler(103, [&wnd](HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled) -> LRESULT
    {
        wnd.MessageBox(_T("Menu"));

        return FALSE;
    });

    wnd.AppendCommandMsgHandler(2, EN_CHANGE, [&label, &edit](HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled) -> LRESULT
    {
        TCHAR szText[MAX_PATH];
        edit.GetWindowText(szText, MAX_PATH);
        label.SetWindowText(szText);        

        return FALSE;
    });

    wnd.AppendCommandMsgHandler(3, [&wnd](HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled) -> LRESULT
    {
        xl::Dialog dlg;
        dlg.Create(wnd, 400, 400);
        dlg.SetWindowText(_T("MyDialog"));

        INT_PTR nID = dlg.DoModal();

        return FALSE;
    });

    wnd.AppendCommandMsgHandler(4, CBN_SELCHANGE, [&edit, &combo](HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled) ->LRESULT
    {
        TCHAR szText[MAX_PATH];
        combo.GetWindowText(szText, MAX_PATH);
        edit.SetWindowText(szText);

        return FALSE;
    });

    wnd.AppendCommandMsgHandler(5, LBN_SELCHANGE, [&edit, &list](HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled) ->LRESULT
    {
        TCHAR szText[MAX_PATH];
        list.GetText(list.GetCurSel(), szText);
        edit.SetWindowText(szText);

        return FALSE;
    });

    wnd.AppendNotifyMsgHandler(8, NM_CLICK, [](HWND hWnd, UINT_PTR wID, UINT wCode, HWND hControl, BOOL &bHandled) -> LRESULT
    {
        ShellExecute(hWnd, _T("open"), _T("http://www.streamlet.org/"), _T(""), _T(""), SW_SHOW);

        return FALSE;
    });

    int nPos = 0;

    wnd.AppendMsgHandler(WM_VSCROLL, [&scroll, &nPos](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) -> LRESULT
    {
        switch (LOWORD(wParam))
        {
        case SB_TOP:
            --nPos;
            break;
        case SB_BOTTOM:
            ++nPos;
            break;
        case SB_LINEUP:
            nPos -= 3;
            break;
        case SB_LINEDOWN:
            nPos += 3;
            break;
        case SB_PAGEUP:
            nPos -= 10;
            break;
        case SB_PAGEDOWN:
            nPos += 10;
            break;
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            nPos = HIWORD(wParam);
            break;
        default:
            break;
        }

        if (nPos < 0)
        {
            nPos = 0;
        }

        if (nPos > 100)
        {
            nPos = 100;
        }

        scroll.SetScrollPos(nPos);

        return 0;
    });

    wnd.AppendMsgHandler(WM_DESTROY, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) -> LRESULT
    {
        PostQuitMessage(0);
        return FALSE;
    });

    wnd.ShowWindow();

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!IsDialogMessage(wnd, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}
