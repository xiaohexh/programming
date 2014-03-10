#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		printf("Usage:%s ip_addr port_number\n", basename(argv[0]));
		return 1;
	}

	char*	ip = argv[1];
	int		port = atoi(argv[2]);

	struct sockaddr_in address;
	bzero(&address, sizeof(address));

	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, ip, &address.sin_addr);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	assert(sock >= 0);

	int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
	assert(ret != -1);

	ret = listen(sock, 5);
	assert(ret != -1);

	struct sockaddr_in client;
	socklen_t clilength = sizeof(client);
	int connfd = accept(sock, (struct sockaddr*)&client, &clilength);
	if (connfd < 0)
	{
		printf("error msg:%s\n", strerror(errno));
	}
	else
	{
		close(STDOUT_FILENO);
		dup(connfd);
		printf("adc");
		close(connfd);
	}

	close(sock);

	return 0;
}
