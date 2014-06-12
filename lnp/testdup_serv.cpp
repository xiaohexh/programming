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
    assert(argc >= 3);

    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    int ret = bind(sockfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sockfd, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t cli_addr_len = sizeof(client);
    int connfd = accept(sockfd, (struct sockaddr*)&client, &cli_addr_len);
    if (connfd < 0)
    {
        printf("accept failed\n");
    }
    else
    {
        char buff[32];
        memset(buff, '\0', 32);
        int rvbytes = recv(connfd, buff, 31, 0);
        if (rvbytes < 0)
        {
            printf("recv failed\n");
        }
        else
        {
            close(STDOUT_FILENO);
            dup(connfd);
            printf("%s\n", buff); // echo to client
            printf("adbcd");
            close(connfd);
        }
    }
    close(sockfd);
    return 0;
}
