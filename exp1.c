#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[100];
    int i = 0;

    printf("Enter an expression: ");
    fgets(str, sizeof(str), stdin);

    printf("\nIdentifiers:\n");
    i = 0;
    while (str[i] != '\0') {
        if (isalpha(str[i]) || str[i] == '_') {
            while (isalnum(str[i]) || str[i] == '_') {
                printf("%c", str[i]);
                i++;
            }
            printf("\n");
        } else {
            i++;
        }
    }

    printf("\nConstants:\n");
    i = 0;
    while (str[i] != '\0') {
        if (isdigit(str[i])) {
            while (isdigit(str[i])) {
                printf("%c", str[i]);
                i++;
            }
            printf("\n");
        } else {
            i++;
        }
    }

    printf("\nOperators:\n");
    i = 0;
    while (str[i] != '\0') {
        if (strchr("+-*/=%<>", str[i])) {
            printf("%c\n", str[i]);
        }
        i++;
    }

    return 0;
}