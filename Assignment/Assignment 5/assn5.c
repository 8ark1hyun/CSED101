#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct //구조체 STATION 선언
{
	char name[21]; //역명 배열
	int posX; //좌표 X
	int posY; //좌표 Y
} STATION;

typedef struct node //구조체 NODE 선언
{
	STATION data; //정보
	struct node* next; //다음 리스트 포인터
}NODE;

typedef struct
{
	int count; //노드 개수
	NODE* head; //헤드 포인터
	NODE* tail; //테일 포인터
}LIST;

int load_station_list(LIST* plist); //사용자 정의 함수(파일을 읽고 역 정보 읽기)
void print_station_list(LIST* plist); //사용자 정의 함수(역 정보 출력)
void print_one_station_list(LIST* plist, STATION s, int no); //사용자 정의 함수(개별 역 정보 출력)
void insert_node(LIST* plist); //사용자 정의 함수(새 노드 생성)
int add_station(STATION* p, LIST* plist); //사용자 정의 함수(새로운 역 정보 추가)
void delete_station(LIST* plist); //사용자 정의 함수(특정 역 삭제)
void move_station(LIST* plist); //사용자 정의 함수(특정 역 순서 변경)
void save_station_list(LIST* plist); //사용자 정의 함수(역 정보 저장)

int main()
{
	char command[20]; //명령어 배열
	LIST station; //역 리스트

	station.count = 0; //역 개수 0으로 초기화
	station.head = NULL; //역 헤드 정보 NULL
	station.tail = NULL; //역 테일 정보 NULL

	while (1)
	{
		if ((load_station_list(&station)) == -1) //역 정보 불러오기
		{
			continue;
		}
		print_station_list(&station); //역 정보 출력

		while (1) //종료할 때까지 반복
		{
			printf("명령어를 입력해주세요. >> "); //명령어 입력 문구 출력
			scanf("%s", command); //명령어 입력
			if (strcmp(command, "show") == 0) //명령어가 "show"이면
			{
				print_station_list(&station); //역 정보 출력
				continue; //처음부터 반복
			}
			else if (strcmp(command, "add") == 0) //명령어가 "add"이면
			{
				insert_node(&station); //노드 생성
				continue; //처음부터 반복
			}
			else if (strcmp(command, "delete") == 0) //명령어가 "delete"이면
			{
				delete_station(&station); //특정 역 정보 삭제
				continue; //처음부터 반복
			}
			else if (strcmp(command, "move") == 0) //명령어가 "move"이면
			{
				move_station(&station); //특정 역 순서 변경
				continue; //처음부터 반복
			}
			else if (strcmp(command, "quit") == 0) //명령어가 "quit"이면
			{
				save_station_list(&station); //역 정보 저장
				break; //종료
			}
			else //유효하지 않은 명령어를 입력받으면 
			{
				printf("\n[Error #2] 유효하지 않은 명령어입니다.\n\n"); //에러메시지 출력
				continue; //처음부터 반복
			}
		}

		return 0; //프로그램 종료
	}

}

int load_station_list(LIST* plist) //사용자 정의 함수(파일을 읽고 역 정보 읽기)
{
	char in_filename[21]; //불러올 파일 배열
	FILE* fp;

	printf("기존의 역 리스트를 저장한 파일 이름을 입력해주세요. >> "); //불러올 파일 이름 입력 문구 출력
	scanf("%s", in_filename); //불러올 파일 이름 입력

	if (!(fp = fopen(in_filename, "r"))) //읽기 모드로 파일을 읽은 후 파일이 존재하지 않으면
	{
		printf("\n[Error #1] 파일 이름이 유효하지 않습니다.\n\n"); //에러메시지 출력
		return -1;
	}
	else
	{
		while (1)
		{
			NODE* temp = (NODE*)malloc(sizeof(NODE)); //새 노드 생성
			temp->next = NULL;
			if ((fscanf(fp, "%s %d %d", &temp->data.name, &temp->data.posX, &temp->data.posY)) != EOF) //파일의 끝이 아니면
			{
				if (plist->head == NULL) //헤드가 NULL이면
				{
					plist->head = temp; //헤드에 새 노드 저장
				}
				else //그렇지 않으면
				{
					plist->tail->next = temp; //테일 다음에 새 노드 저장
				}
				plist->tail = temp; //새 노드를 테일로 지정
				plist->count++; //노드 개수 +1
			}
			else //파일의 끝이면
			{
				break; //반복 종료
			}
		}
	}

	return 0;
}

