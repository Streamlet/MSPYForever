#pragma once
#include <xl/Win32/GUI/xlDialog.h>
#include <xl/Win32/GUI/xlStdButton.h>
#include <xl/Win32/GUI/xlStdStatic.h>


class MainWindow : public xl::Dialog
{
public:
    MainWindow();
    ~MainWindow();

private:
    bool OnInitDialog() override;

private:
    LRESULT OnButtonClicked(HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled);

private:
    bool GetMspyForWin8();
    bool GetMspyForWin81();

private:
    xl::StdStatic m_staticIcon;
    xl::StdButton m_button;
};
