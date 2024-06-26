#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <functional>
#include <locale>
#include "json.hpp"
#include "repo.hpp"
#include "account.hpp"
#include "pkg-del.hpp"
#include "other_comms.hpp"

#define CNAME "NachosConsole"
#define ver "1.1.63"
#ifdef _WIN32
	#include <windows.h>
	#define DIR_COMM "dir "
	#define CLEAR_COMM "cls"
	#define PATH_TO_PROG "pkg\\" + term_input + ".exe"
	#define PROG_FULL "pkg\\" + fullcom
	#define WIN_UTF8 SetConsoleOutputCP(CP_UTF8)
	#ifdef _WIN32 and _WIN64
		#define HOST_OS " for Win64"
	#else
		#define HOST_OS " for Win32"
	#endif
#elif __unix__ or __linux__
	#define DIR_COMM "ls "
	#define CLEAR_COMM "clear"
	#define PATH_TO_PROG "pkg/" + term_input
	#define PROG_FULL "pkg/" + fullcom
	#define WIN_UTF8 cout << ""
	#define HOST_OS " for Linux"
#endif
using namespace std;
using json = nlohmann::json;

int main()
{
	setlocale(LC_ALL, "en_US.utf8");
	WIN_UTF8;
	if (!filesystem::exists("./pkg"))
		system("mkdir pkg");
	
	login();
	system(CLEAR_COMM);

	Repo repos("./settings.json");
	
	string action;
	filesystem::path currentDir = filesystem::current_path();
	string pathIn = currentDir.string();
    while(true)
    {
		filesystem::path dirWhere = filesystem::current_path();
		string whereAmI = dirWhere.string();
		string passwd_back;
        string term_input;
		string parameter;
		string fullcom;
		cout << user() << "@" << pcname() << " [" << whereAmI << "]$ ";
        getline(cin, term_input);
		fullcom = term_input;
		istringstream iss(term_input);
		iss >> term_input;
        if(term_input == "help")
        {
            cout << "about						about " CNAME << endl <<
            "passwd						change in-app password" << endl <<
            "clear						clear console" << endl <<
			"pkg [parameter] [package]			get/remove pkg" << endl <<
			"ls						shows the contents of the directory" << endl <<
			"echo						displays messages" << endl <<
			"exit						close " CNAME << endl;
            cout << endl;
        }
        else if(term_input == "about")
        {
            cout << ".................." << endl <<
                    "..#.....#..######.\t" CNAME << HOST_OS << endl <<
                    "..##....#....#....\t" ver << endl <<
                    "..#.#...#....#....\tBy NachosTeam" << endl <<
                    "..#..#..#....#....\t2024" << endl <<
                    "..#...#.#....#...." << endl <<
                    "..#....##....#....\thttps://github.com/nachosteam/nachos-console" << endl <<
                    "..#.....#....#...." << endl <<
                    ".................." << endl;
		}
        else if(term_input == "exit")
            return 0;
        else if(term_input == "passwd")
			passwd_change();
        else if(term_input == "clear")
			system(CLEAR_COMM);
		else if (term_input == "pkg")
		{
			iss >> parameter;
        
			if (parameter == "-s" or parameter == "--sync")
			{
				iss >> action;
				
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
				if (to_string(hashValue) == passwd_exists)
				{
					repos.downloadPackage(action);
				}
				else
					cout << "Invalid password. Aborted." << endl;
			}
			else if (parameter == "-r" or parameter == "--remove")
			{
				iss >> action;
				del_pkg(action);
			}
			else if (parameter == "-h" or parameter == "--help")
			{
				iss >> action;
				cout << "-h|--help\tget list of avalible parameters" << endl
				<< "-s|--sync\tsync pkg" << endl
				<< "-r|--remove\tremove pkg" << endl;
			}
			else
				cout << "Unknown parameter. Type 'pkg --help'" << endl;
		}
		else if (term_input == "ls")
		{
			iss >> parameter;
			string dir_cmd = DIR_COMM + parameter;
			system(dir_cmd.c_str());
		}
		else if (term_input == "echo")
		{
			system(fullcom.c_str());
		}
		/*else if (term_input == "test")
		{
			const char* str = "Привет, Hello";
			string str2 = "Привет, Hello";
			cout << str << endl;
			cout << str2 << endl;
			cout << "Проверка отображения кириллицы" << endl;
		}
		else if (term_input == "кириллица")
		{
			const char* str = "Привет, Hello";
			string str2 = "Привет, Hello";
			cout << str << endl;
			cout << str2 << endl;
			printf("Проверка отображения кириллицы\n");
		}*/ //this shit is crashing, 'test' doesn't output russian text, 'кириллица' crashs because filesystem error - illegal symbols
		else
		{
			if (filesystem::exists(PATH_TO_PROG))
			{
				string app_launch = PROG_FULL;
				system(app_launch.c_str());
			}
			else if (term_input != "")
				cout << "Unknown command: " << term_input << endl;
		}
    }
}
