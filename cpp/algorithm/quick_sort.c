#include <stdio.h>

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//************************************************/
//brief: quick sort
int partition(int*a, int start, int end)
{
	int pivot_value = a[end];
	int j = start - 1, i = start;
	for (i = start; i < end; ++ i)
	{
		if (a[i] <= pivot_value)
		{
			++j;
			if (i != j)
			{
				swap(&a[i], &a[j]);
			}
		}
	}

	swap(&a[j + 1], &a[end]);

	return j + 1;
}

void quick_sort(int* a, int start, int end)
{
	if (start >= end)
		return;
	int pivot = partition(a, start, end);
	quick_sort(a, start, pivot - 1); 
	quick_sort(a, pivot + 1, end); 
}
//************************************************/

int main()
{
	int i;
	int a[] = {5, 6, 7, 4, 3, 8};
	int arr_len = sizeof(a) / sizeof(a[0]);
	printf("before quick sort:");
	for (i = 0; i < arr_len; ++i)
	{
		printf("%d", a[i]);
		if (i != arr_len -1)
			printf(",");
	}
	printf("\n");
	quick_sort(a, 0, 5);
	printf("after quick sort:");
	for (i = 0; i < arr_len; ++i)
	{
		printf("%d", a[i]);
		if (i != arr_len -1)
			printf(",");
	}
	printf("\n");

	return 0;
}
