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
};

MainWindow::MainWindow()
{
    AppendCommandMsgHandler(ID_BUTTON, BN_CLICKED, CommandMsgHandler(this, &MainWindow::OnButtonClicked));
}

MainWindow::~MainWindow()
{

}

bool MainWindow::OnInitDialog()
{
    HICON hIcon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_APP));
    SetIcon(hIcon);
    SetIcon(hIcon, FALSE);

    m_staticIcon.Create(ID_STATIC, this, 12, 10, 32, 32, WS_CHILD | WS_VISIBLE | SS_ICON);
    m_staticIcon.SetIcon(hIcon);
    m_button.Create(ID_BUTTON, this, 100, 100, 100, 25);
    m_button.SetWindowText(_T("开始"));

    return true;
}

LRESULT MainWindow::OnButtonClicked(HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled)
{
    OSVersion osv = Utility::GetOSVersion();

    switch (osv)
    {
    case OSV_Win8:
        if (GetMspyForWin8())
        {
            MessageBox(_T("已经帮您找回 Win8 下的微软拼音新体验模式，请打开控制面板设置输入法。"), _T("信息"), MB_OK | MB_ICONINFORMATION);
        }
        else
        {
            MessageBox(_T("操作失败。再见。"), nullptr, MB_OK | MB_ICONWARNING);
        }
        break;
    case OSV_Win81:
        if (GetMspyForWin81())
        {
            MessageBox(_T("已经帮您找回 Win8.1 下的微软拼音新体验模式，请打开控制面板设置输入法。"), _T("信息"), MB_OK | MB_ICONINFORMATION);
        }
        else
        {
            MessageBox(_T("操作失败。再见。"), nullptr, MB_OK | MB_ICONWARNING);
        }
        break;
    default:
        break;
    }

    return 0;
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
