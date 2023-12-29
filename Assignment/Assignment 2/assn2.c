#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void draw_line(); //사용자 정의 함수(선 긋기)
void print_marble_status(int n1, int n2); //사용자 정의 함수(유저, 컴퓨터 구슬 보유 개수 표시)
int get_rand_num(int* a, int b); //사용자 정의 함수(컴퓨터가 숨길 구슬 개수 랜덤 선택)
int get_user_guess(int a, int* b, int* c); //사용자 정의 함수(컴퓨터가 숨긴 개수 추측)
int is_valid_num(int a, int b, int* c); //사용자 정의 함수(추측 성공 여부 확인)
void change_marble_num(int* n1, int* n2, int a, int c); //사용자 정의 함수(승패에 따른 구슬 개수 변경)
int get_user_choice(int* a, int b, int* c, int* d); //사용자 정의 함수(유저가 숨길 구슬 개수 선택)
int get_computer_guess(int* a); //사용자 정의 함수(컴퓨터가 0, 1, 2 중 랜덤 선택)
int win_or_lose(int n1, int n2, int* a, int b, int c); //사용자 정의 함수(게임 승패 출력)
int the_end(int a, int b); //사용자 정의 함수(게임 종료)

int main(void) //메인 함수
{
    int game = 1; //변수 game = 진행한 게임 판 수
    int user_num = 20; //변수 user_num = 유저가 보유하고 있는 구슬 개수
    int comp_num = 20; //변수 comp_num = 컴퓨터가 보유하고 있는 구슬 개수
    int hide, guess, result; //변수 hide =  숨길 구슬 개수, 변수 guess = 추측값, 변수 result = 결과값
    char next; //변수 next = 다음 판 진행 여부
    int win_num = 0; //변수 win_num = 유저가 이긴 횟수

    srand(time(NULL)); //실행할 때마다 값 초기화

    printf("[CSED101 Assignment 2]\n"); //과제 제목 출력
    draw_line();
    printf("▩▩                                ▩▩\n");
    printf("▩▩          Marble  Game          ▩▩\n"); //게임 제목 출력
    printf("▩▩                                ▩▩\n");
    draw_line();
    printf("\n Welcome to the Marble Game! Have fun~!\n"); //게임 인사말 출력
    draw_line();

    for (game = 1; game <= 9; game++) //1번째 판부터 9번째 판까지 게임 진행
    {
        user_num = 20; //게임 시작할 때마다 유저, 컴퓨터 구슬 개수 20개로 초기화
        comp_num = 20;
        printf("\n[Game #%d]\n", game); //게임 판 수 안내
        print_marble_status(user_num, comp_num); //유저, 컴퓨터 구슬 보유 개수 표시
        while (1) //한 쪽이 구슬 개수가 0이 될 때까지 반복
        {
            get_rand_num(&hide, comp_num); //컴퓨터가 숨길 구슬 개수 랜덤 선택
            get_user_guess(hide, &guess, &result); //컴퓨터가 숨긴 개수 추측
            change_marble_num(&user_num, &comp_num, hide, result); //추측 성공 여부에 따른 구슬 개수 변경
            print_marble_status(user_num, comp_num); //유저, 컴퓨터 구슬 보유 개수 표시
            if (user_num == 0 || comp_num == 0) //한 쪽이 구슬 개수가 0이 되면
            {
                if (comp_num == 0) //컴퓨터의 구슬 개수가 0일 때
                {
                    win_num++; //유저가 이긴 횟수 +1
                }
                win_or_lose(user_num, comp_num, &next, win_num, game); //게임 승패 출력
                if (next == 'y') //유저가 다음 판을 진행하기로 하면
                {
                    break; // 안쪽 반복문을 종료하고 바깥 반복문부터 다시 실행
                }
                else //유저가 종료하기로 하면
                {
                    the_end(win_num, game); //게임 종료 안내
                    return 0; //프로그램 종료
                }
            }
            get_user_choice(&hide, user_num, &result, &guess); //유저가 숨길 구슬 개수 선택
            change_marble_num(&comp_num, &user_num, hide, result); //추측 성공 여부에 따른 구슬 개수 변경
            print_marble_status(user_num, comp_num); //유저, 컴퓨터 구슬 보유 개수 표시
            if (user_num == 0 || comp_num == 0) //한 쪽이 구슬 개수가 0이 되면
            {
                if (comp_num == 0) //컴퓨터의 구슬 개수가 0일 때
                {
                    win_num++; //유저가 이긴 횟수 +1
                }
                win_or_lose(user_num, comp_num, &next, win_num, game); //게임 승패 출력
                if (next == 'y') //유저가 다음 판을 진행하기로 하면
                {
                    break; // 안쪽 반복문을 종료하고 바깥 반복문부터 다시 실행
                }
                else //유저가 종료하기로 하면
                {
                    the_end(win_num, game); //게임 종료 안내
                    return 0; //프로그램 종료
                }
            }
        }
    }
}

