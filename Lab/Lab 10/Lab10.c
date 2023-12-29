#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int find_minmax(int* arr, int size, int* max, int* min);

int main()
{
	int size, i;
	int* arr;
	int max, min;

	printf("Enter array size: ");
	scanf("%d", &size);

	arr = (int*)malloc(sizeof(int) * size);
	for (i = 0; i < size; i++)
	{
		scanf("%d", arr + i);
	}
	printf("Entered numbers are\n");
	for (i = 0; i < size; i++)
	{
		printf("%d ", *(arr + i));
	}
	find_minmax(arr, size, &max, &min);
	printf("\nMaximum is %d\n", max);
	printf("Minimum is %d\n", min);

	printf("\nEnter array size: ");
	scanf("%d", &size);

	arr = (int*)realloc(arr, sizeof(int) * size);
	for (i = 0; i < size; i++)
	{
		scanf("%d", arr + i);
	}
	printf("Entered numbers are\n");
	for (i = 0; i < size; i++)
	{
		printf("%d ", *(arr + i));
	}
	find_minmax(arr, size, &max, &min);
	printf("\nMaximum is %d\n", max);
	printf("Minimum is %d\n", min);
	free(arr);

	return 0;
}

int find_minmax(int* arr, int size, int* max, int* min)
{
	int pmax = *arr;
	int pmin = *arr;
	for (int i = 0; i < size; i++)
	{
		if (pmax < *(arr + i))
		{
			pmax = *(arr + i);
		}
	}
	*max = pmax;
	for (int i = 0; i < size; i++)
	{
		if (pmin > *(arr + i))
		{
			pmin = *(arr + i);
		}
	}
	*min = pmin;
}