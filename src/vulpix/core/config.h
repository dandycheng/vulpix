
#include "yaml-cpp/yaml.h"
#include "shell.h"
#include <vector>
#include <string>
#include <stdint.h>
#include <array>
#include <iostream>
#include "configDefines.h"

class Config
{
public:
    Config(string configFile);
    ~Config(void);

    string getConfigName(void) const;
    bool setupConfig(void);
    bool isConfigValid(configPropIndex_t index);
    const vector<configPropIndex_t>* getChildProps(configPropIndex_t index);

protected:
    YAML::Node m_config;

private:
    System* m_sys;
};