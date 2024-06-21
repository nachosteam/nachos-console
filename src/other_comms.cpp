#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <functional>
#include "json.hpp"

void passwd_change()
{
	std::string new_passwd;
    std::cout << "Enter a new password: " << std::endl;
    std::getline(std::cin, new_passwd);
    std::hash<std::string> hasher;
	std::size_t hashValue = hasher(new_passwd);
	std::ofstream out;
	out.open("password");
	if (out.is_open())
	{
		out << hashValue << std::endl;
	}
	out.close();
}