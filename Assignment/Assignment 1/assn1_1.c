#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //헤더파일 선언

char ruby_encryptor(char input, char key); //사용자 정의 함수 (루비 암호를 통해 이니셜 암호화)

int main(void) //메인 함수
{
	char input1, input2, input3; //이니셜 각 문자 변수의 선언
	char key1, key2, key3; //키워드 각 문자 변수의 선언
	char output1, output2, output3; //암호화 문자 변수의 선언

	printf("Enter your initials to encrypt (length: 3): "); //이니셜 입력 안내문 출력
	scanf("%c %c %c", &input1, &input2, &input3); //이니셜 각 문자 입력

	getchar(); //입력 버퍼를 비우기 위함

	printf("Enter your keyword (length: 3): "); //키워드 입력 안내문 출력
	scanf(" %c %c %c", &key1, &key2, &key3); //키워드 각 문자 입력

	output1 = ruby_encryptor(input1, key1); //사용자 정의 함수를 통해 암호화 문자 값 산출
	output2 = ruby_encryptor(input2, key2);
	output3 = ruby_encryptor(input3, key3);

	printf("%c%c%c\n", output1, output2, output3); //암호화 문자 출력

	return 0;
}

char ruby_encryptor(char input, char key) //사용자 정의 함수
{
	return ((input - 19) + (key - 97)) % 26 + 65;

	/*
	ASCII 코드 이용
	'z'를 넘어서는 경우, 알파벳 26자가 마치 원으로 연결된 것처럼 'a'로 돌아오도록 구현해야 한다.

	1. 키워드 알파벳 ASCII값에서 'a'의 ASCII값인 97을 빼주어 몇 칸 이동해야 하는지 파악한다.
	2. 'a'부터 오름차순의 값을 갖도록 하기 위해 먼저 이니셜 알파벳 ASCII값에 19를 뺀다.
	   (알파벳 ASCII값에 26을 산술 연산자 %를 이용해 계산하면
	   'a'=19부터 증가하다가 'h'=0이 되고 이후 다시 증가한다.
	   고유 ASCII값도 오름차순이기 때문에 19를 빼줌으로써 'a'부터 오름차순이 되도록 설정할 수 있다.)
	3. 1번 값과 2번 값을 더한다.
	4. 3번 값을 산술 연산자 %를 이용하여 알파벳 개수인 26으로 나누어주면
	   'a'=0, 'b'=1, ... , 'z'=25라는 고유값을 가지게 된다.
	5. 암호화 문자를 대문자로 출력하기 위해 'A'의 ASCII값인 65를 더한다.
	*/
}