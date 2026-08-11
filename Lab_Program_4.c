/*
 * Lab Program 4
 * Design a Lexical Analyzer to validate operators: recognize
 * relational, logical, assignment and arithmetic operators using C.
 */
#include <stdio.h>
#include <string.h>

#define MAX_LEN 10

int main(void)
{
    char s[MAX_LEN];
    int len;

    printf("Enter an operator (e.g. +, -, *, /, ==, <=, >=, !=, &&, ||):\n");
    if (fgets(s, sizeof(s), stdin) == NULL) {
        printf("No input read.\n");
        return 0;
    }
    len = (int)strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        printf("No operator entered.\n");
        return 0;
    }

    switch (s[0]) {
        case '>':
            if (len > 1 && s[1] == '=') printf("Relational operator: Greater than or equal to\n");
            else printf("Relational operator: Greater than\n");
            break;
        case '<':
            if (len > 1 && s[1] == '=') printf("Relational operator: Less than or equal to\n");
            else printf("Relational operator: Less than\n");
            break;
        case '=':
            if (len > 1 && s[1] == '=') printf("Relational operator: Equal to\n");
            else printf("Assignment operator\n");
            break;
        case '!':
            if (len > 1 && s[1] == '=') printf("Relational operator: Not equal to\n");
            else printf("Logical operator: NOT\n");
            break;
        case '&':
            if (len > 1 && s[1] == '&') printf("Logical operator: AND\n");
            else printf("Bitwise operator: AND\n");
            break;
        case '|':
            if (len > 1 && s[1] == '|') printf("Logical operator: OR\n");
            else printf("Bitwise operator: OR\n");
            break;
        case '+':
            printf("Arithmetic operator: Addition\n");
            break;
        case '-':
            printf("Arithmetic operator: Subtraction\n");
            break;
        case '*':
            printf("Arithmetic operator: Multiplication\n");
            break;
        case '/':
            printf("Arithmetic operator: Division\n");
            break;
        case '%':
            printf("Arithmetic operator: Modulus\n");
            break;
        default:
            printf("Not a recognized operator\n");
    }

    return 0;
}

/*
Sample Input:
<=

Sample Output:
Relational operator: Less than or equal to
*/
