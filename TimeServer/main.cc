#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include "CommonMethod.h"

#define MAX_LINE 1024
#define IPV4

#ifdef IPV4
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stdout, "usage: <port>!\n");
		return -1;
	}
	struct sockaddr_in serveraddr;
	int listenfd, n;
	if ((listenfd = socketcommon::Socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stdout, "Socket error!\n");
		return 1;
	}
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	int portnumber = atoi(argv[1]);
	serveraddr.sin_port = htons(portnumber);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	/* if (socketcommon::Bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr)) < 0)
	{
		fprintf(stdout, "Bind Error\n");
		return 1;
	}
	if (socketcommon::Listen(listenfd, 5) < 0)
	{
		fprintf(stdout, "Listen Error\n");
		return 1;		
	} */
	socketcommon::Bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr));
	socketcommon::Listen(listenfd, 5);
	char buf[MAX_LINE];
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		int fd = socketcommon::Accept(listenfd, NULL, NULL);
		{
			socklen_t len = sizeof(struct sockaddr);
			struct sockaddr_in sa;
			memset(&sa, 0, sizeof(struct sockaddr));
			if (!getpeername(fd, (struct sockaddr *)&sa, &len))
			{
				char sql[1024];
				char machine_ip[1024];
				memset(sql, 0, 1024);
				snprintf(sql, 1024, "client login. ip: %s, port :%d", inet_ntoa(sa.sin_addr), ntohs(sa.sin_port));
				snprintf(machine_ip, 17, "%s", inet_ntoa(sa.sin_addr));
				//mylog(sql);
				fprintf(stdout, "Conn=[%s,%s].\n", machine_ip, sql);
			}
		}
		time_t ti = time(NULL);
		/* tm* t= localtime(&ti);
		snprintf(buf, strlen(buf), "%s\n", ctime(&ti)); */
		strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&ti));
		//fprintf(stdout, "result=[%s].\n", buf);
		socketcommon::Write(fd, (void *)buf, strlen(buf));
		socketcommon::Close(fd);
	}
}
#endif
