#include <stdio.h>

int main(void)
{
	int i, dan;

	for (i = 1; i <= 9; i++)
	{
		for (dan = 2; dan <= 9; dan++)
		{
			printf("%d * %d = %2d  ", dan, i, dan * i);
		}
		printf("\n");
	}

	return 0;
}