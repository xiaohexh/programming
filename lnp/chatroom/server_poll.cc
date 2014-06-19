#define _GNU_SOURCE 1 // to use POLLRDHUP
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <assert.h>
#include <errno.h>

#define USER_LIMIT		5      //maximum user number
#define BUFFER_SIZE		64
#define FD_LIMIT		65535

struct client_data
{
	struct sockaddr_in address;
	char* write_buf;
	char buf[BUFFER_SIZE];
};

int setnonblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd, new_option, F_SETFL);
	return old_option;
}

int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		printf("Usage:%s ip_addres port_number\n", basename(argv[0]));
		return 1;
	}

	const char* ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &addr.sin_addr);
	addr.sin_port = htons(port);

	int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	assert(listen_sock >= 0);

	int ret = bind(listen_sock, (struct sockaddr*)&addr, sizeof(addr));
	assert(ret != -1);

	ret = listen(listen_sock, 5);
	assert(ret != -1);

	client_data* users = new client_data[FD_LIMIT];

	pollfd pfds[USER_LIMIT + 1];

	pfds[0].fd = listen_sock;
	pfds[0].events = POLLIN;
	pfds[0].revents = 0;

	for (int i = 1; i <= USER_LIMIT; ++i)
	{
		pfds[i].fd = -1;
		pfds[i].events = 0;
	}

	int user_counter = 0;
	while (1)
	{
		ret = poll(pfds, user_counter + 1, -1);
		if (ret < 0)
		{
			printf("poll failed\n");
			break;
		}

		for (int i = 0; i < user_counter + 1; ++i)
		{
			if ((pfds[i].fd == listen_sock) && (pfds[i].revents & POLLIN))
			{
				struct sockaddr_in client_addr;
				socklen_t addr_len = sizeof(client_addr);
				int conn_sock = accept(listen_sock, (struct sockaddr*)&client_addr, &addr_len);
				if (conn_sock < 0)
				{
					printf("accept failed\n");
					continue;
				}

				if (user_counter > USER_LIMIT)
				{
					const char* info = "too may users\n";
					send(conn_sock, info, strlen(info), 0);
					close(conn_sock);
					continue;
				}

				++user_counter;
				users[conn_sock].address = client_addr;
				setnonblocking(conn_sock);
				pfds[user_counter].fd = conn_sock;
				pfds[user_counter].events = POLLIN | POLLRDHUP;
				pfds[user_counter].revents = 0;
				printf("comes a new user, now have %d users\n", user_counter);
			}
			else if (pfds[i].revents & POLLERR)
			{
				printf("get an error from %d\n", pfds[i].fd);
				char errors[128];
				memset(errors, '\0', 128);
				socklen_t length = sizeof(errors);
				if (getsockopt(pfds[i].fd, SOL_SOCKET, SO_ERROR, &errors, &length) < 0)
				{
					printf("get socket option failed\n");
				}
				printf("error message:%s\n", errors);
				continue;
			}
			else if (pfds[i].revents & POLLRDHUP)
			{
				printf("client shutdown connection!\n");
				close(pfds[i].fd);
				users[pfds[i].fd] = users[pfds[user_counter].fd];
				pfds[i] = pfds[user_counter];
				--user_counter;
				printf("leave a user, now have %d users\n", user_counter);
			}
			else if (pfds[i].revents & POLLIN)
			{
				int conn_sock = pfds[i].fd;
				memset(users[conn_sock].buf, '\0', BUFFER_SIZE);
				int ret = recv(conn_sock, users[conn_sock].buf, BUFFER_SIZE - 1, 0);
				if (ret < 0)
				{
					// read error, shutdown connection
					if (errno != EAGAIN)
					{
						close(conn_sock);
						users[pfds[i].fd] = users[pfds[user_counter].fd];
						pfds[i] = pfds[user_counter];
						--user_counter;
					}
				}
				else if (ret == 0)
				{
					close(conn_sock);
					break;
				}
				else
				{
					for (int j = 1; j <= user_counter; ++j)
					{
						if (pfds[j].fd == conn_sock)
							continue;

						pfds[j].events &= ~POLLIN;
						pfds[j].events |= POLLOUT;
						users[pfds[j].fd].write_buf = users[conn_sock].buf;
					}
				}
			}
			else if (pfds[i].revents & POLLOUT)
			{
				printf("index:%d poll out event!\n", i);
				int conn_sock = pfds[i].fd;
				if (!users[conn_sock].write_buf)
					continue;

				printf("poll out fd:%d, and data is :%s, user_counter:%d\n", conn_sock, users[conn_sock].write_buf, user_counter);
				ret = send(conn_sock, users[conn_sock].write_buf, strlen(users[conn_sock].write_buf), 0);
				users[conn_sock].write_buf = NULL;

				pfds[i].events &= ~POLLOUT;
				pfds[i].events |= POLLIN;
			}
		}
	}

	close(listen_sock);

	delete [] users;

	return 0;

}
