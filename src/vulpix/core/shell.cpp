#include "shell.h"

string joinCmd(vector<string>* cmd, string separator)
{
    string result = "";

    for (vector<string>::iterator i = cmd->begin(); i != cmd->end(); i++)
    {
        result += (i == (cmd->end() - 1) ? *i : *i + separator);
    }

    return result;
}

int runCmd(SystemInterface* sys, const char* cmd)
{
    return sys->system(cmd);
}

int System::system(const char* cmd)
{
    return ::system(cmd);
}