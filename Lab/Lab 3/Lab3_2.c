#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

char upperToLower(char c);
int getPosition(char c);

int main(void)
{
	char c, lower, position;

	printf("Input a character in Uppercase: ");
	scanf("%c", &c);

	lower = upperToLower(c);
	position = getPosition(c);

	printf("Lowercase of Entered character is %c\n", lower);
	printf("Position of '%c' in English Alphabets is %d\n", lower, position);

	return 0;
}

char upperToLower(char c)
{
	return c + 32;
}

int getPosition(char c)
{
	return c - 64;
}