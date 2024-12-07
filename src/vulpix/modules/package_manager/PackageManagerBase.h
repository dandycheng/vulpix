#ifndef PACKAGE_MANAGER_BASE_H
#define PACKAGE_MANAGER_BASE_H

#include <string>
#include <vector>
#include "shell.h"

using namespace std;

typedef enum PackageManagerType
{
    APTITUDE,
    RPM,
    ZYPPER,
    UNKNOWN_PKG_MGR
} packageManager_t;

class PackageManagerBase
{
public:
    PackageManagerBase(packageManager_t packageManagerType);
    ~PackageManagerBase(void);

    // virtual bool updatePackageInfo(void);
    virtual bool installPackage(SystemCallInterface* sys, vector<string>* packages, bool assumeYes = true, bool skipMalformedPackages = true);
    // virtual bool removePackage(vector<string> packages);
    virtual void sanitizePackageNames(vector<string>* packages, bool printInvalidPackagenames = true);

private:
    string m_cmd;
    packageManager_t m_pkgMgr;
    SystemCall* m_sys;
};

#endif