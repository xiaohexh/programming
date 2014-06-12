#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <assert.h>

#define USER_LIMIT		5      //maximum user number
#define BUFFER_SIZE		64
#define FD_LIMIT		65535

