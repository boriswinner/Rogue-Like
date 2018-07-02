#include "config.h"

Config::Config() {
    std::ifstream configStream(filename);
    configStream >> data;
}

Config &Config::Instance() {
    static Config s;
    return s;
}
