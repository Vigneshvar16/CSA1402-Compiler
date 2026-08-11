/*
 * Lab Program 18
 * Write a C program to implement the back end of the compiler: given
 * a series of three address code statements of the form
 *   result = operand1 op operand2
 * generate simple target (assembly-like) code using a single
 * register per statement.
 */
#include <stdio.h>
#include <string.h>

#define MAX_LINES 20
#define MAX_LEN 50

int main(void)
{
    int n, i;
    char lines[MAX_LINES][MAX_LEN];

    printf("Enter the number of three address code statements: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_LINES) {
        printf("Invalid input.\n");
        return 0;
    }
    while (getchar() != '\n'); /* consume newline */

    printf("Enter each statement as  result=operand1opoperand2  (no spaces),\n");
    printf("e.g.  a=b+c\n");
    for (i = 0; i < n; i++) {
        printf("Statement %d: ", i + 1);
        if (fgets(lines[i], sizeof(lines[i]), stdin) == NULL) {
            lines[i][0] = '\0';
        } else {
            int len = (int)strlen(lines[i]);
            if (len > 0 && lines[i][len - 1] == '\n') lines[i][len - 1] = '\0';
        }
    }

    printf("\nGenerated target code:\n\n");
    for (i = 0; i < n; i++) {
        char result[20], op1[20], op2[20], opChar = 0;
        int eq = -1, opPos = -1, j;
        int len = (int)strlen(lines[i]);

        for (j = 0; j < len; j++) {
            if (lines[i][j] == '=') { eq = j; break; }
        }
        if (eq == -1) {
            printf("Skipping invalid statement: %s\n", lines[i]);
            continue;
        }
        for (j = eq + 1; j < len; j++) {
            if (strchr("+-*/", lines[i][j]) != NULL) { opPos = j; opChar = lines[i][j]; break; }
        }
        if (opPos == -1) {
            printf("Skipping invalid statement: %s\n", lines[i]);
            continue;
        }

        strncpy(result, lines[i], eq); result[eq] = '\0';
        strncpy(op1, lines[i] + eq + 1, opPos - eq - 1); op1[opPos - eq - 1] = '\0';
        strcpy(op2, lines[i] + opPos + 1);

        printf("; %s = %s %c %s\n", result, op1, opChar, op2);
        printf("MOV %s, R%d\n", op1, i);
        switch (opChar) {
            case '+': printf("ADD %s, R%d\n", op2, i); break;
            case '-': printf("SUB %s, R%d\n", op2, i); break;
            case '*': printf("MUL %s, R%d\n", op2, i); break;
            case '/': printf("DIV %s, R%d\n", op2, i); break;
        }
        printf("MOV R%d, %s\n\n", i, result);
    }

    return 0;
}

/*
Sample Input:
2
a=b+c
d=n*d

Sample Output:
Generated target code:

; a = b + c
MOV b, R0
ADD c, R0
MOV R0, a

; d = n * d
MOV n, R1
MUL d, R1
MOV R1, d
*/
