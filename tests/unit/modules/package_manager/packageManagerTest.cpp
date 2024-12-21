#include <gtest/gtest.h>
#include "packageManagerTestUtils.h"
#include "Aptitude.h"

using ::testing::Return;
using ::testing::StrEq;

TEST(UnitTest_Aptitude, testInstallPackage)
{
    SystemMock mock;
    Aptitude apt;

    struct testItem
    {
        packageManager_t pkgMgrType;
        vector<string> packages;
        bool skipMalformedPkgs;
        bool assumeYes;
        string expectCmd;
    };

    testItem testCases[] =
    {
        // pkgMgrType     packages                       skipMalformedPkgs    assumeYes    expectCmd
        {  APTITUDE,     { "g++", "cmake", "bison" },    true,                true,        "sudo apt install -y g++ cmake bison" },
        {  APTITUDE,     { "7zip", "android-sdk"   },    true,                false,       "sudo apt install 7zip android-sdk"   },
        {  APTITUDE,     { "#123", "build-essential" },  false,               true,        ""                                    },
    };

    uint8_t i = 0;

    for (testItem item : testCases)
    {
        bool validCmd = (item.expectCmd.length() > 0);

        if (validCmd)
        {
            EXPECT_CALL(mock, system(StrEq(item.expectCmd)))
                .Times(1)
                .WillOnce(Return(0));
        }

        if (item.pkgMgrType == APTITUDE)
        {
            ASSERT_EQ(apt.installPackage(&mock, &item.packages, item.assumeYes, item.skipMalformedPkgs), validCmd) << "Index: " << (i++);
        }
    }

}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}