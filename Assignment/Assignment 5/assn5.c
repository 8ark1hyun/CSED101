#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct //����ü STATION ����
{
	char name[21]; //���� �迭
	int posX; //��ǥ X
	int posY; //��ǥ Y
} STATION;

typedef struct node //����ü NODE ����
{
	STATION data; //����
	struct node* next; //���� ����Ʈ ������
}NODE;

typedef struct
{
	int count; //��� ����
	NODE* head; //��� ������
	NODE* tail; //���� ������
}LIST;

int load_station_list(LIST* plist); //����� ���� �Լ�(������ �а� �� ���� �б�)
void print_station_list(LIST* plist); //����� ���� �Լ�(�� ���� ���)
void print_one_station_list(LIST* plist, STATION s, int no); //����� ���� �Լ�(���� �� ���� ���)
void insert_node(LIST* plist); //����� ���� �Լ�(�� ��� ����)
int add_station(STATION* p, LIST* plist); //����� ���� �Լ�(���ο� �� ���� �߰�)
void delete_station(LIST* plist); //����� ���� �Լ�(Ư�� �� ����)
void move_station(LIST* plist); //����� ���� �Լ�(Ư�� �� ���� ����)
void save_station_list(LIST* plist); //����� ���� �Լ�(�� ���� ����)

int main()
{
	char command[20]; //��ɾ� �迭
	LIST station; //�� ����Ʈ

	station.count = 0; //�� ���� 0���� �ʱ�ȭ
	station.head = NULL; //�� ��� ���� NULL
	station.tail = NULL; //�� ���� ���� NULL

	while (1)
	{
		if ((load_station_list(&station)) == -1) //�� ���� �ҷ�����
		{
			continue;
		}
		print_station_list(&station); //�� ���� ���

		while (1) //������ ������ �ݺ�
		{
			printf("��ɾ �Է����ּ���. >> "); //��ɾ� �Է� ���� ���
			scanf("%s", command); //��ɾ� �Է�
			if (strcmp(command, "show") == 0) //��ɾ "show"�̸�
			{
				print_station_list(&station); //�� ���� ���
				continue; //ó������ �ݺ�
			}
			else if (strcmp(command, "add") == 0) //��ɾ "add"�̸�
			{
				insert_node(&station); //��� ����
				continue; //ó������ �ݺ�
			}
			else if (strcmp(command, "delete") == 0) //��ɾ "delete"�̸�
			{
				delete_station(&station); //Ư�� �� ���� ����
				continue; //ó������ �ݺ�
			}
			else if (strcmp(command, "move") == 0) //��ɾ "move"�̸�
			{
				move_station(&station); //Ư�� �� ���� ����
				continue; //ó������ �ݺ�
			}
			else if (strcmp(command, "quit") == 0) //��ɾ "quit"�̸�
			{
				save_station_list(&station); //�� ���� ����
				break; //����
			}
			else //��ȿ���� ���� ��ɾ �Է¹����� 
			{
				printf("\n[Error #2] ��ȿ���� ���� ��ɾ��Դϴ�.\n\n"); //�����޽��� ���
				continue; //ó������ �ݺ�
			}
		}

		return 0; //���α׷� ����
	}

}

int load_station_list(LIST* plist) //����� ���� �Լ�(������ �а� �� ���� �б�)
{
	char in_filename[21]; //�ҷ��� ���� �迭
	FILE* fp;

	printf("������ �� ����Ʈ�� ������ ���� �̸��� �Է����ּ���. >> "); //�ҷ��� ���� �̸� �Է� ���� ���
	scanf("%s", in_filename); //�ҷ��� ���� �̸� �Է�

	if (!(fp = fopen(in_filename, "r"))) //�б� ���� ������ ���� �� ������ �������� ������
	{
		printf("\n[Error #1] ���� �̸��� ��ȿ���� �ʽ��ϴ�.\n\n"); //�����޽��� ���
		return -1;
	}
	else
	{
		while (1)
		{
			NODE* temp = (NODE*)malloc(sizeof(NODE)); //�� ��� ����
			temp->next = NULL;
			if ((fscanf(fp, "%s %d %d", &temp->data.name, &temp->data.posX, &temp->data.posY)) != EOF) //������ ���� �ƴϸ�
			{
				if (plist->head == NULL) //��尡 NULL�̸�
				{
					plist->head = temp; //��忡 �� ��� ����
				}
				else //�׷��� ������
				{
					plist->tail->next = temp; //���� ������ �� ��� ����
				}
				plist->tail = temp; //�� ��带 ���Ϸ� ����
				plist->count++; //��� ���� +1
			}
			else //������ ���̸�
			{
				break; //�ݺ� ����
			}
		}
	}

	return 0;
}

