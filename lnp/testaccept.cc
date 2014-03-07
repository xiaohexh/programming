#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		printf("Usage:%s ip_address, port_number", basename(argv[0]));
		return 1;
	}

	const char* ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr);
	address.sin_port = htons(port);

	int sock = socket(PF_INET, SOCK_STREAM, 0);
	assert(sock >= 0);

	int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
	assert(ret != -1);

	printf("Before listen ...\n");
	ret = listen(sock, 5);
	printf("After listen ...\n");

    //sleep(20);

	struct sockaddr_in client;
	socklen_t cliaddr_len = sizeof(client);

	printf("Before accept ...\n");
	int connfd = accept(sock, (struct sockaddr*)&client, &cliaddr_len);
	printf("After accept ...\n");
	if (connfd < 0)
	{
		printf("error msg is %s", strerror(errno));
	}
	else
	{
		char remote_cli[INET_ADDRSTRLEN];
		printf("Connect with ip:%s, port:%d\n", \
				inet_ntop(AF_INET, &client.sin_addr, remote_cli, INET_ADDRSTRLEN), \
				ntohs(client.sin_port));

		//--------------------------//
		// getsockname/getpeername
		//--------------------------//
		struct sockaddr_in local;
		socklen_t localaddr_len = sizeof(local);
		getsockname(sock, (struct sockaddr*)&local, &localaddr_len); 
		char localip[20];
		inet_ntop(AF_INET, &local.sin_addr, localip, 20); 
		printf("local ip:%s, local port:%d\n", localip, ntohs(local.sin_port));

		struct sockaddr_in remote;
		socklen_t remoteaddr_len = sizeof(remote);
		getpeername(connfd, (struct sockaddr*)&remote, &remoteaddr_len);
		char remoteip[20];
		inet_ntop(AF_INET, &remote.sin_addr, remoteip, 20); 
		printf("remote ip:%s, remote port:%d\n", remoteip, ntohs(remote.sin_port));

		close(connfd);
	}

	close(sock);

	return 0;
}
