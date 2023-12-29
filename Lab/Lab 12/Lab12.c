#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	char name[20];
	int exam[2];
	float avg;
	char grade;
}STUDENT;

typedef struct node
{
	STUDENT data;
	struct node* next;
}NODE;

typedef struct
{
	int count;
	NODE* head;
	NODE* tail;
}LIST;

void insert_node(LIST* plist);
void print_list(LIST* plist);
void print_one_student(STUDENT s, int no);
void add_student(STUDENT* p);

int main()
{
	char command[20];
	char name[20];
	LIST slist;
	NODE* temp;

	slist.count = 0;
	slist.head = NULL;
	slist.tail = NULL;

	while (1)
	{
		printf("\n>> ");
		scanf("%s", command);

		if (strcmp(command, "add") == 0)
		{
			insert_node(&slist);
		}
		else if (strcmp(command, "print") == 0)
		{
			print_list(&slist);
		}
		else if (strcmp(command, "find") == 0)
		{
			printf("이름: ");
			scanf("%s", name);
			printf("번호  이름                 중간  기말  평균  (학점)\n");
			int i = 0;
			for (temp = slist.head; temp != NULL; temp = temp->next)
			{
				i++;
				if (strcmp(temp->data.name, name) == 0)
				{
					print_one_student(temp->data, i);
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

void insert_node(LIST* plist)
{
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->next = NULL;
	add_student(&temp->data);

	if (plist->head == NULL)
	{
		plist->head = temp;
	}
	else
	{
		plist->tail->next = temp;
	}
	plist->tail = temp;
	plist->count++;
}

void print_list(LIST* plist)
{
	NODE* temp;
	int i = 0;
	printf("번호  이름                 중간  기말  평균  (학점)\n");
	for (temp = plist->head; temp != NULL; temp = temp->next)
	{
		i++;
		print_one_student(temp->data, i);
	}
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

void add_student(STUDENT* p)
{
	printf("이름: ");
	scanf("%s", p->name);
	printf("중간고사: ");
	scanf("%d", &p->exam[0]);
	printf("기말고사: ");
	scanf("%d", &p->exam[1]);
}