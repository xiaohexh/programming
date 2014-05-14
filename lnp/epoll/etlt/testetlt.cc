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

	epoll_ctrl(epollfd, EPOLL_CTRL_ADD, fd, &event);
	setnonblocking(fd);
}

// LT mode
void lt(epoll_event* events, int number, int epollfd, int listenfd)
{
	char buf[BUFF_SIZE];
	for (int i = 0; i < number; ++i)
	{

	}
}













