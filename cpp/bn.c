#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

int main()
{
	char *path = "/root/home/admin";
	//printf("dir name:%s\n", dirname(path));
	printf("base name:%s\n", basename(path));

	return 0;
}