void print_station_list(LIST* plist) //사용자 정의 함수(역 정보 출력)
{
	NODE* temp;
	int i = 0;

	if (plist->head == NULL) //헤드가 NULL이면
	{
		printf("\n[Error #3] 역 리스트가 비어 있습니다.\n\n"); //에러메시지 출력
		return;
	}

	printf("\n========================================================\n");
	printf("  번호        역명                           위치(좌표)  \n");
	printf("--------------------------------------------------------\n");
	for (temp = plist->head; temp != NULL; temp = temp->next) //헤드부터 테일까지 반복
	{
		i++;
		print_one_station_list(plist, temp->data, i); //개별 역 정보 출력
	}
	printf("========================================================\n");
	printf("[total: %d stations]\n\n", i); //역 총 개수 출력
}

void print_one_station_list(LIST* plist, STATION s, int no) //사용자 정의 함수(개별 역 정보 출력)
{
	if (no == 1) //첫 번째 역이면
	{
		printf("  %2d [기점]   %-21s           (%d, %d)   \n", no, s.name, s.posX, s.posY);
	}
	else if (no == plist->count) //마지막 역이면
	{
		printf("  %2d [종점]   %-21s           (%d, %d)   \n", no, s.name, s.posX, s.posY);
	}
	else //중간 역이면
	{
		printf("  %2d          %-21s           (%d, %d)   \n", no, s.name, s.posX, s.posY);
	}

	return;
}

void insert_node(LIST* plist) //사용자 정의 함수(새 노드 생성)
{
	int a;
	NODE* n;

	NODE* temp = (NODE*)malloc(sizeof(NODE)); //새 노드 생성
	temp->next = NULL;
	a = add_station(&temp->data, plist); //새로운 역 정보 추가

	if (a == -1) //반환값이 '-1'이면
	{
		return;
	}

	if (a == 1) //반환값이 '1'이면
	{
		temp->next = plist->head; //새 노드 다음을 헤드와 연결
		plist->head = temp; //새 노드 다음을 헤드로 지정
	}
	else
	{
		n = plist->head; //n이 헤드를 가리킴
		for (int i = 0; i < a - 2; i++) //입력받은 위치까지 반복
		{
			n = n->next; //n이 n 다음 노드를 가리킴
		}
		temp->next = n->next; //새 노드 다음을 입력받은 위치 다음 노드와 연결
		n->next = temp; //입력받은 위치 전 노드를 새 노드와 연결
	}
	plist->count++; //역 총 개수 +1

	return;
}

