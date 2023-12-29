#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int add(int x, int y);
float average(int x, int y);
void printResults(int x, int y, int sum, float avg);

int main(void)
{
	int x, y, sum;
	float avg;

	printf("Enter two integers: ");
	scanf("%d %d", &x, &y);

	sum = add(x, y);
	avg = average(x, y);
	printResults(x, y, sum, avg);

	return 0;
}

int add(int x, int y)
{
	return x + y;
}

float average(int x, int y)
{
	return (float) (x + y) / 2;
}

void printResults(int x, int y, int sum, float avg)
{
	return printf("The sum of %d and %d is %d\nThe average of numbers is %.1f\n", x, y, sum, avg);
}