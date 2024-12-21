#include "file.h"
#include <iostream>

/*
TODO: Add file compression/archive and decompression/unarchive utility
        - Compress/uncompresss each file
*/
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
