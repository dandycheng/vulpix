#ifndef SANITIZER_H
#define SANITIZER_H

#include <string>
#include <vector>
#include <regex>

using namespace std;

// ECMAScript regular expressions
#define REGEX_PACKAGE_FORMAT     regex("^[A-Za-z0-9][A-Za-z0-9+._-]+[A-Za-z0-9]?$", std::regex_constants::ECMAScript)

bool regexIsValidPackageFormat(string text);
void sanitizeStrings(vector<string>* strings, regex re, vector<string>* malformedStrings = nullptr);

#endif