#include "PackageManagerBase.h"
#include "PackageManagerMacro.h"
#include "Aptitude.h"
#include "distro.h"
#include <vector>

PackageManagerMacro::PackageManagerMacro(Config* config) :
    MacroBase(config),
    m_pkgMgr(nullptr)
{
}

PackageManagerMacro::~PackageManagerMacro(void)
{
}

bool PackageManagerMacro::runMacro(void)
{
    bool success { false };

    switch (getDistro())
    {
        case UBUNTU:
            m_pkgMgr = new Aptitude();
            break;
        default:
            break;
    }

    if (m_pkgMgr != nullptr)
    {
        System sys;
        YAML::Node packageManagerNode { (*m_config)[CFG_PROP_INDEX_LINUX_PACKAGE_MANAGER] };
        YAML::Node installs           { packageManagerNode[CFG_PROP_INSTALL] };
        bool assumeYes                { packageManagerNode[CFG_PROP_ASSUME_YES].as<bool>() };
        vector<string> installsVec    { installs.as<vector<string>>() };

        success = m_pkgMgr->installPackage(&sys, &installsVec, assumeYes);
    }

    return success;
}

bool PackageManagerMacro::undoMacro(void)
{
    return true;    // TODO: Complete
}