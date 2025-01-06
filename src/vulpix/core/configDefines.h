#ifndef CONFIG_KEYS_H
#define CONFIG_KEYS_H

#include <stdint.h>
#include <vector>
#include "LambdaBase.h"

#define MAX_CHILD_PROPS_BITS             4
#define MAX_PROP_ROLE_BITS               2
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
    unsigned int role : MAX_PROP_ROLE_BITS;
    unsigned int childPropsRequiredMask : MAX_CHILD_PROPS_BITS;
    funcPtr_t getDefaultValue;
} property_t;


#define CFG_PROP_ROLE_PARENT          1
#define CFG_PROP_ROLE_CHILD           2
#define CFG_PROP_ROLE_BOTH            3

#define DEFINE_CFG_STR(config)        (string) config
#define CFG_PROP_STOP_ON_ERR          DEFINE_CFG_STR("stop_on_error")
#define CFG_PROP_NAME                 DEFINE_CFG_STR("name")
#define CFG_PROP_LINUX_PKG_MANAGER    DEFINE_CFG_STR("package_manager")
#define CFG_PROP_APT                  DEFINE_CFG_STR("apt")
#define CFG_PROP_YUM                  DEFINE_CFG_STR("yum")
#define CFG_PROP_ZYPPER               DEFINE_CFG_STR("zypper")
#define CFG_PROP_APTITUDE             DEFINE_CFG_STR("aptitude")
#define CFG_PROP_INSTALL              DEFINE_CFG_STR("install")
#define CFG_PROP_NAME                 DEFINE_CFG_STR("name")
#define CFG_PROP_ASSUME_YES           DEFINE_CFG_STR("assume_yes")
#define CFG_PROP_NO_GPG_CHECK         DEFINE_CFG_STR("no_gpg_check")

// Properties: Maps to CONFIG_TABLE, increment CFG_MAX_INDEX by 1 when adding a new config index.
// Use configPropIndex_t.

#define CFG_PROP_INDEX_NAME                     0x0000
#define CFG_PROP_INDEX_LINUX_PACKAGE_MANAGER    0x0001
#define CFG_PROP_INDEX_ASSUME_YES               0x0002
#define CFG_PROP_INDEX_INSTALL                  0x0003
#define CFG_PROP_INDEX_STOP_ON_ERR              0x0004
#define CFG_PROP_INDEX_NO_GPG_CHECK             0x0005

// WARNING: Config indices must be less than CFG_MAX_INDEX!
#define CFG_MAX_INDEX                   0x0006

#define CFG_CHILD_PROPS(...)    { __VA_ARGS__ }
#define CFG_PROP_LINUX_PKG_MANAGER_CHILD_PROPS    CFG_CHILD_PROPS(CFG_PROP_INDEX_INSTALL, CFG_PROP_INDEX_ASSUME_YES, CFG_PROP_INDEX_NO_GPG_CHECK)

property_t const CONFIG_TABLE[]
{
//    key                            required    childProps                                 role                    childPropsRequiredMask           getDefaultValue
    { CFG_PROP_NAME,                 true,       { },                                       CFG_PROP_ROLE_BOTH,      CHILD_PROP_MASK_ALL_REQUIRED,    nullptr         },
    { CFG_PROP_LINUX_PKG_MANAGER,    false,      CFG_PROP_LINUX_PKG_MANAGER_CHILD_PROPS,    CFG_PROP_ROLE_PARENT,    0b001,                           nullptr         },
    { CFG_PROP_ASSUME_YES,           false,      { },                                       CFG_PROP_ROLE_CHILD,     CHILD_PROP_MASK_ALL_REQUIRED,    nullptr         },
    { CFG_PROP_INSTALL,              true,       { },                                       CFG_PROP_ROLE_CHILD,     CHILD_PROP_MASK_ALL_REQUIRED,    nullptr         },
    { CFG_PROP_STOP_ON_ERR,          false,      { },                                       CFG_PROP_ROLE_PARENT,    CHILD_PROP_MASK_ALL_REQUIRED,    nullptr         },
    { CFG_PROP_NO_GPG_CHECK,         false,      { },                                       CFG_PROP_ROLE_CHILD,     CHILD_PROP_MASK_ALL_REQUIRED,    nullptr         }
};

#endif