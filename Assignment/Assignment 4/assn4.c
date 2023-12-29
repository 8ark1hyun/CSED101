#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//image 배열이 아닌 red, green, blue의 세 가지 색상의 배열로 나눠서 구현하였습니다.
//따라서 아래 사용자 정의 함수에서 image 3차원 배열이 아닌 red, green, blue 2차원 배열로 매개변수를 수정하였습니다.

void print_menu(); //사용자 정의 함수(메뉴 출력)
int load_image(const char* filename, int*** red, int*** green, int*** blue, int* width, int* height); //사용자 정의 함수(파일을 읽고 너비와 높이를 입력 받아 색상별 배열 생성)
int** create_image(int width, int height); //사용자 정의 함수(색상별 배열 동적 할당)
int save_image(const char* filename, int** red, int** green, int** blue, int width, int height); //사용자 정의 함수(너비와 높이, 색상별 배열을 새로운 파일에 저장)
int resize_image(int** src_red, int** src_green, int** src_blue, int src_width, int src_height, int** dst_red, int** dst_green, int** dst_blue, int dst_width, int dst_height); //사용자 정의 함수(쌍선형 보간을 이용하여 이미지 크기 조절)
void delete_image(int** red, int** green, int** blue, int height); //사용자 정의 함수(색상별 배열 동적 할당 해제)

int main()
{
	int option; //변수 option = 실행할 번호
	char in_filename[101]; //불러올 파일
	char out_filename[101]; //저장할 파일
	int width = 0; //변수 width = 너비
	int height = 0; //변수 hwight = 높이
	int new_width = 0; //변수 new_width = 크기 조절할 새로운 너비
	int new_height = 0; //변수 new_height = 크기 조절할 새로운 높이
	int** red = 0; //빨간색 2차원 배열
	int** green = 0; //초록색 2차원 배열
	int** blue = 0; //파란색 2차원 배열
	int** new_red = 0; //크기 조절할 빨간색 2차원 배열
	int** new_green = 0; //크기 조절할 초록색 2차원 배열
	int** new_blue = 0; //크기 조절할 파란색 2차원 배열

	while (1) //종료할 때까지 반복
	{
		print_menu(); //메뉴 출력
		printf("Enter number: "); //실행할 번호 입력 문구 출력
		scanf("%d", &option); //실행할 번호 입력
		if (option == 1) //'1' 일 경우
		{
			if (red != NULL || green != NULL || blue != NULL) //색상 배열이 NULL이 아니면
			{
				delete_image(red, green, blue, height); //이미지를 불러오면 전의 이미지 색상 배열 동적 할당 해제
				//이미지 NULL 처리
				red = NULL;
				green = NULL;
				blue = NULL;
			}
			printf("Enter input filename: "); //불러올 파일 이름 입력 문구 출력
			scanf("%s", in_filename); //불러올 파일 이름 입력
			if ((load_image(&in_filename, &red, &green, &blue, &width, &height)) == -1) //파일을 불러온 후 불러올 파일이 없으면(-1 값을 반환받으면)
			{
				continue; //처음부터 반복
			}
			printf("Read %s (%dx%d)\n\n", in_filename, width, height); //불러온 파일 이름, 너비, 높이 출력
			continue; //처음부터 반복
		}
		else if (option == 2) //'2'일 경우
		{
			if (red == NULL || green == NULL || blue == NULL) //색상 배열이 NULL이면
			{
				printf("Image is not loaded\n\n"); //불러온 파일이 없다는 문구 출력
			}
			else if (red != NULL || green != NULL || blue != NULL) //색상 배열이 NULL이 아니면
			{
				printf("Enter output filename: "); //저장할 파일 이름 입력 문구 출력
				scanf("%s", out_filename); //저장할 파일 이름 입력
				save_image(&out_filename, red, green, blue, width, height); //파일 저장
				printf("Saved %s (%dx%d)\n\n", out_filename, width, height); //저장한 파일 이름, 너비, 높이 출력
			}
			continue; //처음부터 반복
		}
		else if (option == 3) //'3'일 경우
		{
			if (red == NULL || green == NULL || blue == NULL) //색상 배열이 NULL이면
			{
				printf("Image is not loaded\n\n"); //불러온 파일이 없다는 문구 출력
			}
			else if (red != NULL || green != NULL || blue != NULL) //색상 배열이 NULL이 아니면
			{
				printf("Enter output size: "); //조절할 이미지 크기 입력 문구 출력
				scanf("%d %d", &new_width, &new_height); //조절할 이미지 크기 입력
				if (new_width < 0 || new_height < 0) //입력 받은 이미지 크기가 양수가 아니면
				{
					printf("Invalid size\n\n"); //오류메시지 출력
					continue; //처음부터 반복
				}
				new_red = create_image(new_width, new_height); //크기 조절할 빨간색 2차원 배열 생성, 동적 할당
				new_green = create_image(new_width, new_height); //크기 조절할 초록색 2차원 배열 생성, 동적 할당
				new_blue = create_image(new_width, new_height); //크기 조절할 파란색 2차원 배열 생성, 동적 할당
				resize_image(red, green, blue, width, height, new_red, new_green, new_blue, new_width, new_height); //이미지 크기 조절
				printf("Resized image (%dx%d -> %dx%d)\n\n", width, height, new_width, new_height); //조절한 이미지 크기 출력
				delete_image(red, green, blue, height); //기존 색상별 배열 동적 할당 해제
				width = new_width; //조절한 너비 값을 기존 너비 값 변수에 저장
				height = new_height; //조절한 높이 값을 기존 높이 값 변수에 저장
				red = new_red; //조절한 빨간색 배열을 기존 빨간색 배열에 저장
				green = new_green; //조절한 초록색 배열을 기존 초록색 배열에 저장
				blue = new_blue; //조절한 파란색 배열을 기존 파란색 배열에 저장
			}
			continue; //처음부터 반복
		}
		else if (option == 0) //'0'일 경우
		{
			printf("Quit program\n\n"); //종료 안내 문구 출력
			delete_image(red, green, blue, height); //색상별 배열 동적 할당 해제
			return 0; //반복문 종료
		}
		else
		{
			printf("Invalid menu selected\n\n"); //'0~3'사이의 값이 아닐 경우
			continue; //처음부터 반복
		}
	}

	return 0; //프로그램 종료
}

