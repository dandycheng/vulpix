#ifndef APTITUDE_H
#define APTITUDE_H

#include "PackageManagerBase.h"

class Aptitude : public PackageManagerBase
{
public:
    Aptitude(void);
    virtual ~Aptitude(void);

    // virtual bool updatePackageInfo(void) override;
    // virtual bool removePackage(vector<string>) override;
};

#endif