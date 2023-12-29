#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void draw_line(); //����� ���� �Լ�(�� �߱�)
void print_marble_status(int n1, int n2); //����� ���� �Լ�(����, ��ǻ�� ���� ���� ���� ǥ��)
int get_rand_num(int* a, int b); //����� ���� �Լ�(��ǻ�Ͱ� ���� ���� ���� ���� ����)
int get_user_guess(int a, int* b, int* c); //����� ���� �Լ�(��ǻ�Ͱ� ���� ���� ����)
int is_valid_num(int a, int b, int* c); //����� ���� �Լ�(���� ���� ���� Ȯ��)
void change_marble_num(int* n1, int* n2, int a, int c); //����� ���� �Լ�(���п� ���� ���� ���� ����)
int get_user_choice(int* a, int b, int* c, int* d); //����� ���� �Լ�(������ ���� ���� ���� ����)
int get_computer_guess(int* a); //����� ���� �Լ�(��ǻ�Ͱ� 0, 1, 2 �� ���� ����)
int win_or_lose(int n1, int n2, int* a, int b, int c); //����� ���� �Լ�(���� ���� ���)
int the_end(int a, int b); //����� ���� �Լ�(���� ����)

int main(void) //���� �Լ�
{
    int game = 1; //���� game = ������ ���� �� ��
    int user_num = 20; //���� user_num = ������ �����ϰ� �ִ� ���� ����
    int comp_num = 20; //���� comp_num = ��ǻ�Ͱ� �����ϰ� �ִ� ���� ����
    int hide, guess, result; //���� hide =  ���� ���� ����, ���� guess = ������, ���� result = �����
    char next; //���� next = ���� �� ���� ����
    int win_num = 0; //���� win_num = ������ �̱� Ƚ��

    srand(time(NULL)); //������ ������ �� �ʱ�ȭ

    printf("[CSED101 Assignment 2]\n"); //���� ���� ���
    draw_line();
    printf("�̢�                                �̢�\n");
    printf("�̢�          Marble  Game          �̢�\n"); //���� ���� ���
    printf("�̢�                                �̢�\n");
    draw_line();
    printf("\n Welcome to the Marble Game! Have fun~!\n"); //���� �λ縻 ���
    draw_line();

    for (game = 1; game <= 9; game++) //1��° �Ǻ��� 9��° �Ǳ��� ���� ����
    {
        user_num = 20; //���� ������ ������ ����, ��ǻ�� ���� ���� 20���� �ʱ�ȭ
        comp_num = 20;
        printf("\n[Game #%d]\n", game); //���� �� �� �ȳ�
        print_marble_status(user_num, comp_num); //����, ��ǻ�� ���� ���� ���� ǥ��
        while (1) //�� ���� ���� ������ 0�� �� ������ �ݺ�
        {
            get_rand_num(&hide, comp_num); //��ǻ�Ͱ� ���� ���� ���� ���� ����
            get_user_guess(hide, &guess, &result); //��ǻ�Ͱ� ���� ���� ����
            change_marble_num(&user_num, &comp_num, hide, result); //���� ���� ���ο� ���� ���� ���� ����
            print_marble_status(user_num, comp_num); //����, ��ǻ�� ���� ���� ���� ǥ��
            if (user_num == 0 || comp_num == 0) //�� ���� ���� ������ 0�� �Ǹ�
            {
                if (comp_num == 0) //��ǻ���� ���� ������ 0�� ��
                {
                    win_num++; //������ �̱� Ƚ�� +1
                }
                win_or_lose(user_num, comp_num, &next, win_num, game); //���� ���� ���
                if (next == 'y') //������ ���� ���� �����ϱ�� �ϸ�
                {
                    break; // ���� �ݺ����� �����ϰ� �ٱ� �ݺ������� �ٽ� ����
                }
                else //������ �����ϱ�� �ϸ�
                {
                    the_end(win_num, game); //���� ���� �ȳ�
                    return 0; //���α׷� ����
                }
            }
            get_user_choice(&hide, user_num, &result, &guess); //������ ���� ���� ���� ����
            change_marble_num(&comp_num, &user_num, hide, result); //���� ���� ���ο� ���� ���� ���� ����
            print_marble_status(user_num, comp_num); //����, ��ǻ�� ���� ���� ���� ǥ��
            if (user_num == 0 || comp_num == 0) //�� ���� ���� ������ 0�� �Ǹ�
            {
                if (comp_num == 0) //��ǻ���� ���� ������ 0�� ��
                {
                    win_num++; //������ �̱� Ƚ�� +1
                }
                win_or_lose(user_num, comp_num, &next, win_num, game); //���� ���� ���
                if (next == 'y') //������ ���� ���� �����ϱ�� �ϸ�
                {
                    break; // ���� �ݺ����� �����ϰ� �ٱ� �ݺ������� �ٽ� ����
                }
                else //������ �����ϱ�� �ϸ�
                {
                    the_end(win_num, game); //���� ���� �ȳ�
                    return 0; //���α׷� ����
                }
            }
        }
    }
}

