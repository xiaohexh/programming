#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int i;
	for (i = 0; i < 2; ++i)
	{
		fork();
		printf("a ");
	}
	return 0;
}
