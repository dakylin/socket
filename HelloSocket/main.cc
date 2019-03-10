#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define IPV4
/*
test sample: This IP and port works well
GetTime 128.138.141.172 13
*/
#ifdef IPV4
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stdout, "usage: <IPADRESS> <port>!\n");
		return -1;
	}
	int sockfd, n;
	char receiveline[MAX_LINE + 1];
	struct sockaddr_in serveraddr;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stdout, "Socket error!\n");
		return 1;
	}
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	
	int portnumber = atoi(argv[2]);
	//printf("testNumber =[%d]\n", portnumber);

	serveraddr.sin_port = htons(portnumber);
	if (inet_pton(AF_INET, argv[1], &serveraddr.sin_addr) <= 0)
	{
		fprintf(stdout, "inet_pton error!\n");
		return 1;
	}
	if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
	{
		fprintf(stdout, "connect error!\n");
		return 1;
	}
	while((n = read(sockfd, receiveline, MAX_LINE)) > 0)
	{
		receiveline[n] = '\0';
		if (fputs(receiveline, stdout) == EOF)
		{
			fprintf(stdout, "fputs error!\n");
			return 1;
		}
		fprintf(stdout, "receive data:[%s]\n", receiveline);
	}
	if (n < 0)
	{
		fprintf(stdout, "read error!\n");
		return 1;
	}
	//fprintf(stdout, "End receive data:[%s]\n", receiveline);
	return 0;
}

#else
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stdout, "usage: <IPADRESS> <port>!\n");
		return -1;
	}
	int sockfd, n;
	char receiveline[MAX_LINE + 1];
	struct sockaddr_in6 serveraddr;

	if ((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stdout, "Socket error!\n");
		return 1;
	}
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin6_family = AF_INET;
	
	int portnumber = atoi(argv[2]);
	//printf("testNumber =[%d]\n", portnumber);

	serveraddr.sin6_port = htons(portnumber);
	if (inet_pton(AF_INET6, argv[1], &serveraddr.sin6_addr) <= 0)
	{
		fprintf(stdout, "inet_pton error!\n");
		return 1;
	}
	if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
	{
		fprintf(stdout, "connect error!\n");
		return 1;
	}
	while((n = read(sockfd, receiveline, MAX_LINE)) > 0)
	{
		receiveline[n] = '\0';
		if (fputs(receiveline, stdout) == EOF)
		{
			fprintf(stdout, "fputs error!\n");
			return 1;
		}
		fprintf(stdout, "receive data:[%s]\n", receiveline);
	}
	if (n < 0)
	{
		fprintf(stdout, "read error!\n");
		return 1;
	}
	//fprintf(stdout, "End receive data:[%s]\n", receiveline);
	return 0;

}
#endif
