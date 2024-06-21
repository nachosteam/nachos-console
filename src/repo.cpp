#include "repo.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

#ifdef _WIN32
    #define REPO_LINK std::string("/raw/branch/main/win32/")
    #define FILE_EXTENSION ".exe"
    #define REMOVE_COMMAND "del"
#elif __unix__
    #define REPO_LINK std::string("/raw/branch/main/unix/")
    #define FILE_EXTENSION ""
    #define REMOVE_COMMAND "rm"
#endif

void Repo::downloadPackage(std::string package) {
    unsigned short count = 1;
    bool isInstalled = false;
    std::string foundedRepo = "";

    if (std::filesystem::exists("./pkg/" + package + ".json"))
        isInstalled = true;

    for (std::string repo : this->settings["repos"]) {
        std::cout << (count < 10 ? '0' : '\0') << count << ": Get: " << repo;
        std::string info = std::string("curl -s ") + repo + REPO_LINK + package + "/" + package + ".json -o " + "./pkg/" + (isInstalled ? "new_" : "") + package + ".json";
        system(info.c_str());

        std::ifstream file(std::string("./pkg/") + (isInstalled ? "new_" : "") + package + ".json");

        if (file) {
            std::string content;
            getline(file, content);

            if (content == "Not found." || content.empty()) {
                if (content.empty()) {
                    throw std::runtime_error("Error connection");
                }

                file.close();
                remove(("./pkg/" + package + ".json").c_str());
                std::cout << ": Not found!" << std::endl;
            } else {
                std::cout << ": Found!" << std::endl;
                foundedRepo = repo;

                if (isInstalled) {
                    std::ifstream i("./pkg/" + package + ".json");

                    file.seekg(0);

                    json old_data = json::parse(i);
                    json new_data = json::parse(file);

                    file.close();

                    std::string old_pkg_ver = old_data["pkg_ver"];
                    std::string new_pkg_ver = new_data["pkg_ver"];

                    if (old_pkg_ver != new_pkg_ver) {
                        std::string renm_new = REMOVE_COMMAND " .\\pkg\\new_" + package + ".json";
                        std::string info_dl_new = "curl -s " + repo + REPO_LINK + package + "/" + package + ".json -o " + "./pkg/" + package + ".json";
                        std::string pkg_dl_new = "curl -s " + repo + REPO_LINK + package + "/" + package + FILE_EXTENSION " -o " + "./pkg/" + package + FILE_EXTENSION;
                        system(renm_new.c_str());
                        system(pkg_dl_new.c_str());
                        system(info_dl_new.c_str());
                        std::cout << "Package " << package << " updated." << std::endl;
                    } else {
                        std::string rm_new = REMOVE_COMMAND " .\\pkg\\new_" + package + ".json";
                        system(rm_new.c_str());
                        std::cout << "Package is up to date. Nothing updated." << std::endl;
                    }

                    return;
                }
                break;
            }
        }
        file.close();

        count++;
    }

    if (foundedRepo.empty()) {
        std::cerr << "Package not found!" << std::endl;
        return;
    }

    std::ifstream i("./pkg/" + package + ".json");
    json data = json::parse(i);
    std::string pkg_name = data["pkg_name"];
    std::string pkg_ver = data["pkg_ver"];
    std::string pkg_size = data["pkg_size"];
    std::string pkg_creator = data["pkg_creator"];
    std::string pkg_link = data["pkg_link"];

    std::cout << "\tPackage: " << pkg_name << std::endl
    << "\tVersion: " << pkg_ver << std::endl
    << "\tSize: " << pkg_size << std::endl
    << "\tBy: " << pkg_creator << std::endl
    << "\tOriginal: " << pkg_link << std::endl;

    i.close();
    std::string confirm;
    std::cout << "Are you sure? [Y/n] ";
    getline(std::cin, confirm);

    if (confirm == "y" || confirm == "Y" || confirm == "yes" || confirm.empty()) {
        std::cout << "Downloading file: " << package << FILE_EXTENSION << std::endl;
        std::string compiled = "curl -s " + foundedRepo + REPO_LINK + package + "/" + package + FILE_EXTENSION " -o " + "./pkg/" + package + FILE_EXTENSION;
        system(compiled.c_str());
        std::cout << "The package is installed. Enjoy!" << std::endl;
    } else {
        remove(("./pkg/" + package + ".json").c_str());
        std::cout << "Operation aborted." << std::endl;
    }

    if (std::string(FILE_EXTENSION).empty()) {
        std::string command = "chmod +x ./pkg/" + package + FILE_EXTENSION;
        system(command.c_str());
    }
}