void draw_line() //����� ���� �Լ�(�� �߱�)
{
    int line; //���� line = �� ����

    for (line = 1; line <= 20; line++) //�� 20�� ���
    {
        printf("��");
    }
    printf("\n");
}

void print_marble_status(int n1, int n2) //����� ���� �Լ�(����, ��ǻ�� ���� ���� ���� ǥ��) / n1 = ���� ���� ���� ����, n2 = ��ǻ�� ���� ���� ����
{
    printf("----------------------------------------\n");
    printf("USER: �� (%d)\n", n1); //���� ���� ����� ���� ǥ��
    printf("COMP: �� (%d)\n", n2); //��ǻ�� ���� ����� ���� ǥ��

    if (n1 <= n2) //������ ���� ������ ��ǻ���� ���� �������� ���ų� ���ٸ�
    {
        for (n1 = 0; n1 < 40 - n2; n1++) //���� ���� ������ŭ ǥ��
        {
            printf("��");
        }
        for (n2 = 0; n2 < 20 - n1; n2++) //�� �ٿ� 20���� ǥ���ϱ� ���� ù��°�� 20�� �� ���� ���� ������ŭ ǥ���ϰ� ���� ������ŭ ��ǻ�� ������ ǥ��
        {
            printf("��");
        }
        printf("\n");
        for (n2 = 1; n2 <= 20; n2++) //�ι�°�� ��� ��ǻ�� ������ 20�� ǥ��
        {
            printf("��");
        }
        printf("\n");
        printf("----------------------------------------\n");
    }
    else if (n1 > n2) //������ ���� ������ ��ǻ���� ���� �������� ���ٸ�
    {
        for (n1 = 1; n1 <= 20; n1++) //ù��°�� ��� ���� ������ 20�� ǥ��
        {
            printf("��");
        }
        printf("\n"); //���� ���� �������� ù��°�� 20���� ǥ���ϰ� ���� ������ŭ ���� ���� ǥ��
        for (n1 = 0; n1 < 20 - n2; n1++)
        {
            printf("��");
        }
        for (n2 = 0; n2 < 20 - n1; n2++) //��ǻ�� ���� ������ŭ ǥ��
        {
            printf("��");
        }
        printf("\n");
        printf("----------------------------------------\n");
    }
}

int get_rand_num(int* a, int b) //����� ���� �Լ�(��ǻ�Ͱ� �ּ� 1������ �ִ� �ڽ��� �����ϰ� �ִ� ���� ���� ������ ���� ���� ���� ���� ����) / a = ��ǻ�Ͱ� ���� ���� ����, b = ��ǻ�� ���� ���� ����
{
    *a = rand() % b + 1;
}

