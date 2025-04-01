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
    virtual ~PackageManagerBase(void);

    // virtual bool updatePackageInfo(void);
    virtual bool installPackage(SystemInterface* sys, vector<string>* packages, bool assumeYes = true, bool skipMalformedPackages = true) = 0;
    virtual bool removePackage(SystemInterface* sys, vector<string>* packages, bool assumeYes = true, bool skipMalformedPackages = true) = 0;
    virtual bool sanitizePackageNames(vector<string>* packages, bool printInvalidPackagenames = true);

private:
};

#endif