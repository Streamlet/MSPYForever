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
        MessageBox(nullptr, _T("������� 32 λ�汾��֧�� 64 λϵͳ�������� 64 λ�汾��"), nullptr, MB_OK | MB_ICONWARNING);
        return 0;
    }
#endif

    if (!Utility::SetPrivilege(SE_TAKE_OWNERSHIP_NAME, true) ||
        !Utility::SetPrivilege(SE_RESTORE_NAME, true))
    {
        MessageBox(nullptr, _T("�����漰һЩ��Ȩ�޵Ĳ��������Թ���Ա������б�����"), nullptr, MB_OK | MB_ICONWARNING);
        return 0;
    }

    if (Utility::GetOSVersion() == OSV_Other)
    {
        MessageBox(nullptr, _T("������ֻ֧�� Win8��Win8.1���ټ���"), nullptr, MB_OK | MB_ICONWARNING);
        return 0;
    }

    MainWindow::Show();

    return 0;
}
