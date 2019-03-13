#include "CommonMethod.h"

namespace socketcommon
{
	int Socket(int family, int type, int protocol)
	{
		int n = socket(family, type, protocol);
		if (n < 0)
		{
			fprintf(stdout, "socket error!\n");
		}
		return n;
	}

	int Bind(int socket, struct sockaddr* Addr, size_t _size)
	{
		int n = bind(socket, Addr, _size);
		if (n < 0)
		{
			fprintf(stdout, "bind error, n=[%d]!\n", n);
		}
		return n;
	}

	int Listen(int socket, int type)
	{
		int n = listen(socket, type);
		if (n < 0)
		{
			fprintf(stdout, "listen error!\n");
		}
		return n;
	}

	int Accept(int socket, struct sockaddr* Addr, socklen_t* _size)
	{
		int n = accept(socket, Addr, _size);
		return n;
	}

	size_t Write(int socket, void *buf, size_t nbytes)
	{
		size_t n = write(socket, buf, nbytes);
	}

	int Close(int socket)
	{
		close(socket);
	}
}

