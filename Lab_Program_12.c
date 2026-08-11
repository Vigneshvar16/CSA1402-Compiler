/*
 * Lab Program 12
 * Write a C program to construct a recursive descent parser for the
 * given grammar:
 *   E  -> T E'
 *   E' -> + T E' | epsilon
 *   T  -> F T'
 *   T' -> * F T' | epsilon
 *   F  -> ( E ) | id
 *
 * "id" is represented by any single letter (a-z, A-Z).
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

char input[MAX_LEN];
int pos;

int E(void);
int EP(void);
int T(void);
int TP(void);
int F(void);

int E(void)
{
    return T() && EP();
}

int EP(void)
{
    if (input[pos] == '+') {
        pos++;
        return T() && EP();
    }
    return 1; /* epsilon */
}

int T(void)
{
    return F() && TP();
}

int TP(void)
{
    if (input[pos] == '*') {
        pos++;
        return F() && TP();
    }
    return 1; /* epsilon */
}

int F(void)
{
    if (input[pos] == '(') {
        pos++;
        if (!E()) return 0;
        if (input[pos] == ')') {
            pos++;
            return 1;
        }
        return 0;
    } else if (isalpha((unsigned char)input[pos])) {
        pos++;
        return 1;
    }
    return 0;
}

int main(void)
{
    int len;

    printf("Recursive descent parser for the grammar:\n");
    printf("E  -> T E'\n");
    printf("E' -> + T E' | epsilon\n");
    printf("T  -> F T'\n");
    printf("T' -> * F T' | epsilon\n");
    printf("F  -> ( E ) | id\n\n");

    printf("Enter the string to be checked (letters, +, *, ( ) only, no spaces):\n");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("No input read.\n");
        return 0;
    }
    len = (int)strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    pos = 0;
    if (E() && pos == len) {
        printf("\nString is ACCEPTED by the grammar.\n");
    } else {
        printf("\nString is NOT accepted by the grammar.\n");
    }

    return 0;
}

/*
Sample Input:
(a+b)*c

Sample Output:
String is ACCEPTED by the grammar.

Sample Input:
a/c+d

Sample Output:
String is NOT accepted by the grammar.
*/
