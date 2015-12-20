#include "RegKeyPrivilege.h"
#include <xl/Common/Memory/xlMemory.h>
#include <xl/Common/Meta/xlScopeExit.h>
#include <xl/Windows/Registry/xlRegistry.h>
#include <tchar.h>
#include "TraceLog.h"

RegKeyPrivilegeAquireRestore::RegKeyPrivilegeAquireRestore(REGSAM samDesired,
                                                           SECURITY_INFORMATION SecurityInformation) :
    m_samDesired(samDesired),
    m_SecurityInformation(SecurityInformation),
    m_hRootKey(nullptr),
    m_bBackedup(false)
{


}

RegKeyPrivilegeAquireRestore::~RegKeyPrivilegeAquireRestore()
{
    Restore();
}

bool RegKeyPrivilegeAquireRestore::Restore()
{
    XL_INFO_FUNCTION();

    if (!m_bBackedup)
    {
        return false;
    }

    HKEY hKey = nullptr;

    LSTATUS lRes = RegOpenKeyEx(m_hRootKey,
                   m_strSubKey,
                   0,
                   m_samDesired,
                   &hKey);

    if (lRes != ERROR_SUCCESS || hKey == nullptr)
    {
        XL_ERROR(_T("Failed to open Key: %s."), (LPCTSTR)m_strSubKey);
        return false;
    }

    XL_ON_BLOCK_EXIT(RegCloseKey, hKey);

    PSECURITY_DESCRIPTOR pSd = (PSECURITY_DESCRIPTOR)m_pOldSd.RawPointer();
    lRes = RegSetKeySecurity(hKey, m_SecurityInformation, pSd);

    if (lRes != ERROR_SUCCESS)
    {
        XL_ERROR(_T("Failed to restore security information to Key: %s."), (LPCTSTR)m_strSubKey);
        return false;
    }

    m_bBackedup = false;

    return true;
}

bool RegKeyPrivilegeAquireRestore::Backup(HKEY hRootKey, LPCTSTR lpszSubKey)
{
    XL_INFO_FUNCTION();

    if (m_bBackedup)
    {
        XL_INFO(_T("Already backedup, no need to backup again. Key: %s."), lpszSubKey);
        return false;
    }

    m_hRootKey = hRootKey;
    m_strSubKey = lpszSubKey;

    HKEY hKey = nullptr;

    LSTATUS lRes = RegOpenKeyEx(m_hRootKey,
                                m_strSubKey,
                                0,
                                READ_CONTROL,
                                &hKey);

    if (lRes != ERROR_SUCCESS || hKey == nullptr)
    {
        XL_ERROR(_T("Failed to open key with READ_CONTROL access. Key: %s."), (LPCTSTR)m_strSubKey);
        return false;
    }

    XL_ON_BLOCK_EXIT(RegCloseKey, hKey);

    DWORD dwSize = 0;
    lRes = RegGetKeySecurity(hKey, m_SecurityInformation, nullptr, &dwSize);

    if (lRes != ERROR_INSUFFICIENT_BUFFER)
    {
        XL_ERROR(_T("Failed to get security information of Key: %s."), (LPCTSTR)m_strSubKey);
        return false;
    }

    m_pOldSd = new BYTE[dwSize];
    PSECURITY_DESCRIPTOR pSd = (PSECURITY_DESCRIPTOR)m_pOldSd.RawPointer();
    lRes = RegGetKeySecurity(hKey, m_SecurityInformation, pSd, &dwSize);

    if (lRes != ERROR_SUCCESS)
    {
        XL_ERROR(_T("Failed to get security information of Key: %s."), (LPCTSTR)m_strSubKey);
        return false;
    }

    m_bBackedup = true;

    return true;
}

RegKeyOwnerAquireRestore::RegKeyOwnerAquireRestore() :
    RegKeyPrivilegeAquireRestore(WRITE_OWNER, OWNER_SECURITY_INFORMATION)
{

}

RegKeyOwnerAquireRestore::~RegKeyOwnerAquireRestore()
{

}

