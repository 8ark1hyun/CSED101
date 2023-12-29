#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 20

void print_matrix(int ary[][MAX_SIZE], int size);

int main()
{
	int a[MAX_SIZE][MAX_SIZE];
	int size;
	int r, c;

	printf("Enter the size of square: ");
	scanf("%d", &size);
	
	for (r = 0; r < size; r++)
	{
		for (c = 0; c < size - r - 1; c++)
		{
			a[r][c] = 1;
		}
		a[r][c] = 0;
		for (c = size - r; c < size; c++)
		{
			a[r][c] = -1;
		}
	}
	
	print_matrix(a, size);

	return 0;
}

void print_matrix(int ary[][MAX_SIZE], int size)
{
	int r, c;

	for (r = 0; r < size; r++)
	{
		for (c = 0; c < size; c++)
		{
			printf("%2d ", ary[r][c]);
		}
		printf("\n");
	}
}