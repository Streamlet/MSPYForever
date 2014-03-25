#include "MainWindow.h"
#include "Utility.h"
#include <Windows.h>
#include <tchar.h>


int WINAPI _tWinMain(__in HINSTANCE hInstance,
                     __in_opt HINSTANCE hPrevInstance,
                     __in LPTSTR lpCmdLine,
                     __in int nShowCmd)
{
#ifndef _WIN64
    if (Utility::IsWow64())
    {
        MessageBox(nullptr, _T("本软件的 32 位版本不支持 64 位系统，请运行 64 位版本。"), nullptr, MB_OK | MB_ICONWARNING);
        return 0;
    }
#endif

    if (!Utility::SetPrivilege(SE_TAKE_OWNERSHIP_NAME, true) ||
        !Utility::SetPrivilege(SE_RESTORE_NAME, true))
    {
        MessageBox(nullptr, _T("由于涉及一些高权限的操作，请以管理员身份运行本程序。"), nullptr, MB_OK | MB_ICONWARNING);
        return 0;
    }

    if (Utility::GetOSVersion() == OSV_Other)
    {
        MessageBox(nullptr, _T("本工具只支持 Win8、Win8.1。再见。"), nullptr, MB_OK | MB_ICONWARNING);
        return 0;
    }

    if (_tcsicmp(lpCmdLine, _T("/do")) == 0)
    {
        HWND hModalOwner = FindWindow(MAINWINDOW_CLASSNAME, nullptr);
        OSVersion osv = Utility::GetOSVersion();

        switch (osv)
        {
        case OSV_Win8:
            if (Utility::GetMspyForWin8())
            {
                MessageBox(hModalOwner, _T("已经帮您找回 Win8 下的微软拼音长句模式，请打开控制面板进一步设置输入法。"), _T("信息"), MB_OK | MB_ICONINFORMATION);
            }
            else
            {
                MessageBox(hModalOwner, _T("操作失败。再见。"), nullptr, MB_OK | MB_ICONWARNING);
            }
            break;
        case OSV_Win81:
            if (Utility::GetMspyForWin81())
            {
                MessageBox(hModalOwner, _T("已经帮您找回 Win8.1 下的微拼长句模式，请打开控制面板进一步设置输入法。"), _T("信息"), MB_OK | MB_ICONINFORMATION);
            }
            else
            {
                MessageBox(hModalOwner, _T("操作失败。再见。"), nullptr, MB_OK | MB_ICONWARNING);
            }
            break;
        default:
            break;
        }
    }
    else
    {
        MainWindow::Show();
    }

    return 0;
}
