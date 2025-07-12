#ifndef MACRO_BASE_H
#define MACRO_BASE_H

#include "yaml-cpp/yaml.h"

class Config;

typedef bool (*macro_t)(void);
typedef YAML::Node macroData_t;

class MacroBase
{
public:
    MacroBase(Config* config);
    virtual ~MacroBase(void);

    virtual bool runMacro(macroData_t data) = 0;
    virtual bool undoMacro(macroData_t data) = 0;

protected:
    Config* m_config;
};

#endif