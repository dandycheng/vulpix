#ifndef PACKAGE_MANAGER_H
#define PACKAGE_MANAGER_H

#include <string>
#include <vector>

using namespace std;

bool aptInstallPackages(vector<string>* pkgs, bool assumeYes = false, bool skipMalformedPkgs = true);

#endif