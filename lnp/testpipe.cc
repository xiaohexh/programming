#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sstream>
#include <iostream>

#define BUF_SIZE 128

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		printf("Usage:%s <string>\n", basename(argv[0]));
		return 1;
	}

	int pfds[2];
	if (pipe(pfds) < 0)
	{
		printf("pipe failed\n");
		return 1;
	}

	printf("parent pid:%d\n", getpid());

	int cpid = fork();
	if (cpid < 0)
	{
		printf("fork child failed\n");
		return 1;
	}

	if (cpid == 0)
	{
		close(pfds[1]);
		char buf[BUF_SIZE];
		memset(buf, '\0', BUF_SIZE);
		while (read(pfds[0], buf, BUF_SIZE - 1) > 0)
		{
			write(STDOUT_FILENO, buf, strlen(buf));
			memset(buf, '\0', BUF_SIZE);
		}
		write(STDOUT_FILENO, "\n", 1);
		close(pfds[0]);
		exit(EXIT_SUCCESS);
	}

	close(pfds[0]);
	write(pfds[1], argv[1], strlen(argv[1]));
	close(pfds[1]);
	wait(NULL);

	return 0;
}
