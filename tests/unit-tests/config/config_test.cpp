#include "config.h"
#include <gtest/gtest.h>
#include <iostream>

class Config_subClassTest : public Config
{
public:
    Config_subClassTest(string configFile) : Config(configFile) {}
    bool hasRequiredSubProperty(const char* propertyName, vector<subProperty_t>* subProperties)
    {
        return Config::hasRequiredSubProperty(propertyName, subProperties);
    }
};

class SkipFixture : public testing::Test
{
protected:
    void SetUp() override
    {
        GTEST_SKIP() << "Skipping all tests for this fixture.";
    }
};

class UnitTest_Config : public testing::Test
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

TEST_F(UnitTest_Config, testConfigDefaultValuesBool)
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

TEST_F(UnitTest_Config, testHasRequiredSubProperty)
{
    struct testItem
    {
        const char* key;
        vector<subProperty_t> subProperties;
        bool expect;
    };

    testItem testItems[] =
    {
        { "apt",  { INSTALL, ASSUME_YES },         true  },
        { "apt",  { INSTALL, NO_SUB_PROPERTY },    false },
        { "apt",  { NO_SUB_PROPERTY, INSTALL },    false }
    };

    uint8_t testSize = sizeof(testItems) / sizeof(testItems[0]);

    for (uint8_t i = 0; i < testSize; i++)
    {
        EXPECT_EQ(m_config->hasRequiredSubProperty("apt", &testItems[i].subProperties), testItems[i].expect);
    }
}

TEST_F(UnitTest_Config, testHasRequiredSubPropertyVariantCase)
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

TEST_F(UnitTest_Config, testConfigValidity)
{
    EXPECT_TRUE(m_config->isConfigValid());
}

// TODO: Test framework
TEST_F(SkipFixture, testConfigReadSanitizeStringStressTest)
{
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}