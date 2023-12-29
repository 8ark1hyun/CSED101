#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //������� ����

char ruby_encryptor(char input, char key); //����� ���� �Լ� (��� ��ȣ�� ���� �̴ϼ� ��ȣȭ)

int main(void) //���� �Լ�
{
	char input1, input2, input3; //�̴ϼ� �� ���� ������ ����
	char key1, key2, key3; //Ű���� �� ���� ������ ����
	char output1, output2, output3; //��ȣȭ ���� ������ ����

	printf("Enter your initials to encrypt (length: 3): "); //�̴ϼ� �Է� �ȳ��� ���
	scanf("%c %c %c", &input1, &input2, &input3); //�̴ϼ� �� ���� �Է�

	getchar(); //�Է� ���۸� ���� ����

	printf("Enter your keyword (length: 3): "); //Ű���� �Է� �ȳ��� ���
	scanf(" %c %c %c", &key1, &key2, &key3); //Ű���� �� ���� �Է�

	output1 = ruby_encryptor(input1, key1); //����� ���� �Լ��� ���� ��ȣȭ ���� �� ����
	output2 = ruby_encryptor(input2, key2);
	output3 = ruby_encryptor(input3, key3);

	printf("%c%c%c\n", output1, output2, output3); //��ȣȭ ���� ���

	return 0;
}

char ruby_encryptor(char input, char key) //����� ���� �Լ�
{
	return ((input - 19) + (key - 97)) % 26 + 65;

	/*
	ASCII �ڵ� �̿�
	'z'�� �Ѿ�� ���, ���ĺ� 26�ڰ� ��ġ ������ ����� ��ó�� 'a'�� ���ƿ����� �����ؾ� �Ѵ�.

	1. Ű���� ���ĺ� ASCII������ 'a'�� ASCII���� 97�� ���־� �� ĭ �̵��ؾ� �ϴ��� �ľ��Ѵ�.
	2. 'a'���� ���������� ���� ������ �ϱ� ���� ���� �̴ϼ� ���ĺ� ASCII���� 19�� ����.
	   (���ĺ� ASCII���� 26�� ��� ������ %�� �̿��� ����ϸ�
	   'a'=19���� �����ϴٰ� 'h'=0�� �ǰ� ���� �ٽ� �����Ѵ�.
	   ���� ASCII���� ���������̱� ������ 19�� �������ν� 'a'���� ���������� �ǵ��� ������ �� �ִ�.)
	3. 1�� ���� 2�� ���� ���Ѵ�.
	4. 3�� ���� ��� ������ %�� �̿��Ͽ� ���ĺ� ������ 26���� �������ָ�
	   'a'=0, 'b'=1, ... , 'z'=25��� �������� ������ �ȴ�.
	5. ��ȣȭ ���ڸ� �빮�ڷ� ����ϱ� ���� 'A'�� ASCII���� 65�� ���Ѵ�.
	*/
}