#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler()
{
	printf("Hello\n");
}

void print()
{
	printf("print\n");
}

int main()
{
	int i = 1;
	signal(SIGALRM, print);
	alarm(5);
	signal(SIGUSR1, handler);
	raise(SIGUSR1);
	kill(getpid(), SIGUSR1);

	printf("After kill syscall\n");

	for (; i < 8; ++i)
	{
		printf("sleep %d ... \n", i);
		sleep(1);
	}

	return 0;
}