void print_menu() //사용자 정의 함수(메뉴 출력)
{
	for (int line = 1; line < 30; line++) //선 출력
	{
		printf("=");
	}
	printf("\n");
	printf("|       IMAGE RESIZER       |\n"); //제목 출력
	printf("|   1. Load       2. Save   |\n"); //옵션 출력
	printf("|   3. Resize     0. Quit   |\n"); //옵션 출력
	for (int line = 1; line < 30; line++) //선 출력
	{
		printf("=");
	}
	printf("\n");
}

int load_image(const char* filename, int*** red, int*** green, int*** blue, int* width, int* height) //사용자 정의 함수(파일을 읽고 너비와 높이를 입력 받아 색상별 배열 생성)
{
	FILE* fp;
	int pixel_num = 0; //변수 pixel_num = 픽셀 값 개수
	char a = 0;
	int b = 0;

	if (!(fp = fopen(filename, "r"))) //읽기모드로 파일 열기 후 파일이 존재하지 않으면
	{
		printf("File not exists\n\n"); //파일이 존재하지 않는다는 문구 출력
		return -1; //-1 값을 반환
	}
	fscanf(fp, "%c%c", &a, &a); //P3
	fscanf(fp, "%d %d", width, height); //파일에서 너비와 높이 값 입력
	fscanf(fp, "%d", &b); //255
	*red = create_image(*width, *height); //빨간색 배열 생성, 동적 할당
	*green = create_image(*width, *height); //초록색 배열 생성, 동적 할당
	*blue = create_image(*width, *height); //파란색 배열 생성, 동적 할당
	for (int i = 0; i < *height; i++) //높이만큼 반복
	{
		for (int j = 0; j < *width; j++) //너비만큼 반복
		{
			if ((fscanf(fp, "%d %d %d", &(*red)[i][j], &(*green)[i][j], &(*blue)[i][j])) != EOF) //파일의 끝까지 색상별 픽셀 값을 입력 받아 색상별 배열에 저장
			{
				pixel_num++; //픽셀 값 총 개수 계산
				if ((*red)[i][j] < 0 || (*red)[i][j] > 255 || (*green)[i][j] < 0 || (*green)[i][j] > 255 || (*blue)[i][j] < 0 || (*blue)[i][j] > 255) //픽셀 값이 0~255 사이의 값이 아니면
				{
					printf("Image corrupted\n\n"); //오류메시지 출력
					return -1; //-1 값을 반환
				}
			}
		}
	}
	if ((fscanf(fp, "%d", &b)) != EOF || pixel_num != *width * *height) //파일의 끝이 아니거나 픽셀 값 총 개수가 너비와 높이의 곱과 같지 않으면
	{
		printf("Image corrupted\n\n"); //오류메시지 출력
		return -1; //-1값을 반환
	}
	return 0;
}

int** create_image(int width, int height) //사용자 정의 함수(색상별 배열 동적 할당)
{
	int** color;
	int i;

	color = (int**)malloc(sizeof(int*) * height); //높이만큼 할당
	for (i = 0; i < height; i++)
	{
		*(color + i) = (int*)malloc(sizeof(int) * width); ///너비만큼 할당
	}

	return color; //동적 할당된 배열 반환
}

int save_image(const char* filename, int** red, int** green, int** blue, int width, int height) //사용자 정의 함수(너비와 높이, 색상별 배열을 새로운 파일에 저장)
{
	FILE* fp;

	fp = fopen(filename, "w"); //쓰기모드로 파일 열기
	fprintf(fp, "P3 "); //P3 출력
	fprintf(fp, "%d %d ", width, height); //너비와 높이 출력
	fprintf(fp, "255\n"); //255 출력
	for (int i = 0; i < height; i++) //높이만큼 반복
	{
		for (int j = 0; j < width; j++) //너비만큼 반복
		{
			fprintf(fp, "%d %d %d ", red[i][j], green[i][j], blue[i][j]); //색상별 배열 픽셀 값 출력
		}
	}
}

