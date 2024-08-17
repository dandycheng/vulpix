#include "packageManager.h"
#include <iostream>
#include "sanitizer.h"
#include "logs.h"
#include "shellDefines.h"

// TODO: Create a base class for all package managers
/**
 * @brief
 * Installs a package via aptitude.
 * 
 * @param pkg_name Package name to install
 */
bool aptInstallPackages(vector<string>* pkgs, bool assumeYes, bool skipMalformedPkgs)
{
    returnCode_t retVal = COMMAND_UNSUCCESSFUL;
    string cmd { "sudo apt install " };
    vector<string> malformedPkgs;

    sanitizeStrings(pkgs, REGEX_PACKAGE_FORMAT, &malformedPkgs);

    if (malformedPkgs.size() > 0)
    {
        cout << "Config contains invalid packages names: \n";

        for (string pkg : malformedPkgs)
        {
                cout << "    - " << pkg << endl;
        }

        cout << (skipMalformedPkgs ? "Skipping invalid packages.\n" : "Stopping installation.\n") << endl;
    }

    if ((*pkgs).size() > 0)
    {
        for (string pkg : *pkgs)
        {
            cmd += " " + pkg;
        }

        if (assumeYes)
        {
            cmd += " -y";
        }

        cmd += ";";
        retVal = system(cmd.c_str());
    }
    else
    {
        cout << "Nothing to install.\n";
    }

    return (retVal == COMMAND_SUCCESSFUL);
}