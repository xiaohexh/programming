#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <errno.h>

#define MAX_EVENT_NUM	1024
#define BUFF_SIZE		10

// set file description to non-blocking
int setnonblocking(int fd)
{
	int oldflag = fcntl(fd, F_GETFL);
	int newflag = oldflag | O_NONBLOCK;
	fcntl(fd, newflag, F_SETFL);
	return oldflag;
}

// register fd to epoll kernel event table
void addfd(int epollfd, int fd, bool enable_et)
{
	epoll_event event;
	event.data.fd = fd;
	if (enable_et)
	{
		event.events |= EPOLLET;
	}

	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblocking(fd);
}

// LT mode
void lt(epoll_event* events, int number, int epollfd, int listenfd)
{
	char buf[BUFF_SIZE];
	for (int i = 0; i < number; ++i)
	{
		int sockfd = events[i].data.fd;
		if (sockfd == listenfd)
		{
			struct sockaddr_in client;
			socklen_t cliAddrLen = sizeof(client);
			int connfd = accept(listenfd, (struct sockaddr*)&client, &cliAddrLen);
			addfd(epollfd, connfd, false);
		}
		else if (events[i].events & EPOLLIN)
		{
			printf("event trigger once\n");
			memset(buf, '\0', sizeof(buf));
			int ret = recv(sockfd, buf, sizeof(buf) - 1, 0);
			if (ret <= 0)
			{
				close(sockfd);
				continue;
			}
			printf("receive %d bytes data:%s\n", ret, buf);
		}
		else
		{
			printf("something else happened.\n");
		}
	}
}

void et(epoll_event* events, int number, int epollfd, int listenfd)
{
	char buf[BUFF_SIZE];
	for (int i = 0; i < number; ++i)
	{
		int sockfd = events[i].data.fd;
		if (sockfd == listenfd)
		{
			struct sockaddr_in client;
			socklen_t cli_addr_len = sizeof(client);
			int connfd = accept(listenfd, (struct sockaddr*)&client, &cli_addr_len);
			addfd(epollfd, connfd, true);
		}
		else if (events[i].events & EPOLLIN)
		{
			printf("event trigger once\n");
			while (1)
			{
				memset(buf, '\0', BUFF_SIZE);
				int ret = recv(sockfd, buf, BUFF_SIZE - 1, 0);
				if (ret < 0)
				{
					if (errno == EAGAIN || errno == EWOULDBLOCK)
					{
						printf("read later\n");
						break;
					}
					close(sockfd);
					break;
				}
				else if (ret == 0)
				{
					close(sockfd);
				}
				else
				{
					printf("recv %d bytes data:%s\n", ret, buf);
				}

			}
		}
		else
		{
			printf("something else happened\n");
		}
	}
}

int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		printf("Usage: %s ip_address port_number\n", basename(argv[0]));
		return 1;
	}

	const char* ip = argv[1];
	int port = atoi(argv[2]);

	int ret = 0;
	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr);
	address.sin_port = htons(port);

	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(listenfd >= 0);

	ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
	assert(ret != -1);

	ret = listen(listenfd, 5);
	assert(ret != -1);

	epoll_event events[MAX_EVENT_NUM];
	int epollfd = epoll_create(5);
	assert(epollfd != -1);
	addfd(epollfd, listenfd, true);

	while (1)
	{
		int ret = epoll_wait(epollfd, events, MAX_EVENT_NUM, -1);
		if (ret < 0)
		{
			printf("epoll failure\n");
			break;
		}

		lt(events, ret, epollfd, listenfd); // use lt mode
		et(events, ret, epollfd, listenfd); // use et mode
	}

	close(listenfd);
	return 0;
}
