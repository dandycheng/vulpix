#include "sanitizer.h"

bool regexIsValidPackageFormat(string text)
{
    return true;
}

void sanitizeStrings(vector<string>* strings, regex re, vector<string>* malformedStrings)
{
    smatch match;
    vector<string>::iterator i = (*strings).begin();

    for (; i < (*strings).end(); i++)
    {
        if (!regex_match(*i, match, re))
        {
            if (malformedStrings != nullptr)
            {
                malformedStrings->push_back(*i);
            }

            (*strings).erase(i);
            --i;
        }
    }
}