void print_station_list(LIST* plist) //����� ���� �Լ�(�� ���� ���)
{
	NODE* temp;
	int i = 0;

	if (plist->head == NULL) //��尡 NULL�̸�
	{
		printf("\n[Error #3] �� ����Ʈ�� ��� �ֽ��ϴ�.\n\n"); //�����޽��� ���
		return;
	}

	printf("\n========================================================\n");
	printf("  ��ȣ        ����                           ��ġ(��ǥ)  \n");
	printf("--------------------------------------------------------\n");
	for (temp = plist->head; temp != NULL; temp = temp->next) //������ ���ϱ��� �ݺ�
	{
		i++;
		print_one_station_list(plist, temp->data, i); //���� �� ���� ���
	}
	printf("========================================================\n");
	printf("[total: %d stations]\n\n", i); //�� �� ���� ���
}

void print_one_station_list(LIST* plist, STATION s, int no) //����� ���� �Լ�(���� �� ���� ���)
{
	if (no == 1) //ù ��° ���̸�
	{
		printf("  %2d [����]   %-21s           (%d, %d)   \n", no, s.name, s.posX, s.posY);
	}
	else if (no == plist->count) //������ ���̸�
	{
		printf("  %2d [����]   %-21s           (%d, %d)   \n", no, s.name, s.posX, s.posY);
	}
	else //�߰� ���̸�
	{
		printf("  %2d          %-21s           (%d, %d)   \n", no, s.name, s.posX, s.posY);
	}

	return;
}

void insert_node(LIST* plist) //����� ���� �Լ�(�� ��� ����)
{
	int a;
	NODE* n;

	NODE* temp = (NODE*)malloc(sizeof(NODE)); //�� ��� ����
	temp->next = NULL;
	a = add_station(&temp->data, plist); //���ο� �� ���� �߰�

	if (a == -1) //��ȯ���� '-1'�̸�
	{
		return;
	}

	if (a == 1) //��ȯ���� '1'�̸�
	{
		temp->next = plist->head; //�� ��� ������ ���� ����
		plist->head = temp; //�� ��� ������ ���� ����
	}
	else
	{
		n = plist->head; //n�� ��带 ����Ŵ
		for (int i = 0; i < a - 2; i++) //�Է¹��� ��ġ���� �ݺ�
		{
			n = n->next; //n�� n ���� ��带 ����Ŵ
		}
		temp->next = n->next; //�� ��� ������ �Է¹��� ��ġ ���� ���� ����
		n->next = temp; //�Է¹��� ��ġ �� ��带 �� ���� ����
	}
	plist->count++; //�� �� ���� +1

	return;
}

