#include "PackageManagerBase.h"
#include "sanitizer.h"
#include "shell.h"
#include <iostream>

PackageManagerBase::PackageManagerBase(packageManager_t packageManagerType)
{
}

PackageManagerBase::~PackageManagerBase(void)
{
}

/**
 * Abstract:
 *  Sanitizes packages names. Returns true if there are invalid package names.
 */
bool PackageManagerBase::sanitizePackageNames(vector<string>* packages, bool printInvalidPackagenames)
{
    vector<string> malformedPkgs;
    sanitizeStrings(packages, REGEX_PACKAGE_FORMAT, &malformedPkgs);

    if (printInvalidPackagenames & (malformedPkgs.size() > 0))
    {
        cout << "Config contains invalid packages names: \n";

        for (string pkg : malformedPkgs)
        {
            cout << "    - " << pkg << endl;
        }
    }

    return (malformedPkgs.size() > 0);
}

bool PackageManagerBase::installPackage(SystemInterface* sys, vector<string>* packages, bool assumeYes, bool skipMalformedPkgs)
{
    return COMMAND_SUCCESSFUL;
}

bool PackageManagerBase::removePackage(SystemInterface* sys, vector<string>* packages, bool assumeYes, bool skipMalformedPkgs)
{
    return COMMAND_UNSUCCESSFUL;
}