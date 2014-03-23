#pragma once
#include <Windows.h>
#include <xl/Containers/xlArray.h>
#include <xl/String/xlString.h>
#include <xl/Win32/Memory/xlSafeSmartPtr.h>


struct IRegKeyPrivilegeAquireRestore
{
    virtual ~IRegKeyPrivilegeAquireRestore()
    {
    
    }

    virtual bool Aquire(HKEY hRootKey, LPCTSTR lpszSubKey) = 0;
    virtual bool Restore() = 0;
};

class RegKeyPrivilegeAquireRestore : public IRegKeyPrivilegeAquireRestore
{
public:
    RegKeyPrivilegeAquireRestore(REGSAM samDesired, SECURITY_INFORMATION SecurityInformation);
    ~RegKeyPrivilegeAquireRestore();

public:
    bool Restore() override;

protected:
    bool Backup(HKEY hRootKey, LPCTSTR lpszSubKey);

private:
    REGSAM m_samDesired;
    SECURITY_INFORMATION m_SecurityInformation;
    HKEY m_hRootKey;
    xl::String m_strSubKey;
    xl::SafeSharedArray<BYTE> m_pOldSd;
    bool m_bBackedup;
};

class RegKeyOwnerAquireRestore : public RegKeyPrivilegeAquireRestore
{
public:
    RegKeyOwnerAquireRestore();
    ~RegKeyOwnerAquireRestore();

public:
    bool Aquire(HKEY hRootKey, LPCTSTR lpszSubKey) override;
};

class RegKeyDaclAquireRestore : public RegKeyPrivilegeAquireRestore
{
public:
    RegKeyDaclAquireRestore();
    ~RegKeyDaclAquireRestore();

public:
    bool Aquire(HKEY hRootKey, LPCTSTR lpszSubKey) override;
};

class RegKeyOwnerDaclAquireRestoreRec
{
public:
    RegKeyOwnerDaclAquireRestoreRec(HKEY hRootKey, LPCTSTR lpszSubKey);
    ~RegKeyOwnerDaclAquireRestoreRec();

private:
    bool Aquire(HKEY hRootKey, LPCTSTR lpszSubKey);
    bool Restore();

private:
    typedef xl::SafeSharedPtr<IRegKeyPrivilegeAquireRestore> IRegKeyPrivilegeAquireRestorePtr;
    typedef xl::Array<IRegKeyPrivilegeAquireRestorePtr> IRegKeyPrivilegeAquireRestorePtrList;

    IRegKeyPrivilegeAquireRestorePtrList m_listAquireRestore;
};