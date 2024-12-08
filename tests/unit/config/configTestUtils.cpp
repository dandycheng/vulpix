#include "configTestUtils.h"
#include "SystemMock.h"

bool Config_subClassTest::hasRequiredSubProperty(const char* propertyName, vector<subProperty_t>* subProperties)
{
    return Config::hasRequiredSubProperty(propertyName, subProperties);
}