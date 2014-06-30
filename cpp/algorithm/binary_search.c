#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int binary_search(int* a, int size, int target)
{
	int start = 0, end = size - 1;
	while (start <= end)
	{
		int middle = (start + end) / 2;
		if (a[middle] == target)
		{
			return middle;
		}
		else if (a[middle] < target)
		{
			start = middle + 1;
		}
		else
		{
			end = middle - 1;
		}
	}
	return -1;
}

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		printf("Usage:%s target_number\n", basename(argv[0]));
		return 1;
	}

	int target = atoi(argv[1]);

	int a[] = {3, 4, 7, 10, 15, 20};

	int index = binary_search(a, 6, target);
	if (index == -1)
		printf("cannot find:%d\n", target);
	else
		printf("%d is at %d\n", target, index);

	return 0;
}
