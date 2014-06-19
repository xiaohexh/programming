#define _GNU_SOURCE 1  // to use POLLRDHUP
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

#define BUFFER_SIZE 64

int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		printf("Usage: %s ip_address port_number\n",
				basename(argv[0]));
		return 1;
	}

	const char* ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in serv_addr;
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &serv_addr.sin_addr);
	serv_addr.sin_port = htons(port);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd >= 0);

	int ret = connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (ret < 0)
	{
		printf("connect to server failed\n");
		close(sockfd);
		return 1;
	}
	
	pollfd fds[2];
	fds[0].fd = 0;  // standard input
	fds[0].events = POLLIN;
	fds[0].revents = 0;
	fds[1].fd = sockfd;
	fds[1].events = POLLIN;
	fds[0].revents = 0;

	char read_buf[BUFFER_SIZE];
	int pipefd[2];
	ret = pipe(pipefd);
	assert(ret != -1);

	while (1)
	{
		ret = poll(fds, 2, -1);
		if (ret < 0)
		{
			printf("poll failure\n");
			break;
		}

		if (fds[1].revents & POLLRDHUP)
		{
			printf("server close the connection\n");
			break;
		}
		if (fds[1].revents & POLLIN)
		{
			memset(read_buf, '\0', BUFFER_SIZE);
			ret = recv(fds[1].fd, read_buf, BUFFER_SIZE - 1, 0);
			printf("%s", read_buf);
		}
		else if(fds[0].revents & POLLIN)
		{
			ret = splice(0, NULL, pipefd[1], NULL, 32768,
					SPLICE_F_MORE | SPLICE_F_MOVE);
			ret = splice(pipefd[0], NULL, fds[1].fd, NULL, 32768,
					SPLICE_F_MORE | SPLICE_F_MOVE);
		}
	}

	close(sockfd);
	return 0;
}
