#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <functional>
#include "json.hpp"
#include "sha256.h"
#ifdef _WIN32
	#define PATH_TO_PKG "./pkg/" + action + ".exe"
	#define DEL_EXE "del .\\pkg\\" + action + ".exe"
	#define DEL_JSON "del .\\pkg\\" + action + ".json"
#elif __unix__
	#define PATH_TO_PKG "./pkg/" + action
	#define DEL_EXE "rm ./pkg/" + action
	#define DEL_JSON "rm ./pkg/" + action + ".json"
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
			std::string del1 = DEL_EXE;
			std::string del2 = DEL_JSON;
			system(del1.c_str());
			system(del2.c_str());
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