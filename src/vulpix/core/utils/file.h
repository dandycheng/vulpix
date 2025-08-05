#ifndef VPX_CORE_UTILS_FILE_H
#define VPX_CORE_UTILS_FILE_H

#include <string>
#include <fstream>
#include <regex>

using namespace std;

string findTextInFile(string filePath, regex re);

#endif