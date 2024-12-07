#ifndef CONFIG_H
#define CONFIG_H

#include "yaml-cpp/yaml.h"
#include "configKeys.h"
#include "shell.h"
#include <vector>
#include <string>
#include <cstdint>
#include <array>
#include <iostream>

using namespace std;

#define OS_RELEASE_PATH "/etc/os-release"

typedef enum Distro
{
    UBUNTU,
    REDHAT,
    OPEN_SUSE,
    UNKNOWN_DISTRO
} distro_t;

typedef enum DataType
{
    STRING,
    BOOL,
    INT,
    DOUBLE,
    STRUCT,
    INVALID_DATA_TYPE
} dataType_t;

/*
Sub property types. Increase in the power of 2.
Note: Update NUM_SUB_PROPERTIES when updating this.
*/
typedef enum SubProperty
{
    NO_SUB_PROPERTY      = 0x0000,
    INSTALL              = 0x0001,
    ASSUME_YES           = 0x0002,
    NO_GPG_CHECK         = 0x0004,
    INVALID_SUB_PROPERTY = 0xFFFF
} subProperty_t;

#define NUM_SUB_PROPERTIES      4

const std::array<std::pair<int, string>, NUM_SUB_PROPERTIES> g_subProperties
{{
    { INSTALL,         CFG_KEY_INSTALL      },
    { ASSUME_YES,      CFG_KEY_ASSUME_YES   },
    { NO_GPG_CHECK,    CFG_KEY_NO_GPG_CHECK },
}};

typedef uint16_t requiredPropMask_t;
typedef void* (*funcPtr_t)(void);
typedef struct propertyStruct
{
    const char* key;
    bool required;
    bool allowsChildren;
    funcPtr_t getDefaultValue;
    dataType_t dataType;
    requiredPropMask_t requiredSubPropertyMask;
} property_t;


void* getDefaultValueStopOnError(void);

// TODO: Consider using LinkedList for compile time evaluation?
const property_t g_configTypes[] =
{
    // key                    required    allowsChildren    getDefaultValue                 dataType    requiredSubPropertyMask
    { CFG_KEY_NAME,           true,       false,            nullptr,                        STRING,     NO_SUB_PROPERTY        },
    { CFG_KEY_APT,            false,      true,             nullptr,                        STRING,     (INSTALL | ASSUME_YES) },
    { CFG_KEY_STOP_ON_ERR,    false,      false,            &getDefaultValueStopOnError,    BOOL,       NO_SUB_PROPERTY        }
};

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

private:
    System* m_sys;
};

distro_t getDistro(void);

#endif