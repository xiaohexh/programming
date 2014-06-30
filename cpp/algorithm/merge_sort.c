#include <stdio.h>
#include <stdlib.h>

void merge(int* a, int start, int middle, int end)
{
	int i = start, j = middle + 1;
    int h = -1, k = 0;

	int len = end - start + 1;
	int* tmp = (int*)malloc(sizeof(int) * len);

	while (i <= middle && j <= end)
	{
		if (a[i] < a[j])
		{
			tmp[++h] = a[i++];
		}
		else
		{
			tmp[++h] = a[j++];
		}
	}
	while (i <= middle)
		tmp[++h] = a[i++];
	while (j <= end)
		tmp[++h] = a[j++];

	while (k < len)
		a[start++] = tmp[k++];

	free(tmp);
}

void merge_sort(int* a, int start, int end)
{
	if (start < end)
	{
		int middle = (end + start) / 2;
		merge_sort(a, start, middle);
		merge_sort(a, middle + 1, end);
		merge(a, start, middle, end);
	}
}

int main()
{
	int i;
	int a[] = {2, 9, 1, 8, 4, 5};
	int size = sizeof(a) / sizeof(a[0]);
	merge_sort(a, 0, size - 1);
	for (i = 0; i < size; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}
