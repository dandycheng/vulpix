#include "SystemMock.h"
#include <gtest/gtest.h>
#include "configTestUtils.h"

using ::testing::_;

class UnitTestFixture_Config : public testing::Test
{
protected:
    void SetUp() override
    {
        config = new ConfigTest("mock_config_valid.yaml");
    }

    void TearDown() override
    {
        delete config;
    }

    ConfigTest* config;
};

TEST_F(UnitTestFixture_Config, testGetConfigName)
{
    ASSERT_TRUE(config->getConfigName().compare("kernel build") == 0);
}

TEST_F(UnitTestFixture_Config, testIsConfigValid)
{
    ASSERT_TRUE(config->isConfigValid(CFG_PROP_INDEX_LINUX_PACKAGE_MANAGER));
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}