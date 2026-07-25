#include <stdio.h>

int main()
{
    int num1 = 100;
    float rate = 25.5;
    char ch = 'a';
    int total = 50 + 20;
    int num2 = 30;
    int count = 40;

    printf("Welcome to Compiler Design\n");

    int x = 9;
    int y = 0x12;
    float z = 12.34;

    char str1[] = "Hello";
    char str2[] = "World";

    int _valid = 10;
    int invalid_id = 20;

    float value = 5.6;
    int data = 10 + 5;

    char c = 'x';
    int value3 = 60;

    printf("num1 = %d\n", num1);
    printf("Rate = %.1f\n", rate);
    printf("Character = %c\n", ch);
    printf("Total = %d\n", total);
    printf("num2 = %d\n", num2);
    printf("Count = %d\n", count);
    printf("x = %d\n", x);
    printf("Hex Value (y) = %d\n", y);
    printf("z = %.2f\n", z);
    printf("Strings: %s %s\n", str1, str2);
    printf("_valid = %d\n", _valid);
    printf("invalid_id = %d\n", invalid_id);
    printf("Value = %.1f\n", value);
    printf("Data = %d\n", data);
    printf("Character c = %c\n", c);
    printf("Value3 = %d\n", value3);

    return 0;
}