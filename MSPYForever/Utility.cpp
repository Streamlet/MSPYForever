#include "Utility.h"
#include <VersionHelpers.h>
#include <ShlObj.h>
#include <tchar.h>
#include <xl/Meta/xlScopeExit.h>
#include "TraceLog.h"


bool Utility::IsWow64()
{
    typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);
    LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(_T("kernel32")), "IsWow64Process");

    BOOL bIsWow64 = FALSE;
    if (fnIsWow64Process != nullptr)
    {
        if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
        {
            XL_ERROR(_T("Failed to call IsWow64Process."));
        }
    }

    return !!bIsWow64;
}

OSVersion Utility::GetOSVersion()
{
    XL_INFO_FUNCTION();

    OSVersion osv = OSV_Other;
  
    do
    {
        if (IsWindows8OrGreater())
        {
            osv = OSV_Win8;
        }

        if (IsWindows8Point1OrGreater())
        {
            osv = OSV_Win81;
        }

        if (IsWindowsVersionOrGreater(6, 4, 0) || IsWindowsVersionOrGreater(7, 0, 0))
        {
            osv = OSV_Other;
        }

    } while (false);
    
    return osv;
}

bool Utility::SetPrivilege(LPCTSTR szPrivilegeName, bool bEnable)
{
    XL_INFO_FUNCTION();

    HANDLE hProcess = GetCurrentProcess();
    HANDLE hToken = NULL;

    if (!OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        XL_ERROR(_T("Failed to open current process token."));
        return false;
    }

    XL_ON_BLOCK_EXIT(CloseHandle, hToken);

    LUID luid = {};

    if (!LookupPrivilegeValue(NULL, szPrivilegeName, &luid))
    {
        XL_ERROR(_T("Failed to look up privilege value."));
        return false;
    }

    TOKEN_PRIVILEGES tp = {};

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;

    if (bEnable)
    {
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    }
    else
    {
        tp.Privileges[0].Attributes = SE_PRIVILEGE_REMOVED;
    }

    if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL))
    {
        XL_ERROR(_T("Failed to adjust token privileges."));
        return false;
    }

    return true;
}

bool Utility::RegisterComDll(LPCTSTR lpszFileName)
{
    XL_INFO_FUNCTION();

    HMODULE hModule = LoadLibrary(lpszFileName);

    if (hModule == nullptr)
    {
        XL_ERROR(_T("Failed to load DLL: %s."), lpszFileName);
        return false;
    }

    XL_ON_BLOCK_EXIT(FreeLibrary, hModule);

    typedef HRESULT (STDAPICALLTYPE *FNDllRegisterServer)();
    FNDllRegisterServer fnDllRegisterServer = (FNDllRegisterServer)GetProcAddress(hModule, "DllRegisterServer");

    if (fnDllRegisterServer == nullptr)
    {
        XL_ERROR(_T("Failed to find DllRegisterServer."));
        return false;
    }

    if (FAILED(fnDllRegisterServer()))
    {
        XL_ERROR(_T("Failed to call DllRegisterServer."));
        return false;
    }

    return true;
}

xl::String Utility::GetKnownDir(int csidl)
{
    TCHAR szPath[MAX_PATH] = {};

    if (FAILED(SHGetFolderPath(nullptr, csidl, nullptr, SHGFP_TYPE_CURRENT, szPath)))
    {
        XL_ERROR(_T("Failed to get known directory."));
        return _T("");
    }

    return szPath;
}

xl::String Utility::GetSystemDir()
{
    return GetKnownDir(CSIDL_SYSTEM);
}

xl::String Utility::GetSysWow64Dir()
{
    TCHAR szPath[MAX_PATH] = {};

    if (GetSystemWow64Directory(szPath, _countof(szPath)) == 0)
    {
        return _T("");
    }

    return szPath;
}

xl::String Utility::GetWinDir()
{
    return GetKnownDir(CSIDL_WINDOWS);
}

xl::String Utility::GetExeDir()
{
    TCHAR szPath[MAX_PATH] = {};

    if (GetModuleFileName(nullptr, szPath, _countof(szPath)) == 0)
    {
        XL_ERROR(_T("Failed to get exe directory."));
        return _T("");
    }

    xl::String strPath = szPath;
    int iPos = strPath.LastIndexOf(_T("\\"));

    return strPath.SubString(0, iPos);
}

bool Utility::SHCopyDir(HWND hWnd, LPCTSTR lpszSourceDir, LPCTSTR lpszDestDir)
{
    xl::String strSourceDir = lpszSourceDir;
    xl::String strDestDir = lpszDestDir;
    strSourceDir.AppendBack(_T('\0'));
    strDestDir.AppendBack(_T('\0'));

    SHFILEOPSTRUCT op = {};
    op.hwnd = hWnd;
    op.wFunc = FO_COPY;
    op.pFrom = strSourceDir.GetAddress();
    op.pTo = strDestDir.GetAddress();

    int iErrorCode = SHFileOperation(&op);

    if (iErrorCode != ERROR_SUCCESS)
    {
        return false;
    }

    return true;
}
