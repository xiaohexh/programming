#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>

const int ADDRLEN = 32;

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

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd >= 0);

	int ret = connect(sockfd, (struct sockaddr*)&address, sizeof(address));
	if (ret < 0)
	{
		printf("connet to %s:%d failed\n", ip, port);
	}
	else
	{
		struct sockaddr_in local_addr;
		struct sockaddr_in remote_addr;
		socklen_t local_len;
		socklen_t remote_len;
		if (//(getsockname(sockfd, (struct sockaddr*)&local_addr, &local_len) < 0))
				getpeername(sockfd, (struct sockaddr*)&remote_addr, &remote_len) < 0)
		{
			printf("getsockname failed\n");
		}
		else
		{
			char addr[ADDRLEN];
			/*
			memset(addr, '\0', ADDRLEN);
			const char* local_ip = inet_ntop(AF_INET, &local_addr.sin_addr, addr, local_len);
			printf("local_addr:%s\n", local_ip);
			*/

			memset(addr, '\0', ADDRLEN);
			const char* remote_ip = inet_ntop(AF_INET, &remote_addr.sin_addr, addr, remote_len);
			printf("remote addr:%s\n", remote_ip);
		}

		const char* oob_data = "Hello";
		const char* normal_data = "123456";
		send(sockfd, normal_data, strlen(normal_data), 0);
		sleep(3);
		send(sockfd, oob_data, strlen(oob_data), MSG_OOB);
		sleep(3);
		send(sockfd, normal_data, strlen(normal_data), 0);
	}

	close(sockfd);

	return 0;
}
