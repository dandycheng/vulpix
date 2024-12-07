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

/**
 * @brief Parses the user config and start the setup process.
 * 
 * @returns bool - To indicate whether the setup is successful.
 */
bool Config::setupConfig(void)
{
    string configName { getConfigName() };
    vector<string> packages { getInstalls("apt") };

    cout << "Running config setup: " << configName.c_str() << "\n\n";
    Aptitude apt;

    return apt.installPackage(m_sys, &packages);
}

const string Config::getConfigName(void)
{
    return m_config["name"].as<string>();
}

bool Config::isConfigValid(void)
{
    bool isValid { true };

    for (property_t config : g_configTypes)
    {
        if (!m_config[config.key].IsDefined() && config.required)
        {
            cout << "\"" << config.key << "\" is a required property but it's missing." << endl;
            isValid = false;
        }
        else if (m_config[config.key].IsNull())
        {
            cout << "\"" << config.key << "\" is defined but no value is provided." << endl;
            isValid = false;
        }
    }

    DEBUG_LOG(LOG_DEBUG, "Is config valid?: %s", isValid ? "yes" : "no");

    return isValid;
}

bool Config::hasRequiredSubProperty(string key, vector<subProperty_t>* subProperties)
{
    return hasRequiredSubProperty(key.c_str(), subProperties);
}

bool Config::hasRequiredSubProperty(const char* key, vector<subProperty_t>* subProperties)
{
    if (subProperties->size() == 0)
    {
        return false;
    }

    bool hasProperty { true };

    if (m_config[key].IsDefined())
    {
        for (uint8_t i = 0; i < g_subProperties.size(); i++)
        {
            if (strcmp(g_configTypes[i].key, key) == 0  )
            {
                requiredPropMask_t subProp = g_configTypes[i].requiredSubPropertyMask;

                for (vector<subProperty_t>::iterator i = (*subProperties).begin(); i < (*subProperties).end(); i++)
                {
                    hasProperty &= (*i & subProp) > 0;
                }

                return hasProperty;
            }
        }
    }

    return false;
}

bool Config::stopOnError(void)
{
    bool buf { true };
    //TODO: getConfigFromKey<bool>(&buf, "stop_on_error");

    return buf;
}

/**
 *  Return a list of dependencies for a key in the user config.
 * 
 * @returns vector<string>
 */
vector<string> Config::getInstalls(string key)
{
    // TODO: Instead of throwing error when the key isn't in the config, print message.
    // FIXME: Update UT lists as well, not just string
    YAML::Node node { m_config[key][CFG_KEY_INSTALL] };
    vector<string> packages;

    if (node.Type() == YAML::NodeType::Sequence)
    {
        for (YAML::Node item : node)
        {
            packages.push_back(item.as<string>());
        }
    }
    else
    {
        stringstream ss(node.as<string>());
        string package;

        while (getline(ss, package, ' '))
        {
            packages.push_back(package);
        }
    }

    return packages;
}

void* getDefaultValueStopOnError(void)
{
    return (void*) true;
}

distro_t getDistro(void)
{
    string distro { findTextInFile(OS_RELEASE_PATH, std::regex("^ID", std::regex_constants::ECMAScript)) };

    if (distro.length() > 0)
    {
        distro = distro.substr(3, distro.length());    // Trim off the "ID="

        std::transform(distro.begin(), distro.end(), distro.begin(), ::tolower);

        if (distro == "ubuntu") return UBUNTU;
        if (distro == "opensuse") return OPEN_SUSE;
        if (distro == "redhat") return REDHAT;
    }

    DEBUG_LOG(LOG_ERROR, "Unable to open file: %s", OS_RELEASE_PATH);

    return UNKNOWN_DISTRO;
}