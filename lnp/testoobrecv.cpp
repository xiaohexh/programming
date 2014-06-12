#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <assert.h>

const int BKLOG = 5;
const int BUFFSIZE = 128;

int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		printf("Usage:%s ip_address port_number\n",
				basename(argv[0]));
		return 1;
	}

	const char* ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr);
	address.sin_port = htons(port);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	assert(sock >= 0);

	int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
	assert(ret != -1);

	ret = listen(sock, BKLOG);
	assert(ret != -1);

	struct sockaddr_in cliAddr;
	socklen_t cliAddrLen = sizeof(cliAddr);
	int connfd = accept(sock, (struct sockaddr*)&cliAddr, &cliAddrLen);
	if (connfd < 0)
	{
		printf("accept failed\n");
	}
	else
	{
		char buffer[BUFFSIZE];
		memset(buffer, '\0', BUFFSIZE);
		ret = recv(connfd, buffer, BUFFSIZE - 1, 0);
		printf("got %d bytes of normal data '%s'\n", ret, buffer);

		memset(buffer, '\0', BUFFSIZE);
		ret = recv(connfd, buffer, BUFFSIZE - 1, 0);
		printf("got %d bytes of oob data '%s'\n", ret, buffer);

		memset(buffer, '\0', BUFFSIZE);
		ret = recv(connfd, buffer, BUFFSIZE - 1, 0);
		printf("got %d bytes of normal data '%s'\n", ret, buffer);

		close(connfd);
	}
		
	close(sock);
	return 0;
}
