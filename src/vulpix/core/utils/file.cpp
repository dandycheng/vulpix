#include "file.h"
#include <iostream>

string findTextInFile(string filePath, regex re)
{
    ifstream ss(filePath, fstream::in);

    if (ss.good())
    {
        string line;
        smatch match;

        while (std::getline(ss, line))
        {
            if (regex_search(line, match, re))
            {
                return line;
            }
        }
    }

    ss.close();
    return "";
}
