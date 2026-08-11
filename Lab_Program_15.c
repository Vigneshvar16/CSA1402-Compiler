/*
 * Lab Program 15
 * Write a C program to implement operator precedence parsing for the
 * grammar:
 *   E -> E + E | E - E | E * E | E / E | E ^ E | ( E ) | id
 *
 * "id" is represented by the letter i. A standard operator precedence
 * table is used to decide whether to shift or reduce at each step.
 */
#include <stdio.h>
#include <string.h>

#define MAX 100

/* symbols handled, in this fixed order, used to index the table */
const char symbols[] = "+-*/^i()$";

/* precedence table: '<' means the stack top yields to the input
   symbol (shift), '>' means the stack top takes precedence (reduce),
   '=' means equal precedence (used for matching parentheses), and
   ' ' means the combination is invalid. Rows = stack top, Cols = input. */
const char table[9][9] = {
    /*        +    -    *    /    ^    i    (    )    $  */
    /* + */ {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
    /* - */ {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
    /* * */ {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    /* / */ {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    /* ^ */ {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    /* i */ {'>', '>', '>', '>', '>', ' ', ' ', '>', '>'},
    /* ( */ {'<', '<', '<', '<', '<', '<', '<', '=', ' '},
    /* ) */ {'>', '>', '>', '>', '>', ' ', ' ', '>', '>'},
    /* $ */ {'<', '<', '<', '<', '<', '<', '<', ' ', '='},
};

int indexOf(char c)
{
    int i;
    for (i = 0; symbols[i] != '\0'; i++) {
        if (symbols[i] == c) return i;
    }
    return -1;
}

char stack[MAX];
int top = -1;

void push(char c) { stack[++top] = c; }
char peekTerminal(void)
{
    /* topmost terminal symbol on the stack (skip non-terminals E if any) */
    int i;
    for (i = top; i >= 0; i--) {
        if (indexOf(stack[i]) != -1) return stack[i];
    }
    return '$';
}

void printStep(const char *input, int ip, const char *action)
{
    int i;
    for (i = 0; i <= top; i++) printf("%c", stack[i]);
    printf("\t\t");
    printf("%s", input + ip);
    printf("\t\t%s\n", action);
}

int main(void)
{
    char raw[MAX], input[MAX];
    int len, i, ip = 0;

    printf("Grammar: E -> E+E | E-E | E*E | E/E | E^E | (E) | id\n");
    printf("Enter the expression using 'i' for id (e.g. i+i*i):\n");
    if (fgets(raw, sizeof(raw), stdin) == NULL) {
        printf("No input read.\n");
        return 0;
    }
    len = (int)strlen(raw);
    if (len > 0 && raw[len - 1] == '\n') raw[--len] = '\0';

    strcpy(input, raw);
    input[len] = '$';
    input[len + 1] = '\0';
    len++;

    for (i = 0; i < len; i++) {
        if (indexOf(input[i]) == -1 && !(input[i] >= 'a' && input[i] <= 'z')) {
            printf("Invalid character '%c' in input.\n", input[i]);
            return 0;
        }
    }

    push('$');
    printf("\nStack\t\tInput\t\tAction\n");
    printStep(input, ip, "--");

    while (1) {
        char topTerm = peekTerminal();
        char cur = input[ip];
        int r = indexOf(topTerm), c = indexOf(cur);
        char rel = (r == -1 || c == -1) ? ' ' : table[r][c];

        if (topTerm == '$' && cur == '$') {
            printf("\nString ACCEPTED by the grammar.\n");
            break;
        }

        if (rel == '<' || rel == '=') {
            push(cur);
            ip++;
            printStep(input, ip, "Shift");
        } else if (rel == '>') {
            /* pop the handle: keep popping terminals/E until we hit a
               symbol whose relation with the new top is '<' (or stack
               empties) - simplified handle popping for id, (E), and
               E op E patterns */
            if (top >= 0 && stack[top] == 'i') {
                stack[top] = 'E';
            } else if (top >= 2 && stack[top] == ')' && stack[top - 2] == '(') {
                stack[top - 2] = 'E';
                top -= 2;
            } else if (top >= 2 && stack[top - 2] == 'E' && stack[top] == 'E' &&
                       strchr("+-*/^", stack[top - 1]) != NULL) {
                stack[top - 2] = 'E';
                top -= 2;
            } else if (top >= 0 && stack[top] == 'E') {
                /* nothing further to reduce right now */
                printf("\nParsing error: cannot reduce.\n");
                break;
            } else {
                printf("\nString NOT accepted (parsing error).\n");
                break;
            }
            printStep(input, ip, "Reduce");
        } else {
            printf("\nString NOT accepted (no precedence relation).\n");
            break;
        }
    }

    return 0;
}

/*
Sample Input:
i+i*i

Sample Output (abridged):
Stack           Input           Action
$               i+i*i$          --
$i              +i*i$           Shift
$E              +i*i$           Reduce
$E+             i*i$            Shift
$E+i            *i$             Shift
$E+E            *i$             Reduce
$E+E*           i$              Shift
$E+E*i          $               Shift
$E+E*E          $               Reduce
$E+E            $               Reduce
$E              $               Reduce

String ACCEPTED by the grammar.
*/