int get_user_guess(int a, int* b, int* c) //����� ���� �Լ�(��ǻ�Ͱ� ���� ���� ������ 3���� ���� ������, �� 0, 1, 2 �߿� �����Ͽ� �ϳ� ����) / a = ��ǻ�Ͱ� ���� ���� ����, b = ������ ������, c = �����
{
    printf("\nIt's your turn to guess!\n"); //������ ���� �ȳ��� ���
    printf("\nGuess 0, 1, or 2: ");
    scanf("%d", b); //������ ������ �Է�

    if (*b == 0 || *b == 1 || *b == 2) //������ 0, 1, 2 ���� ���� �Է��ϸ�
    {
        is_valid_num(a, *b, c); //���� ���� ���� Ȯ��
    }
    else //������ ���� ���� ���� �Է��ϸ�
    {
        while (1) //�ùٸ� ���� �Է��� ������ �ݺ�
        {
            printf("That is a wrong input!\n"); //���� ���� ���� �Է��ߴٴ� �ȳ��� ���
            printf("Please guess 0, 1, or 2: ");
            scanf("%d", b); //������ ������ �ٽ� �Է�

            if (*b == 0 || *b == 1 || *b == 2) //�ùٸ� ���� �Է��ϸ�
            {
                break; //�ݺ��� ����
            }
        }
        is_valid_num(a, *b, c); //���� ���� ���� Ȯ��
    }

    if (*c == 1) //������� 1�̸�(������ ������ �����ϸ�)
    {
        printf("\nYou guessed correctly!\n"); //���� ���� �ȳ��� ���
        printf("The computer hid %d marbles.\n\n", a); //��ǻ�Ͱ� ���� ���� ���� ǥ��
    }
    else if (*c == 0) //������� 0�̸�(������ ������ �����ϸ�)
    {
        printf("\nYou guessed incorrectly...\n"); //���� ���� �ȳ��� ���
        printf("The computer hid %d marbles.\n", a); //��ǻ�Ͱ� ���� ���� ���� ǥ��
        printf("The correct guess would have been %d\n\n", (int)a % 3); //������ �����ϱ� ���� ���� ���
    }
}

int is_valid_num(int a, int b, int* c) //����� ���� �Լ�(���� ���� ���� Ȯ��) / a = ���� ���� ����, b = ������, c = �����
{
    if (b == (int)a % 3) //������ �����ϸ�
    {
        *c = 1; //��������� 1 ���
    }
    else //������ �����ϸ�
    {
        *c = 0; //��������� 0 ���
    }
}

void change_marble_num(int* n1, int* n2, int a, int c) //����� ���� �Լ�(���п� ���� ���� ���� ����) / n1 = ���� ���� ���� ����, n2 = ��ǻ�� ���� ���� ����, a = ���� ���� ����, c = �����
{
    if (c == 1) //������� 1�̸�(������ �����ϸ�)
    {
        *n1 = *n1 + a; //���� ������ŭ ������ ���� �������� ����
        *n2 = *n2 - a; //���� ������ŭ ��ǻ���� ���� �������� ��
        if (*n2 < 0) //��� �� ��ǻ���� ���� ������ 0 �̸��̸�
        {
            *n1 = 40; //���� ���� ���� 40���� ǥ��
            *n2 = 0; //��ǻ�� ���� ���� 0���� ǥ��
        }
    }
    else if (c == 0) //������� 0�̸�(������ �����ϸ�)
    {
        *n1 = *n1 - a; //���� ������ŭ ������ ���� �������� ��
        *n2 = *n2 + a; //���� ������ŭ ��ǻ���� ���� �������� ����
        if (*n1 < 0) //��� �� ������ ���� ������ 0 �̸��̸�
        {
            *n1 = 0; //���� ���� ���� 0���� ǥ��
            *n2 = 40; //��ǻ�� ���� ���� 40���� ǥ��
        }
    }
}

