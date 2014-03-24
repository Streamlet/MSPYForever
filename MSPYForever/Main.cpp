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

    MainWindow::Show();

    return 0;
}
