#ifndef CONFIG_H
#define CONFIG_H

#include "yaml-cpp/yaml.h"
#include "shell.h"
#include <vector>
#include <string>
#include <stdint.h>
#include <array>
#include <iostream>
#include "configDefines.h"
#include "PackageManagerMacro.h"

// TODO: Create wrapper for YAML parser

class Config
{
public:
    Config(string configFile);
    ~Config(void);

    string getConfigName(void) const;
    bool setupConfig(void);
    bool isConfigPropValid(configPropIndex_t index);
    bool verifyConfigFile(void);
    bool runModuleMacro(configPropIndex_t index);

    node_t operator [] (configPropIndex_t index) const;

    static vector<string> strNodeToVec(node_t node);    // TODO: Move this to wrapper

protected:
    node_t m_config;
    bool m_stopOnErr;

private:
    System* m_sys;
};

#endif