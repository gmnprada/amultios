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

// net stuff
#include <stdint.h>
#if defined(_WIN32)
#include <WS2tcpip.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#endif

#ifdef _WIN32
#undef errno
#undef ECONNABORTED
#undef ECONNRESET
#undef ENOTCONN
#undef EAGAIN
#undef EINPROGRESS
#undef EISCONN
#undef EALREADY
#define errno WSAGetLastError()
#define ECONNABORTED WSAECONNABORTED
#define ECONNRESET WSAECONNRESET
#define ENOTCONN WSAENOTCONN
#define EAGAIN WSAEWOULDBLOCK
#define EINPROGRESS WSAEWOULDBLOCK
#define EISCONN WSAEISCONN
#define EALREADY WSAEALREADY
#else
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close
#endif
extern int createTcpListenSocket(uint16_t port,const int backlog);
extern void enable_address_reuse(int fd);
extern void change_blocking_mode(int fd, int nonblocking);
extern FILE *OpenCFile(const std::string &filename, const char *mode);
extern void sleep_ms(int ms);