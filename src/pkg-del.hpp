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
	#define PATH_TO_PKG "./pkg/" + action
	#define DIR_DEL "rmdir /s /q " + action
#elif __linux__
	#define PATH_TO_PKG "./pkg/" + action
	#define DIR_DEL "rm -rf " + action
#endif

void del_pkg(std::string action)
{
	std::string passwd_back;
	std::cout << "\t|password: ";
	std::getline(std::cin, passwd_back);
	std::ifstream i("password");
	std::string passwd_exists;
	std::getline(i, passwd_exists);
	std::string pb_hash = SHA256::hashString(passwd_back);
	i.close();
	if (pb_hash == passwd_exists)
	{
    	std::ifstream file(PATH_TO_PKG);
		if (file)
		{
			file.close();
			std::string del = DIR_DEL;
			system(del.c_str());
			std::cout << "Deleted successfully." << std::endl;
		}
		else
		{
			file.close();
			std::cout << "The package is not installed. Nothing has been deleted." << std::endl;
		}
	}
	else
		std::cout << "Invalid password. Aborted." << std::endl;
}