#pragma once
#include <xl/Windows/GUI/xlDialog.h>
#include <xl/Windows/GUI/xlStdButton.h>
#include <xl/Windows/GUI/xlStdStatic.h>
#include <xl/Windows/GUI/xlStdLink.h>


#define MAINWINDOW_CLASSNAME    _T("MSPYForeverMainWindowByStreamlet")

class MainWindow : public xl::Windows::Dialog
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
    xl::Windows::StdStatic m_staticIcon;
    xl::Windows::StdStatic m_staticWatchword;
    xl::Windows::StdLink m_lineWebSite;
    xl::Windows::StdButton m_button;

    HFONT m_hFont;
};
