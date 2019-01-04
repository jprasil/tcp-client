//---------------------------------------------------
/*
 	\file		comm.cpp

 	\brief		This module defines communication
 				messages based on TCP protocol

	\date		25.10.2018
	\version	1.0

	\author		Bc. Jan Prasil

	\note		Implements ClientComm() only
*/
//---------------------------------------------------

#include "comm.h"
#include "help.h"

#include <sys/socket.h>
#include <cstring>
#include <cerrno>
#include <unistd.h>


//---------------------------------------------------
//! Commands definition
const char *cmd[] = {"cpu", "mem"};

//---------------------------------------------------
/*
	\brief	Function sends request to server

	\param	_socket	Client's socket descriptor
			_comm	Passed pointer to buffer
*/
//---------------------------------------------------
int ClientComm(int _socket, char* _buff)
{
	bool running = true;
	int retval = 0;

	// When command is valid then prepare request
	if(strcmp(_buff, &cmd[Cmd::CPU_UTILIZATION][0]) != 0 &&
			strcmp(_buff, &cmd[Cmd::MEM_USAGE][0]) != 0)
	{
		ErrorMessage("Invalid request command: %s", _buff);
	}
	else
	{
		// Prepare request
		size_t len = strlen(_buff);
		_buff[len++] = '\n';
		_buff[len] = 0;

		// Number of attempts for send request
		int attempts = 10;
		while(running && attempts)
		{
			// Send request
			len = send(_socket, _buff, len, 0);

			if(len == -1)
			{
				// Send error
				attempts--;
				ErrorMessage("send() error: %s", strerror(errno));
			}
			else
			{
				// Wait for response
				DebugMessage("It was sent %d bytes, waiting for receive", len);
				len = recv(_socket, _buff, (BUFF_SIZE - 1), 0);

				if(len == -1)
				{
					HandleError("recv() error");
				}
				else
				{
					// Response is received and stored into the buffer
					_buff[len] = 0;
					retval = len;
					running = false;
				}
			}
		}
	}

	return retval;
}
