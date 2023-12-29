#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//image �迭�� �ƴ� red, green, blue�� �� ���� ������ �迭�� ������ �����Ͽ����ϴ�.
//���� �Ʒ� ����� ���� �Լ����� image 3���� �迭�� �ƴ� red, green, blue 2���� �迭�� �Ű������� �����Ͽ����ϴ�.

void print_menu(); //����� ���� �Լ�(�޴� ���)
int load_image(const char* filename, int*** red, int*** green, int*** blue, int* width, int* height); //����� ���� �Լ�(������ �а� �ʺ�� ���̸� �Է� �޾� ���� �迭 ����)
int** create_image(int width, int height); //����� ���� �Լ�(���� �迭 ���� �Ҵ�)
int save_image(const char* filename, int** red, int** green, int** blue, int width, int height); //����� ���� �Լ�(�ʺ�� ����, ���� �迭�� ���ο� ���Ͽ� ����)
int resize_image(int** src_red, int** src_green, int** src_blue, int src_width, int src_height, int** dst_red, int** dst_green, int** dst_blue, int dst_width, int dst_height); //����� ���� �Լ�(�ּ��� ������ �̿��Ͽ� �̹��� ũ�� ����)
void delete_image(int** red, int** green, int** blue, int height); //����� ���� �Լ�(���� �迭 ���� �Ҵ� ����)

