//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2011-02-24
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../Include/xl/Windows/GUI/xlWindow.h"
#include "../../Include/xl/Windows/GUI/xlMenu.h"
#include "../../Include/xl/Windows/GUI/xlDialog.h"
#include "../../Include/xl/Windows/GUI/xlStdStatic.h"
#include "../../Include/xl/Windows/GUI/xlStdButton.h"
#include "../../Include/xl/Windows/GUI/xlStdEdit.h"
#include "../../Include/xl/Windows/GUI/xlStdComboBox.h"
#include "../../Include/xl/Windows/GUI/xlStdListBox.h"
#include "../../Include/xl/Windows/GUI/xlStdScrollBar.h"
#include "../../Include/xl/Windows/GUI/xlStdListView.h"
#include "../../Include/xl/Windows/GUI/xlStdLink.h"
#include "../../Include/xl/Windows/GUI/xlStdProgressBar.h"

int WINAPI wWinMain(__in HINSTANCE hInstance,
                     __in_opt HINSTANCE hPrevInstance,
                     __in LPTSTR lpCmdLine,
                     __in int nShowCmd)
{
    xl::Windows::Menu popupMenu;
    popupMenu.CreatePopup();
    popupMenu.AppendMenu(MF_POPUP | MF_STRING, 103, L"&New");
    popupMenu.AppendMenu(MF_POPUP | MF_STRING, 104, L"&Open");
    popupMenu.AppendMenu(MF_POPUP | MF_SEPARATOR, 0, nullptr);
    popupMenu.AppendMenu(MF_POPUP | MF_STRING, 105, L"&Quit");

    xl::Windows::Menu mainMenu;
    mainMenu.Create();
    mainMenu.AppendMenu(MF_POPUP, (UINT_PTR)(HMENU)popupMenu, L"&File");
    mainMenu.AppendMenu(MF_STRING, 101, L"&Edit");
    mainMenu.AppendMenu(MF_SEPARATOR, 0, nullptr);
    mainMenu.AppendMenu(MF_STRING, 102, L"&Help");

    xl::Windows::Window wnd;
    wnd.Create(nullptr, 300, 240, 500, 400, WS_OVERLAPPEDWINDOW, 0);
    wnd.SetWindowText(L"MyWindow");
    wnd.SetMenu(mainMenu);

    xl::Windows::StdStatic label;
    label.Create(wnd, 1, 80, 30, 200, 18);
    label.SetWindowText(L"Please input:");

    xl::Windows::StdEdit edit;
    edit.Create(wnd, 2, 80, 50, 200, 24);

    xl::Windows::StdButton button;
    button.Create(wnd, 3, 80, 80, 200, 24);
    button.SetWindowText(L"Show Dialog");

    xl::Windows::StdComboBox combo;
    combo.Create(wnd, 4, 80, 110, 200, 100);
    combo.AddString(L"Please select");
    combo.AddString(L"Item1");
    combo.AddString(L"Item2");
    combo.AddString(L"Item3");
    combo.SetCurSel(0);

    xl::Windows::StdListBox list;
    list.Create(wnd, 5, 80, 140, 200, 100);
    list.AddString(L"ListItem1");
    list.AddString(L"ListItem2");
    list.AddString(L"ListItem3");

    xl::Windows::StdScrollBar scroll;
    scroll.Create(wnd, 6, 474, 0, 20, 372);
    scroll.SetScrollRange(0, 100);

    xl::Windows::StdListView listview;
    listview.Create(wnd, 7, 300, 30, 160, 150);
    listview.AddColumn(L"Column0", 0);
    listview.AddColumn(L"Column1", 1);
    listview.AddItem(0, 0, L"R0C0");
    listview.AddItem(0, 1, L"R0C1");
    listview.AddItem(1, 0, L"R1C0");
    listview.AddItem(1, 1, L"R1C1");
    listview.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT);

    xl::Windows::StdLink link;
    link.Create(wnd, 8, 300, 200, 160, 20);
    SetWindowText(link, L"<a href=\"http://www.streamlet.org/\">·ÃÎÊÏªÁ÷ÍøÕ¾</a>");

    xl::Windows::StdProgressBar progressbar;
    progressbar.Create(wnd, 9, 300, 240, 160, 20);
    progressbar.OffsetPos(60);

    wnd.AppendMsgHandler(WM_RBUTTONUP, [&popupMenu](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) -> LRESULT
    {
        POINT point = {};
        GetCursorPos(&point);
        popupMenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, hWnd, nullptr);

        return FALSE;
    });

    wnd.AppendMenuCommandMsgHandler(103, [&wnd](HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled) -> LRESULT
    {
        wnd.MessageBox(L"Menu", NULL, MB_OK);

        return FALSE;
    });

    wnd.AppendCommandMsgHandler(2, EN_CHANGE, [&label, &edit](HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled) -> LRESULT
    {
        wchar_t szText[MAX_PATH];
        edit.GetWindowText(szText, MAX_PATH);
        label.SetWindowText(szText);

        return FALSE;
    });

    wnd.AppendCommandMsgHandler(3, [&wnd](HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled) -> LRESULT
    {
        xl::Windows::Dialog dlg;
        dlg.Create(wnd, 400, 400);
        dlg.SetWindowText(L"MyDialog");

        INT_PTR nID = dlg.DoModal();

        return FALSE;
    });

    wnd.AppendCommandMsgHandler(4, CBN_SELCHANGE, [&edit, &combo](HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled) ->LRESULT
    {
        wchar_t szText[MAX_PATH];
        combo.GetWindowText(szText, MAX_PATH);
        edit.SetWindowText(szText);

        return FALSE;
    });

    wnd.AppendCommandMsgHandler(5, LBN_SELCHANGE, [&edit, &list](HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled) ->LRESULT
    {
        wchar_t szText[MAX_PATH];
        list.GetText(list.GetCurSel(), szText);
        edit.SetWindowText(szText);

        return FALSE;
    });

    wnd.AppendNotifyMsgHandler(8, NM_CLICK, [](HWND hWnd, LPNMHDR lpNMHDR, BOOL &bHandled) -> LRESULT
    {
        ShellExecute(hWnd, L"open", L"http://www.streamlet.org/", L"", L"", SW_SHOW);

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

    wnd.ShowWindow(SW_SHOW);

    MSG msg = {};

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
