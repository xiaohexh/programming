#include <stdio.h>
#include <unistd.h>
#include <ctime>

int func(double n)
{
}

int func(int n)
{
	int sum = 0;
	int i;
	for (i = 0; i < n; ++i)
	{
		sum += i;
	}
	return sum;
}

int main(int argc, char** argv)
{
	int n = 100;
	int i = 0;
	printf("%d\n", func(5));

	while (1)
	{
		sleep(1);
		++i;
		if (i > n)
			break;
	}

	return 0;
}
