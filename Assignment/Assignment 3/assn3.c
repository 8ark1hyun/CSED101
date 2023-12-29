#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

int make_board(int board[][MAX_SIZE], int* row, int* col); //사용자 정의 함수(파일을 읽고 게임판의 행과 열의 크기와 무늬 값 저장)
void print_board(int board[][MAX_SIZE], int row, int col); //사용자 정의 함수(게임판(2차원 배열)을 전달받아 게임판 출력)
int remove_tiles(int board[][MAX_SIZE], int row, int col); //사용자 정의 함수(타일을 제거하고, 제거된 무늬 존재 여부에 따라 적절한 상수를 반환하여 프로그램 종료에 사용)
void update_board(int board[][MAX_SIZE], int row, int col); //사용자 정의 함수(타일이 제거된 빈 칸에 위쪽의 무늬들을 순서대로 내려 채움)
int total_tiles_num(int board[][MAX_SIZE], int row, int col, int* total_tiles); //사용자 정의 함수(제거된 타일의 총 개수를 계산)
int write_tiles(int board[][MAX_SIZE], int row, int col, int total_tiles); //사용자 정의 함수(결과 화면을 파일에 출력)


int main()
{
	int board[MAX_SIZE][MAX_SIZE]; //게임판 2차원 배열
	int r = 0; //변수 r = 열
	int c = 0; //변수 c = 행
	int total_tiles = 0; //변수 total_tiles = 총 제거된 타일의 개수

	if ((make_board(board, &r, &c)) == -1) //파일을 읽고 오류가 발생하면(-1 값을 반환받으면)
	{
		return 0; //프로그램 종료
	}

	while (1) //게임이 종료될 때까지 반복
	{
		print_board(board, r, c); //게임판 출력
		if ((remove_tiles(board, r, c)) == -1) //더 이상 제거 가능한 타일이 없으면(-1 값을 반환받으면)
		{
			break; //게임 종료
		}
		getchar(); //화면 지우기
		system("cls"); //화면 지우기
		print_board(board, r, c); //타일 제거한 후의 게임판 출력
		update_board(board, r, c); //타일이 제거된 빈 칸에 위쪽의 무늬들을 순서대로 내려 채움
		getchar(); //화면 지우기
		system("cls"); //화면 지우기
	}
	total_tiles_num(board, r, c, &total_tiles); //제거된 타일의 총 개수를 계산
	printf("\n=========================\n");
	printf(" Total removed tiles: %d\n", total_tiles); //제거된 타일의 총 개수를 출력
	printf("=========================\n");
	write_tiles(board, r, c, total_tiles); //결과 화면을 파일에 출력

	return 0;
}

int make_board(int board[][MAX_SIZE], int* row, int* col) //사용자 정의 함수(파일을 읽고 게임판의 행과 열의 크기와 무늬 값 저장)
{
	FILE* infile;
	int tiles_num = 0; //변수 tiles_num = 총 타일의 개수
	int r = 0;
	int c = 0;

	if (!(infile = fopen("board.txt", "r"))) //읽기모드로 파일 열기 후 파일이 존재하지 않으면
	{
		printf("파일이 존재하지 않습니다!\n"); //오류메세지 출력
		return -1; //-1 값을 반환
	}
	fscanf(infile, "%d %d", col, row); //파일의 첫 줄에 행과 열의 크기를 입력
	for (r = 0; r < *row; r++) //열마다 반복
	{
		for (c = 0; c < *col; c++) //행마다 반복
		{
			if ((fscanf(infile, "%d", &board[r][c])) != EOF) //파일의 끝까지 타일의 무늬 값을 입력 받아 2차원 배열에 저장
			{
				tiles_num++; //총 타일의 개수 계산
				if (board[r][c] < 1 || board[r][c] > 8) //타일의 무늬 값이 올바르지 않으면
				{
					printf("타일의 숫자가 올바르지 않습니다!\n"); //오류메시지 출력
					return -1; //-1 값을 반환
				}
			}
		}
	}
	if ((fscanf(infile, "%d")) != EOF || tiles_num != *row * *col) //행과 열의 크기와 총 타일의 개수가 일치하지 않으면
	{
		printf("게임판 타일의 개수가 올바르지 않습니다!\n"); //오류메시지 출력
		return -1; //-1 값을 반환
	}
	return 0;
}

