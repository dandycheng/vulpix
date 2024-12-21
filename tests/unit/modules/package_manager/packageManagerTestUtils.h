#include "PackageManagerBase.h"
#include "shell.h"
#include "SystemMock.h"
#include <gmock/gmock.h>

class PackageManagerTest : public PackageManagerBase
{
public:
    PackageManagerTest(packageManager_t packageManagerType);

private:
    SystemInterface* m_sys;
};