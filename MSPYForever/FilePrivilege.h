#pragma once
#include <Windows.h>
#include <xl/Common/Containers/xlArray.h>
#include <xl/Common/String/xlString.h>
#include <xl/Windows/Memory/xlSafeSmartPtr.h>


struct IFilePrivilegeAquireRestore
{
    virtual ~IFilePrivilegeAquireRestore()
    {

    }

    virtual bool Aquire(LPCTSTR lpszPath) = 0;
    virtual bool Restore() = 0;
};

class FilePrivilegeAquireRestore : public IFilePrivilegeAquireRestore
{
public:
    FilePrivilegeAquireRestore(REGSAM samDesired, SECURITY_INFORMATION SecurityInformation);
    ~FilePrivilegeAquireRestore();

public:
    bool Restore() override;

protected:
    bool Backup(LPCTSTR lpszPath);

private:
    REGSAM m_samDesired;
    SECURITY_INFORMATION m_SecurityInformation;
    xl::String m_strPath;
    PSID m_psidOwner = NULL;
    PSID m_psidGroup = NULL;
    PACL m_pDacl = NULL;
    PACL m_pSacl = NULL;
    PSECURITY_DESCRIPTOR m_pSecurityDescriptor = NULL;
    bool m_bBackedup;
};

class FileOwnerAquireRestore : public FilePrivilegeAquireRestore
{
public:
    FileOwnerAquireRestore();
    ~FileOwnerAquireRestore();

public:
    bool Aquire(LPCTSTR lpszPath) override;
};

class FileDaclAquireRestore : public FilePrivilegeAquireRestore
{
public:
    FileDaclAquireRestore();
    ~FileDaclAquireRestore();

public:
    bool Aquire(LPCTSTR lpszPath) override;
};
