#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
#include <regex>

using namespace std;

string findTextInFile(string filePath, regex re);

#endif