int add_station(STATION* p, LIST* plist) //사용자 정의 함수(새로운 역 정보 추가)
{
	int a = 0;
	int error = 0;
	int x = 0;
	int y = 0;

	printf("\n+ 몇 번째의 역 정보로 추가할까요? >> "); //역 위치 입력 문구 출력
	scanf("%d", &a); //역 위치 입력
	printf("+ 추가할 역 정보의 역명을 입력해주세요. >> "); //역명 입력 문구 출력
	scanf("%s", p->name); //역명 입력
	printf("+ 추가할 역 정보의 위치 정보 x 좌표를 입력해주세요. >> "); //역 X좌표 입력 문구 출력
	scanf("%d", &p->posX); //역 X좌표 입력
	printf("+ 추가할 역 정보의 위치 정보 y 좌표를 입력해주세요. >> "); //역 Y좌표 입력 문구 출력
	scanf("%d", &p->posY); //역 Y좌표 입력
	printf("\n");

	if (a < 1 || a > plist->count + 1) //범위 밖의 수를 입력받으면
	{
		error = 1; //에러값 = '1'
	}

	for (NODE* temp = plist->head; temp != NULL; temp = temp->next) //헤드부터 테일까지 반복
	{
		if (strcmp(p->name, temp->data.name) == 0) //입력받은 역명이 이미 존재하면
		{
			if (error == 1) //에러값이 '1'이면
			{
				error = 3; //에러값 = '3'
			}
			else //에러값이 '0'이면
			{
				error = 2; //에러값 = '2'
			}
		}

		x = p->posX - temp->data.posX; //역 간 X좌표 차이 값
		y = p->posY - temp->data.posY; //역 간 Y좌표 차이 값
		if (((p->posX == temp->data.posX) && (p->posY == temp->data.posY)) || sqrt(pow(x, 2) + pow(y, 2)) < 3) //이미 존재하는 역 위치이거나 각 역과의 거리가 3 미만이면
		{
			if (error == 1 || error == 3) //에러값이 '1'이거나 '3'이면
			{
				error = 3; //에러값 = '3'
			}
			else if (error == 0 || error == 2) // 에러값이 '0'이거나 '2'이면
			{
				error = 2; //에러값 = '2'
			}
		}
	}

	if (error == 0) //에러값이 '0'이면
	{
		return a; //a 반환(a = 역 위치)
	}
	else if (error == 1) //에러값이 '1'이면
	{
		printf("[Error #4] %d 번째의 위치에 추가할 수 없습니다.\n\n", a); //에러메시지 출력
		return -1; //'-1' 반환
	}
	else if (error == 2) //에러값이 '2'이면
	{
		printf("[Error #5] 유효하지 않은 역 정보입니다.\n\n"); //에러메시지 출력
		return -1; //'-1' 반환
	}
	else if (error == 3) //에러값이 '3'이면
	{
		printf("[Error #4] %d 번째의 위치에 추가할 수 없습니다.\n", a); //에러메시지 출력
		printf("[Error #5] 유효하지 않은 역 정보입니다.\n\n");
		return -1; //'-1' 반환
	}
}

void delete_station(LIST* plist) //사용자 정의 함수(특정 역 삭제)
{
	int a = 0;
	int error = 0;
	NODE* n;
	NODE* m;

	printf("\n+ 몇 번째의 역 정보를 삭제할까요? >> "); //삭제할 역 번호 입력 문구 출력
	scanf("%d", &a); //삭제할 역 번호 입력

	if (a < 1 || a > plist->count) //범위 밖의 수를 입력받으면
	{
		error = 1; //에러값 = '1'
	}

	if (plist->head == NULL) //헤드가 NULL이면
	{
		if (error == 1) //에러값이 '1'이면
		{
			error = 3; //에러값 = '3'
		}
		else //에러값이 '0'이면
		{
			error = 2; //에러값 = '2'
		}
	}

	if (error == 1) //에러값이 '1'이면
	{
		printf("\n[Error #6] %d 번째의 역 정보는 존재하지 않습니다.\n\n", a); //에러메시지 출력
		return;
	}
	else if (error == 2) //에러값이 '2'이면
	{
		printf("\n[Error #7] 역 리스트가 비어 있습니다.\n\n"); //에러메시지 출력
		return;
	}
	else if (error == 3) //에러값이 '3'이면
	{
		printf("\n[Error #6] %d 번째의 역 정보는 존재하지 않습니다.\n", a); //에러메시지 출력
		printf("[Error #7] 역 리스트가 비어 있습니다.\n\n");
		return;
	}

	if (a == 1) //삭제할 역 번호가 '1'이면
	{
		m = plist->head; //m이 헤드를 가리킴
		plist->head = plist->head->next; //헤드 다음을 헤드로 지정
	}
	else //그렇지 않으면
	{
		n = plist->head; //n이 헤드를 가리킴
		for (int i = 0; i < a - 2; i++) //입력받은 위치까지 반복
		{
			n = n->next; //n이 n 다음 노드를 가리킴
		}
		m = n->next; //삭제할 역 노드를 m에 저장
		n->next = n->next->next; //n 다음이 n 다음 다음 노드를 가리킴
	}
	free(m); //삭제하려는 역 노드 동적할당해제
	plist->count--; //역 총 개수 -1
	printf("\n");

	return;
}

