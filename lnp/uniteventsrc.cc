#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <assert.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_EVENT_NUMBER	1024
static int pipefd[2];

int setnonblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

void addfd(int epollfd, int fd)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblocking(fd);
}

// signal handing function
void sig_handler(int sig)
{
	// save errno, keep re-enter of function after function restore
	int save_errno = errno;
	int msg = sig;
	send(pipefd[1], (char *)&msg, 1, 0);  // write signal num to pipe, in order to inform main loop
	errno = save_errno;
}

void addsig(int sig)
{
	struct sigaction sa;
	memset(&sa, '\0', sizeof(sa));
	sa.sa_handler = sig_handler;
	sa.sa_flags |= SA_RESTART;
	sigfillset(&sa.sa_mask);
	assert(sigaction(sig, &sa, NULL) != -1);
}

int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		printf("Usage: %s ip_address, port_number\n", basename(argv[0]));
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

	int listenfd = socket(PF_INET, SOCK_STREAM, 0);
	assert(listenfd > 0);

	ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
	assert(ret != -1);

	ret = listen(listenfd, 5);
	assert(ret != -1);

	epoll_event events[MAX_EVENT_NUMBER];
	int epollfd = epoll_create(5);
	assert(epollfd != -1);
	addfd(epollfd, listenfd);

	ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd);
	assert(ret != -1);
	setnonblocking(pipefd[1]);
	addfd(epollfd, pipefd[0]);

	addsig(SIGHUP);
	addsig(SIGCHLD);
	addsig(SIGTERM);
	addsig(SIGINT);
	bool stop_server = false;

	while (!stop_server)
	{
		int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
		if ((number < 0) && (errno == EINTR))
		{
			printf("error happened!\n");
			break;
		}

		for (int i = 0; i < number; ++i)
		{
			int sockfd = events[i].data.fd;
			if (sockfd == listenfd)
			{
				struct sockaddr_in client_addr;
				socklen_t cliaddr_len = sizeof(client_addr);
				int connfd = accept(sockfd, (struct sockaddr*)&client_addr, &cliaddr_len);
				addfd(epollfd, connfd);
			}
			else if ((sockfd == pipefd[0]) && (events[i].events & EPOLLIN))
			{
				char signals[1024];
				int ret = recv(sockfd, signals, sizeof(signals), 0);
				if (ret == -1 || ret == 0)
				{
					continue;
				}
				else
				{
					for (int i = 0; i < ret; ++i)
					{
						switch(signals[i])
						{
							case SIGINT:
							case SIGTERM:
								stop_server = true;
								break;
							case SIGHUP:
							case SIGCHLD:
								continue;
						}
					}
				}
			}
			else
			{
			}
		}
	}

	printf("close fd\n");
	close(listenfd);
	close(pipefd[0]);
	close(pipefd[1]);

	return 0;
}
