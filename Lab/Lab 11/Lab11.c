#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct
{
	char name[20];
	int exam[2];
	float avg;
	char grade;
}STUDENT;

void print_one_student(STUDENT s, int no);
void print_students(STUDENT slist[], int n);
void add_student(STUDENT* p);

int main()
{
	STUDENT slist[10];
	char command[20];
	int idx = 0;
	char name[20];

	while (1)
	{
		printf("\n>> ");
		scanf("%s", command);

		if (strcmp(command, "add") == 0)
		{
			add_student(&slist[idx]);
			idx++;
		}
		else if (strcmp(command, "print") == 0)
		{
			print_students(slist, idx);
		}
		else if (strcmp(command, "find") == 0)
		{
			printf("이름: ");
			scanf("%s", name);
			printf("번호  이름                 중간  기말  평균  (학점)\n");
			for (int a = 1; a <= idx; a++)
			{
				if (strcmp(&slist[a-1], name) == 0)
				{
					print_one_student(slist[a-1], a);
				}
			}
		}
		else if (strcmp(command, "quit") == 0)
		{
			break;
		}
	}

	return 0;
}

void print_one_student(STUDENT s, int no)
{
	s.avg = ((float)s.exam[0] + (float)s.exam[1]) / (float)2;
	if (s.avg >= 90)
	{
		s.grade = 'A';
	}
	else if (s.avg < 90 && s.avg >= 80)
	{
		s.grade = 'B';
	}
	else if (s.avg < 80 && s.avg >= 70)
	{
		s.grade = 'C';
	}
	else if (s.avg < 70 && s.avg >= 60)
	{
		s.grade = 'D';
	}
	else if (s.avg < 60)
	{
		s.grade = 'F';
	}
	printf(" %d    %-20s %3d   %3d   %3.1f   (%c)\n", no, s.name, s.exam[0], s.exam[1], s.avg, s.grade);
}

void print_students(STUDENT slist[], int n)
{
	int i;
	printf("번호  이름                 중간  기말  평균  (학점)\n");
	for (i = 0; i < n; i++)
	{
		print_one_student(slist[i], i+1);
	}
}

void add_student(STUDENT* p)
{
	printf("이름: ");
	scanf("%s", p->name);
	printf("중간고사: ");
	scanf("%d", &p->exam[0]);
	printf("기말고사: ");
	scanf("%d", &p->exam[1]);
}