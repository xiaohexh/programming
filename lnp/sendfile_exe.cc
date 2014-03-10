#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>

int main(int argc, char** argv)
{
	if (argc <= 3)
	{
		printf("Usage:%s ip_address port_number file_name\n", basename(argv[0]));
		return 1;
	}

	char*	ip = argv[1];
	int		port = atoi(argv[2]);
	char*	file_name = argv[3];

	int		fd = open(file_name, O_RDONLY);
	assert(fd != -1);
	struct stat stat_buff;
	fstat(fd, &stat_buff);

	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr);
	address.sin_port = htons(port);

	int		sock = socket(PF_INET, SOCK_STREAM, 0);
	assert(sock != -1);

	socklen_t	len = sizeof(address);
	int		ret = bind(sock, (struct sockaddr*)&address, len);
	assert(ret != -1);

	ret = listen(sock, 5);
	assert(ret != -1);

	struct sockaddr_in client;
	socklen_t	clilen = sizeof(client);
	int connfd = accept(sock, (struct sockaddr*)&client, &clilen);
	if (connfd < 0)
	{
		printf("accept failed\n");
	}
	else
	{
		sendfile(connfd, fd, NULL, stat_buff.st_size);
		close(connfd);
	}
	
	close(sock);
	return 0;
}
