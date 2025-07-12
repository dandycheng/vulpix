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

    virtual bool runMacro(macroData_t data, bool isUndo);

private:
    virtual bool undoMacro(macroData_t data);

private:
    PackageManagerBase* m_pkgMgr;
};

#endif