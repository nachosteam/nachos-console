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
#define ver "2.1.0"
#ifdef _WIN32
	#if defined(_WIN32) && defined(_WIN64)
		#define HOST_OS " for Win64"
	#else
		#define HOST_OS " for Win32"
	#endif
#elif __linux__
	#define HOST_OS " for Linux"
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

void about()
{
	std::ifstream i("nc-bin/settings.json");
	nlohmann::json data;
	i >> data;
	if (data["tegvdTsv56376"] == "eb699c583c2aba362d3def8346d55620dcf000d37a6dafdb7af663383d169841")
	{
		std::cout << ".................." << std::endl <<
					 "\x1B[47;30mo^•.•^o\033[0m " CNAME << std::endl <<
					 ver << std::endl <<
					 "with \x1B[91mlove\033[0m by NachosTeam" << std::endl <<
					 "Developers:" << std::endl <<
					 "\x1B[91mNikita Belov (https://github.com/TolyaGosuslugi)\033[0m" << std::endl <<
					 "\x1B[91mhonakac (https://github.com/honakac)\033[0m" << std::endl <<
					 "For: " << user() << std::endl <<
					 "Thanks for using " CNAME << "! meow :3" << std::endl << std::endl;
	}
	else
	{
		std::cout << ".................." << std::endl <<
				"..#.....#..######.\t" CNAME << HOST_OS << std::endl <<
				"..##....#....#....\t" ver << std::endl <<
				"..#.#...#....#....\tBy \x1B[33mNachosTeam\033[0m 2024" << std::endl <<
				"..#..#..#....#....\thttps://github.com/nachosteam/nachos-console" << std::endl <<
				"..#...#.#....#...." << std::endl <<
				"..#....##....#....\t\x1B[36mUnder MIT License\033[0m" << std::endl <<
				"..#.....#....#...." << std::endl <<
				".................." << std::endl;
	}
}

void adminPanel(std::string parameter, std::string action)
{
	std::ifstream i("nc-bin/settings.json");
	nlohmann::json data;
	i >> data;
	if (parameter == "on")
	{
		if (action == "AboutEasterEgg")
		{
			data["tegvdTsv56376"] = SHA256::hashString("CatActivated");
			std::ofstream output("nc-bin/settings.json");
			output << data.dump(4);
			std::cout << "Easter Egg Activated" << std::endl;
		}
	}
	else if (parameter == "off")
	{
		if (action == "AboutEasterEgg")
		{
			data["tegvdTsv56376"] = "placeholder :D";
			std::ofstream output("nc-bin/settings.json");
			output << data.dump(4);
			std::cout << "Easter Egg Deactivated" << std::endl;
		}
	}
}