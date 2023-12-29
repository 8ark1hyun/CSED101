#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

float calc_average(int mid, int fin);
char calc_grade(float avg);

int main(void)
{
	int mid, fin;
	float avg;
	char grade;

	printf("Enter your midterm score: ");
	scanf("%d", &mid);

	printf("Enter your final score: ");
	scanf("%d", &fin);

	avg = calc_average(mid, fin);
	grade = calc_grade(avg);

	printf("Average: %.1f\n", avg);
	printf("Grade: %c\n", grade);
	
	return 0;
}

float calc_average(int mid, int fin)
{
	return (float)(mid + fin) / 2;
}

char calc_grade(float avg)
{
	if (avg >= 90)
	{
		return 65;
	}
	else if (avg < 90 && avg >= 80)
	{
		return 66;
	}
	else if (avg < 80 && avg >= 70)
	{
		return 67;
	}
	else if (avg < 70 && avg >= 60)
	{
		return 68;
	}
	else if (avg < 60)
	{
		return 70;
	}
}