void move_station(LIST* plist) //사용자 정의 함수(특정 역 순서 변경)
{
	int a = 0;
	int b = 0;
	NODE* n;
	NODE* m;
	NODE* o;

	printf("\n+ 몇 번째의 역 정보를 이동할까요? >> "); //이동시킬 역 번호 입력 문구 출력
	scanf("%d", &a); //이동시킬 역 번호 입력
	printf("+ %d 번째 역 정보를 몇 번째로 이동할까요? >> ", a); //이동시킬 역 위치 입력 문구 출력
	scanf("%d", &b); //이동시킬 역 위치 입력
	printf("\n");

	if (a < 1 || b < 1 || a > plist->count || b > plist->count) //범위 밖의 수를 입력받으면
	{
		printf("[Error #8] 유효하지 않은 입력입니다.\n\n"); //에러메시지 출력
		return;
	}

	if (a == b)
	{
		return;
	}

	if (a == 1) //이동시킬 역 번호가 첫 번째면
	{
		n = plist->head; //n이 헤드를 가리킴
		m = plist->head; //m이 헤드를 가리킴
		for (int i = 0; i < b - 1; i++) //입력받은 위치까지 반복
		{
			n = n->next; //n이 다음 노드를 가리킴
		}
		plist->head = m->next; //헤드 다음 노드로 헤드로 지정
		m->next = n->next; //첫 번째 역 노드와 이동시킬 역 위치 다음 노드 연결
		n->next = m; //이동시킬 역 위치 전 노드와 이동시킬 역 노드 연결
	}
	else if (b == 1) //이동시킬 역 위치가 첫 번째면
	{
		n = plist->head; //n이 헤드를 가리킴
		for (int i = 0; i < a - 2; i++) //입력받은 위치까지 반복
		{
			n = n->next; //n이 다음 노드를 가리킴
		}
		m = n->next; //m에 이동시킬 역 노드 저장
		n->next = m->next; //이동시킬 역 전 노드와 이동시킬 역 다음 노드 연결
		m->next = plist->head; //이동시킬 역 노드와 헤드 노드 연결
		plist->head = m; //이동시킨 역 노드를 헤드로 지정

	}
	else
	{
		n = plist->head;
		m = plist->head;
		o = plist->head;
		for (int i = 0; i < a - 1; i++) //입력받은 위치까지 반복
		{
			n = n->next; //n이 n 다음 노드를 가리킴
		}
		if (a < b)
		{
			for (int i = 0; i < b - 1; i++) //입력받은 위치까지 반복(경우에 따라 반복 횟수 다름)
			{
				m = m->next; //m이 m 다음 노드를 가리킴
			}
		}
		else if (a > b)
		{
			for (int i = 0; i < b - 2; i++) //입력받은 위치까지 반복(경우에 따라 반복 횟수 다름)
			{
				m = m->next; //m이 m 다음 노드를 가리킴
			}
		}
		for (int i = 0; i < a - 2; i++) //입력받은 위치까지 반복
		{
			o = o->next; //o가 o 다음 노드를 가리킴
		}
		o->next = n->next; //노드 연결을 통해 순서 변경
		n->next = m->next;
		m->next = n;
	}

	return;
}

void save_station_list(LIST* plist) //사용자 정의 함수(역 정보 저장)
{
	char out_filename[21]; //저장할 파일 배열
	FILE* fp;
	NODE* temp;

	printf("\n+ 저장할 파일 이름을 입력해주세요. >> "); //저장할 파일 이름 입력 문구 출력
	scanf("%s", out_filename); //저장할 파일 이름 입력

	if (plist->head == NULL) //헤드가 NULL이면
	{
		printf("\n[Error #9] 역 리스트에 저장할 정보가 없습니다.\n\n"); //에러메시지 출력
		return;
	}

	fp = fopen(out_filename, "w"); //쓰기 모드로 파일 열기

	for (temp = plist->head; temp != NULL; temp = temp->next) //헤드부터 테일까지 반복
	{
		fprintf(fp, "%s %d %d", temp->data.name, temp->data.posX, temp->data.posY); //파일에 역 정보 출력
		fprintf(fp, "\n");
	}

	while (plist->head) //헤드가 NULL이 아닐 때까지 반복
	{
		temp = plist->head; //노드가 헤드를 가리킴
		plist->head = plist->head->next; //헤드 다음 노드를 헤드로 지정
		plist->count--; //역 개수 초기화
		free(temp); //노드 동적할당해제
	}

	printf("\n");

	return;
}