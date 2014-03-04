#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	char dst[128];
	memset(dst, 0, 128);
	dst[127] = '\0';
	char *src = "192.168.8.212";
	char *sz = inet_pton(AF_INET, src, dst);
	printf("%x\n", dst);

	return 0;
}
