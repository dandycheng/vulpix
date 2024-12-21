#include "sanitizer.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(UnitTest_Sanitizer, testSanitizeStrings)
{
    struct testItem
    {
        vector<string> input;
        regex re;
        vector<string> expect;
    };

    vector<string> emptyVector;

    testItem testItems[] =
    {
        { emptyVector,                                REGEX_PACKAGE_FORMAT,    emptyVector                           },
        { { "cmake", "build-essential", "g++"   },    REGEX_PACKAGE_FORMAT,    { "cmake", "build-essential", "g++" } },
        { { "#invalid-pkg", "$%^&", "", "---"   },    REGEX_PACKAGE_FORMAT,    emptyVector                           },
        { { "g + +", "python", "Dummy-package"  },    REGEX_PACKAGE_FORMAT,    { "python", "Dummy-package"         } }
    };

    for (testItem item : testItems)
    {
        sanitizeStrings(&item.input, item.re);

        if (item.expect.size() < 1)
        {
            EXPECT_LT(item.input.size(), 1);
        }
        else
        {
            EXPECT_TRUE(equal(item.expect.begin(), item.expect.end(), item.input.begin(), item.input.end()));
        }
    }
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}