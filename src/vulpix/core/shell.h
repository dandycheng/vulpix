#ifndef SHELL_H
#define SHELL_H

#include <cstdint>

enum ReturnCode
{
    COMMAND_SUCCESSFUL,
    COMMAND_UNSUCCESSFUL,
    NO_FILE_OR_DIR,
    UNKNOWN_ERROR
};

typedef uint8_t returnCode_t;

#endif