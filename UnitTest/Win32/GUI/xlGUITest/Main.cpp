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
#include <xl/Win32/GUI/xlStdScrollBar.h>
#include <xl/Win32/GUI/xlStdListView.h>
#include <xl/Win32/GUI/xlStdLink.h>

int WINAPI _tWinMain(__in HINSTANCE hInstance,
                     __in_opt HINSTANCE hPrevInstance,
                     __in LPTSTR lpCmdLine,
                     __in int nShowCmd)
{
    xl::Window wnd;
    wnd.Create(500, 400, 300, 240);
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

    xl::StdScrollBar scroll;
    scroll.Create(6, &wnd, 474, 0, 20, 372);
    scroll.SetScrollRange(0, 100);

    xl::StdListView listview;
    listview.Create(7, &wnd, 300, 30, 160, 150);
    listview.AddColumn(_T("Column0"), 0);
    listview.AddColumn(_T("Column1"), 1);
    listview.AddItem(0, 0, _T("R0C0"));
    listview.AddItem(0, 1, _T("R0C1"));
    listview.AddItem(1, 0, _T("R1C0"));
    listview.AddItem(1, 1, _T("R1C1"));
    listview.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT);

    xl::StdLink link;
    link.Create(8, &wnd, 300, 200, 160, 20);
    link.SetWindowText(_T("<a href=\"http://www.streamlet.org/\">·ÃÎÊÏªÁ÷ÍøÕ¾</a>"));

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
    
    wnd.AppendNotifyMsgHandler(8, NM_CLICK, [](HWND hWnd, UINT wID, UINT wCode, HWND hControl) -> LRESULT
    {
        ShellExecute(hWnd, _T("open"), _T("http://www.streamlet.org/"), _T(""), _T(""), SW_SHOW);

        return FALSE;
    });

    int nPos = 0;

    wnd.AppendMsgHandler(WM_VSCROLL, [&scroll, &nPos](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
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

    wnd.AppendMsgHandler(WM_DESTROY, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
    {
        PostQuitMessage(0);
        return FALSE;
    });

    wnd.ShowWindow();

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!IsDialogMessage(wnd.GetHWND(), &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}
