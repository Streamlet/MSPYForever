#include "Utility.h"
#include "TraceLog.h"
#include "RegKeyPrivilege.h"
#include <VersionHelpers.h>
#include <ShlObj.h>
#include <tchar.h>
#include <xl/Meta/xlScopeExit.h>
#include <xl/Win32/Registry/xlRegistry.h>


// Win8
#define REG_MSPY_ROOT_80       _T("SOFTWARE\\Microsoft\\CTF\\TIP\\{81d4e9c9-1d3b-41bc-9e6c-4b40bf79e35e}")  // 总路径，要改权限

// Win8.1
#define REG_MSPY_ROOT_81       _T("SOFTWARE\\Microsoft\\CTF\\TIP\\{81d4e9c9-1d3b-41bc-9e6c-4b40bf79e35f}")  // 总路径
#define REG_MSPY_PATH_SF       _T("\\LanguageProfile\\0x00000804\\{FA550B04-5AD7-411f-A5AC-CA038EC515D7}")  // 微软拼音简拼，注册后要删除
#define REG_MSPY_PATH_NE       _T("\\LanguageProfile\\0x00000804\\{F3BA9077-6C7E-11D4-97FA-0080C882687E}")  // 微软拼音新体验

// 声明支持 Metro 应用的 GUID，见 http://msdn.microsoft.com/zh-cn/library/windows/apps/hh967425.aspx#SET_COMPATIBILITY_FLAG
#define REG_MSPY_PATH_CATEGORY_IMMERSIVESUPPORT      _T("\\Category\\Category\\{13A016DF-560B-46CD-947A-4C3AF1E0E35D}\\{81d4e9c9-1d3b-41bc-9e6c-4b40bf79e35e}") 
#define REG_MSPY_PATH_CATEGORY_ITEM_IMMERSIVESUPPORT _T("\\Category\\Item\\{81d4e9c9-1d3b-41bc-9e6c-4b40bf79e35e}\\{13A016DF-560B-46CD-947A-4C3AF1E0E35D}")
// 声明支持托盘图标
#define REG_MSPY_PATH_CATEGORY_SYSTRAYSUPPORT        _T("\\Category\\Category\\{25504FB4-7BAB-4BC1-9C69-CF81890F0EF5}\\{81d4e9c9-1d3b-41bc-9e6c-4b40bf79e35e}")
#define REG_MSPY_PATH_CATEGORY_ITEM_SYSTRAYSUPPORT   _T("\\Category\\Item\\{81d4e9c9-1d3b-41bc-9e6c-4b40bf79e35e}\\{25504FB4-7BAB-4BC1-9C69-CF81890F0EF5}")

// Win8、Win8.1 公用
#define REG_MSPY_KEY_DESC      _T("Display Description")
#define REG_MSPY_VALUE_DESC_NE _T("@%SystemRoot%\\SYSTEM32\\input.dll,-5091")
#define REG_MSPY_KEY_ICON      _T("IconFile")
#define REG_MSPY_VALUE_ICON_NE _T("%SystemRoot%\\SYSTEM32\\InputMethod\\Shared\\ResourceDll.dll")

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
    xl::String strPath = GetExePath();
    int iPos = strPath.LastIndexOf(_T("\\"));

    return strPath.SubString(0, iPos);
}

