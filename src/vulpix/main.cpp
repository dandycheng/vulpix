#include "yaml-cpp/yaml.h"
#include <iostream>
#include <string>
#include <fstream>
#include "config.h"
#include "packageManager.h"
#include "sanitizer.h"

int main(int argc, char* argv[])
{
    std::string configFile = argv[1];
    Config* config = new Config(configFile);
    config->setupConfig();
    delete config;
}