int main()
{
	int option; //���� option = ������ ��ȣ
	char in_filename[101]; //�ҷ��� ����
	char out_filename[101]; //������ ����
	int width = 0; //���� width = �ʺ�
	int height = 0; //���� hwight = ����
	int new_width = 0; //���� new_width = ũ�� ������ ���ο� �ʺ�
	int new_height = 0; //���� new_height = ũ�� ������ ���ο� ����
	int** red = 0; //������ 2���� �迭
	int** green = 0; //�ʷϻ� 2���� �迭
	int** blue = 0; //�Ķ��� 2���� �迭
	int** new_red = 0; //ũ�� ������ ������ 2���� �迭
	int** new_green = 0; //ũ�� ������ �ʷϻ� 2���� �迭
	int** new_blue = 0; //ũ�� ������ �Ķ��� 2���� �迭

	while (1) //������ ������ �ݺ�
	{
		print_menu(); //�޴� ���
		printf("Enter number: "); //������ ��ȣ �Է� ���� ���
		scanf("%d", &option); //������ ��ȣ �Է�
		if (option == 1) //'1' �� ���
		{
			if (red != NULL || green != NULL || blue != NULL) //���� �迭�� NULL�� �ƴϸ�
			{
				delete_image(red, green, blue, height); //�̹����� �ҷ����� ���� �̹��� ���� �迭 ���� �Ҵ� ����
				//�̹��� NULL ó��
				red = NULL;
				green = NULL;
				blue = NULL;
			}
			printf("Enter input filename: "); //�ҷ��� ���� �̸� �Է� ���� ���
			scanf("%s", in_filename); //�ҷ��� ���� �̸� �Է�
			if ((load_image(&in_filename, &red, &green, &blue, &width, &height)) == -1) //������ �ҷ��� �� �ҷ��� ������ ������(-1 ���� ��ȯ������)
			{
				continue; //ó������ �ݺ�
			}
			printf("Read %s (%dx%d)\n\n", in_filename, width, height); //�ҷ��� ���� �̸�, �ʺ�, ���� ���
			continue; //ó������ �ݺ�
		}
		else if (option == 2) //'2'�� ���
		{
			if (red == NULL || green == NULL || blue == NULL) //���� �迭�� NULL�̸�
			{
				printf("Image is not loaded\n\n"); //�ҷ��� ������ ���ٴ� ���� ���
			}
			else if (red != NULL || green != NULL || blue != NULL) //���� �迭�� NULL�� �ƴϸ�
			{
				printf("Enter output filename: "); //������ ���� �̸� �Է� ���� ���
				scanf("%s", out_filename); //������ ���� �̸� �Է�
				save_image(&out_filename, red, green, blue, width, height); //���� ����
				printf("Saved %s (%dx%d)\n\n", out_filename, width, height); //������ ���� �̸�, �ʺ�, ���� ���
			}
			continue; //ó������ �ݺ�
		}
		else if (option == 3) //'3'�� ���
		{
			if (red == NULL || green == NULL || blue == NULL) //���� �迭�� NULL�̸�
			{
				printf("Image is not loaded\n\n"); //�ҷ��� ������ ���ٴ� ���� ���
			}
			else if (red != NULL || green != NULL || blue != NULL) //���� �迭�� NULL�� �ƴϸ�
			{
				printf("Enter output size: "); //������ �̹��� ũ�� �Է� ���� ���
				scanf("%d %d", &new_width, &new_height); //������ �̹��� ũ�� �Է�
				if (new_width < 0 || new_height < 0) //�Է� ���� �̹��� ũ�Ⱑ ����� �ƴϸ�
				{
					printf("Invalid size\n\n"); //�����޽��� ���
					continue; //ó������ �ݺ�
				}
				new_red = create_image(new_width, new_height); //ũ�� ������ ������ 2���� �迭 ����, ���� �Ҵ�
				new_green = create_image(new_width, new_height); //ũ�� ������ �ʷϻ� 2���� �迭 ����, ���� �Ҵ�
				new_blue = create_image(new_width, new_height); //ũ�� ������ �Ķ��� 2���� �迭 ����, ���� �Ҵ�
				resize_image(red, green, blue, width, height, new_red, new_green, new_blue, new_width, new_height); //�̹��� ũ�� ����
				printf("Resized image (%dx%d -> %dx%d)\n\n", width, height, new_width, new_height); //������ �̹��� ũ�� ���
				delete_image(red, green, blue, height); //���� ���� �迭 ���� �Ҵ� ����
				width = new_width; //������ �ʺ� ���� ���� �ʺ� �� ������ ����
				height = new_height; //������ ���� ���� ���� ���� �� ������ ����
				red = new_red; //������ ������ �迭�� ���� ������ �迭�� ����
				green = new_green; //������ �ʷϻ� �迭�� ���� �ʷϻ� �迭�� ����
				blue = new_blue; //������ �Ķ��� �迭�� ���� �Ķ��� �迭�� ����
			}
			continue; //ó������ �ݺ�
		}
		else if (option == 0) //'0'�� ���
		{
			printf("Quit program\n\n"); //���� �ȳ� ���� ���
			delete_image(red, green, blue, height); //���� �迭 ���� �Ҵ� ����
			return 0; //�ݺ��� ����
		}
		else
		{
			printf("Invalid menu selected\n\n"); //'0~3'������ ���� �ƴ� ���
			continue; //ó������ �ݺ�
		}
	}

	return 0; //���α׷� ����
}

void print_menu() //����� ���� �Լ�(�޴� ���)
{
	for (int line = 1; line < 30; line++) //�� ���
	{
		printf("=");
	}
	printf("\n");
	printf("|       IMAGE RESIZER       |\n"); //���� ���
	printf("|   1. Load       2. Save   |\n"); //�ɼ� ���
	printf("|   3. Resize     0. Quit   |\n"); //�ɼ� ���
	for (int line = 1; line < 30; line++) //�� ���
	{
		printf("=");
	}
	printf("\n");
}

