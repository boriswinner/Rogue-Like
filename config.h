#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>

using json = nlohmann::json;

class Config {
public:
    static Config &Instance();

    json data;
    const std::string filename = "config.json";
private:
    Config();

    ~Config() {}

    Config(Config const &) = delete;

    Config &operator=(Config const &) = delete;


};

extern Config &game_config;



