#include "parser.h"
#include <gtest/gtest.h>

TEST(UnitTest_Sanitizer, testSanitizeStrings)
{
    string test = "${test}";

    EXPECT_TRUE(isLambdaStrValid(test));
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}