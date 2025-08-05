#include "parser.h"

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

template<typename T>
void evalLambdaStr(string str, T item)
{

}