#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"
using json = nlohmann::json;

class Repo {
public:
    std::vector<std::string> repos;
    json settings;
    
    Repo(std::string inputFile) {
        std::ifstream file(inputFile);
        settings = json::parse(file);
    }
    void downloadPackage(std::string package);
};