int load_image(const char* filename, int*** red, int*** green, int*** blue, int* width, int* height) //����� ���� �Լ�(������ �а� �ʺ�� ���̸� �Է� �޾� ���� �迭 ����)
{
	FILE* fp;
	int pixel_num = 0; //���� pixel_num = �ȼ� �� ����
	char a = 0;
	int b = 0;

	if (!(fp = fopen(filename, "r"))) //�б���� ���� ���� �� ������ �������� ������
	{
		printf("File not exists\n\n"); //������ �������� �ʴ´ٴ� ���� ���
		return -1; //-1 ���� ��ȯ
	}
	fscanf(fp, "%c%c", &a, &a); //P3
	fscanf(fp, "%d %d", width, height); //���Ͽ��� �ʺ�� ���� �� �Է�
	fscanf(fp, "%d", &b); //255
	*red = create_image(*width, *height); //������ �迭 ����, ���� �Ҵ�
	*green = create_image(*width, *height); //�ʷϻ� �迭 ����, ���� �Ҵ�
	*blue = create_image(*width, *height); //�Ķ��� �迭 ����, ���� �Ҵ�
	for (int i = 0; i < *height; i++) //���̸�ŭ �ݺ�
	{
		for (int j = 0; j < *width; j++) //�ʺ�ŭ �ݺ�
		{
			if ((fscanf(fp, "%d %d %d", &(*red)[i][j], &(*green)[i][j], &(*blue)[i][j])) != EOF) //������ ������ ���� �ȼ� ���� �Է� �޾� ���� �迭�� ����
			{
				pixel_num++; //�ȼ� �� �� ���� ���
				if ((*red)[i][j] < 0 || (*red)[i][j] > 255 || (*green)[i][j] < 0 || (*green)[i][j] > 255 || (*blue)[i][j] < 0 || (*blue)[i][j] > 255) //�ȼ� ���� 0~255 ������ ���� �ƴϸ�
				{
					printf("Image corrupted\n\n"); //�����޽��� ���
					return -1; //-1 ���� ��ȯ
				}
			}
		}
	}
	if ((fscanf(fp, "%d", &b)) != EOF || pixel_num != *width * *height) //������ ���� �ƴϰų� �ȼ� �� �� ������ �ʺ�� ������ ���� ���� ������
	{
		printf("Image corrupted\n\n"); //�����޽��� ���
		return -1; //-1���� ��ȯ
	}
	return 0;
}

int** create_image(int width, int height) //����� ���� �Լ�(���� �迭 ���� �Ҵ�)
{
	int** color;
	int i;

	color = (int**)malloc(sizeof(int*) * height); //���̸�ŭ �Ҵ�
	for (i = 0; i < height; i++)
	{
		*(color + i) = (int*)malloc(sizeof(int) * width); ///�ʺ�ŭ �Ҵ�
	}

	return color; //���� �Ҵ�� �迭 ��ȯ
}

int save_image(const char* filename, int** red, int** green, int** blue, int width, int height) //����� ���� �Լ�(�ʺ�� ����, ���� �迭�� ���ο� ���Ͽ� ����)
{
	FILE* fp;

	fp = fopen(filename, "w"); //������� ���� ����
	fprintf(fp, "P3 "); //P3 ���
	fprintf(fp, "%d %d ", width, height); //�ʺ�� ���� ���
	fprintf(fp, "255\n"); //255 ���
	for (int i = 0; i < height; i++) //���̸�ŭ �ݺ�
	{
		for (int j = 0; j < width; j++) //�ʺ�ŭ �ݺ�
		{
			fprintf(fp, "%d %d %d ", red[i][j], green[i][j], blue[i][j]); //���� �迭 �ȼ� �� ���
		}
	}
}

