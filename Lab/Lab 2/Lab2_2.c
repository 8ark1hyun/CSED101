#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	double r, pi;
	pi = 3.141592;

	printf("�������� �Է��Ͻÿ�: ");
	scanf("%lf", &r);

	printf("�� �ѷ�: %lf\n", 2 * pi * r);
	printf("�� ����: %lf\n", pi * r * r);
	
	return 0;
}