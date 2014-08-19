#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>

#define MAXSIZE 128

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("usage:%s ipaddress port\n", basename(argv[0]));
		exit(1);
	}

	int sock;
	struct sockaddr_in srvaddr;
	int ret = 0;
	char* msg;
	char buff[MAXSIZE];

	bzero(&srvaddr, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &srvaddr.sin_addr);
	srvaddr.sin_port = htons(atoi(argv[2]));

	sock = socket(AF_INET, SOCK_STREAM, 0);

	msg = "Hello World!\n";
	ret = connect(sock, (struct sockaddr*)&srvaddr, sizeof(srvaddr));
	send(sock, msg, sizeof(msg), 0);

	recv(sock, buff, sizeof(buff), 0);
	fputs(buff, stdout);

	return 0;	
}