int resize_image(int** src_red, int** src_green, int** src_blue, int src_width, int src_height, int** dst_red, int** dst_green, int** dst_blue, int dst_width, int dst_height) //����� ���� �Լ�(�ּ��� ������ �̿��Ͽ� �̹��� ũ�� ����)
{
	double a = 0;
	double b = 0;
	int c = 0;
	int d = 0;

	for (int i = 0; i < dst_height - 1; i++) //������ �̹��� ũ���� ���̸�ŭ �ݺ� (���� �Ʒ� �������� ������׿� ���� ���� ���)
	{
		for (int j = 0; j < dst_width - 1; j++) //������ �̹��� ũ���� �ʺ�ŭ �ݺ� (���� ������ �������� ������׿� ���� ���� ���)
		{
			a = i * (double)(src_height - 1) / (double)(dst_height - 1); //���� ���̿� ���ο� ������ ������ ���� �ȼ� ��ǥ ��
			b = j * (double)(src_width - 1) / (double)(dst_width - 1); //���� �ʺ�� ���ο� �ʺ��� ������ ���� �ȼ� ��ǥ ��
			c = floor(a); //a �� ����
			d = floor(b); //b �� ����
			//�Ʒ��� �ּ��� ���� ���, �ݿø�
			dst_red[i][j] = round((src_red[c][d] * (d + 1 - b) + src_red[c][d + 1] * (b - d)) * (c + 1 - a) + (src_red[c + 1][d] * (d + 1 - b) + src_red[c + 1][d + 1] * (b - d)) * (a - c));
			dst_green[i][j] = round((src_green[c][d] * (d + 1 - b) + src_green[c][d + 1] * (b - d)) * (c + 1 - a) + (src_green[c + 1][d] * (d + 1 - b) + src_green[c + 1][d + 1] * (b - d)) * (a - c));
			dst_blue[i][j] = round((src_blue[c][d] * (d + 1 - b) + src_blue[c][d + 1] * (b - d)) * (c + 1 - a) + (src_blue[c + 1][d] * (d + 1 - b) + src_blue[c + 1][d + 1] * (b - d)) * (a - c));
		}
	}
	for (int j = 0; j < dst_width - 1; j++) //������ �̹��� ũ���� �ʺ�ŭ �ݺ�
	{
		b = j * (double)(src_width - 1) / (double)(dst_width - 1); //���� �ʺ�� ���ο� �ʺ��� ������ ���� �ȼ� ��ǥ ��
		d = floor(b); //b �� ����
		//�Ʒ��� ���� �Ʒ� ������ �ּ��� ���� ���, �ݿø�
		dst_red[dst_height - 1][j] = round(src_red[src_height - 1][d] * (d + 1 - b) + src_red[src_height - 1][d + 1] * (b - d));
		dst_green[dst_height - 1][j] = round(src_green[src_height - 1][d] * (d + 1 - b) + src_green[src_height - 1][d + 1] * (b - d));
		dst_blue[dst_height - 1][j] = round(src_blue[src_height - 1][d] * (d + 1 - b) + src_blue[src_height - 1][d + 1] * (b - d));
	}
	for (int i = 0; i < dst_height - 1; i++) //������ �̹��� ũ���� ���̸�ŭ �ݺ�
	{
		a = i * (double)(src_height - 1) / (double)(dst_height - 1); //���� ���̿� ���ο� ������ ������ ���� �ȼ� ��ǥ ��
		c = floor(a); //a �� ����
		//�Ʒ��� ���� ������ ������ �ּ��� ����, �ݿø�
		dst_red[i][dst_width - 1] = round(src_red[c][src_width - 1] * (c + 1 - a) + src_red[c + 1][src_width - 1] * (a - c));
		dst_green[i][dst_width - 1] = round(src_green[c][src_width - 1] * (c + 1 - a) + src_green[c + 1][src_width - 1] * (a - c));
		dst_blue[i][dst_width - 1] = round(src_blue[c][src_width - 1] * (c + 1 - a) + src_blue[c + 1][src_width - 1] * (a - c));
	}
	//�Ʒ��� ������ �Ʒ� �𼭸� �ȼ� ��
	dst_red[dst_height - 1][dst_width - 1] = src_red[src_height - 1][src_width - 1];
	dst_green[dst_height - 1][dst_width - 1] = src_green[src_height - 1][src_width - 1];
	dst_blue[dst_height - 1][dst_width - 1] = src_blue[src_height - 1][src_width - 1];
}

void delete_image(int** red, int** green, int** blue, int height) //����� ���� �Լ�(���� �迭 ���� �Ҵ� ����)
{
	for (int i = 0; i < height; i++) //���̸�ŭ �ݺ�
	{
		free(*(red + i)); //���� �Ҵ� ����
		free(*(green + i)); //���� �Ҵ� ����
		free(*(blue + i)); //���� �Ҵ� ����
	}
	free(red); //���� �Ҵ� ����
	free(green); //���� �Ҵ� ����
	free(blue); //���� �Ҵ� ����
}