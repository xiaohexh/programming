#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
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

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	socklen_t len = sizeof(address);

	int ret = connect(sockfd, (struct sockaddr*)&address, len);
	if (ret < 0) 
	{
		printf("connect to server failed\n");
	}
	else
	{
		const char* msg = "Andy";
		send(sockfd, msg, strlen(msg), 0);

		char buffer[32];
		memset(buffer, '\0', 32);
		//int rvbytes = recv(sockfd, buffer, buffer_len - 1, 0);
		int rvbytes = read(sockfd, buffer, buffer_len - 1);
		printf("%s\n", buffer);
	}

	close(sockfd);
	return 0;
}
