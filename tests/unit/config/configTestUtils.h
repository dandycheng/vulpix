#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <regex>
#include "config.h"

using namespace std;

class ConfigTest : public Config
{
public:
    ConfigTest(string configFile) : Config(configFile) {}
};