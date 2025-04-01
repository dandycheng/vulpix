#ifndef APTITUDE_H
#define APTITUDE_H

#include "PackageManagerBase.h"

class Aptitude : public PackageManagerBase
{
public:
    Aptitude(void);
    virtual ~Aptitude(void);

    // virtual bool updatePackageInfo(void);
    virtual bool installPackage(SystemInterface* sys, vector<string>* packages, bool assumeYes = true, bool skipMalformedPackages = true);
    virtual bool removePackage(SystemInterface* sys, vector<string>* packages, bool assumeYes = true, bool skipMalformedPackages = true);
private:
    string m_cmd;
};

#endif