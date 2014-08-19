#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

#define MAXSIZE 128

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("useage:%s ipaddress port\n", basename(argv[0]));
		exit(1);
	}

	int listensock;
	int connsock;
	struct sockaddr_in srvaddr;

	int nrecv = 0;
	int ntmp = 0;
	char* buff[MAXSIZE + 1];
	char* ptr;

	bzero(&srvaddr, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &srvaddr.sin_addr);
	srvaddr.sin_port = htons(atoi(argv[2]));

	listensock = socket(AF_INET, SOCK_STREAM, 0);

	bind(listensock, (struct sockaddr*)&srvaddr, sizeof(srvaddr));

	listen(listensock, 5);

	for (;;)
	{
		connsock = accept(listensock, (struct sockaddr*)NULL, NULL);
		if (fork() == 0) // child process
		{
			close(listensock); // close listen socket

			// receive from client
			memset(buff, "\0", MAXSIZE);
			ptr = buff;
			while (1)
			{
				if ((nrecv = recv(connsock, ptr, MAXSIZE, 0)) < 0)
				{
					if (errno == EINTR)
						nrecv = 0;
					else
						return -1;
				}
				else if (nrecv == 0)
					break;

				ptr += nrecv;
			}

			// send to client
			send(connsock, buff, sizeof(buff), 0);

			close(connsock);

		}
		close(connsock);
	}

	close(listensock);

	return 0;
}
