#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define BUFFSIZE 1024

int main(int argc, char** argv)
{
    if (argc <= 2)
    {
        printf("Usage:%s server_ip server_port_number\n", basename(argv[0]));
        return 1;
    }

    char* ip = argv[1];
    int   port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &address.sin_addr);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock > 0);

    socklen_t servip_len = sizeof(address);
    int ret = connect(sock, (struct sockaddr*)&address, servip_len);
    if (ret == -1)
    {
        printf("error msg:%s\n", strerror(errno));
        return 1;
    }
    else
    {
        printf("Connect to server successfully!\n");
    }

    assert(ret != -1);

    char buffer[BUFFSIZE];
    memset(buffer, '\0', BUFFSIZE);
    ret = recv(sock, buffer, BUFFSIZE - 1, 0);
    if (ret > 0)
    {
        printf("read from server:%s\n", buffer);
    }
    else if (ret == 0)
    {
        printf("server end is shutdown\n");
    }
    else
    {
        printf("error happened, error msg:%s\n", strerror(errno));
        exit(1);
    }

    return 0;
}
