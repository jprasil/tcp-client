//---------------------------------------------------
/*
 	\file		help.cpp

 	\brief		Common functions

	\date		25.10.2018
	\version	1.0

	\author		Bc. Jan Prasil
*/
//---------------------------------------------------



#include "help.h"


#include <iostream>
#include <locale>

using namespace std;

//---------------------------------------------------
/*
	\brief	Function print help
*/
//---------------------------------------------------
void PrintHelp()
{
	cout << endl;
	cout << "tcp_client [options]" << endl << endl;
	cout << "Options:" << endl;
	cout << "-a       Server address (default is 127.0.0.1)" << endl;
	cout << "-p       Server listening port" << endl;
	cout << "-r       Type of request, may be used: cpu, mem" << endl << endl;
	cout << "--help   Print this help" << endl << endl;
}
//---------------------------------------------------
/*
	\brief	Function convert uppercase letter of input
			string to lowercase letter

	\param	_str	Converted string
*/
//---------------------------------------------------
void StringToLowercase(std::string& _str)
{
	std::locale loc;
	for(auto& it: _str)
	{
		it = std::tolower(it, loc);
	}
}
//---------------------------------------------------
/*
	\brief	Function parse arguments, which are passed
			through _argv

	\param	_argc	Number of arguments in the _argv
					array (invalid value can cause
					segmentation fault exception)
			_argv	Array with arguments values
			_cont	Map container, which define
					key-word for parsing arguments
*/
//---------------------------------------------------
void ParseArguments(const int _argc, char* _arg[], map<const string, string>& _cont)
{
	static int n = 1;

	if(n < _argc)
	{
		// Read argument
		string tmp = &_arg[n][0];

		// Test argument
		auto it = _cont.find(tmp);
		if(it != _cont.end())
		{
			// Argument is key-word
			if(it->first == "--help")
			{
				// Argument is --help key-word -> finish parsing
				it->second = "help";
				return;
			}
			else
			{
				// Argument is not --help key-word -> store argument value
				n++;
				it->second = &_arg[n][0];
			}
		}
		else
		{
			// Argument is not key-word -> attempt to find key-word and value
			if(tmp.size() > 2)
			{
				string key = tmp.substr(0, 2);
				string value = tmp.substr(2);
				auto it = _cont.find(key);
				if(it != _cont.end())
				{
					// Argument contains key-word -> store rest of argument as value
					it->second = value;
				}
			}
		}
		// Go to the parsing of next argument
		n++;
		ParseArguments(_argc, _arg, _cont);
	}
}

//---------------------------------------------------
/*
	\brief	Printing message into the standard output
			(stdout)

	\param	_str	Message (may included string
					arguments e.g. %s, %d, ..)
			...		String argument's values
*/
//---------------------------------------------------
void DebugMessage(const char* _str, ...)
{
#ifdef _DEBUG
	va_list args;
	char text[512];

	va_start(args, _str);
	vsnprintf(text, 512, _str, args);
	va_end(args);
	std::cout << text << std::endl;
#endif //_DEBUG
}

void ErrorMessage(const char* _str, ...)
{
	va_list args;
	char text[512];

	va_start(args, _str);
	vsnprintf(text, 512, _str, args);
	va_end(args);
	std::cerr << text << std::endl;
}


