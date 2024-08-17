#ifndef CONFIG_DEFINES_H
#define CONFIG_DEFINES_H

#include <string>
#include <cstdint>
#include <array>

using namespace std;

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
    { INSTALL,         "install"    },
    { ASSUME_YES,      "assume_yes" },
    { NO_GPG_CHECK,    "nogpgcheck" },
}};

typedef uint16_t requiredPropMask_t;
typedef struct propertyStruct
{
    const char* key;
    bool required;
    bool allowsChildren;
    void* (*getDefaultValue)(void);
    dataType_t dataType;
    requiredPropMask_t requiredSubPropertyMask;
} property_t;

void* getDefaultValueStopOnError(void);

const property_t g_configTypes[] =
{
    // key                required    allowsChildren    getDefaultValue                 dataType    requiredSubPropertyMask
    { "name",             true,       false,            nullptr,                        STRING,     NO_SUB_PROPERTY        },
    { "apt",              false,      true,             nullptr,                        STRING,     (INSTALL | ASSUME_YES) },
    { "stop_on_error",    false,      false,            &getDefaultValueStopOnError,    BOOL,       NO_SUB_PROPERTY        }
};

#endif