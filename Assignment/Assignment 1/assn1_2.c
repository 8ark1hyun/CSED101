#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //������� ����
#include <math.h> //�����Լ� ���

float calc_dist(int x1, int y1, int x2, int y2); //����� ���� �Լ� (�� �� ���� �Ÿ� ���)
float calc_area(int x1, int y1, int x2, int y2, int x3, int y3); //����� ���� �Լ� (�ﰢ�� ���� ���)

int main(void)
{
	int px1, py1, px2, py2, px3, py3; //�� �� ��ǥ ������ ����
	float dist1, dist2, dist3, perimeter, area; // �� �� ������ �Ÿ�, �ѷ�, ���� ������ ����

	printf("Enter P1(x1,y1): "); //ù ��° �� ��ǥ �Է� �ȳ��� ���
	scanf("%d %d", &px1, &py1); //ù ��° �� ��ǥ �Է�

	printf("Enter P2(x2,y2): "); //�� ��° �� ��ǥ �Է� �ȳ��� ���
	scanf("%d %d", &px2, &py2); //�� ��° �� ��ǥ �Է�
	
	printf("Enter P3(x3,y3): "); //�� ��° �� ��ǥ �Է� �ȳ��� ���
	scanf("%d %d", &px3, &py3); //�� ��° �� ��ǥ �Է�

	dist1 = calc_dist(px1, py1, px2, py2); //����� ���� �Լ��� ���� �� �� ������ �Ÿ� �� ����
	dist2 = calc_dist(px2, py2, px3, py3);
	dist3 = calc_dist(px3, py3, px1, py1);
	perimeter = dist1 + dist2 + dist3; // �ѷ� = �� ���� ���� ��

	area = calc_area(px1, py1, px2, py2, px3, py3); //����� ���� �Լ��� ���� �ﰢ�� ���� �� ����

	printf("The perimeter of triangle is: %.2f\n", perimeter); //�ﰢ�� �ѷ� ���
	printf("The area of triangle is: %.2f\n", area); //�ﰢ�� ���� ���

	return 0;
}

float calc_dist(int x1, int y1, int x2, int y2) //����� ���� �Լ� (�� �� ���� �Ÿ� ���)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); //�� �� ���� �Ÿ� ���
}
float calc_area(int x1, int y1, int x2, int y2, int x3, int y3) //����� ���� �Լ�(�ﰢ�� ���� ���)
{
	return fabs((x1 * y2 + x2 * y3 + x3 * y1) - (x2 * y1 + x3 * y2 + x1 * y3)) / 2; //�ﰢ�� ���� ���
}