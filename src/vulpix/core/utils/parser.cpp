#include "parser.h"

namespace config_parser
{
bool isLambdaStrValid(string str)
{
    bool valid { true };
    size_t numVarPrefix { 0 };
    size_t numVarSuffix { 0 };
    smatch match;

    regex_search(str, REGEX_LAMBDA_VAR_PREFIX, regex_constants::match_not_null);
    numVarPrefix = match.size();
    regex_search(str, REGEX_LAMBDA_VAR_SUFFIX, regex_constants::match_not_null);
    numVarSuffix = match.size();

    // Check whether the variables include closing curly braces
    valid = numVarPrefix != numVarSuffix;

    // Check whether the variables are nested inside each other (throw error)
    return valid;
}

void findInnerVarBlock(string str, int& startIndex, int& endIndex, parseResult_t& parseResult)
{
    startIndex = -1;
    endIndex = -1;
    parseResult = PARSE_SUCCESS;

    if (str.size() == 0)
    {
        return;
    }

    string::const_iterator it = str.cbegin();
    uint8_t i = 0;
    uint8_t j = 0;

    for (uint8_t i = 0; i < str.size(); i++, j = str.size() - 1 - i)
    {
        // TODO: Check for escapes
        if ((str.at(i) == '$') && (str.at(i + 1) == '{'))
        {
            startIndex = i;
        }

        // Start searching the suffix from the end of the string.
        // TODO: Check for escapes
        // TODO: Inner var block?
        if (str.at(j) == '}' &&
            (((j - 1) > 0) && (str.at(j - 1) != '\\')))
        {
            endIndex = j;
        }
    }

    if ((startIndex >= 0) && (endIndex < 0))
    {
        parseResult = ERR_CLOSING_BRACKET_EXPECTED;
    }
    else if ((endIndex - startIndex) == LAMBDA_VAR_PREFIX_SZ)
    {
        parseResult = ERR_EMPTY_VAR;
    }
}

template<typename T>
void evalLambdaStr(string str, T item)
{
    // Parse from the most inner block first, so the upper
    // block can be evaluated accordingly.


}
}