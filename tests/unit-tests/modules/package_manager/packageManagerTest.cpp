#include <gtest/gtest.h>
#include "packageManagerTestUtils.h"
#include "Aptitude.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::StrEq;

TEST(UnitTest_Aptitude, testInstallPackage)
{
    SystemCallMock mock;
    vector<string> packages { "g++", "cmake", "bison" };
    Aptitude* apt { new Aptitude() };

    EXPECT_CALL(mock, system(StrEq("sudo apt install -y g++ cmake bison"))).Times(1);

    apt->installPackage(&mock, &packages, true, true);
    delete apt;
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}