#ifndef SYSTEM_MOCK_H
#define SYSTEM_MOCK_H

#include "shell.h"
#include <gmock/gmock.h>

class SystemMock : public SystemInterface
{
public:
    MOCK_METHOD(int, system, (const char* cmd), (override));
};

#endif