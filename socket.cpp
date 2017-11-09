// Copyright (c) 2014- PPSSPP Project.
// Refactored by and used on Amultios Project https://amultios.net

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0 or later versions.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official git repository for ppsspp and contact information can be found at
// https://github.com/hrydgard/ppsspp and http://www.ppsspp.org/.

// This is a refactored code port of Coldbird's code from http://code.google.com/p/aemu/
// All credit goes to him!

#include "global.h"
#include "socket.h"
#include <cstring>

int createTcpListenSocket(uint16_t port, const int backlog) {

	// Create Socket
	int fd = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Created Socket
	if (fd != SOCKET_ERROR)
	{
		// Enable Address Reuse
		enable_address_reuse(fd); // Shouldn't Reuse the port for built-in AdhocServer to prevent conflict with Dedicated AdhocServer

								  // Make Socket Nonblocking
		change_blocking_mode(fd, 1);

		// Prepare Local Address Information
		struct sockaddr_in local;
		memset(&local, 0, sizeof(local));
		local.sin_family = AF_INET;
		local.sin_addr.s_addr = INADDR_ANY;
		local.sin_port = htons(port);

		// Bind Local Address to Socket
		int bindresult = bind(fd, (struct sockaddr *)&local, sizeof(local));

		// Bound Local Address to Socket
		if (bindresult != SOCKET_ERROR)
		{
			// Switch Socket into Listening Mode
			listen(fd, backlog);

			// Return Socket
			return fd;
		}

		// Notify User
		else printf("TCP Create Socket: Bind returned %d (Socket error %d) \n", bindresult, errno);

		// Close Socket
		closesocket(fd);
	}

	// Notify User
	else printf("TCP Create Socket: Socket returned %d (Socket error %d \n", fd, errno);

	// Return Error
	return SOCKET_ERROR;
}

void enable_address_reuse(int fd) {
	int on = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on));
}

void change_blocking_mode(int fd, int nonblocking) {
	unsigned long on = 1;
	unsigned long off = 0;
#ifdef _WIN32
	if (nonblocking) {
		// Change to Non-Blocking Mode
		ioctlsocket(fd, FIONBIO, &on);
	}
	else {
		// Change to Blocking Mode
		ioctlsocket(fd, FIONBIO, &off);
	}
#else
	// Change to Non-Blocking Mode
	if (nonblocking) fcntl(fd, F_SETFL, O_NONBLOCK);

	// Change to Blocking Mode
	else
	{
		// Get Flags
		int flags = fcntl(fd, F_GETFL);

		// Remove Non-Blocking Flag
		fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);
	}
#endif
}

FILE *OpenCFile(const std::string &filename, const char *mode) {
#if defined(_WIN32) && defined(UNICODE)
	return _wfopen(ConvertUTF8ToWString(filename).c_str(), ConvertUTF8ToWString(mode).c_str());
#else
	return fopen(filename.c_str(), mode);
#endif
}


void sleep_ms(int ms) {
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(ms * 1000);
#endif
}