int resize_image(int** src_red, int** src_green, int** src_blue, int src_width, int src_height, int** dst_red, int** dst_green, int** dst_blue, int dst_width, int dst_height) //사용자 정의 함수(쌍선형 보간을 이용하여 이미지 크기 조절)
{
	double a = 0;
	double b = 0;
	int c = 0;
	int d = 0;

	for (int i = 0; i < dst_height - 1; i++) //조절할 이미지 크기의 높이만큼 반복 (가장 아래 가로줄은 참고사항에 따라 따로 계산)
	{
		for (int j = 0; j < dst_width - 1; j++) //조절할 이미지 크기의 너비만큼 반복 (가장 오른쪽 세로줄을 참고사항에 따라 따로 계산)
		{
			a = i * (double)(src_height - 1) / (double)(dst_height - 1); //기존 높이와 새로운 높이의 비율과 원본 픽셀 좌표 곱
			b = j * (double)(src_width - 1) / (double)(dst_width - 1); //기존 너비와 새로운 너비의 비율과 원본 픽셀 좌표 곱
			c = floor(a); //a 값 내림
			d = floor(b); //b 값 내림
			//아래는 쌍선형 보간 계산, 반올림
			dst_red[i][j] = round((src_red[c][d] * (d + 1 - b) + src_red[c][d + 1] * (b - d)) * (c + 1 - a) + (src_red[c + 1][d] * (d + 1 - b) + src_red[c + 1][d + 1] * (b - d)) * (a - c));
			dst_green[i][j] = round((src_green[c][d] * (d + 1 - b) + src_green[c][d + 1] * (b - d)) * (c + 1 - a) + (src_green[c + 1][d] * (d + 1 - b) + src_green[c + 1][d + 1] * (b - d)) * (a - c));
			dst_blue[i][j] = round((src_blue[c][d] * (d + 1 - b) + src_blue[c][d + 1] * (b - d)) * (c + 1 - a) + (src_blue[c + 1][d] * (d + 1 - b) + src_blue[c + 1][d + 1] * (b - d)) * (a - c));
		}
	}
	for (int j = 0; j < dst_width - 1; j++) //조절할 이미지 크기의 너비만큼 반복
	{
		b = j * (double)(src_width - 1) / (double)(dst_width - 1); //기존 너비와 새로운 너비의 비율과 원본 픽셀 좌표 곱
		d = floor(b); //b 값 내림
		//아래는 가장 아래 가로줄 쌍선형 보간 계산, 반올림
		dst_red[dst_height - 1][j] = round(src_red[src_height - 1][d] * (d + 1 - b) + src_red[src_height - 1][d + 1] * (b - d));
		dst_green[dst_height - 1][j] = round(src_green[src_height - 1][d] * (d + 1 - b) + src_green[src_height - 1][d + 1] * (b - d));
		dst_blue[dst_height - 1][j] = round(src_blue[src_height - 1][d] * (d + 1 - b) + src_blue[src_height - 1][d + 1] * (b - d));
	}
	for (int i = 0; i < dst_height - 1; i++) //조절할 이미지 크기의 높이만큼 반복
	{
		a = i * (double)(src_height - 1) / (double)(dst_height - 1); //기존 높이와 새로운 높이의 비율과 원본 픽셀 좌표 곱
		c = floor(a); //a 값 내림
		//아래는 가장 오른쪽 세로줄 쌍선형 보간, 반올림
		dst_red[i][dst_width - 1] = round(src_red[c][src_width - 1] * (c + 1 - a) + src_red[c + 1][src_width - 1] * (a - c));
		dst_green[i][dst_width - 1] = round(src_green[c][src_width - 1] * (c + 1 - a) + src_green[c + 1][src_width - 1] * (a - c));
		dst_blue[i][dst_width - 1] = round(src_blue[c][src_width - 1] * (c + 1 - a) + src_blue[c + 1][src_width - 1] * (a - c));
	}
	//아래는 오른쪽 아래 모서리 픽셀 값
	dst_red[dst_height - 1][dst_width - 1] = src_red[src_height - 1][src_width - 1];
	dst_green[dst_height - 1][dst_width - 1] = src_green[src_height - 1][src_width - 1];
	dst_blue[dst_height - 1][dst_width - 1] = src_blue[src_height - 1][src_width - 1];
}

void delete_image(int** red, int** green, int** blue, int height) //사용자 정의 함수(색상별 배열 동적 할당 해제)
{
	for (int i = 0; i < height; i++) //높이만큼 반복
	{
		free(*(red + i)); //동적 할당 해제
		free(*(green + i)); //동적 할당 해제
		free(*(blue + i)); //동적 할당 해제
	}
	free(red); //동적 할당 해제
	free(green); //동적 할당 해제
	free(blue); //동적 할당 해제
}