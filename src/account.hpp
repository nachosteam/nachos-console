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
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <functional>
#include "json.hpp"
#include "sha256.h"
#ifdef _WIN32
	#define CLEAR_COMM "cls"
#elif __linux__
	#define CLEAR_COMM "clear"
#endif

void new_login()
{
	std::cout << "No users!" << std::endl <<
	"Creating a new one: " << std::endl;
	std::string login_new;
	std::cout << "\t|Login: ";
	std::getline(std::cin, login_new);
	std::ifstream i("nc-bin/settings.json");
	nlohmann::json data;
	i >> data;
	data["username"] = login_new;
	std::ofstream output("nc-bin/settings.json");
	output << data.dump(4);
}

void new_password()
{
	std::string pass_new;
	std::cout << "\t|Password: ";
	std::getline(std::cin, pass_new);
	std::string hashValue = SHA256::hashString(pass_new);
	std::ifstream i("nc-bin/settings.json");
	nlohmann::json data;
	i >> data;
	data["password"] = hashValue;
	std::ofstream output("nc-bin/settings.json");
	output << data.dump(4);
}

void new_pcname()
{
	std::string pc_new;
	std::cout << "\t|PC name: ";
	std::getline(std::cin, pc_new);
	std::ifstream i("nc-bin/settings.json");
	nlohmann::json data;
	i >> data;
	data["pcname"] = pc_new;
	std::ofstream output("nc-bin/settings.json");
	output << data.dump(4);
}

std::string user()
{
	std::string username;
	std::ifstream i("nc-bin/settings.json");
	nlohmann::json data = nlohmann::json::parse(i);
	std::string userFromFile = data["username"];
	username = userFromFile;
	i.close();
	return username;
}

std::string pcname()
{
	std::string pc_name;
	std::ifstream i("nc-bin/settings.json");
	nlohmann::json data = nlohmann::json::parse(i);
	std::string pcFromFile = data["pcname"];
	pc_name = pcFromFile;
	i.close();
	return pc_name;
}

std::string workdir() {
	std::filesystem::path dirWhere = std::filesystem::current_path();
	return dirWhere.string();
}

/*
'prompt' Format:
    \\u - Username
    \\p - Pc name
    \\w - Path to work dir
*/
std::string prompt() {
	std::ifstream i("nc-bin/settings.json");
	nlohmann::json data = nlohmann::json::parse(i);
	
	std::string out{};
	std::string format = data["prompt"];

	bool isFuckingBullshit = false;
	for (char ch : format) {
		if (ch == '/') {
			isFuckingBullshit = !isFuckingBullshit;
			continue;
		}
		if (isFuckingBullshit) {
			switch (ch) {
				case 'u': out += user(); break;
				case 'w': out += workdir(); break;
				case 'p': out += pcname(); break;
				default:
					std::cerr << "Error: Unknown special character for formatting!" << std::endl;
					exit(42);
			}
			isFuckingBullshit = false;
		} else
			out += ch;
	}

	i.close();
	return out;
}

void create_file()
{
	std::string mkdir_bin = "mkdir nc-bin";
	system(mkdir_bin.c_str());
	std::ofstream out;
    out.open("nc-bin/settings.json");
    if (out.is_open())
    {
        out << "{" << std::endl << "\t\"username\": \"null\","
				   << std::endl << "\t\"pcname\": \"pc\"," 
				   << std::endl << "\t\"password\": \"root\"," 
				   << std::endl << "\t\"repos\": [\"https://raw.githubusercontent.com/nachosteam/nc-repo\"]," 
				   << std::endl << "\t\"tegvdTsv56376\": \"placeholder :D\"," 
				   << std::endl << "\t\"prompt\": \"/u@/p [/w]$ \"" << std::endl << "}";
		out.close();
    }
}

void login()
{
	if (!std::filesystem::exists("nc-bin/settings.json")) /* or !std::filesystem::exists("./password"))*/
	{
		create_file();
		new_login();
		new_password();
		new_pcname();
	}
	else
	{
		std::string login_back;
		while(true)
		{
			std::cout << "\t|login: ";
			std::getline(std::cin, login_back);
			std::ifstream i ("nc-bin/settings.json");
			nlohmann::json data;
			i >> data;
			std::string login_exists = data["username"];
			i.close();
			if (login_back == login_exists)
				break;
			else
				std::cout << "Incorrect login. Try again." << std::endl;
		}
		while(true)
		{
			std::string passwd_back;
			std::cout << "\t|password: ";
			std::getline(std::cin, passwd_back);
			std::ifstream i ("nc-bin/settings.json");
			nlohmann::json data;
			i >> data;
			std::string passwd_exists = data["password"];
			std::string hashValue = SHA256::hashString(passwd_back);
			if (hashValue == passwd_exists)
				break;
			else
				std::cout << "Incorrect password. Try again." << std::endl;
		}
	}
}