#include "Aptitude.h"
#include "sanitizer.h"
#include "shell.h"
#include <iostream>

Aptitude::Aptitude(void) :
    PackageManagerBase(APTITUDE),
    m_cmd("apt")
{
}

Aptitude::~Aptitude(void)
{
}

// TODO: Refactor
bool Aptitude::installPackage(SystemInterface* sys, vector<string>* packages, bool assumeYes, bool skipMalformedPkgs)
{
    returnCode_t retCode     { COMMAND_UNSUCCESSFUL };
    vector<string> cmdPrefix { "sudo", m_cmd, "install" };
    bool hasMalformedPkgs    { sanitizePackageNames(packages) };

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

bool Aptitude::removePackage(SystemInterface* sys, vector<string>* packages, bool assumeYes, bool skipMalformedPkgs)
{
    returnCode_t retCode     { COMMAND_UNSUCCESSFUL };
    vector<string> cmdPrefix { "sudo", m_cmd, "remove" };
    bool hasMalformedPkgs    { sanitizePackageNames(packages) };

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