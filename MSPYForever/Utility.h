#pragma once
#include <Windows.h>
#include <xl/Common/String/xlString.h>


enum OSVersion
{
    OSV_Win8,
    OSV_Win81,
    OSV_Win10,
    OSV_Win10_1803,
    OSV_Win10_21H2,
    OSV_Win11,
    OSV_Other,
};

namespace Utility
{
    bool IsWow64();
    OSVersion GetOSVersion();
    bool SetPrivilege(LPCTSTR szPrivilegeName, bool bEnable);

    xl::String GetKnownDir(int csidl);
    xl::String GetSystemDir();
    xl::String GetSysWow64Dir();
    xl::String GetWinDir();
    xl::String GetExeDir();
    xl::String GetExePath();

    bool SHCopyDir(LPCTSTR lpszSourceDir, LPCTSTR lpszDestDir);

    bool RunProcess(LPCTSTR lpszCmdLine, bool bWait = true);

    bool RegisterComDll(LPCTSTR lpszFileName);
    bool MergeRegFile(LPCTSTR lpszFileName);

    bool GetMspyForWin8();
    bool GetMspyForWin81(bool bCopyIMEShared = false);
}
