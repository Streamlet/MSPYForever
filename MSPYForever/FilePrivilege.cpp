#include "FilePrivilege.h"
#include <xl/Common/Memory/xlMemory.h>
#include <xl/Common/Meta/xlScopeExit.h>
#include <xl/Windows/Registry/xlRegistry.h>
#include <aclapi.h>
#include <tchar.h>
#include "TraceLog.h"

FilePrivilegeAquireRestore::FilePrivilegeAquireRestore(REGSAM samDesired,
    SECURITY_INFORMATION SecurityInformation) :
    m_samDesired(samDesired),
    m_SecurityInformation(SecurityInformation),
    m_bBackedup(false)
{


}

FilePrivilegeAquireRestore::~FilePrivilegeAquireRestore()
{
    Restore();
}

bool FilePrivilegeAquireRestore::Restore()
{
    XL_INFO_FUNCTION();

    if (!m_bBackedup)
    {
        return false;
    }

    DWORD dwRes = SetNamedSecurityInfo(const_cast<LPTSTR>((LPCTSTR)m_strPath),
        SE_FILE_OBJECT,
        m_SecurityInformation,
        m_psidOwner,
        m_psidGroup,
        m_pDacl,
        m_pSacl);

    if (dwRes != ERROR_SUCCESS)
    {
        XL_ERROR(_T("Failed to restore security information to File: %s."), (LPCTSTR)m_strPath);
        return false;
    }

    LocalFree(m_pSecurityDescriptor);

    m_bBackedup = false;

    return true;
}

bool FilePrivilegeAquireRestore::Backup(LPCTSTR lpszPath)
{
    XL_INFO_FUNCTION();

    if (m_bBackedup)
    {
        XL_INFO(_T("Already backedup, no need to backup again. File: %s."), lpszPath);
        return false;
    }

    m_strPath = lpszPath;

    DWORD dwRes = GetNamedSecurityInfo(m_strPath,
        SE_FILE_OBJECT,
        m_SecurityInformation,
        &m_psidOwner,
        &m_psidGroup,
        &m_pDacl,
        &m_pSacl,
        &m_pSecurityDescriptor);

    if (dwRes != ERROR_SUCCESS)
    {
        XL_ERROR(_T("Failed to open file with READ_CONTROL access. File: %s."), (LPCTSTR)m_strPath);
        return false;
    }

    m_bBackedup = true;

    return true;
}

FileOwnerAquireRestore::FileOwnerAquireRestore() :
    FilePrivilegeAquireRestore(WRITE_OWNER, OWNER_SECURITY_INFORMATION)
{

}

FileOwnerAquireRestore::~FileOwnerAquireRestore()
{

}

bool FileOwnerAquireRestore::Aquire(LPCTSTR lpszPath)
{
    XL_INFO_FUNCTION();

    if (!Backup(lpszPath))
    {
        XL_WARNING(_T("Failed to backup, operation will not be restored. Key %s."), lpszPath);
    }

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

    DWORD dwRes = SetNamedSecurityInfo(const_cast<LPTSTR>(lpszPath),
        SE_FILE_OBJECT,
        OWNER_SECURITY_INFORMATION,
        pSid,
        NULL,
        NULL,
        NULL);

    if (dwRes != ERROR_SUCCESS)
    {
        XL_ERROR(_T("Failed to set Owner to File: %s."), lpszPath);
        return false;
    }

    return true;
}

FileDaclAquireRestore::FileDaclAquireRestore() :
    FilePrivilegeAquireRestore(WRITE_DAC, DACL_SECURITY_INFORMATION)
{

}

FileDaclAquireRestore::~FileDaclAquireRestore()
{

}

bool FileDaclAquireRestore::Aquire(LPCTSTR lpszPath)
{
    XL_INFO_FUNCTION();

    if (!Backup(lpszPath))
    {
        XL_WARNING(_T("Failed to backup, operation will not be restored. File %s."), lpszPath);
    }

    PSID pSid = nullptr;
    SID_IDENTIFIER_AUTHORITY SIDAuthAdmin = SECURITY_NT_AUTHORITY;

    if (!AllocateAndInitializeSid(&SIDAuthAdmin, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pSid))
    {
        XL_ERROR(_T("Failed to initialize Sid for Administrators."));
        return false;
    }

    XL_ON_BLOCK_EXIT(FreeSid, pSid);

    EXPLICIT_ACCESS ea = {};
    ea.grfAccessPermissions = STANDARD_RIGHTS_ALL | SPECIFIC_RIGHTS_ALL | ACCESS_SYSTEM_SECURITY | MAXIMUM_ALLOWED;
    ea.grfAccessMode = SET_ACCESS;
    ea.grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
    ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ea.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
    ea.Trustee.ptstrName = (LPTSTR)pSid;

    PACL pDACL = NULL;
    DWORD dwRes = SetEntriesInAcl(1, &ea, NULL, &pDACL);
    if (dwRes != ERROR_SUCCESS)
    {
        XL_ERROR(_T("Failed to set DACL."));
        return false;
    }

    DWORD lRes = SetNamedSecurityInfo(const_cast<LPTSTR>(lpszPath),
        SE_FILE_OBJECT,
        DACL_SECURITY_INFORMATION,
        NULL,
        NULL,
        pDACL,
        NULL);

    if (lRes != ERROR_SUCCESS)
    {
        XL_ERROR(_T("Failed to set DACL to File: %s."), lpszPath);
        return false;
    }

    return true;
}
