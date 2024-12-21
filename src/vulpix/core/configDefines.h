#ifndef CONFIG_KEYS_H
#define CONFIG_KEYS_H

#include <stdint.h>
#include <vector>

#define MAX_CHILD_PROPS_BITS             4
#define CHILD_PROP_MASK_ALL_REQUIRED     0xF
#define IS_BIT_SET(mask, pos)    (mask & (1 << pos))

typedef void* (*funcPtr_t)(void);
typedef uint8_t childPropBitmask_t;     // TODO: Write UT to confirm this is larger than MAX_CHILD_PROPS_BITS
typedef uint16_t configPropIndex_t;
typedef struct property
{
    string key;
    bool required;
    vector<configPropIndex_t> childProps;
    unsigned int childPropsRequiredMask : MAX_CHILD_PROPS_BITS;
    funcPtr_t getDefaultValue;
    funcPtr_t lambda;
} property_t;

#define CFG_PROP_STOP_ON_ERR          "stop_on_error"
#define CFG_PROP_NAME                 "name"
#define CFG_PROP_LINUX_PKG_MANAGER    "package_manager"
#define CFG_PROP_APT                  "apt"
#define CFG_PROP_YUM                  "yum"
#define CFG_PROP_ZYPPER               "zypper"
#define CFG_PROP_APTITUDE             "aptitude"
#define CFG_PROP_INSTALL              "install"
#define CFG_PROP_NAME                 "name"
#define CFG_PROP_ASSUME_YES           "assume_yes"
#define CFG_PROP_NO_GPG_CHECK         "no_gpg_check"

// Properties: Maps to CONFIG_TABLE, increment CFG_MAX_INDEX by 1 when adding a new config index.
// Use configPropIndex_t.

#define CFG_PROP_INDEX_NAME                     0
#define CFG_PROP_INDEX_LINUX_PACKAGE_MANAGER    1
#define CFG_PROP_INDEX_ASSUME_YES               2
#define CFG_PROP_INDEX_INSTALL                  3
#define CFG_PROP_INDEX_STOP_ON_ERR              4
#define CFG_PROP_INDEX_NO_GPG_CHECK             5

// WARNING: Config indices must be less than CFG_MAX_INDEX!
#define CFG_MAX_INDEX                   6
#define CFG_NOOP_PROP                   0xFFFF      // Default value for child props.

#define CFG_CHILD_PROPS(...)    { __VA_ARGS__ }
#define CFG_PROP_LINUX_PKG_MANAGER_CHILD_PROPS    CFG_CHILD_PROPS(CFG_PROP_INDEX_INSTALL, CFG_PROP_INDEX_ASSUME_YES, CFG_PROP_INDEX_NO_GPG_CHECK)

property_t const CONFIG_TABLE[]
{
//    key                            required    childProps                                 childPropsRequiredMask           getDefaultValue    lambda
    { CFG_PROP_NAME,                 true,       { },                                       CHILD_PROP_MASK_ALL_REQUIRED,    nullptr,           nullptr},
    { CFG_PROP_LINUX_PKG_MANAGER,    false,      CFG_PROP_LINUX_PKG_MANAGER_CHILD_PROPS,    0b001,                           nullptr,           nullptr},
    { CFG_PROP_ASSUME_YES,           false,      { },                                       CHILD_PROP_MASK_ALL_REQUIRED,    nullptr,           nullptr},
    { CFG_PROP_INSTALL,              true,       { },                                       CHILD_PROP_MASK_ALL_REQUIRED,    nullptr,           nullptr},
    { CFG_PROP_STOP_ON_ERR,          false,      { },                                       CHILD_PROP_MASK_ALL_REQUIRED,    nullptr,           nullptr},
    { CFG_PROP_NO_GPG_CHECK,         false,      { },                                       CHILD_PROP_MASK_ALL_REQUIRED,    nullptr,           nullptr}
};

#endif