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
		//printf("Usage:%s ip_address port_number\n", basename(argv[0]));
		printf("Usage:./client ip_address port_number\n");
		return 1;
	}

	const char* ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &server_addr.sin_addr);
	server_addr.sin_port = htons(port);

	int conn_sock = socket(AF_INET, SOCK_STREAM, 0);

	int len = sizeof(server_addr);
	int ret = connect(conn_sock, (struct sockaddr*)&server_addr, len);

	const char* msg = "Hello World!";
	int bytes = send(conn_sock, msg, strlen(msg), 0);

	close(conn_sock);

	return 0;
}
