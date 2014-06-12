#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>

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

	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(listenfd >= 0);

	int ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
	assert(ret != -1);

	ret = listen(listenfd, 5);
	assert(ret != -1);

	struct sockaddr_in cli_addr;
	socklen_t cli_addr_len = sizeof(cli_addr);
	int connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &cli_addr_len);
	if (connfd < 0)
	{
		printf("errno is: %d\n", errno);
		close(listenfd);
	}

	char buf[1024];
	fd_set read_fds;
	fd_set except_fds;
	FD_ZERO(&read_fds);
	FD_ZERO(&except_fds);

	struct timeval wait_time = {3, 0};

	while (1)
	{
		memset(buf, '\0', 1024);
		FD_SET(connfd, &read_fds);
		FD_SET(connfd, &except_fds);
		printf("*********************\n");
		ret = select(connfd + 1, &read_fds, NULL, &except_fds, &wait_time);
		printf("---------------------\n");
		if (ret < 0)
		{
			printf("selection failure\n");
			break;
		}

		if (FD_ISSET(connfd, &read_fds))
		{
			ret = recv(connfd, buf, sizeof(buf) - 1, 0);
			if (ret <= 0)
			{
				break;
			}
			printf("get %d bytes of normal data:%s\n",
					ret, buf);
		}
		else if (FD_ISSET(connfd, &except_fds))
		{
			ret = recv(connfd, buf, sizeof(buf) - 1, MSG_OOB);
			if (ret <= 0)
			{
				break;
			}
			printf("get %d bytes of oob data:%s\n",
					ret, buf);
		}
	}

	close(connfd);
	close(listenfd);

	return 0;
}