xl::String Utility::GetExePath()
{
    TCHAR szPath[MAX_PATH] = {};

    if (GetModuleFileName(nullptr, szPath, _countof(szPath)) == 0)
    {
        XL_ERROR(_T("Failed to get exe directory."));
        return _T("");
    }

    return szPath;
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

bool Utility::RunProcess(LPCTSTR lpszCmdLine, bool bWait/* = true*/)
{
    STARTUPINFOW si = { sizeof(STARTUPINFOW) };
    PROCESS_INFORMATION pi = {};

    int iLen = (int)_tcslen(lpszCmdLine) + 1;
    xl::SharedArray<TCHAR> lp = new TCHAR[iLen];
    _tcscpy_s(lp.RawPointer(), iLen, lpszCmdLine);

    if (!CreateProcess(nullptr, lp.RawPointer(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi))
    {
        XL_ERROR(_T("Failed to create process with CmdLine: %s."), lpszCmdLine);
        return false;
    }

    if (bWait)
    {
        WaitForSingleObject(pi.hProcess, INFINITE);
    }

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return true;
}

bool Utility::RegisterComDll(LPCTSTR lpszFileName)
{
    XL_INFO_FUNCTION();

    xl::String strCmdLine = _T("regsvr32 /s ");
    strCmdLine += _T("\"");
    strCmdLine += lpszFileName;
    strCmdLine += _T("\"");

    if (!RunProcess(strCmdLine.GetAddress()))
    {
        return false;
    }

    return true;
}

bool Utility::MergeRegFile(LPCTSTR lpszFileName)
{
    XL_INFO_FUNCTION();

    xl::String strCmdLine = _T("regedit /s ");
    strCmdLine += _T("\"");
    strCmdLine += lpszFileName;
    strCmdLine += _T("\"");

    if (!RunProcess(strCmdLine.GetAddress()))
    {
        return false;
    }

    return true;
}

bool Utility::GetMspyForWin8()
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
                                       REG_MSPY_ROOT_80 REG_MSPY_PATH_NE,
                                       REG_MSPY_KEY_DESC,
                                       REG_MSPY_VALUE_DESC_NE))
    {
        XL_ERROR(_T("Failed to set IME display description."));
        return false;
    }

    return true;
}

bool Utility::GetMspyForWin81()
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
        if (!Utility::SHCopyDir(nullptr, folderMap[i].strSource.GetAddress(), folderMap[i].strDest.GetAddress()))
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

    if (!xl::Registry::DeleteKeyRecursion(HKEY_LOCAL_MACHINE, REG_MSPY_ROOT_81 REG_MSPY_PATH_SF))
    {
        XL_ERROR(_T("Failed to delete MSPY SimpleFast."));
    }

    if (!xl::Registry::SetExpandString(HKEY_LOCAL_MACHINE,
                                       REG_MSPY_ROOT_81 REG_MSPY_PATH_NE,
                                       REG_MSPY_KEY_DESC,
                                       REG_MSPY_VALUE_DESC_NE))
    {
        XL_ERROR(_T("Failed to set IME display description."));
        return false;
    }
    if (!xl::Registry::SetExpandString(HKEY_LOCAL_MACHINE,
                                       REG_MSPY_ROOT_81 REG_MSPY_PATH_NE,
                                       REG_MSPY_KEY_ICON,
                                       REG_MSPY_VALUE_ICON_NE))
    {
        XL_ERROR(_T("Failed to set IME icon."));
        return false;
    }

    if (!xl::Registry::CreateKey(HKEY_LOCAL_MACHINE, REG_MSPY_ROOT_81 REG_MSPY_PATH_CATEGORY_IMMERSIVESUPPORT) ||
        !xl::Registry::CreateKey(HKEY_LOCAL_MACHINE, REG_MSPY_ROOT_81 REG_MSPY_PATH_CATEGORY_ITEM_IMMERSIVESUPPORT))
    {
        XL_WARNING(_T("Failed to declare Metro compatibility."));
    }
    if (!xl::Registry::CreateKey(HKEY_LOCAL_MACHINE, REG_MSPY_ROOT_81 REG_MSPY_PATH_CATEGORY_SYSTRAYSUPPORT) ||
        !xl::Registry::CreateKey(HKEY_LOCAL_MACHINE, REG_MSPY_ROOT_81 REG_MSPY_PATH_CATEGORY_ITEM_SYSTRAYSUPPORT))
    {
        XL_WARNING(_T("Failed to declare systray support."));
    }

    if (!Utility::MergeRegFile((strExePath + _T("\\Files\\Dict.reg")).GetAddress()))
    {
        XL_WARNING(_T("Failed to register dictionaries."));
    }

    return true;
}
