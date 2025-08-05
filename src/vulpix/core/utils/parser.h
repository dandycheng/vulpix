#ifndef VPX_CORE_UTILS_PARSER_H
#define VPX_CORE_UTILS_PARSER_H

#include <cstdint>
#include <string>
#include <regex>

using namespace std;

#define REGEX_LAMBDA_VAR_PREFIX     regex("\${", std::regex_constants::ECMAScript)
#define REGEX_LAMBDA_VAR_SUFFIX     regex("}", std::regex_constants::ECMAScript)

typedef uint8_t lambdaStr_t;

bool isLambdaStrValid(string str);

template<typename T> void evalLambdaStr(string str, T item);

#endif