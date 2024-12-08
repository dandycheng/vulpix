#include "SystemMock.h"
#include <gtest/gtest.h>
#include "configTestUtils.h"

using ::testing::_;

class UnitTestFixture_Config : public testing::Test
{
protected:
    void SetUp() override
    {
        m_config = new Config_subClassTest("mock_config_valid.yaml");
    }

    void TearDown() override
    {
        delete m_config;
    }

    Config_subClassTest* m_config;
};

TEST_F(UnitTestFixture_Config, testConfigDefaultValuesBool)
{
    struct testItem
    {
        void* (*func)(void);
        bool defaultVal;
    };

    testItem defaultValFuncs[] =
    {
        { &getDefaultValueStopOnError, true }
    };

    for (testItem item : defaultValFuncs)
    {
        EXPECT_EQ((bool) item.func(), item.defaultVal);
    }
}

TEST_F(UnitTestFixture_Config, testHasRequiredSubPropertyVariantCase)
{
    struct testItem
    {
        const char* key;
        vector<subProperty_t> subProperties;
        bool expect;
    };

    vector<subProperty_t> emptyVector;

    testItem testItems[] =
    {
        { "apt",    { INSTALL, NO_SUB_PROPERTY },    false },
        { "apt",    { NO_SUB_PROPERTY, INSTALL },    false },
        { "apt",    emptyVector,                     false }
    };

    uint8_t testSize = sizeof(testItems) / sizeof(testItems[0]);

    for (uint8_t i = 0; i < testSize; i++)
    {
        EXPECT_EQ(m_config->hasRequiredSubProperty("apt", &testItems[i].subProperties), testItems[i].expect);
    }
}

TEST_F(UnitTestFixture_Config, testConfigValidity)
{
    EXPECT_TRUE(m_config->isConfigValid());
}

TEST(UnitTest_Config, testGetDistroParameters)
{
    regex re = regex("^ID", regex_constants::ECMAScript);
    smatch match;
    string dummyString { "ID=ubuntu" };

    ASSERT_EQ(OS_RELEASE_PATH, "/etc/os-release");
    ASSERT_TRUE(regex_search(dummyString, match, re));
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}