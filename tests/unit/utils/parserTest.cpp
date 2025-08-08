#include "parser.h"
#include <vector>
#include <utility>
#include <gtest/gtest.h>
using namespace config_parser;

TEST(UnitTest_Sanitizer, testSanitizeStrings)
{
    string test = "${test}";

    EXPECT_TRUE(isLambdaStrValid(test));
}

TEST(UnitTest_Sanitizer, testFindInnerVarBlock)
{
    struct testItem
    {
        string testString;
        pair<int, int> startEndPos;
        parseResult_t parseResult;
    };

    testItem testItems[]
    {
        "my ${test} string",        { 3,   9 },    PARSE_SUCCESS,
        "my test string",           { -1, -1 },    PARSE_SUCCESS,
        "my test string}",          { -1, -1 },    PARSE_SUCCESS,
        "my test \\${string\\}",    { -1, -1 },    PARSE_SUCCESS,
        "my test\\${\\} string",    { -1, -1 },    PARSE_SUCCESS,
        "my\\}\\${test string",     { -1, -1 },    PARSE_SUCCESS,
        "${my test string",         { 0 , -1 },    ERR_CLOSING_BRACKET_EXPECTED,
        "my}${test string",         { 3,  -1 },    ERR_CLOSING_BRACKET_EXPECTED,
        "my test${} string",        { 7,   9 },    ERR_EMPTY_VAR
    };

    int startIndex = 0;
    int endIndex   = 0;
    parseResult_t parseResult { PARSE_SUCCESS };

    bool expectedIsActual = false;

    for (testItem t : testItems)
    {
        findInnerVarBlock(t.testString, startIndex, endIndex, parseResult);

        expectedIsActual = (startIndex == t.startEndPos.first) &&
                           (endIndex == t.startEndPos.second) && 
                           (parseResult == t.parseResult);

        EXPECT_TRUE(expectedIsActual)
            << "[Start index]  Expected: " << t.startEndPos.first << ", Actual: " << startIndex
            << "\n[End index]    Expected: " << t.startEndPos.second << ", Actual: " << endIndex
            << "\n[Parse result] Expected: " << t.parseResult << ", Actual: " << parseResult;
    }
}


int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
