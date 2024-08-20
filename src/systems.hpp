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

#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "json.hpp"
#include "account.hpp"
#define CNAME "NachosConsole"
#ifdef _WIN32
	#define PROG_FULL "nc-bin\\" + term_input + "\\" + fullcom
	#define PKG_DIR "nc-bin\\" + term_input + "\\"
#elif __linux__
	#define PROG_FULL "nc-bin/" + term_input + "/" + fullcom
	#define PKG_DIR "nc-bin/" + term_input + "/"
#endif

void passwd_change()
{
	std::string new_passwd;
    std::cout << "Enter a new password: ";
	std::getline(std::cin, new_passwd);
	std::string hashValue = SHA256::hashString(new_passwd);
	std::ifstream i("nc-bin/settings.json");
	nlohmann::json data;
	i >> data;
	data["password"] = hashValue;
	std::ofstream output("nc-bin/settings.json");
	output << data.dump(4);
}

void help_com(std::string a)
{
	if (a == "default")
	{
		std::cout << "about						about " CNAME << std::endl <<
        "passwd						change in-app password" << std::endl <<
        "clear						clear console" << std::endl <<
		/*"pkg [parameter] [package]			get/remove pkg" << std::endl <<*/
		"ls						shows the contents of the directory" << std::endl <<
		"echo						displays messages" << std::endl <<
		"exit						close " CNAME << std::endl;
        std::cout << std::endl;
	}
	/*if (a == "pkg")
	{
		std::cout << "-h|--help\tget list of avalible parameters" << std::endl
		<< "-s|--sync\tsync pkg" << std::endl
		<< "-r|--remove\tremove pkg" << std::endl;
	}*/
}

void clear()
{
	#ifdef _WIN32
		system("cls");
	#elif __linux__
		system("clear");
	#endif
}

void run_pkg(std::string term_input, std::string fullcom)
{
	std::ifstream i("nc-bin/" + term_input + "/info.json");
	nlohmann::json data = nlohmann::json::parse(i);
	std::string execute = data["execute"];
	std::string args = data["args"];
	std::string start = PKG_DIR + execute;
	system(start.c_str());
	/*std::string app_launch = PROG_FULL;
	system(app_launch.c_str());*/
}