bool RegKeyOwnerAquireRestore::Aquire(HKEY hRootKey, LPCTSTR lpszSubKey)
{
    XL_INFO_FUNCTION();

    if (!Backup(hRootKey, lpszSubKey))
    {
        XL_WARNING(_T("Failed to backup, operation will not be restored. Key lpszSubKey."));
    }

    HKEY hKey = nullptr;

    LSTATUS lRes = RegOpenKeyEx(hRootKey,
                                lpszSubKey,
                                0,
                                WRITE_OWNER,
                                &hKey);

    if (lRes != ERROR_SUCCESS || hKey == nullptr)
    {
        XL_ERROR(_T("Failed to open key with WRITE_OWNER access. Key: %s."), lpszSubKey);
        return false;
    }

    XL_ON_BLOCK_EXIT(RegCloseKey, hKey);

    SECURITY_DESCRIPTOR sd = {};

    if (!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION))
    {
        XL_ERROR(_T("Failed to initialize security descriptor."));
        return false;
    }

    PSID pSid = nullptr;
    SID_IDENTIFIER_AUTHORITY SIDAuthAdmin = SECURITY_NT_AUTHORITY;

    if (!AllocateAndInitializeSid(&SIDAuthAdmin, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pSid))
    {
        XL_ERROR(_T("Failed to initialize Sid for Administrators."));
        return false;
    }

    XL_ON_BLOCK_EXIT(FreeSid, pSid);

    if (!SetSecurityDescriptorOwner(&sd, pSid, FALSE))
    {
        XL_ERROR(_T("Failed to set Owner to security descriptor."));
        return false;
    }

    lRes = RegSetKeySecurity(hKey, OWNER_SECURITY_INFORMATION, &sd);

    if (lRes != ERROR_SUCCESS)
    {
        XL_ERROR(_T("Failed to set Owner to Key: %s."), lpszSubKey);
        return false;
    }

    return true;
}

RegKeyDaclAquireRestore::RegKeyDaclAquireRestore() :
    RegKeyPrivilegeAquireRestore(WRITE_DAC, DACL_SECURITY_INFORMATION)
{

}

RegKeyDaclAquireRestore::~RegKeyDaclAquireRestore()
{

}

bool RegKeyDaclAquireRestore::Aquire(HKEY hRootKey, LPCTSTR lpszSubKey)
{
    XL_INFO_FUNCTION();

    Backup(hRootKey, lpszSubKey);

    HKEY hKey = nullptr;

    LSTATUS lRes = RegOpenKeyEx(hRootKey,
                                lpszSubKey,
                                0,
                                WRITE_DAC,
                                &hKey);

    if (lRes != ERROR_SUCCESS || hKey == nullptr)
    {
        XL_ERROR(_T("Failed to open key with WRITE_DAC access. Key: %s."), lpszSubKey);
        return false;
    }

    XL_ON_BLOCK_EXIT(RegCloseKey, hKey);

    SECURITY_DESCRIPTOR sd = {};

    if (!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION))
    {
        XL_ERROR(_T("Failed to initialize security descriptor."));
        return false;
    }

    if (!SetSecurityDescriptorDacl(&sd, FALSE, nullptr, FALSE))
    {
        XL_ERROR(_T("Failed to clear DACL in security descriptor."));
        return false;
    }

    lRes = RegSetKeySecurity(hKey, DACL_SECURITY_INFORMATION, &sd);

    if (lRes != ERROR_SUCCESS)
    {
        XL_ERROR(_T("Failed to set DACL to Key: %s."), lpszSubKey);
        return false;
    }

    return true;
}

RegKeyOwnerDaclAquireRestoreRec::RegKeyOwnerDaclAquireRestoreRec(HKEY hRootKey, LPCTSTR lpszSubKey)
{
    Aquire(hRootKey, lpszSubKey);
}

RegKeyOwnerDaclAquireRestoreRec::~RegKeyOwnerDaclAquireRestoreRec()
{
    Restore();
}

bool RegKeyOwnerDaclAquireRestoreRec::Aquire(HKEY hRootKey, LPCTSTR lpszSubKey)
{
    XL_INFO_FUNCTION();

    IRegKeyPrivilegeAquireRestore *pOwner = new RegKeyOwnerAquireRestore();

    if (!pOwner->Aquire(hRootKey, lpszSubKey))
    {
        XL_ERROR(_T("Failed to aquire Owner for Key: %s."), lpszSubKey);
        return false;
    }

    m_listAquireRestore.PushBack(pOwner);

    IRegKeyPrivilegeAquireRestore *pDacl = new RegKeyDaclAquireRestore();

    if (!pDacl->Aquire(hRootKey, lpszSubKey))
    {
        XL_ERROR(_T("Failed to aquire DACL for Key: %s."), lpszSubKey);
        return false;
    }

    m_listAquireRestore.PushBack(pDacl);

    xl::String strPath = lpszSubKey;
    xl::Array<xl::String> arrSubKeys;
    xl::Windows::Registry::EnumSubKey(hRootKey, strPath, &arrSubKeys);

    for (auto it = arrSubKeys.Begin(); it != arrSubKeys.End(); ++it)
    {
        if (!Aquire(hRootKey, (strPath + L"\\" + *it)))
        {
            return false;
        }
    }

    return true;
}

bool RegKeyOwnerDaclAquireRestoreRec::Restore()
{
    XL_INFO_FUNCTION();

    bool bRet = true;

    for (auto it = m_listAquireRestore.ReverseBegin(); it != m_listAquireRestore.ReverseEnd(); ++it)
    {
        bRet = (*it)->Restore() && bRet;
    }

    return bRet;
}
