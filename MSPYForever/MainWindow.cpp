#include "MainWindow.h"
#include "RegKeyPrivilege.h"
#include "Utility.h"
#include "TraceLog.h"
#include "resource.h"
#include <tchar.h>
#include <xl/Win32/Registry/xlRegistry.h>


#define REG_MSPY_ROOT_80          _T("SOFTWARE\\Microsoft\\CTF\\TIP\\{81d4e9c9-1d3b-41bc-9e6c-4b40bf79e35e}")
#define REG_MSPY_ROOT_81          _T("SOFTWARE\\Microsoft\\CTF\\TIP\\{81d4e9c9-1d3b-41bc-9e6c-4b40bf79e35f}")
#define REG_MSPY_NE_PATH_SF       _T("\\LanguageProfile\\0x00000804\\{FA550B04-5AD7-411f-A5AC-CA038EC515D7}")
#define REG_MSPY_NE_PATH_NE       _T("\\LanguageProfile\\0x00000804\\{F3BA9077-6C7E-11D4-97FA-0080C882687E}")
#define REG_MSPY_NE_KEY_DESC      _T("Display Description")
#define REG_MSPY_NE_VALUE_DESC_NE _T("@%SystemRoot%\\SYSTEM32\\input.dll,-5091")
#define REG_MSPY_NE_KEY_ICON      _T("IconFile")
#define REG_MSPY_NE_VALUE_ICON_NE _T("%SystemRoot%\\SYSTEM32\\InputMethod\\Shared\\ResourceDll.dll")

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
    dlg.Create(600, 400, nullptr);
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

    m_staticWatchword.Create(ID_STATIC, this, 80, 20, 490, 300, WS_CHILD | WS_VISIBLE);
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

    m_button.Create(ID_BUTTON, this, 360, 320, 210, 30);
    m_button.SetWindowText(_T("�ͻ��˴��һس���ģʽ"));

    return true;
}

LRESULT MainWindow::OnButtonClicked(HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled)
{
    m_button.EnableWindow(FALSE);

    OSVersion osv = Utility::GetOSVersion();

    switch (osv)
    {
    case OSV_Win8:
        if (GetMspyForWin8())
        {
            MessageBox(_T("�Ѿ������һ� Win8 �µ�΢��ƴ������ģʽ����򿪿�������һ���������뷨��"), _T("��Ϣ"), MB_OK | MB_ICONINFORMATION);
        }
        else
        {
            MessageBox(_T("����ʧ�ܡ��ټ���"), nullptr, MB_OK | MB_ICONWARNING);
        }
        break;
    case OSV_Win81:
        if (GetMspyForWin81())
        {
            MessageBox(_T("�Ѿ������һ� Win8.1 �µ�΢ƴ����ģʽ����򿪿�������һ���������뷨��"), _T("��Ϣ"), MB_OK | MB_ICONINFORMATION);
        }
        else
        {
            MessageBox(_T("����ʧ�ܡ��ټ���"), nullptr, MB_OK | MB_ICONWARNING);
        }
        break;
    default:
        break;
    }

    return 0;
}

LRESULT MainWindow::OnLinkWebsiteClick(HWND hWnd, UINT_PTR uID, UINT uCode, HWND hControl, BOOL &bHandled)
{
    ShellExecute(m_hWnd, _T("open"), _T("http://www.streamlet.org/"), NULL, NULL, SW_SHOW);
    return FALSE;
}

bool MainWindow::GetMspyForWin8()
{
    RegKeyOwnerDaclAquireRestoreRec r(HKEY_LOCAL_MACHINE, REG_MSPY_ROOT_80);

    xl::String strPath = Utility::GetSystemDir() + _T("\\IME\\IMESC\\IMSCTIP.dll");

    if (!Utility::RegisterComDll(strPath.GetAddress()))
    {
        XL_ERROR(_T("Failed to register IMSCTIP.dll."));
        return false;
    }

#ifdef _WIN64
    strPath = Utility::GetSysWow64Dir() + _T("\\IME\\IMESC\\IMSCTIP.dll");

    if (!Utility::RegisterComDll(strPath.GetAddress()))
    {
        XL_ERROR(_T("Failed to register IMSCTIP.dll."));
        return false;
    }
#endif

    if (!xl::Registry::SetExpandString(HKEY_LOCAL_MACHINE,
                                       REG_MSPY_ROOT_80 REG_MSPY_NE_PATH_NE,
                                       REG_MSPY_NE_KEY_DESC,
                                       REG_MSPY_NE_VALUE_DESC_NE))
    {
        XL_ERROR(_T("Failed to set IME display description."));
        return false;
    }

    return true;
}

