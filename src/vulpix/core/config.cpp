#include "config.h"
#include "logs.h"
#include "file.h"
#include "Aptitude.h"
#include "PackageManagerMacro.h"
#include <cstring>
#include <iostream>

using namespace std;

Config::Config(string configFile) :
    m_sys(new System()),
    m_stopOnErr(false)
{
    try
    {
        DEBUG_LOG(LOG_DEBUG, "Parsing config file: %s", configFile.c_str());
        m_config = YAML::LoadFile(configFile);
    }
    catch(const std::exception& e)
    {
        DEBUG_LOG(LOG_ERROR, "Failed to load YAML file: %s", e.what());
    }
}

Config::~Config(void)
{
}

string Config::getConfigName(void) const
{
    return m_config[CFG_PROP_NAME].as<string>();
}

bool Config::setupConfig(void)
{
    bool isValid { true };
    bool success { true };

    for (configPropIndex_t i = 0; i < CFG_MAX_INDEX; i++)
    {
        isValid &= isConfigPropValid(i);

        if (!isValid)
        {
            ERROR_LOG("Property \"%s\" is required but not defined in config file.", CONFIG_TABLE[i].key.c_str());
        }
    }

    DEBUG_LOG(LOG_DEBUG, "Is config valid?: %s", LOG_BOOL_TO_YES_NO(isValid));

    if (isValid)
    {
        for (configPropIndex_t i = 0; i < CFG_MAX_INDEX; i++)
        {
            if (CONFIG_TABLE[i].hasMacro)
            {
                success &= runModuleMacro(i);
            }
        }
    }
    else
    {
        ERROR_LOG("Config file is invalid!");
        return false;
    }

    return success;
}

bool Config::isConfigPropValid(configPropIndex_t index)
{
    string key = CONFIG_TABLE[index].key;

    if (IS_BIT_SET(CONFIG_TABLE[index].role, CFG_PROP_ROLE_PARENT) &&
        CONFIG_TABLE[index].required && !m_config[key].IsDefined())
    {
        DEBUG_LOG(LOG_ERROR, "%s parent property is required but not found!", CONFIG_TABLE[index].key.c_str());
        return false;
    }

    vector<configPropIndex_t> childProps = CONFIG_TABLE[index].childProps;
    childPropBitmask_t childPropMask = CONFIG_TABLE[index].childPropsRequiredMask;
    configPropIndex_t j = 0;

    /* For each mask child prop, use the childRequiredPropMask to check whether if
      the child prop is a required property.*/
    for (vector<configPropIndex_t>::const_iterator i = childProps.begin(); i != childProps.end(); i++)
    {
        string childPropKey = CONFIG_TABLE[*i].key;

        if ((!m_config[key][childPropKey].IsDefined() || m_config[key][childPropKey].IsNull()) &&
            IS_BIT_SET(childPropMask, j))
        {
            return false;
        }

        j++;
    }

    return true;
}

bool Config::verifyConfigFile(void)
{
    for (uint8_t i = 0; i < CFG_MAX_INDEX; i++)
    {
        if (!isConfigPropValid(i))
        {
            return false;
        }
    }

    return true;
}

vector<string> Config::strNodeToVec(node_t node)
{
    string contents { node.as<string>() };
    vector<string> result;

    if (!node.IsSequence())
    {
        stringstream ss;
        string package;

        while (getline(ss, package, ' '))
        {
            result.push_back(package);
        }
    }

    return result;
}

bool Config::runModuleMacro(configPropIndex_t index)
{
    bool isUndo = false;
    string propKey = CONFIG_TABLE[index].key;
    string undoPropKey = CONFIG_TABLE[CFG_PROP_INDEX_UNDO].key;

    if (!m_config[propKey][undoPropKey].IsNull() && 
        m_config[propKey][undoPropKey].as<bool>())
    {
        isUndo = true;
    }

    switch (index)
    {
        case CFG_PROP_INDEX_LINUX_PACKAGE_MANAGER:
            return PackageManagerMacro(this).runMacro(m_config[index], isUndo);

        default:
            break;
    }

    return false;
}

node_t Config::operator [] (configPropIndex_t index) const
{
    return m_config[CONFIG_TABLE[index].key];
}
