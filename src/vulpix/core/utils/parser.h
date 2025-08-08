#ifndef VPX_CORE_UTILS_PARSER_H
#define VPX_CORE_UTILS_PARSER_H

#include <cstdint>
#include <string>
#include <regex>

using namespace std;

namespace config_parser
{

#define REGEX_LAMBDA_VAR_PREFIX     regex("\\$\\{", std::regex_constants::ECMAScript)
#define REGEX_LAMBDA_VAR_SUFFIX     regex("\\}", std::regex_constants::ECMAScript)

typedef uint8_t lambdaStr_t;

typedef enum ParseResult
{
    PARSE_SUCCESS,
    ERR_CLOSING_BRACKET_EXPECTED,
    ERR_EMPTY_VAR
} parseResult_t;

bool isLambdaStrValid(string str);
void findInnerVarBlock(string str, int& startIndex, int& endIndex, parseResult_t& parseResult);
template<typename T> void evalLambdaStr(string str, T item);

}

#endif