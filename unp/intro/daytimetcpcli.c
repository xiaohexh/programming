#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <netinet/in.h>  // struct sockaddr_in
#include <arpa/inet.h>
#include <sys/types.h>   // int8_t/int16_t/uint8_t/...

#define BUFFERSIZE 128

int main(int argc, char** argv)
{
	int connSock;
	char recvLine[BUFFERSIZE + 1];
	struct sockaddr_in srvAddr;
	int n = 0;

	if (argc < 3)
	{
		printf("usage: %s ipaddress port\n", basename(argv[0]));
		exit(1);
	}

	char* ip = argv[1];
	int port = atoi(argv[2]);

	if ((connSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket return failed\n");
		exit(1);
	}

	bzero(&srvAddr, sizeof(srvAddr));
	srvAddr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &srvAddr.sin_addr);
	srvAddr.sin_port = htons(port);

	if (connect(connSock, (struct sockaddr*)&srvAddr, sizeof(srvAddr)) < 0)
	{
		printf("connect failed\n");
		exit(1);
	}

	while ((n = recv(connSock, recvLine, BUFFERSIZE, 0)) > 0)
	{
		fputs(recvLine, stdout);
	}

	if (n < 0)
	{
		fputs("receive error\n", stdout);
	}

	exit(0);
}
