#include "yaml-cpp/yaml.h"
#include "config.h"
#include <fstream>

int main(int argc, char* argv[])
{
    std::string configFile = argv[1];
    Config* config = new Config(configFile);
    config->setupConfig();
    delete config;
}