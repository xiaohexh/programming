#include <stdio.h>

void daemon()
{
	while (1)
	{
		printf("I still living...!\n");
		sleep(5);
	}
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

int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		printf("Usage: tst user_name!\n");
		return 1;
	}
	printf("Hello, %s\n", argv[1]);

	int		i;
	long	result = 0; 
	for (i = 1; i <= 100; ++i)
		result += i;

	printf("result[1-100] = %d\n", result);
	printf("result[1-250] = %d\n", func(250));

	daemon();
	
	return 0;
}
