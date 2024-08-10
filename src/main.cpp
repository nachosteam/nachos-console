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

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <functional>
#include <locale>
#include "json.hpp"
#include "sha256.h"
#include "account.hpp"
#include "systems.hpp"

#define CNAME "NachosConsole"
//#define ver "2.0.3"
#ifdef _WIN32
	#include <windows.h>
	#define DIR_COMM "dir "
	#define PATH_TO_PROG "pkg\\" + term_input + ".exe"
	#define PROG_FULL "pkg\\" + fullcom
	#define WIN_UTF8 SetConsoleOutputCP(CP_UTF8)
	#if defined(_WIN32) && defined(_WIN64)
		#define HOST_OS " for Win64"
	#else
		#define HOST_OS " for Win32"
	#endif
#elif __linux__
	#define DIR_COMM "ls "
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
	/*if (!filesystem::exists("./pkg"))
		system("mkdir pkg");*/
	
	login();
	clear();

	/*Repo repos("./settings.json");*/
	
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
			help_com("default");
        }
        else if(term_input == "about")
        {
			about();
            /*cout << ".................." << endl <<
                    "..#.....#..######.\t" CNAME << HOST_OS << endl <<
                    "..##....#....#....\t" ver << endl <<
                    "..#.#...#....#....\tBy \x1B[33mNachosTeam\033[0m 2024" << endl <<
                    "..#..#..#....#....\thttps://github.com/nachosteam/nachos-console" << endl <<
                    "..#...#.#....#...." << endl <<
                    "..#....##....#....\t\x1B[36mUnder MIT License\033[0m" << endl <<
                    "..#.....#....#...." << endl <<
                    ".................." << endl;*/
		}
        else if(term_input == "exit")
            return 0;
        else if(term_input == "passwd")
			passwd_change();
        else if(term_input == "clear" or term_input == "cls")
			clear();
		/*else if (term_input == "pkg")
		{
			iss >> parameter;
        
			if (parameter == "-s" or parameter == "--sync")
			{
				iss >> action;
				
				string passwd_back;
				cout << "\t|password: ";
				getline(cin, passwd_back);
				ifstream i ("settings.json");
				json data;
				i >> data;
				string passwd_exists = data["password"];
				string pb_hash = SHA256::hashString(passwd_back);
				if (pb_hash == passwd_exists)
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
				help_com("pkg");
			else
				cout << "Unknown parameter. Type 'pkg --help'" << endl;
		}*/
		else if (term_input == "ls" or term_input == "dir")
		{
			iss >> parameter;
			string dir_cmd = DIR_COMM + parameter;
			system(dir_cmd.c_str());
		}
		else if (term_input == "echo")
			system(fullcom.c_str());
			//this command correctrly display only english text
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
		}*/
		//this shit is crashing, 'test' doesn't output russian text, 'кириллица' crashs because filesystem error
		//edited: 'test' is correctly output russian text, code has been converted from Windows-1251 to UTF-8(wtf code was in Windows-1251?), left problem with input on Cirillic (filesystem error) 
		/*else if (term_input == "test")
		{
			cout << "\x1B[36mTexting\033[0m" << endl;
		}*/
		else if (term_input == "SuperMegaAsFuckAdminPanelForEnablingSomething")
		{
			iss >> parameter;
			iss >> action;
			adminPanel(parameter, action);
		}
		else
		{
			/*if (filesystem::exists(PATH_TO_PROG))
			{
				string app_launch = PROG_FULL;
				system(app_launch.c_str());
			}
			else if (term_input != "")*/
			cout << "Unknown command: " << term_input << endl;
		}
    }
}
