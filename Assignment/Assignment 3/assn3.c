#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

int make_board(int board[][MAX_SIZE], int* row, int* col); //����� ���� �Լ�(������ �а� �������� ��� ���� ũ��� ���� �� ����)
void print_board(int board[][MAX_SIZE], int row, int col); //����� ���� �Լ�(������(2���� �迭)�� ���޹޾� ������ ���)
int remove_tiles(int board[][MAX_SIZE], int row, int col); //����� ���� �Լ�(Ÿ���� �����ϰ�, ���ŵ� ���� ���� ���ο� ���� ������ ����� ��ȯ�Ͽ� ���α׷� ���ῡ ���)
void update_board(int board[][MAX_SIZE], int row, int col); //����� ���� �Լ�(Ÿ���� ���ŵ� �� ĭ�� ������ ���̵��� ������� ���� ä��)
int total_tiles_num(int board[][MAX_SIZE], int row, int col, int* total_tiles); //����� ���� �Լ�(���ŵ� Ÿ���� �� ������ ���)
int write_tiles(int board[][MAX_SIZE], int row, int col, int total_tiles); //����� ���� �Լ�(��� ȭ���� ���Ͽ� ���)


int main()
{
	int board[MAX_SIZE][MAX_SIZE]; //������ 2���� �迭
	int r = 0; //���� r = ��
	int c = 0; //���� c = ��
	int total_tiles = 0; //���� total_tiles = �� ���ŵ� Ÿ���� ����

	if ((make_board(board, &r, &c)) == -1) //������ �а� ������ �߻��ϸ�(-1 ���� ��ȯ������)
	{
		return 0; //���α׷� ����
	}

	while (1) //������ ����� ������ �ݺ�
	{
		print_board(board, r, c); //������ ���
		if ((remove_tiles(board, r, c)) == -1) //�� �̻� ���� ������ Ÿ���� ������(-1 ���� ��ȯ������)
		{
			break; //���� ����
		}
		getchar(); //ȭ�� �����
		system("cls"); //ȭ�� �����
		print_board(board, r, c); //Ÿ�� ������ ���� ������ ���
		update_board(board, r, c); //Ÿ���� ���ŵ� �� ĭ�� ������ ���̵��� ������� ���� ä��
		getchar(); //ȭ�� �����
		system("cls"); //ȭ�� �����
	}
	total_tiles_num(board, r, c, &total_tiles); //���ŵ� Ÿ���� �� ������ ���
	printf("\n=========================\n");
	printf(" Total removed tiles: %d\n", total_tiles); //���ŵ� Ÿ���� �� ������ ���
	printf("=========================\n");
	write_tiles(board, r, c, total_tiles); //��� ȭ���� ���Ͽ� ���

	return 0;
}

int make_board(int board[][MAX_SIZE], int* row, int* col) //����� ���� �Լ�(������ �а� �������� ��� ���� ũ��� ���� �� ����)
{
	FILE* infile;
	int tiles_num = 0; //���� tiles_num = �� Ÿ���� ����
	int r = 0;
	int c = 0;

	if (!(infile = fopen("board.txt", "r"))) //�б���� ���� ���� �� ������ �������� ������
	{
		printf("������ �������� �ʽ��ϴ�!\n"); //�����޼��� ���
		return -1; //-1 ���� ��ȯ
	}
	fscanf(infile, "%d %d", col, row); //������ ù �ٿ� ��� ���� ũ�⸦ �Է�
	for (r = 0; r < *row; r++) //������ �ݺ�
	{
		for (c = 0; c < *col; c++) //�ึ�� �ݺ�
		{
			if ((fscanf(infile, "%d", &board[r][c])) != EOF) //������ ������ Ÿ���� ���� ���� �Է� �޾� 2���� �迭�� ����
			{
				tiles_num++; //�� Ÿ���� ���� ���
				if (board[r][c] < 1 || board[r][c] > 8) //Ÿ���� ���� ���� �ùٸ��� ������
				{
					printf("Ÿ���� ���ڰ� �ùٸ��� �ʽ��ϴ�!\n"); //�����޽��� ���
					return -1; //-1 ���� ��ȯ
				}
			}
		}
	}
	if ((fscanf(infile, "%d")) != EOF || tiles_num != *row * *col) //��� ���� ũ��� �� Ÿ���� ������ ��ġ���� ������
	{
		printf("������ Ÿ���� ������ �ùٸ��� �ʽ��ϴ�!\n"); //�����޽��� ���
		return -1; //-1 ���� ��ȯ
	}
	return 0;
}

