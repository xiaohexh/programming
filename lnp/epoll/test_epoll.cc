#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <assert.h>
#include <errno.h>

#define BUF_SIZE 1024
#define MAX_EVENTS_SIZE 10
#define SERV_IP	"127.0.0.1"
#define PORT_NUM 12345

int setnonblocking(int fd)
{
    int old_flag = fcntl(fd, F_GETFL);
    int new_flag = old_flag | O_NONBLOCK;
    fcntl(fd, new_flag, F_SETFL);
    return old_flag;
}

int main(int argc, char** argv)
{
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(listen_sock >= 0);
    setnonblocking(listen_sock);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(PORT_NUM);

    int ret = bind(listen_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    assert(ret != -1);

    ret = listen(listen_sock, 10);
    assert(ret != -1);

    struct epoll_event ev, events[MAX_EVENTS_SIZE];
    int epollfd = epoll_create(MAX_EVENTS_SIZE);
    if (epollfd == -1)
    {
        perror("epoll create failed\n");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) < 0)
    {
        perror("epoll ctl add listen sock failed\n");
        exit(EXIT_FAILURE);
    }

    for (;;)
    {
        int nfds = epoll_wait(epollfd, events, MAX_EVENTS_SIZE, -1);
        if (nfds < 0)
        {
        }

		int conn_sock;

        for (int i = 0; i < nfds; ++i)
        {
            if (events[i].data.fd == listen_sock)
            {
                struct sockaddr_in cli_addr;
                socklen_t addrlen = sizeof(cli_addr);
                conn_sock = accept(listen_sock, (struct sockaddr*)&cli_addr, &addrlen);
                if (conn_sock == -1)
                {
                    perror("accept failed\n");
                    exit(EXIT_FAILURE);
                }

                setnonblocking(conn_sock);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = conn_sock;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev);
            }
            else if (events[i].events & EPOLLIN)
            {
                if ((conn_sock = events[i].data.fd) < 0)
                {
                    printf("events[%d].data.fd:%d is invalid!\n", i, conn_sock);
                    exit(EXIT_FAILURE);
                }

                char buf[BUF_SIZE];
                std::string contents;
                while (1)
                {
					memset(buf, '\0', BUF_SIZE);
                    int nbytes = recv(conn_sock, buf, BUF_SIZE - 1, 0);
                    if (nbytes < 0)
                    {
                        perror("recv failed\n");
						break;
                    }
                    else if (nbytes == 0)
                    {
                        close(conn_sock);
                        events[i].data.fd = -1;
                    }
                    else
                    {
						contents.append(buf);
                    }
                }
				printf("recv data from client:%s\n", contents.c_str());
				contents.clear();
            }
			else if (events[i].events & EPOLLOUT)
			{
				// write data to socket fd
			}
        }
    }

    return 0;
}
