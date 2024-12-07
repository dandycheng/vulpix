#include "PackageManagerBase.h"
#include "shell.h"
#include <gmock/gmock.h>

class SystemCallMock : public SystemCallInterface
{
public:
    MOCK_METHOD(int, system, (const char* cmd), (override));
};

class PackageManagerTest : public PackageManagerBase
{
public:
    PackageManagerTest(packageManager_t packageManagerType);

private:
    SystemCallInterface* m_sys;
};