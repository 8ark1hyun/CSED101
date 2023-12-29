#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //헤더파일 선언
#include <math.h> //수학함수 사용

float calc_dist(int x1, int y1, int x2, int y2); //사용자 정의 함수 (두 점 사이 거리 계산)
float calc_area(int x1, int y1, int x2, int y2, int x3, int y3); //사용자 정의 함수 (삼각형 넓이 계산)

int main(void)
{
	int px1, py1, px2, py2, px3, py3; //세 점 좌표 변수의 선언
	float dist1, dist2, dist3, perimeter, area; // 두 점 사이의 거리, 둘레, 넓이 변수의 선언

	printf("Enter P1(x1,y1): "); //첫 번째 점 좌표 입력 안내문 출력
	scanf("%d %d", &px1, &py1); //첫 번째 점 좌표 입력

	printf("Enter P2(x2,y2): "); //두 번째 점 좌표 입력 안내문 출력
	scanf("%d %d", &px2, &py2); //두 번째 점 좌표 입력
	
	printf("Enter P3(x3,y3): "); //세 번째 점 좌표 입력 안내문 출력
	scanf("%d %d", &px3, &py3); //세 번째 점 좌표 입력

	dist1 = calc_dist(px1, py1, px2, py2); //사용자 정의 함수를 통해 두 점 사이의 거리 값 산출
	dist2 = calc_dist(px2, py2, px3, py3);
	dist3 = calc_dist(px3, py3, px1, py1);
	perimeter = dist1 + dist2 + dist3; // 둘레 = 세 변의 길이 합

	area = calc_area(px1, py1, px2, py2, px3, py3); //사용자 정의 함수를 통해 삼각형 넓이 값 산출

	printf("The perimeter of triangle is: %.2f\n", perimeter); //삼각형 둘레 출력
	printf("The area of triangle is: %.2f\n", area); //삼각형 넓이 출력

	return 0;
}

float calc_dist(int x1, int y1, int x2, int y2) //사용자 정의 함수 (두 점 사이 거리 계산)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); //두 점 사이 거리 계산
}
float calc_area(int x1, int y1, int x2, int y2, int x3, int y3) //사용자 정의 함수(삼각형 넓이 계산)
{
	return fabs((x1 * y2 + x2 * y3 + x3 * y1) - (x2 * y1 + x3 * y2 + x1 * y3)) / 2; //삼각형 넓이 계산
}