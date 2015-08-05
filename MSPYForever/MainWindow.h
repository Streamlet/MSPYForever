#pragma once
#include <xl/Win32/GUI/xlDialog.h>
#include <xl/Win32/GUI/xlStdButton.h>
#include <xl/Win32/GUI/xlStdStatic.h>
#include <xl/Win32/GUI/xlStdLink.h>


#define MAINWINDOW_CLASSNAME    _T("MSPYForeverMainWindowByStreamlet")

class MainWindow : public xl::Dialog
{
public:
    static void Show();

private:
    MainWindow();
    ~MainWindow();

private:
    bool OnInitDialog() override;

private:
    LRESULT OnButtonClicked(HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled);
    LRESULT OnLinkWebsiteClick(HWND hWnd, UINT_PTR uID, UINT uCode, HWND hControl, BOOL &bHandled);

private:
    xl::StdStatic m_staticIcon;
    xl::StdStatic m_staticWatchword;
    xl::StdLink m_lineWebSite;
    xl::StdButton m_button;

    HFONT m_hFont;
};
