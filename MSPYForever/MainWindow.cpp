#include "MainWindow.h"
#include "resource.h"
#include "Utility.h"
#include <tchar.h>

enum
{
    ID_STATIC = -1,
    ID_NULL = 0,

    ID_START = 100,

    ID_BUTTON,
    ID_LINK,
};

void MainWindow::Show()
{
    MainWindow dlg;
    dlg.Create(nullptr, 600, 400, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, MAINWINDOW_CLASSNAME);
    dlg.DoModal();
}

MainWindow::MainWindow() : m_hFont(nullptr)
{
    AppendCommandMsgHandler(ID_BUTTON, BN_CLICKED, CommandMsgHandler(this, &MainWindow::OnButtonClicked));
    AppendNotifyMsgHandler(ID_LINK, NM_CLICK, NotifyMsgHandler(this, &MainWindow::OnLinkWebsiteClick));

    NONCLIENTMETRICS m_tagNONCLIENTMETRICSW = { sizeof(m_tagNONCLIENTMETRICSW) };
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &m_tagNONCLIENTMETRICSW, 0);

    m_hFont = CreateFontIndirect(&m_tagNONCLIENTMETRICSW.lfCaptionFont);
}

MainWindow::~MainWindow()
{
    if (m_hFont != nullptr)
    {
        DeleteObject(m_hFont);
        m_hFont = nullptr;
    }
}

bool MainWindow::OnInitDialog()
{
    HICON hLargeIcon = (HICON)LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_APP), IMAGE_ICON, 48, 48, 0);
    HICON hSmallIcon = (HICON)LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_APP), IMAGE_ICON, 16, 16, 0);
    SetIcon(hLargeIcon);
    SetIcon(hSmallIcon, FALSE);

    SetWindowText(_T("纪念逝去的的微拼长句模式"));
    SetFont(m_hFont);

    m_staticIcon.Create(m_hWnd, ID_STATIC, 20, 20, 48, 48, WS_CHILD | WS_VISIBLE | SS_ICON);
    m_staticIcon.SetIcon(hLargeIcon);

    m_staticWatchword.Create(m_hWnd, ID_STATIC, 80, 20, 470, 300, WS_CHILD | WS_VISIBLE);
    m_staticWatchword.SetWindowText(_T("来，跟我念台词:\r\n")
                                    _T("\r\n")
                                    _T("　　众所周知，长句模式是微软拼音输入法诞生以来的经典模式，是神圣不可放弃的精髓模式。\r\n")
                                    _T("\r\n")
                                    _T("　　近年来，随着词组输入法的兴起与流入，傻逼大微软终究没有抵制住词组输入法这个糖衣炮")
                                    _T("弹的诱惑，竟然毅然决然地在 Windows 8 中放弃了长句模式。\r\n")
                                    _T("\r\n")
                                    _T("　　如此倒行逆施，广大朝鲜人民不答应！阿佤人民不答应！大韩宇宙后裔不答应！\r\n")
                                    _T("\r\n")
                                    _T("　　望傻逼大微软悬崖勒马，在下一个升级中改正，勿谓言之不预也。\r\n"));

    m_lineWebSite.Create(m_hWnd, ID_LINK, 80, 324, 120, 16, WS_CHILD | WS_VISIBLE);
    m_lineWebSite.SetWindowText(_T("<a>溪流软件工作室出品</a>"));

    m_button.Create(m_hWnd, ID_BUTTON, 390, 320, 160, 30);
    m_button.SetWindowText(_T("猛击此处找回长句模式"));
    Button_SetElevationRequiredState(m_button, TRUE);

    return true;
}

LRESULT MainWindow::OnButtonClicked(HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled)
{
    ShellExecute(nullptr, _T("runas"), Utility::GetExePath(), _T("/do"), nullptr, SW_SHOW);
    return 0;
}

LRESULT MainWindow::OnLinkWebsiteClick(HWND hWnd, UINT_PTR uID, UINT uCode, HWND hControl, BOOL &bHandled)
{
    ShellExecute(m_hWnd, _T("open"), _T("http://www.streamlet.org/"), NULL, NULL, SW_SHOW);
    return 0;
}
