#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

enum ReturnCode
{
    COMMAND_UNSUCCESSFUL = -1,
    COMMAND_SUCCESSFUL,
    NO_FILE_OR_DIR,
    UNKNOWN_ERROR
};

typedef int returnCode_t;

class SystemInterface
{
public:
    virtual ~SystemInterface() = default;
    virtual int system(const char* cmd) = 0;
};

class System : public SystemInterface
{
public:
    int system(const char* cmd);
};

string joinCmd(vector<string>* cmd, string separator = " ");
int runCmd(SystemInterface* sys, const char* cmd);

#endif