/*
 * Lab Program 14
 * Implement the concept of Shift-Reduce parsing in C, for the grammar:
 *   E -> E + E | E * E | id
 *
 * "id" is represented by any single lower-case letter. The parser
 * shifts input symbols onto a stack and reduces the top of the stack
 * whenever it matches the right hand side of a production.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 50

char stack[MAX_LEN];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop(void) { return stack[top--]; }

void printState(const char *input, int ip, const char *action)
{
    int i;
    printf("$");
    for (i = 0; i <= top; i++) printf("%c", stack[i]);
    printf("\t\t");
    for (i = ip; input[i] != '\0'; i++) printf("%c", input[i]);
    printf("$\t\t%s\n", action);
}

/* Try one reduction on the top of the stack. Returns 1 if a reduction
   was made, 0 otherwise. */
int tryReduce(void)
{
    if (top >= 0 && islower((unsigned char)stack[top])) {
        stack[top] = 'E';
        return 1;
    }
    if (top >= 2 && stack[top - 2] == 'E' &&
        (stack[top - 1] == '+' || stack[top - 1] == '*') && stack[top] == 'E') {
        char op = stack[top - 1];
        top -= 2;
        stack[top] = 'E';
        (void)op;
        return 1;
    }
    return 0;
}

int main(void)
{
    char input[MAX_LEN];
    int len, ip = 0;

    printf("Grammar: E -> E + E | E * E | id\n");
    printf("Enter the input string (letters for id, + and * only, no spaces):\n");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("No input read.\n");
        return 0;
    }
    len = (int)strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    printf("\nStack\t\tInput\t\tAction\n");
    printState(input, ip, "--");

    while (ip < len) {
        push(input[ip]);
        ip++;
        {
            char action[20];
            sprintf(action, "Shift '%c'", stack[top]);
            printState(input, ip, action);
        }
        while (tryReduce()) {
            printState(input, ip, "Reduce");
        }
    }

    if (top == 0 && stack[0] == 'E') {
        printf("\nString ACCEPTED by the grammar.\n");
    } else {
        printf("\nString NOT accepted by the grammar.\n");
    }

    return 0;
}

/*
Sample Input:
a+b*c

Sample Output:
Stack           Input           Action
$                       a+b*c$          --
$a                      +b*c$           Shift 'a'
$E                      +b*c$           Reduce
$E+                     b*c$            Shift '+'
$E+b                    *c$             Shift 'b'
$E+E                    *c$             Reduce
$E                      *c$             Reduce
$E*                     c$              Shift '*'
$E*c                    $               Shift 'c'
$E*E                    $               Reduce
$E                      $               Reduce

String ACCEPTED by the grammar.

Note: this simple demonstration reduces as soon as a right hand side
is found on top of the stack, so it does not encode operator
precedence between + and * (a real precedence based shift-reduce
parser would consult a precedence table before deciding to reduce).
*/
