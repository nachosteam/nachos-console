/*
	MIT License

	Copyright (c) 2024 NachosTeam https://github.com/nachosteam

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include "repo.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

#ifdef _WIN32
    #define REPO_LINK std::string("/main/win/")
    #define FILE_EXTENSION ".exe"
    #define REMOVE_COMMAND "del"
#elif __linux__
    #define REPO_LINK std::string("/main/linux/")
    #define FILE_EXTENSION ""
    #define REMOVE_COMMAND "rm"
#endif

void Repo::downloadPackage(std::string package) {
    unsigned short count = 1;
    bool isInstalled = false;
    std::string foundedRepo = "";

    if (std::filesystem::exists("./pkg/" + package))
        isInstalled = true;

    for (std::string repo : this->settings["repos"]) {
        std::cout << (count < 10 ? '0' : '\0') << count << ": Get: " << repo;
		std::string makedir = "mkdir ./pkg/" + package;
		system(makedir.c_str()); // mb can be replaced with "./tmp/*package*"
        std::string info = "curl -s " + repo + REPO_LINK + package + ".tar.gz -o " + "./pkg/" + package + "/" + package + ".tar.gz";
        system(info.c_str());
		std::cout << info << std::endl; // can be commented
		std::string unzip = "tar -xzf " + package + ".tar.gz";
		system(unzip.c_str());
		std::cout << unzip << std::endl; // can be commented

        //std::ifstream file(std::string("./pkg/") + (isInstalled ? "new_" : "") + package + ".json");

        /*if (file)
		{
            std::string content;
            getline(file, content);

            if (content == "404: Not Found" || content.empty() || content == "{\"error\":\"Not Found\"}")
			{
                if (content.empty())
				{
                    throw std::runtime_error("Error connection");
                }

                file.close();
                remove(("./pkg/" + package + ".json").c_str());
                std::cout << ": Not found!" << std::endl;
            }
			else
			{
                std::cout << ": Found!" << std::endl;
                foundedRepo = repo;

                if (isInstalled)
				{
                    std::ifstream i("./pkg/" + package + "/" + "info.json");

                    file.seekg(0);

                    json old_data = json::parse(i);
                    json new_data = json::parse(file);

                    file.close();

                    std::string old_pkg_ver = old_data["pkg_ver"];
                    std::string new_pkg_ver = new_data["pkg_ver"];

                    if (old_pkg_ver != new_pkg_ver)
					{
                        std::string renm_new = REMOVE_COMMAND " .\\pkg\\new_" + package + ".json";
                        std::string info_dl_new = "curl -s " + repo + REPO_LINK + package + "/" + package + ".json -o " + "./pkg/" + package + ".json";
                        std::string pkg_dl_new = "curl -s " + repo + REPO_LINK + package + "/" + package + FILE_EXTENSION " -o " + "./pkg/" + package + FILE_EXTENSION;
                        system(renm_new.c_str());
                        system(pkg_dl_new.c_str());
                        system(info_dl_new.c_str());
                        std::cout << "Package " << package << " updated." << std::endl;
                    }
					else
					{
                        std::string rm_new = REMOVE_COMMAND " .\\pkg\\new_" + package + ".json";
                        system(rm_new.c_str());
                        std::cout << "Package is up to date. Nothing updated." << std::endl;
                    }

                    return;
                }
                break;
            }
        }
        file.close();*/

        count++;
    }

    if (foundedRepo.empty())
	{
        std::cerr << "Package not found!" << std::endl;
        return;
    }

    /*std::ifstream i("./pkg/" + package + ".json");
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

    i.close();*/ // this shit has a new info | more information: file - neofetch.tar.gz/info.json
    std::string confirm;
    std::cout << "Are you sure? [Y/n] ";
    getline(std::cin, confirm);

    if (confirm == "y" || confirm == "Y" || confirm == "yes" || confirm.empty())
	{
        std::cout << "Downloading file: " << package << FILE_EXTENSION << std::endl;
        std::string compiled = "curl -s " + foundedRepo + REPO_LINK + package + "/" + package + FILE_EXTENSION " -o " + "./pkg/" + package + FILE_EXTENSION;
        system(compiled.c_str());
        std::cout << "The package is installed. Enjoy!" << std::endl;
    }
	else
	{
        remove(("./pkg/" + package + ".json").c_str());
        std::cout << "Operation aborted." << std::endl;
    }

    if (std::string(FILE_EXTENSION).empty())
	{
        std::string command = "chmod +x ./pkg/" + package + FILE_EXTENSION;
        system(command.c_str());
    }
}