void print_board(int board[][MAX_SIZE], int row, int col) //����� ���� �Լ�(������(2���� �迭)�� ���޹޾� ������ ���)
{
	for (int r = 0; r < row; r++) //������ �ݺ�
	{
		for (int c = 0; c < col; c++) //�ึ�� �ݺ�
		{
			printf("%2d", board[r][c]); //2���� �迭�� ����� Ÿ���� ���� �� ���
		}
		printf("\n");
	}
}

int remove_tiles(int board[][MAX_SIZE], int row, int col) //����� ���� �Լ�(Ÿ���� �����ϰ�, ���ŵ� ���� ���� ���ο� ���� ������ ����� ��ȯ�Ͽ� ���α׷� ���ῡ ���)
{
	int remove[MAX_SIZE][MAX_SIZE]; //������ Ÿ���� ��ġ�� �����ϴ� 2���� �迭
	int i = 0; //���� i = ������ Ÿ���� ����

	for (int r = 0; r < row; r++) //������ �ݺ�
	{
		for (int c = 0; c < col; c++) //�ึ�� �ݺ�
		{
			if (board[r][c] == board[r][c + 1] && board[r][c] == board[r + 1][c] && board[r][c] == board[r + 1][c + 1] && board[r][c] != 0) //2X2 ������ ���� ���̰� �ִٸ�
			{
				remove[r][c] = 1;
				remove[r + 1][c] = 1;
				remove[r][c + 1] = 1;
				remove[r + 1][c + 1] = 1; //remove 2���� �迭�� ������ Ÿ���� ��ġ ���� 1�� ����
			}
		}
	}
	for (int r = 0; r < row; r++) //������ �ݺ�
	{
		for (int c = 0; c < col; c++) //�ึ�� �ݺ�
		{
			if (remove[r][c] == 1) //remove 2���� �迭�� ���� 1�̸�
			{
				board[r][c] = 0; //������ 2���� �迭�� ���� ����(0���� ����)
				i++; //���ŵ� Ÿ���� �� ���� ���
			}
		}
	}
	if (i == 0) //���ŵ� Ÿ���� ������
	{
		return -1; //-1 ���� ��ȯ
	}
}

void update_board(int board[][MAX_SIZE], int row, int col) //����� ���� �Լ�(Ÿ���� ���ŵ� �� ĭ�� ������ ���̵��� ������� ���� ä��)
{
	for (int c = 0; c < col; c++) //�ึ�� �ݺ�
	{
		int i = row - 1; //���� i = Ÿ���� ������ �� ������ ���̸� ä�� �� ������ 2���� �迭�� ��
		int j = 0; //���� j = �� ���� ���ŵ� Ÿ���� ����
		for (int r = row - 1; r >= 0; r--) //������ �ݺ�(�Ʒ��� ������ �ݺ�)
		{
			if (board[r][c] != 0) //������ Ÿ���� ���� 0�� �ƴϸ�(���ŵ� Ÿ���� �ƴϸ�)
			{
				board[i][c] = board[r][c]; //Ÿ���� ���� �Ʒ��������� ���ʷ� ����
				i--; //Ÿ���� ���� �����ϸ� ���� ��ĭ�� �ø�
			}
			else
			{
				j++; //�� ���� ���ŵ� �� ����
			}
		}
		for (int r = 0; r < j; r++) //���ŵ� Ÿ���� �������� ��ġ(���� ������ ���ŵ� Ÿ���� ������ŭ 0���� ����)
		{
			board[r][c] = 0; //������ 2���� �迭 ���� 0���� ����
		}
	}
}

int total_tiles_num(int board[][MAX_SIZE], int row, int col, int* total_tiles) //����� ���� �Լ�(���ŵ� Ÿ���� �� ������ ���)
{
	for (int r = 0; r < row; r++) //������ �ݺ�
	{
		for (int c = 0; c < col; c++) //�ึ�� �ݺ�
		{
			if (board[r][c] == 0) //������ 2���� �迭 ���� 0�̸�(���ŵ� Ÿ���̸�)
			{
				(*total_tiles)++; //���ŵ� Ÿ���� �� ���� ���
			}
		}
	}
}

int write_tiles(int board[][MAX_SIZE], int row, int col, int total_tiles) //����� ���� �Լ�(��� ȭ���� ���Ͽ� ���)
{
	FILE* outfile;

	outfile = fopen("result.txt", "w"); //���� ���� ���� ����
	for (int r = 0; r < row; r++) //������ �ݺ�
	{
		for (int c = 0; c < col; c++) //�ึ�� �ݺ�
		{
			fprintf(outfile, "%2d", board[r][c]); //���� ���� ���� 2���� �迭 ���� ���Ͽ� ��� 
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\n=========================\n");
	fprintf(outfile, " Total removed tiles: %d\n", total_tiles); //���ŵ� Ÿ���� �� ������ ���Ͽ� ���
	fprintf(outfile, "=========================\n");
}