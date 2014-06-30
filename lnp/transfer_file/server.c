#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <assert.h>
#include <errno.h>

#define BUFF_SIZE 64

int main(int argc, char** argv)
{
	int listen_sock;
	FILE* fp = NULL;

	if (argc <= 3)
	{
		//printf("Usage:%s ip_address port_number file_name\n", basename(argv[0]));
		printf("Usage:./server ip_address port_number file_name\n");
		return 1;
	}

	const char* ip = argv[1];
	int port = atoi(argv[2]);
	const char* file_name = argv[3];

	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &server_addr.sin_addr);
	server_addr.sin_port = htons(port);

	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	assert(listen_sock != -1);

	int ret = bind(listen_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	assert(ret != -1);

	ret = listen(listen_sock, 10);
	assert(ret != -1);

	while (1)
	{
		struct sockaddr_in client_addr;
		socklen_t len = sizeof(client_addr);
		int conn_sock = accept(listen_sock, (struct sockaddr*)&client_addr, &len);
		
		char buf[BUFF_SIZE];
		memset(buf, '\0', BUFF_SIZE);
		int bytes = recv(conn_sock, buf, BUFF_SIZE - 1, 0);
		if (bytes < 0)
		{
			close(conn_sock);
			return -1;
		}
		else if (bytes == 0)
		{
			close(conn_sock);
			break;
		}
		else
		{
			fp = fopen(file_name, "w");
			fwrite(buf, strlen(buf), 1, fp);
			fclose(fp);
			close(conn_sock);
		}
	}

	close(listen_sock);

	return 0;
}
