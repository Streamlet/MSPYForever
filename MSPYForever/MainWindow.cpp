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
    dlg.Create(600, 400, nullptr, MAINWINDOW_CLASSNAME);
    dlg.DoModal();
}

MainWindow::MainWindow()
{
    AppendCommandMsgHandler(ID_BUTTON, BN_CLICKED, CommandMsgHandler(this, &MainWindow::OnButtonClicked));
    AppendNotifyMsgHandler(ID_LINK, NM_CLICK, NotifyMsgHandler(this, &MainWindow::OnLinkWebsiteClick));
}

MainWindow::~MainWindow()
{

}

bool MainWindow::OnInitDialog()
{
    HICON hLargeIcon = (HICON)LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_APP), IMAGE_ICON, 48, 48, 0);
    HICON hSmallIcon = (HICON)LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_APP), IMAGE_ICON, 16, 16, 0);
    SetIcon(hLargeIcon);
    SetIcon(hSmallIcon, FALSE);

    SetWindowText(_T("������ȥ�ĵ�΢ƴ����ģʽ"));

    m_staticIcon.Create(ID_STATIC, this, 20, 20, 48, 48, WS_CHILD | WS_VISIBLE | SS_ICON);
    m_staticIcon.SetIcon(hLargeIcon);

    m_staticWatchword.Create(ID_STATIC, this, 80, 20, 470, 300, WS_CHILD | WS_VISIBLE);
    m_staticWatchword.SetFont(ms_hFontCaption);
    m_staticWatchword.SetWindowText(_T("����������̨��:\r\n")
                                    _T("\r\n")
                                    _T("����������֪������ģʽ��΢��ƴ�����뷨���������ľ���ģʽ������ʥ���ɷ����ľ���ģʽ��\r\n")
                                    _T("\r\n")
                                    _T("���������������Ŵ������뷨�����������룬ɵ�ƴ�΢���վ�û�е���ס�������뷨���������")
                                    _T("�����ջ󣬾�Ȼ��Ȼ��Ȼ���� Windows 8 �з����˳���ģʽ��\r\n")
                                    _T("\r\n")
                                    _T("������˵�����ʩ����������񲻴�Ӧ���������񲻴�Ӧ����������᲻��Ӧ��\r\n")
                                    _T("\r\n")
                                    _T("������ɵ�ƴ�΢��������������һ�������и�������ν��֮��ԤҲ��\r\n"));

    m_lineWebSite.Create(ID_LINK, this, 80, 324, 120, 16, WS_CHILD | WS_VISIBLE);
    m_lineWebSite.SetWindowText(_T("<a>Ϫ����������ҳ�Ʒ</a>"));

    m_button.Create(ID_BUTTON, this, 390, 320, 160, 30);
    m_button.SetWindowText(_T("�ͻ��˴��һس���ģʽ"));
    Button_SetElevationRequiredState(m_button.GetHWND(), TRUE);

    return true;
}

LRESULT MainWindow::OnButtonClicked(HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled)
{
    ShellExecute(nullptr, _T("runas"), Utility::GetExePath().GetAddress(), _T("/do"), nullptr, SW_SHOW);
    return 0;
}

LRESULT MainWindow::OnLinkWebsiteClick(HWND hWnd, UINT_PTR uID, UINT uCode, HWND hControl, BOOL &bHandled)
{
    ShellExecute(m_hWnd, _T("open"), _T("http://www.streamlet.org/"), NULL, NULL, SW_SHOW);
    return 0;
}
