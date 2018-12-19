//--------------------------------------------------
/*
	\file		main.cpp

 	\brief		Basic tcp client which runs from
 				command line.

 	\note		Syntax for execute tcp_client:
 				tcp_client [-a address][-p port] -r request
 				-a	Server address (default is 127.0.0.1)
				-p	Server listening port (default is 5001)
				-r	Type of request - mem, cpu

	\date		14.11.2018
	\version	1.0

	\author		Bc. Jan Prasil
*/
//--------------------------------------------------
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <map>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>


#include "help.h"
#include "comm.h"

//--------------------------------------------------
//! Max number of characters of input argument
#define MAX_ARG_LEN 20
//#define BUFF_SIZE	100

using namespace std;


int main(int argc, char* argv[])
{
	map<const string, string> argMap = {{"--help", ""},{"-r", ""},{"-p", ""}, {"-a", ""}};	//!< Key-words definition
	struct sockaddr_in servAddr;
	int sockfd;
	bool running = true;

	// Check length of input arguments
	for(int i = 1; i < argc; i++)
	{
		if(strlen(&argv[i][0]) > MAX_ARG_LEN)
		{
			ErrorMessage("Invalid length of input arguments: %s", &argv[i][0]);
			return -1;
		}
	}

	// Parse an arguments of command line
	ParseArguments(argc, argv, argMap);

	// Get value for --help key-word
	string helpVal = argMap.at("--help");

	if(!helpVal.empty())
	{
		// --help key-word was present in the command line
		PrintHelp();
	}
	else
	{
		char buffer[BUFF_SIZE];
		string tmpStr;
		servAddr.sin_family = AF_INET;

		// Read address
		tmpStr = argMap.at("-a");
		strcpy(buffer, tmpStr.c_str());
		if(inet_pton(AF_INET, buffer, &servAddr.sin_addr) <= 0)
		{
			if(inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr) <= 0)
			{
				HandleError("inet_pton() error");
			}
		}

		// Read port
		tmpStr = argMap.at("-p");
		strcpy(buffer, tmpStr.c_str());
		servAddr.sin_port = htons(atoi(buffer));

		// Create TCP socket
		int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(sockfd == -1)
		{
			HandleError("socket() error");
		}

		// Connect to server
		if(connect(sockfd, reinterpret_cast<sockaddr*>(&servAddr), sizeof(servAddr)) == -1)
		{
			HandleError("connect() error");
		}

		// Connection OK - read request
		tmpStr = argMap.at("-r");
		StringToLowercase(tmpStr);
		strcpy(buffer, tmpStr.c_str());


		int len = ClientComm(sockfd, buffer);

		DebugMessage("Receive complete, data: %s length: %d", buffer, len);

		if(fcntl(sockfd, F_GETFD) != -1 || errno != EBADF)
		{
			if(close(sockfd) == -1)
			DebugMessage("Error during socket closing: %s", strerror(errno));
		}

		DebugMessage("Client finished");

/*		char tmpBuff[BUFF_SIZE];
		string tmpStr;
		servAddr.sin_family = AF_INET;

		// Read address
		tmpStr = argMap.at("-a");
		strcpy(tmpBuff, tmpStr.c_str());
		if(inet_pton(AF_INET, tmpBuff, &servAddr.sin_addr) <= 0)
		{
			if(inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr) <= 0)
			{
				HandleError("inet_pton() error");
			}
		}

		// Read port
		tmpStr = argMap.at("-p");
		strcpy(tmpBuff, tmpStr.c_str());
		servAddr.sin_port = htons(atoi(tmpBuff));

		// Read request
		tmpStr = argMap.at("-r");
		StringToLowercase(tmpStr);
		if(tmpStr.compare("mem") && tmpStr.compare("cpu"))
		{
			ErrorMessage("Invalid request command: %s", tmpStr.c_str());
		}
		else
		{
			strcpy(tmpBuff, tmpStr.c_str());

			int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if(sockfd == -1)
			{
				HandleError("socket() error");
			}

			if(connect(sockfd, reinterpret_cast<sockaddr*>(&servAddr), sizeof(servAddr)) == -1)
			{
				HandleError("connect() error");
			}

			// Prepare request
			size_t len = strlen(tmpBuff);
			tmpBuff[len++] = '\n';
			tmpBuff[len] = 0;

			int attempts = 10;
			while(running && attempts)
			{
				// Send request
				len = send(sockfd, tmpBuff, len, 0);

				if(len == -1)
				{
					attempts--;
					ErrorMessage("send() error: %s", strerror(errno));
				}
				else
				{
					DebugMessage("It was send %d bytes, waiting for receive", len);
					len = recv(sockfd, tmpBuff, BUFF_SIZE, 0);
					tmpBuff[len] = 0;

					if(len == -1)
					{
						HandleError("recv() error");
					}
					else
					{
						DebugMessage("Receive complete, data: %s length: %d", tmpBuff, len);
						running = false;
					}

				}
			}

			DebugMessage("Client finished");
		}
		*/
	}
}

