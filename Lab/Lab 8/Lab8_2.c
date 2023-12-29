#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 6

void bubble_sort(int a[], int size);
void swap(int* x, int* y);
void print_array(int a[], int size);
void input_array(int a[], int size);

int main()
{
	int ary[MAX];

	printf("Input integer numbers to be sorted: ");
	input_array(ary, MAX);

	printf(" Unsorted: ");
	print_array(ary, MAX);

	printf("----------------------------\n");
	bubble_sort(ary, MAX);
	printf("----------------------------\n");

	printf("   Sorted: ");
	print_array(ary, MAX);

	return 0;
}

void bubble_sort(int a[], int size)
{
	int i,s;
	for (s = 1; s < size; s++)
	{
		for (i = size - 1; i >= 0; i--)
		{
			if (a[i - 1] > a[i])
			{
				swap(&a[i - 1], &a[i]);
			}
		}
		printf("[step %d]: ", s);
		print_array(a, size);
	}
}

void swap(int* x, int* y)
{
	int i;

	i = *x;
	*x = *y;
	*y = i;
}

void print_array(int a[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void input_array(int a[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		scanf("%d", &a[i]);
	}
}