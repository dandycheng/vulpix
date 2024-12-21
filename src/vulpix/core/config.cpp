#include "config.h"
#include "logs.h"
#include "file.h"
#include "Aptitude.h"
#include <cstring>

using namespace std;

Config::Config(string configFile) :
    m_sys(new System())
{
    try
    {
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
    return true;
}

bool Config::isConfigValid(configPropIndex_t index)
{
    string key = CONFIG_TABLE[index].key;

    if (!m_config[key].IsDefined())
    {
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

        if ((!m_config[key][childPropKey].IsDefined() || m_config[key][childPropKey].IsNull()) && IS_BIT_SET(childPropMask, j))
        {
            return false;
        }

        j++;
    }

    return true;
}