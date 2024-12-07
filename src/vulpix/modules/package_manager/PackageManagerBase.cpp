#include "PackageManagerBase.h"
#include "sanitizer.h"
#include "shell.h"
#include <iostream>

PackageManagerBase::PackageManagerBase(packageManager_t packageManagerType) :
    m_pkgMgr(packageManagerType),
    m_sys(new System())
{
    switch (packageManagerType)
    {
    case APTITUDE:
        m_cmd = "apt";
        break;

    case RPM:
        m_cmd = "rpm";
        break;

    case ZYPPER:
        m_cmd = "zypper";
        break;

    default:
        m_cmd = "";
        break;
    }
}

PackageManagerBase::~PackageManagerBase(void)
{
    delete m_sys;
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
    returnCode_t retCode { COMMAND_UNSUCCESSFUL };
    vector<string> cmdPrefix { "sudo", m_cmd, "install" };
    bool hasMalformedPkgs { sanitizePackageNames(packages) };

    if (hasMalformedPkgs && !skipMalformedPkgs)
    {
        cout << "Stopping.";
    }
    else
    {
        if (assumeYes)
        {
            cmdPrefix.push_back("-y");
        }

        packages->insert(packages->begin(), cmdPrefix.begin(), cmdPrefix.end());
        retCode = runCmd(sys, joinCmd(packages).c_str());
    }

    return retCode == COMMAND_SUCCESSFUL;
}