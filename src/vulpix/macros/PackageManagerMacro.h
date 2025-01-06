#ifndef PACKAGE_MANAGER_H
#define PACKAGE_MANAGER_H

#include "MacroBase.h"
#include "PackageManagerBase.h"
#include "config.h"

class PackageManagerMacro : public MacroBase
{
public:
    PackageManagerMacro(Config* config);
    ~PackageManagerMacro(void);
    virtual bool runMacro(void);
    virtual bool undoMacro(void);

private:
    PackageManagerBase* m_pkgMgr;
};

#endif