void print_board(int board[][MAX_SIZE], int row, int col) //사용자 정의 함수(게임판(2차원 배열)을 전달받아 게임판 출력)
{
	for (int r = 0; r < row; r++) //열마다 반복
	{
		for (int c = 0; c < col; c++) //행마다 반복
		{
			printf("%2d", board[r][c]); //2차원 배열에 저장된 타일의 무늬 값 출력
		}
		printf("\n");
	}
}

int remove_tiles(int board[][MAX_SIZE], int row, int col) //사용자 정의 함수(타일을 제거하고, 제거된 무늬 존재 여부에 따라 적절한 상수를 반환하여 프로그램 종료에 사용)
{
	int remove[MAX_SIZE][MAX_SIZE]; //제거할 타일의 위치를 저장하는 2차원 배열
	int i = 0; //변수 i = 제거할 타일의 개수

	for (int r = 0; r < row; r++) //열마다 반복
	{
		for (int c = 0; c < col; c++) //행마다 반복
		{
			if (board[r][c] == board[r][c + 1] && board[r][c] == board[r + 1][c] && board[r][c] == board[r + 1][c + 1] && board[r][c] != 0) //2X2 형태의 같은 무늬가 있다면
			{
				remove[r][c] = 1;
				remove[r + 1][c] = 1;
				remove[r][c + 1] = 1;
				remove[r + 1][c + 1] = 1; //remove 2차원 배열에 제거할 타일의 위치 값을 1로 저장
			}
		}
	}
	for (int r = 0; r < row; r++) //열마다 반복
	{
		for (int c = 0; c < col; c++) //행마다 반복
		{
			if (remove[r][c] == 1) //remove 2차원 배열의 값이 1이면
			{
				board[r][c] = 0; //게임판 2차원 배열의 값을 제거(0으로 저장)
				i++; //제거된 타일의 총 개수 계산
			}
		}
	}
	if (i == 0) //제거된 타일이 없으면
	{
		return -1; //-1 값을 반환
	}
}

void update_board(int board[][MAX_SIZE], int row, int col) //사용자 정의 함수(타일이 제거된 빈 칸에 위쪽의 무늬들을 순서대로 내려 채움)
{
	for (int c = 0; c < col; c++) //행마다 반복
	{
		int i = row - 1; //변수 i = 타일을 제거한 후 위쪽의 무늬를 채울 때 저장할 2차원 배열의 열
		int j = 0; //변수 j = 각 열의 제거된 타일의 개수
		for (int r = row - 1; r >= 0; r--) //열마다 반복(아래의 열부터 반복)
		{
			if (board[r][c] != 0) //게임판 타일의 값이 0이 아니면(제거된 타일이 아니면)
			{
				board[i][c] = board[r][c]; //타일의 값을 아래에서부터 차례로 저장
				i--; //타일의 값을 저장하면 열을 한칸씩 올림
			}
			else
			{
				j++; //각 열의 제거된 총 개수
			}
		}
		for (int r = 0; r < j; r++) //제거된 타일을 위쪽으로 배치(위쪽 열부터 제거된 타일의 개수만큼 0으로 저장)
		{
			board[r][c] = 0; //게임판 2차원 배열 값을 0으로 저장
		}
	}
}

int total_tiles_num(int board[][MAX_SIZE], int row, int col, int* total_tiles) //사용자 정의 함수(제거된 타일의 총 개수를 계산)
{
	for (int r = 0; r < row; r++) //열마다 반복
	{
		for (int c = 0; c < col; c++) //행마다 반복
		{
			if (board[r][c] == 0) //게임판 2차원 배열 값이 0이면(제거된 타일이면)
			{
				(*total_tiles)++; //제거된 타일의 총 개수 계산
			}
		}
	}
}

int write_tiles(int board[][MAX_SIZE], int row, int col, int total_tiles) //사용자 정의 함수(결과 화면을 파일에 출력)
{
	FILE* outfile;

	outfile = fopen("result.txt", "w"); //쓰기 모드로 파일 열기
	for (int r = 0; r < row; r++) //열마다 반복
	{
		for (int c = 0; c < col; c++) //행마다 반복
		{
			fprintf(outfile, "%2d", board[r][c]); //게임 종료 후의 2차원 배열 값을 파일에 출력 
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\n=========================\n");
	fprintf(outfile, " Total removed tiles: %d\n", total_tiles); //제거된 타일의 총 개수를 파일에 출력
	fprintf(outfile, "=========================\n");
}