void draw_line() //사용자 정의 함수(선 긋기)
{
    int line; //변수 line = ▩ 개수

    for (line = 1; line <= 20; line++) //▩ 20개 출력
    {
        printf("▩");
    }
    printf("\n");
}

void print_marble_status(int n1, int n2) //사용자 정의 함수(유저, 컴퓨터 구슬 보유 개수 표시) / n1 = 유저 보유 구슬 개수, n2 = 컴퓨터 보유 구슬 개수
{
    printf("----------------------------------------\n");
    printf("USER: ● (%d)\n", n1); //유저 구슬 색깔과 개수 표시
    printf("COMP: ○ (%d)\n", n2); //컴퓨터 구슬 색깔과 개수 표시

    if (n1 <= n2) //유저의 구슬 개수가 컴퓨터의 구슬 개수보다 적거나 같다면
    {
        for (n1 = 0; n1 < 40 - n2; n1++) //유저 구슬 개수만큼 표시
        {
            printf("●");
        }
        for (n2 = 0; n2 < 20 - n1; n2++) //한 줄에 20개씩 표시하기 위해 첫번째줄 20개 중 유저 구슬 개수만큼 표시하고 남은 개수만큼 컴퓨터 구슬로 표시
        {
            printf("○");
        }
        printf("\n");
        for (n2 = 1; n2 <= 20; n2++) //두번째줄 모두 컴퓨터 구슬로 20개 표시
        {
            printf("○");
        }
        printf("\n");
        printf("----------------------------------------\n");
    }
    else if (n1 > n2) //유저의 구슬 개수가 컴퓨터의 구슬 개수보다 많다면
    {
        for (n1 = 1; n1 <= 20; n1++) //첫번째줄 모두 유저 구슬로 20개 표시
        {
            printf("●");
        }
        printf("\n"); //유저 구슬 개수에서 첫번째줄 20개를 표시하고 남은 개수만큼 유저 구슬 표시
        for (n1 = 0; n1 < 20 - n2; n1++)
        {
            printf("●");
        }
        for (n2 = 0; n2 < 20 - n1; n2++) //컴퓨터 구슬 개수만큼 표시
        {
            printf("○");
        }
        printf("\n");
        printf("----------------------------------------\n");
    }
}

int get_rand_num(int* a, int b) //사용자 정의 함수(컴퓨터가 최소 1개에서 최대 자신이 보유하고 있는 구슬 개수 사이의 숨길 구슬 개수 랜덤 선택) / a = 컴퓨터가 숨길 구슬 개수, b = 컴퓨터 보유 구슬 개수
{
    *a = rand() % b + 1;
}

