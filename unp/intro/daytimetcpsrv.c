#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <libgen.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFFERSIZE 128

int main(int argc, char** argv)
{
	int listenSock;
	int connSock;
	struct sockaddr_in address;
	time_t ticks = 0;
	char buff[BUFFERSIZE];

	if (argc < 3)
	{
		printf("usage: %s ip_address port\n", basename(argv[0]));
		exit(1);
	}

	if ((listenSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket return failed\n");
		exit(1);
	}

	char* ip = argv[1];
	int port = atoi(argv[2]);

	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr);
	address.sin_port = htons(port);

	bind(listenSock, (struct sockaddr*)&address, sizeof(address));

	listen(listenSock, 5);

	for (;;)
	{
		connSock = accept(listenSock, (struct sockaddr*)NULL, NULL);
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		send(connSock, buff, sizeof(buff), 0);
		close(connSock);
	}

	close(listenSock);
	exit(0);







}
