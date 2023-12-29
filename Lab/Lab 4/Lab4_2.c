#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void randData(int* a, int* b, int* c);
float arithmeticMean(int a, int b);
float geometricMean(int a, int b);
float harmonicMean(int a, int b);


int main(void)
{
	int A1, A2, A3;
	int B1, B2, B3;
	float ari, geo, har;

	srand(time(NULL));

	randData(&A1, &A2, &A3);
	randData(&B1, &B2, &B3);

	ari = arithmeticMean(A1, B1);
	geo = geometricMean(A2, B2);
	har = harmonicMean(A3, B3);

	printf("arithmeticMean(%d, %d) => %.2f\n", A1, B1, ari);
	printf(" geometricMean(%d, %d) => %.2f\n", A2, B2, geo);
	printf("  harmonicMean(%d, %d) => %.2f\n", A3, B3, har);

	return 0;
}

void randData(int* a, int* b, int* c)
{
	*a = rand()%76+5;
	*b = rand()%76+5;
	*c = rand()%76+5;
}	

float arithmeticMean(int a, int b)
{
	return (a + b) / (float)2;
}
float geometricMean(int a, int b)
{
	return sqrt(a * b);
}
float harmonicMean(int a, int b)
{
	return (float)2 * a * b / (a + b);
}