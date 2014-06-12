#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 1024

struct fds
{
	int epollfd;
	int sockfd;
};

int setnonblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

// register EPOLLIN and EPOLLET event into epoll kernel event table
void addfd(int epollfd, int fd, bool oneshot)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;
	if (oneshot)
	{
		event.events |= EPOLLONESHOT;
	}

	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblocking(fd);
}

// reset event on fd
void reset_oneshot(int epollfd, int fd)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

// worker thread
void* worker(void* arg)
{
	int sockfd = ((fds*)arg)->sockfd;
	int epollfd = ((fds*)arg)->epollfd;
	printf("start new thread to receive data on fd:%d\n", sockfd);
	char buf[BUFFER_SIZE];
	memset(buf, '\0', BUFFER_SIZE);

	// recv data on sockfd
	while (1)
	{
		int ret = recv(sockfd, buf, BUFFER_SIZE - 1, 0);
		if (ret == 0)
		{
			printf("foreiner closed the connection\n");
			close(sockfd);
			break;
		}
		else if (ret < 0)
		{
			if (errno == EAGAIN)
			{
				reset_oneshot(epollfd, sockfd);
				printf("read later\n");
				break;
			}
		}
		else
		{
			printf("get content: %s\n", buf);
			// sleep 5s, simulate handle data
			sleep(5);
		}
	}
	printf("end thread receiving data on fd:%d\n", sockfd);
}

int main(int argc, char** argv)
{
}
