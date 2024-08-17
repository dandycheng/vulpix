#ifndef VPX_CONFIG_H
#define VPX_CONFIG_H

#include "yaml-cpp/yaml.h"
#include "configDefines.h"
#include "packageManager.h"
#include <vector>

using namespace std;

class Config
{
public:
    Config(string configFile);
    ~Config(void);

    const string getConfigName(void);
    bool setupConfig(void);
    bool isConfigValid(void);
    bool stopOnError(void);
    vector<string> getInstalls(string key);

protected:
    bool hasRequiredSubProperty(string key, vector<subProperty_t>* subProperties);
    bool hasRequiredSubProperty(const char* key, vector<subProperty_t>* subProperties);

    YAML::Node m_config;
};

#endif