#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 10

int seqSearch(int a[], int size, int target);

int main()
{
	int a[SIZE];
	int i;
	int target;

	printf("Input 10 integers values: ");
	for(i = 0; i <SIZE; i++)
		scanf("%d", &a[i]);
	printf("Entered number is       : ");
	for (i = 0; i < SIZE; i++)
		printf("%d ", a[i]);

	printf("\nInput an integer that you want to find: ");
	scanf("%d", &target);

	i = seqSearch(a, SIZE, target);

	if (i == -1)
	{
		printf("Not Found\n");
	}
	else
	{
		printf("The index of %d is %d\n", target, i);
	}
	return 0;
}

int seqSearch(int a[], int size, int target)
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (a[i] == target)
			return i;
		else
			continue;
	}
	return -1;
}