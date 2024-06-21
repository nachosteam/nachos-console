#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <functional>
#include "json.hpp"
#ifdef _WIN32
	#define CLEAR_COMM "cls"
#elif __unix__
	#define CLEAR_COMM "clear"
#endif

void new_login()
{
	std::cout << "No users!" << std::endl <<
	"Creating a new one: " << std::endl;
	std::string login_new;
	std::cout << "\t|Login: ";
	std::getline(std::cin, login_new);
	std::ifstream i("settings.json");
	nlohmann::json data;
	i >> data;
	std::string input_new_username = data["username"];
	data["username"] = login_new;
	std::ofstream output("settings.json");
	output << data.dump(4);
}

void new_password()
{
	std::string pass_new;
	std::cout << "\t|Password: ";
	std::getline(std::cin, pass_new);
	std::hash<std::string> hasher;
	std::size_t hashValue = hasher(pass_new);
	std::ofstream out;
    out.open("password");
    if (out.is_open())
    {
        out << hashValue << std::endl;
    }
    out.close();
	std::cout << std::endl;
}

void new_pcname()
{
	std::string pc_new;
	std::cout << "\t|PC name: ";
	std::getline(std::cin, pc_new);
	std::ifstream i("settings.json");
	nlohmann::json data;
	i >> data;
	data["pcname"] = pc_new;
	std::ofstream output("settings.json");
	output << data.dump(4);
}

std::string user()
{
	std::string username;
	std::ifstream i("settings.json");
	nlohmann::json data = nlohmann::json::parse(i);
	std::string userFromFile = data["username"];
	username = userFromFile;
	i.close();
	return username;
}

std::string pcname()
{
	std::string pc_name;
	std::ifstream i("settings.json");
	nlohmann::json data = nlohmann::json::parse(i);
	std::string pcFromFile = data["pcname"];
	pc_name = pcFromFile;
	i.close();
	return pc_name;
}

void create_file()
{
	std::ofstream out;
    out.open("settings.json");
    if (out.is_open())
    {
        out << "{" << std::endl << "\t\"username\": \"null\"," << std::endl << "\t\"pcname\": \"pc\"," << std::endl << "\t\"repos\": [\"https://raw.githubusercontent.com/nachosteam/nc-repo\"]" << std::endl << "}";
		out.close();
    }
	out.open("password");
    if (out.is_open())
    {
        out.close();
    }
}

void login()
{
	if (!std::filesystem::exists("./settings.json"))
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
			std::ifstream i ("settings.json");
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
			std::ifstream i("password");
			std::hash<std::string> hasher;
			std::size_t hashValue = hasher(passwd_back);
			std::string passwd_exists;
			std::ifstream in("password");
			std::getline(in, passwd_exists);
			in.close();
			i.close();
			if (std::to_string(hashValue) == passwd_exists)
				break;
			else
				std::cout << "Incorrect password. Try again." << std::endl;
		}
	}
}
