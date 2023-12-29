#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

float calc_average(int mid, int fin);
char calc_grade(float avg);

int main()
{
	int sid, mid, fin;
	int stu_num = 0;
	float avg;
	float all_score = 0;
	float all_avg;
	char grade;

	FILE* infile, *outfile;

	infile = fopen("score.txt", "r");
	if (infile == NULL)
	{
		printf("could not open input file\n");
		return 0;
	}
	outfile = fopen("report.txt", "w");
	if (outfile == NULL)
	{
		printf("could not open output file\n");
		return 0;
	}
	
	fprintf(outfile, "=========================\n");
	fprintf(outfile, " ÇÐ¹ø          ÃÑÁ¡(ÇÐÁ¡)\n");
	fprintf(outfile, "=========================\n");
	while (fscanf(infile, "%d %d %d", &sid, &mid, &fin) != EOF)
	{
		avg = calc_average(mid, fin);
		grade = calc_grade(avg);
		fprintf(outfile, "%d         %.1f (%c)\n", sid, avg, grade);
		stu_num++;
		all_score = all_score + avg;
	}
	all_avg = all_score/stu_num;
	fprintf(outfile, "=========================\n");
	fprintf(outfile, " Æò±Õ            %.1f\n", all_avg);
	fprintf(outfile, "=========================\n");
	fclose(outfile);
	fclose(infile);

	return 0;
}

float calc_average(int mid, int fin)
{
	return (float)(mid * 0.4) + (fin * 0.6);
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