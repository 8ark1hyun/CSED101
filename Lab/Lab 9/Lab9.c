#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void partial_print(int* arr_start, int size);
int partial_sum(int* arr_start, int* arr_end);

int main()
{
	int a[10];
	int start, end, sum;

	printf("Enter 10 elements of array: ");
	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &a[i]);
	}
	printf("Numbers that you enter are: ");
	partial_print(a, 10);
	printf("Enter the starting and ending index: ");
	scanf("%d %d", &start, &end);
	sum = partial_sum(&a[start], &a[end]);
	printf("\nSum from array[%d] to array[%d] is %d\n", start, end, sum);
	printf("Partial array output: ");
	partial_print(&a[start], end - start + 1);

	return 0;
}

void partial_print(int* arr_start, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", *(arr_start+i));
	}
	printf("\n");
}

int partial_sum(int* arr_start, int* arr_end)
{
	int sum = 0;

	for (int i = 0; i <= arr_end - arr_start; i++)
	{
		sum += *(arr_start+i);
	}

	return sum;
}