int get_user_guess(int a, int* b, int* c) //사용자 정의 함수(컴퓨터가 숨긴 구슬 개수를 3으로 나눈 나머지, 즉 0, 1, 2 중에 추측하여 하나 선택) / a = 컴퓨터가 숨긴 구슬 개수, b = 유저의 추측값, c = 결과값
{
    printf("\nIt's your turn to guess!\n"); //추측할 차례 안내문 출력
    printf("\nGuess 0, 1, or 2: ");
    scanf("%d", b); //유저의 추측값 입력

    if (*b == 0 || *b == 1 || *b == 2) //유저가 0, 1, 2 중의 값을 입력하면
    {
        is_valid_num(a, *b, c); //추측 성공 여부 확인
    }
    else //유저가 옳지 않은 값을 입력하면
    {
        while (1) //올바른 값을 입력할 때까지 반복
        {
            printf("That is a wrong input!\n"); //옳지 않은 값을 입력했다는 안내문 출력
            printf("Please guess 0, 1, or 2: ");
            scanf("%d", b); //유저의 추측값 다시 입력

            if (*b == 0 || *b == 1 || *b == 2) //올바른 값을 입력하면
            {
                break; //반복문 종료
            }
        }
        is_valid_num(a, *b, c); //추측 성공 여부 확인
    }

    if (*c == 1) //결과값이 1이면(유저가 추측에 성공하면)
    {
        printf("\nYou guessed correctly!\n"); //추측 성공 안내문 출력
        printf("The computer hid %d marbles.\n\n", a); //컴퓨터가 숨긴 구슬 개수 표시
    }
    else if (*c == 0) //결과값이 0이면(유저가 추측에 실패하면)
    {
        printf("\nYou guessed incorrectly...\n"); //추측 실패 안내문 출력
        printf("The computer hid %d marbles.\n", a); //컴퓨터가 숨긴 구슬 개수 표시
        printf("The correct guess would have been %d\n\n", (int)a % 3); //추측을 성공하기 위한 정답 출력
    }
}

int is_valid_num(int a, int b, int* c) //사용자 정의 함수(추측 성공 여부 확인) / a = 숨긴 구슬 개수, b = 추측값, c = 결과값
{
    if (b == (int)a % 3) //추측에 성공하면
    {
        *c = 1; //결과값으로 1 출력
    }
    else //추측에 실패하면
    {
        *c = 0; //결과값으로 0 출력
    }
}

void change_marble_num(int* n1, int* n2, int a, int c) //사용자 정의 함수(승패에 따른 구슬 개수 변경) / n1 = 유저 보유 구슬 개수, n2 = 컴퓨터 보유 구슬 개수, a = 숨긴 구슬 개수, c = 결과값
{
    if (c == 1) //결과값이 1이면(추측에 성공하면)
    {
        *n1 = *n1 + a; //숨긴 개수만큼 유저의 구슬 개수에서 더함
        *n2 = *n2 - a; //숨긴 개수만큼 컴퓨터의 구슬 개수에서 뺌
        if (*n2 < 0) //계산 후 컴퓨터의 구슬 개수가 0 미만이면
        {
            *n1 = 40; //유저 구슬 개수 40개로 표시
            *n2 = 0; //컴퓨터 구슬 개수 0개로 표시
        }
    }
    else if (c == 0) //결과값이 0이면(추측에 실패하면)
    {
        *n1 = *n1 - a; //숨긴 개수만큼 유저의 구슬 개수에서 뺌
        *n2 = *n2 + a; //숨긴 개수만큼 컴퓨터의 구슬 개수에서 더함
        if (*n1 < 0) //계산 후 유저의 구슬 개수가 0 미만이면
        {
            *n1 = 0; //유저 구슬 개수 0개로 표시
            *n2 = 40; //컴퓨터 구슬 개수 40개로 표시
        }
    }
}

