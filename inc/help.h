//---------------------------------------------------
/*
 	\file		help.h

 	\brief		Common functions

	\date		25.10.2018
	\version	1.0

	\author		Bc. Jan Prasil
*/
//---------------------------------------------------
#ifndef INC_HELP_H_
#define INC_HELP_H_

#include <cstdio>
#include <cstdarg>
#include <map>


//---------------------------------------------------
/*
	\brief	Error handlers, that print error message
			and terminate a process with code
			EXIT_FAILURE
*/
//--------------------------------------------------
#define HandleError(_msg) \
	do{ perror(_msg); exit(EXIT_FAILURE); }while(0)

#define HandleError_ErrNum(_errNum, _msg) \
	do{ errno=_errNum; perror(_msg); exit(EXIT_FAILURE); }while(0)


//---------------------------------------------------
/*
	\brief	Function print help
*/
//---------------------------------------------------
void PrintHelp();
//---------------------------------------------------
/*
	\brief	Function convert uppercase letter of input
			string to lowercase letter

	\param	_str	Converted string
*/
//---------------------------------------------------
void StringToLowercase(std::string& _str);
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
void ParseArguments(const int _argc, char* _arg[], std::map<const std::string, std::string>& _cont);
//---------------------------------------------------
/*
	\brief	Function print message into the	standard
			output	(stdout)

	\param	_str	Message (may included string
					arguments e.g. %s, %d, ..)
			...		String argument's values
*/
//---------------------------------------------------
void DebugMessage(const char* _str, ...);
//---------------------------------------------------
/*
	\brief	Function print message into the error
			output (stderr)

	\param	_str	Message (may included string
					arguments e.g. %s, %d, ..)
			...		String argument's values
*/
//---------------------------------------------------
void ErrorMessage(const char* _str, ...);



#endif /* INC_HELP_H_ */
