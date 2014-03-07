#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <assert.h>

#define BUFFSIZE	128

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Usage:%s hostname\n", basename(argv[0]));
		return 1;
	}

	char* host = argv[1];
	printf("host ip length:%d\n", strlen(host));
	/**
	// get host information through host name
	struct hostent * hostinfo = gethostbyname(host);
    assert(hostinfo);
	**/
	//get host information through host ip
	struct hostent * hostinfo = gethostbyaddr(host, strlen(host), AF_INET);
    assert(hostinfo);

	//get daytime service info
	struct servent* servinfo = getservbyname("daytime", "tcp");
	assert(servinfo);
	printf("daytime port is %d\n", ntohs(servinfo->s_port));

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = servinfo->s_port;
	address.sin_addr = *(struct in_addr *)(*hostinfo->h_addr_list);

	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	int result = connect(sockfd, (struct sockaddr*)&address, sizeof(address));
	assert(result != -1);

	char buffer[BUFFSIZE];
	memset(buffer, '\0', BUFFSIZE);
	result = read(sockfd, buffer, BUFFSIZE - 1);
	assert(result > 0);
	printf("the day time is %s\n", buffer);
	close(sockfd);

	return 0;
}