int add_station(STATION* p, LIST* plist) //����� ���� �Լ�(���ο� �� ���� �߰�)
{
	int a = 0;
	int error = 0;
	int x = 0;
	int y = 0;

	printf("\n+ �� ��°�� �� ������ �߰��ұ��? >> "); //�� ��ġ �Է� ���� ���
	scanf("%d", &a); //�� ��ġ �Է�
	printf("+ �߰��� �� ������ ������ �Է����ּ���. >> "); //���� �Է� ���� ���
	scanf("%s", p->name); //���� �Է�
	printf("+ �߰��� �� ������ ��ġ ���� x ��ǥ�� �Է����ּ���. >> "); //�� X��ǥ �Է� ���� ���
	scanf("%d", &p->posX); //�� X��ǥ �Է�
	printf("+ �߰��� �� ������ ��ġ ���� y ��ǥ�� �Է����ּ���. >> "); //�� Y��ǥ �Է� ���� ���
	scanf("%d", &p->posY); //�� Y��ǥ �Է�
	printf("\n");

	if (a < 1 || a > plist->count + 1) //���� ���� ���� �Է¹�����
	{
		error = 1; //������ = '1'
	}

	for (NODE* temp = plist->head; temp != NULL; temp = temp->next) //������ ���ϱ��� �ݺ�
	{
		if (strcmp(p->name, temp->data.name) == 0) //�Է¹��� ������ �̹� �����ϸ�
		{
			if (error == 1) //�������� '1'�̸�
			{
				error = 3; //������ = '3'
			}
			else //�������� '0'�̸�
			{
				error = 2; //������ = '2'
			}
		}

		x = p->posX - temp->data.posX; //�� �� X��ǥ ���� ��
		y = p->posY - temp->data.posY; //�� �� Y��ǥ ���� ��
		if (((p->posX == temp->data.posX) && (p->posY == temp->data.posY)) || sqrt(pow(x, 2) + pow(y, 2)) < 3) //�̹� �����ϴ� �� ��ġ�̰ų� �� ������ �Ÿ��� 3 �̸��̸�
		{
			if (error == 1 || error == 3) //�������� '1'�̰ų� '3'�̸�
			{
				error = 3; //������ = '3'
			}
			else if (error == 0 || error == 2) // �������� '0'�̰ų� '2'�̸�
			{
				error = 2; //������ = '2'
			}
		}
	}

	if (error == 0) //�������� '0'�̸�
	{
		return a; //a ��ȯ(a = �� ��ġ)
	}
	else if (error == 1) //�������� '1'�̸�
	{
		printf("[Error #4] %d ��°�� ��ġ�� �߰��� �� �����ϴ�.\n\n", a); //�����޽��� ���
		return -1; //'-1' ��ȯ
	}
	else if (error == 2) //�������� '2'�̸�
	{
		printf("[Error #5] ��ȿ���� ���� �� �����Դϴ�.\n\n"); //�����޽��� ���
		return -1; //'-1' ��ȯ
	}
	else if (error == 3) //�������� '3'�̸�
	{
		printf("[Error #4] %d ��°�� ��ġ�� �߰��� �� �����ϴ�.\n", a); //�����޽��� ���
		printf("[Error #5] ��ȿ���� ���� �� �����Դϴ�.\n\n");
		return -1; //'-1' ��ȯ
	}
}

void delete_station(LIST* plist) //����� ���� �Լ�(Ư�� �� ����)
{
	int a = 0;
	int error = 0;
	NODE* n;
	NODE* m;

	printf("\n+ �� ��°�� �� ������ �����ұ��? >> "); //������ �� ��ȣ �Է� ���� ���
	scanf("%d", &a); //������ �� ��ȣ �Է�

	if (a < 1 || a > plist->count) //���� ���� ���� �Է¹�����
	{
		error = 1; //������ = '1'
	}

	if (plist->head == NULL) //��尡 NULL�̸�
	{
		if (error == 1) //�������� '1'�̸�
		{
			error = 3; //������ = '3'
		}
		else //�������� '0'�̸�
		{
			error = 2; //������ = '2'
		}
	}

	if (error == 1) //�������� '1'�̸�
	{
		printf("\n[Error #6] %d ��°�� �� ������ �������� �ʽ��ϴ�.\n\n", a); //�����޽��� ���
		return;
	}
	else if (error == 2) //�������� '2'�̸�
	{
		printf("\n[Error #7] �� ����Ʈ�� ��� �ֽ��ϴ�.\n\n"); //�����޽��� ���
		return;
	}
	else if (error == 3) //�������� '3'�̸�
	{
		printf("\n[Error #6] %d ��°�� �� ������ �������� �ʽ��ϴ�.\n", a); //�����޽��� ���
		printf("[Error #7] �� ����Ʈ�� ��� �ֽ��ϴ�.\n\n");
		return;
	}

	if (a == 1) //������ �� ��ȣ�� '1'�̸�
	{
		m = plist->head; //m�� ��带 ����Ŵ
		plist->head = plist->head->next; //��� ������ ���� ����
	}
	else //�׷��� ������
	{
		n = plist->head; //n�� ��带 ����Ŵ
		for (int i = 0; i < a - 2; i++) //�Է¹��� ��ġ���� �ݺ�
		{
			n = n->next; //n�� n ���� ��带 ����Ŵ
		}
		m = n->next; //������ �� ��带 m�� ����
		n->next = n->next->next; //n ������ n ���� ���� ��带 ����Ŵ
	}
	free(m); //�����Ϸ��� �� ��� �����Ҵ�����
	plist->count--; //�� �� ���� -1
	printf("\n");

	return;
}