bool MainWindow::GetMspyForWin81()
{
    xl::String strExePath = Utility::GetExeDir();

    struct SourceDestFolder
    {
        xl::String strSource;
        xl::String strDest;
    };

    SourceDestFolder folderMap[] =
    {
        { strExePath + _T("\\Files\\Windows\\IME\\IMESC\0"),           Utility::GetWinDir() + _T("\\IME\\\0") },
#ifdef _WIN64
        { strExePath + _T("\\Files\\Windows\\System32\\IME\\IMESC\0"), Utility::GetSystemDir() + _T("\\IME\\\0") },
        { strExePath + _T("\\Files\\Windows\\SysWOW64\\IME\\IMESC\0"), Utility::GetSysWow64Dir() + _T("\\IME\\\0") },
#else
        { strExePath + _T("\\Files\\Windows\\SysWOW64\\IME\\IMESC\0"), Utility::GetSystemDir() + _T("\\IME\\\0") },
#endif
    };

    for (int i = 0; i < _countof(folderMap); ++i)
    {
        if (!Utility::SHCopyDir(m_hWnd, folderMap[i].strSource.GetAddress(), folderMap[i].strDest.GetAddress()))
        {
            XL_ERROR(_T("Failed to copy folder %s."), folderMap[i].strSource.GetAddress());
            return false;
        }
    }

    LPCTSTR lpszDllFiles[] =
    {
        _T("\\ImSCCfg.dll"),
        _T("\\ImSCCore.dll"),
        _T("\\IMSCDICB.dll"),
        _T("\\IMSCTIP.dll"),
        _T("\\applets\\PINTLCSA.dll"),
        _T("\\applets\\PINTLMBX.dll"),
    };

    xl::String strPath = Utility::GetSystemDir() + _T("\\IME\\IMESC");

    for (int i = 0; i < _countof(lpszDllFiles); ++i)
    {
        if (!Utility::RegisterComDll((strPath + lpszDllFiles[i]).GetAddress()))
        {
            XL_ERROR(_T("Failed to register %s."), (strPath + lpszDllFiles[i]).GetAddress());
            return false;
        }
    }

#ifdef _WIN64
    strPath = Utility::GetSysWow64Dir() + _T("\\IME\\IMESC");

    for (int i = 0; i < _countof(lpszDllFiles); ++i)
    {
        if (!Utility::RegisterComDll((strPath + lpszDllFiles[i]).GetAddress()))
        {
            XL_ERROR(_T("Failed to register %s."), (strPath + lpszDllFiles[i]).GetAddress());
            return false;
        }
    }
#endif

    if (!xl::Registry::DeleteKeyRecursion(HKEY_LOCAL_MACHINE, REG_MSPY_ROOT_81 REG_MSPY_NE_PATH_SF))
    {
        XL_ERROR(_T("Failed to delete MSPY SimpleFast."));
    }

    if (!xl::Registry::SetExpandString(HKEY_LOCAL_MACHINE,
                                       REG_MSPY_ROOT_81 REG_MSPY_NE_PATH_NE,
                                       REG_MSPY_NE_KEY_DESC,
                                       REG_MSPY_NE_VALUE_DESC_NE))
    {
        XL_ERROR(_T("Failed to set IME display description."));
        return false;
    }
    if (!xl::Registry::SetExpandString(HKEY_LOCAL_MACHINE,
                                       REG_MSPY_ROOT_81 REG_MSPY_NE_PATH_NE,
                                       REG_MSPY_NE_KEY_ICON,
                                       REG_MSPY_NE_VALUE_ICON_NE))
    {
        XL_ERROR(_T("Failed to set IME icon."));
        return false;
    }

    if (!Utility::MergeRegFile((strExePath + _T("\\Files\\Dict.reg")).GetAddress()))
    {
        XL_WARNING(_T("Failed to register dictionaries."));
    }

    return true;
}
