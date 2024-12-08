#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <regex>
#include "config.h"

using namespace std;

class Config_subClassTest : public Config
{
public:
    Config_subClassTest(string configFile) : Config(configFile) {}
    bool hasRequiredSubProperty(const char* propertyName, vector<subProperty_t>* subProperties);
};