void move_station(LIST* plist) //����� ���� �Լ�(Ư�� �� ���� ����)
{
	int a = 0;
	int b = 0;
	NODE* n;
	NODE* m;
	NODE* o;

	printf("\n+ �� ��°�� �� ������ �̵��ұ��? >> "); //�̵���ų �� ��ȣ �Է� ���� ���
	scanf("%d", &a); //�̵���ų �� ��ȣ �Է�
	printf("+ %d ��° �� ������ �� ��°�� �̵��ұ��? >> ", a); //�̵���ų �� ��ġ �Է� ���� ���
	scanf("%d", &b); //�̵���ų �� ��ġ �Է�
	printf("\n");

	if (a < 1 || b < 1 || a > plist->count || b > plist->count) //���� ���� ���� �Է¹�����
	{
		printf("[Error #8] ��ȿ���� ���� �Է��Դϴ�.\n\n"); //�����޽��� ���
		return;
	}

	if (a == b)
	{
		return;
	}

	if (a == 1) //�̵���ų �� ��ȣ�� ù ��°��
	{
		n = plist->head; //n�� ��带 ����Ŵ
		m = plist->head; //m�� ��带 ����Ŵ
		for (int i = 0; i < b - 1; i++) //�Է¹��� ��ġ���� �ݺ�
		{
			n = n->next; //n�� ���� ��带 ����Ŵ
		}
		plist->head = m->next; //��� ���� ���� ���� ����
		m->next = n->next; //ù ��° �� ���� �̵���ų �� ��ġ ���� ��� ����
		n->next = m; //�̵���ų �� ��ġ �� ���� �̵���ų �� ��� ����
	}
	else if (b == 1) //�̵���ų �� ��ġ�� ù ��°��
	{
		n = plist->head; //n�� ��带 ����Ŵ
		for (int i = 0; i < a - 2; i++) //�Է¹��� ��ġ���� �ݺ�
		{
			n = n->next; //n�� ���� ��带 ����Ŵ
		}
		m = n->next; //m�� �̵���ų �� ��� ����
		n->next = m->next; //�̵���ų �� �� ���� �̵���ų �� ���� ��� ����
		m->next = plist->head; //�̵���ų �� ���� ��� ��� ����
		plist->head = m; //�̵���Ų �� ��带 ���� ����

	}
	else
	{
		n = plist->head;
		m = plist->head;
		o = plist->head;
		for (int i = 0; i < a - 1; i++) //�Է¹��� ��ġ���� �ݺ�
		{
			n = n->next; //n�� n ���� ��带 ����Ŵ
		}
		if (a < b)
		{
			for (int i = 0; i < b - 1; i++) //�Է¹��� ��ġ���� �ݺ�(��쿡 ���� �ݺ� Ƚ�� �ٸ�)
			{
				m = m->next; //m�� m ���� ��带 ����Ŵ
			}
		}
		else if (a > b)
		{
			for (int i = 0; i < b - 2; i++) //�Է¹��� ��ġ���� �ݺ�(��쿡 ���� �ݺ� Ƚ�� �ٸ�)
			{
				m = m->next; //m�� m ���� ��带 ����Ŵ
			}
		}
		for (int i = 0; i < a - 2; i++) //�Է¹��� ��ġ���� �ݺ�
		{
			o = o->next; //o�� o ���� ��带 ����Ŵ
		}
		o->next = n->next; //��� ������ ���� ���� ����
		n->next = m->next;
		m->next = n;
	}

	return;
}

void save_station_list(LIST* plist) //����� ���� �Լ�(�� ���� ����)
{
	char out_filename[21]; //������ ���� �迭
	FILE* fp;
	NODE* temp;

	printf("\n+ ������ ���� �̸��� �Է����ּ���. >> "); //������ ���� �̸� �Է� ���� ���
	scanf("%s", out_filename); //������ ���� �̸� �Է�

	if (plist->head == NULL) //��尡 NULL�̸�
	{
		printf("\n[Error #9] �� ����Ʈ�� ������ ������ �����ϴ�.\n\n"); //�����޽��� ���
		return;
	}

	fp = fopen(out_filename, "w"); //���� ���� ���� ����

	for (temp = plist->head; temp != NULL; temp = temp->next) //������ ���ϱ��� �ݺ�
	{
		fprintf(fp, "%s %d %d", temp->data.name, temp->data.posX, temp->data.posY); //���Ͽ� �� ���� ���
		fprintf(fp, "\n");
	}

	while (plist->head) //��尡 NULL�� �ƴ� ������ �ݺ�
	{
		temp = plist->head; //��尡 ��带 ����Ŵ
		plist->head = plist->head->next; //��� ���� ��带 ���� ����
		plist->count--; //�� ���� �ʱ�ȭ
		free(temp); //��� �����Ҵ�����
	}

	printf("\n");

	return;
}