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

    if (_tcsicmp(lpCmdLine, _T("/do")) == 0)
    {
        HWND hModalOwner = FindWindow(MAINWINDOW_CLASSNAME, nullptr);
        OSVersion osv = Utility::GetOSVersion();

        switch (osv)
        {
        case OSV_Win8:
            if (Utility::GetMspyForWin8())
            {
                MessageBox(hModalOwner, _T("�Ѿ������һ� Win8 �µ�΢��ƴ������ģʽ����򿪿�������һ���������뷨��"), _T("��Ϣ"), MB_OK | MB_ICONINFORMATION);
            }
            else
            {
                MessageBox(hModalOwner, _T("����ʧ�ܡ��ټ���"), nullptr, MB_OK | MB_ICONWARNING);
            }
            break;
        case OSV_Win81:
            if (Utility::GetMspyForWin81())
            {
                MessageBox(hModalOwner, _T("�Ѿ������һ� Win8.1 �µ�΢ƴ����ģʽ����򿪿�������һ���������뷨��"), _T("��Ϣ"), MB_OK | MB_ICONINFORMATION);
            }
            else
            {
                MessageBox(hModalOwner, _T("����ʧ�ܡ��ټ���"), nullptr, MB_OK | MB_ICONWARNING);
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