int get_user_choice(int* a, int b, int* c, int* d) //사용자 정의 함수(유저가 최소 1개에서 최대 자신이 보유하고 있는 구슬 개수 사이의 숨길 개수 선택) / a = 유저가 숨길 구슬 개수, b = 유저 보유 구슬 개수, c = 결과값, d = 컴퓨터의 추측값
{
    printf("It's the computer's turn to guess!\n"); //숨길 차례 안내문 출력
    printf("\nHow many marbles would you like to hide? "); //숨길 개수 물어보는 안내문 출력
    scanf("%d", a); //숨길 구슬 개수 입력

    if (*a >= 1 && *a <= b) //유저가 최소 1에서 최대 자신이 보유하고 있는 구슬 개수 사이의 값을 입력하면(올바른 값을 입력하면)
    {
        get_computer_guess(d); //컴퓨터가 0, 1, 2 중 랜덤 선택
        is_valid_num(*a, *d, c); //추측 성공 여부 확인
    }
    else //유저가 옳지 않은 값을 입력하면
    {
        while (1) //올바른 값을 입력할 때까지 반복
        {
            printf("That is a wrong input!\n"); //옳지 않은 값을 입력했다는 안내문 출력
            printf("Please select a number between 1 and %d: ", b);
            scanf("%d", a); //숨길 구슬 개수 다시 입력

            if (*a >= 1 && *a <= b) //올바른 값을 입력하면
            {
                break; //반복문 종료
            }
        }
        get_computer_guess(d); //컴퓨터가 0, 1, 2 중 랜덤 선택
        is_valid_num(*a, *d, c); //추측 성공 여부 확인
    }

    if (*c == 1) //결과값이 1이면(컴퓨터가 추측에 성공하면)
    {
        printf("\nThe computer guessed %d.\n", *d); //컴퓨터의 추측값 표시
        printf("The computer guessed correctly...\n\n"); //추측 성공 안내문 표시
    }
    else if (*c == 0) //결과값이 0이면(컴퓨터가 추측에 실패하면)
    {
        printf("\nThe computer guessed %d.\n", *d); //컴퓨터의 추측값 표시
        printf("The computer guessed incorrectly!\n"); //추측 실패 안내문 표시
        printf("The correct guess would have been %d.\n\n", (int)*a % 3); //추측을 성공하기 위한 정답 출력
    }
}

int get_computer_guess(int* a) //사용자 정의 함수(컴퓨터가 0, 1, 2 중 랜덤 선택) / a = 컴퓨터의 추측값
{
    *a = rand() % 3;
}

int win_or_lose(int n1, int n2, char* a, int b, int c) //사용자 정의 함수(게임 승패 출력) / n1 = 유저 보유 구슬 개수, n2 = 컴퓨터 보유 구슬 개수, a = 다음 판 진행 여부, b = 유저가 이긴 횟수, c = 진행한 게임 판 수
{
    if (n1 == 0) //유저의 구슬 개수가 0이면
    {
        printf("GAME OVER!\n"); //게임 종료 안내문 출력
        printf("You have lost to the computer :(\n"); //컴퓨터에게 졌다는 안내문 출력
        if (c == 9) //게임이 9판째면
        {
            the_end(b, c); //게임 종료
            *a = 'y'; //다음 판 진행 여부를 강제 y로 입력하여 메인 함수로 돌아갔을 때 안쪽 반복문이 종료되도록 설정
            return;
        }
    }
    else if (n2 == 0) //컴퓨터의 구슬 개수가 0이면
    {
        printf("GAME OVER!\n"); //게임 종료 안내문 출력
        printf("You have won! :)\n"); //유저가 이겼다는 안내문 출력
        if (c == 9) //게임이 9판째면
        {
            the_end(b, c); //게임 종료
            *a = 'y'; //다음 판 진행 여부를 강제 y로 입력하여 메인 함수로 돌아갔을 때 안쪽 반복문이 종료되도록 설정
            return;
        }
    }
    printf("\nWould you like to play again?\n"); //다음 판 진행 여부 물어보는 안내문 출력
    printf("Type 'y' to play again: ");
    getchar(); //입력 버퍼 제거
    scanf("%c", a); //다음 판 진행 여부 입력
    return;
}

int the_end(int a, int b) //사용자 정의 함수(게임 종료) / a = 유저가 이긴 횟수, b = 진행한 게임 판 수
{
    printf("\n");
    draw_line();
    printf("\n");
    printf("You have won %d games out of %d!\n", a, b); //게임 진행 판 수 중에 유저가 이긴 판 수 안내문 출력
    printf("Thank You for playing! Bye~!\n\n"); //게임 종료 인사말 출력
}