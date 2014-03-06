#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	char dst[128];
	char orig[20];
	int i = 0;

	memset(dst, 0, 128);
	memset(orig, 0, 20);

	dst[127] = '\0';
	char *src = "192.168.8.212";
	char *sz = inet_pton(AF_INET, src, dst);
	printf("%x\n", dst);


	char *or = inet_ntop(AF_INET, dst, orig, sizeof(dst));
	while (orig[i])
		printf("%c", orig[i++]);
	printf("\n");

	return 0;
}
