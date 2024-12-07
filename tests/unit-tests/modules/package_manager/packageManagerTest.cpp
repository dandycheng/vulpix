#include <gtest/gtest.h>
#include "packageManagerTestUtils.h"
#include "Aptitude.h"

using ::testing::Return;
using ::testing::StrEq;

TEST(UnitTest_Aptitude, testInstallPackage)
{
    SystemMock mock;
    vector<string> packages { "g++", "cmake", "bison" };
    Aptitude apt;

    struct testItem
    {
        vector<string> packages;
        bool skipMalformedPkgs;
        bool assumeYes;
        string expectCmd;
    };

    testItem testCases[] =
    {
        // packages                       skipMalformedPkgs    assumeYes    expectCmd
        { { "g++", "cmake", "bison" },    true,                true,        "sudo apt install -y g++ cmake bison" },
        { { "7zip", "android-sdk"   },    true,                false,       "sudo apt install 7zip android-sdk"   },
        { { "#123", "build-essential" },  false,               true,        ""                                    },
    };

    uint8_t i = 0;

    for (testItem item : testCases)
    {
        if (item.expectCmd.length() > 0)
        {
            EXPECT_CALL(mock, system(StrEq(item.expectCmd)))
                .Times(1)
                .WillOnce(Return(0));
        }

        bool expectPass = (item.expectCmd.length() > 0);

        ASSERT_EQ(apt.installPackage(&mock, &item.packages, item.assumeYes, item.skipMalformedPkgs), expectPass) << "Index: " << (i++);
    }

}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}