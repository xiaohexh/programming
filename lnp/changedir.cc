//-----------------------------//
// get current dir and change working directory
// ----------------------------//
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PATHLEN 128

int main(int argc, char** argv)
{
	char	path[PATHLEN];
	memset(path, '\0', PATHLEN);
	getcwd(path, PATHLEN - 1);
	printf("%s\n", path);

	if (strcmp("lnp", basename(path)) == 0)
	{
		size_t pathlen = strlen(path);
		path[pathlen - 3] = 'c';
		path[pathlen - 2] = 'p';
		path[pathlen - 1] = 'p';
		if (path[pathlen] == '\0')
			printf("last character is \'\\0\'\n");
		printf("%s\n", path);
		chdir(path);
		memset(path, '\0', PATHLEN);
		getcwd(path, PATHLEN - 1);
		printf("%s\n", path);
	}
	return 0;
}
