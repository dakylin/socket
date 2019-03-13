#ifndef _SOCKET_PACK_FUNCTION_COMMON_METHOD_H_
#define _SOCKET_PACK_FUNCTION_COMMON_METHOD_H_

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace socketcommon
{
	int Socket(int family, int type, int protocol);

	int Bind(int socket, struct sockaddr* Addr, size_t _size);

	int Listen(int socket, int type);

	int Accept(int socket, struct sockaddr* Addr, socklen_t* _size);

	size_t Write(int socket, void *buf, size_t nbytes);

	int Close(int socket);
}
#endif