int get_user_choice(int* a, int b, int* c, int* d) //����� ���� �Լ�(������ �ּ� 1������ �ִ� �ڽ��� �����ϰ� �ִ� ���� ���� ������ ���� ���� ����) / a = ������ ���� ���� ����, b = ���� ���� ���� ����, c = �����, d = ��ǻ���� ������
{
    printf("It's the computer's turn to guess!\n"); //���� ���� �ȳ��� ���
    printf("\nHow many marbles would you like to hide? "); //���� ���� ����� �ȳ��� ���
    scanf("%d", a); //���� ���� ���� �Է�

    if (*a >= 1 && *a <= b) //������ �ּ� 1���� �ִ� �ڽ��� �����ϰ� �ִ� ���� ���� ������ ���� �Է��ϸ�(�ùٸ� ���� �Է��ϸ�)
    {
        get_computer_guess(d); //��ǻ�Ͱ� 0, 1, 2 �� ���� ����
        is_valid_num(*a, *d, c); //���� ���� ���� Ȯ��
    }
    else //������ ���� ���� ���� �Է��ϸ�
    {
        while (1) //�ùٸ� ���� �Է��� ������ �ݺ�
        {
            printf("That is a wrong input!\n"); //���� ���� ���� �Է��ߴٴ� �ȳ��� ���
            printf("Please select a number between 1 and %d: ", b);
            scanf("%d", a); //���� ���� ���� �ٽ� �Է�

            if (*a >= 1 && *a <= b) //�ùٸ� ���� �Է��ϸ�
            {
                break; //�ݺ��� ����
            }
        }
        get_computer_guess(d); //��ǻ�Ͱ� 0, 1, 2 �� ���� ����
        is_valid_num(*a, *d, c); //���� ���� ���� Ȯ��
    }

    if (*c == 1) //������� 1�̸�(��ǻ�Ͱ� ������ �����ϸ�)
    {
        printf("\nThe computer guessed %d.\n", *d); //��ǻ���� ������ ǥ��
        printf("The computer guessed correctly...\n\n"); //���� ���� �ȳ��� ǥ��
    }
    else if (*c == 0) //������� 0�̸�(��ǻ�Ͱ� ������ �����ϸ�)
    {
        printf("\nThe computer guessed %d.\n", *d); //��ǻ���� ������ ǥ��
        printf("The computer guessed incorrectly!\n"); //���� ���� �ȳ��� ǥ��
        printf("The correct guess would have been %d.\n\n", (int)*a % 3); //������ �����ϱ� ���� ���� ���
    }
}

int get_computer_guess(int* a) //����� ���� �Լ�(��ǻ�Ͱ� 0, 1, 2 �� ���� ����) / a = ��ǻ���� ������
{
    *a = rand() % 3;
}

int win_or_lose(int n1, int n2, char* a, int b, int c) //����� ���� �Լ�(���� ���� ���) / n1 = ���� ���� ���� ����, n2 = ��ǻ�� ���� ���� ����, a = ���� �� ���� ����, b = ������ �̱� Ƚ��, c = ������ ���� �� ��
{
    if (n1 == 0) //������ ���� ������ 0�̸�
    {
        printf("GAME OVER!\n"); //���� ���� �ȳ��� ���
        printf("You have lost to the computer :(\n"); //��ǻ�Ϳ��� ���ٴ� �ȳ��� ���
        if (c == 9) //������ 9��°��
        {
            the_end(b, c); //���� ����
            *a = 'y'; //���� �� ���� ���θ� ���� y�� �Է��Ͽ� ���� �Լ��� ���ư��� �� ���� �ݺ����� ����ǵ��� ����
            return;
        }
    }
    else if (n2 == 0) //��ǻ���� ���� ������ 0�̸�
    {
        printf("GAME OVER!\n"); //���� ���� �ȳ��� ���
        printf("You have won! :)\n"); //������ �̰�ٴ� �ȳ��� ���
        if (c == 9) //������ 9��°��
        {
            the_end(b, c); //���� ����
            *a = 'y'; //���� �� ���� ���θ� ���� y�� �Է��Ͽ� ���� �Լ��� ���ư��� �� ���� �ݺ����� ����ǵ��� ����
            return;
        }
    }
    printf("\nWould you like to play again?\n"); //���� �� ���� ���� ����� �ȳ��� ���
    printf("Type 'y' to play again: ");
    getchar(); //�Է� ���� ����
    scanf("%c", a); //���� �� ���� ���� �Է�
    return;
}

int the_end(int a, int b) //����� ���� �Լ�(���� ����) / a = ������ �̱� Ƚ��, b = ������ ���� �� ��
{
    printf("\n");
    draw_line();
    printf("\n");
    printf("You have won %d games out of %d!\n", a, b); //���� ���� �� �� �߿� ������ �̱� �� �� �ȳ��� ���
    printf("Thank You for playing! Bye~!\n\n"); //���� ���� �λ縻 ���
}