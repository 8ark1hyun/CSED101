#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int number;
	int sum = 0;

	printf("Enter a number: ");
	scanf("%d", &number);

	while (1)
	{
		while (number > 0)
		{
			sum = sum + (number % 10);
			number = number / 10;
		}
		
		printf("The sum of the digits is %d\n", sum);
		break;
	}

	return 0;
}