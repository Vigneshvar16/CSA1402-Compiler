/*
 * Lab Program 7
 * Write a C program to find FIRST() - predictive parser - for a
 * given grammar.
 *
 * Grammar used for the sample run:
 *   S -> AaAb | BbBa
 *   A -> epsilon
 *   B -> epsilon
 *
 * Enter each production as  LHS=RHS  (no spaces), e.g.  S=AaAb
 * Non-terminals must be UPPERCASE letters, terminals are any other
 * character. Use $ to represent an epsilon (empty) production.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 20
#define MAX_LEN  20

char lhs[MAX_PROD];
char rhs[MAX_PROD][MAX_LEN];
int numProd = 0;
int visiting[128]; /* recursion guard, indexed by ASCII value of symbol */

void addSymbol(char *result, char sym)
{
    int k;
    for (k = 0; result[k] != '\0'; k++) {
        if (result[k] == sym) return; /* already present */
    }
    result[k] = sym;
    result[k + 1] = '\0';
}

void FIRST(char sym, char *result)
{
    result[0] = '\0';

    if (!isupper((unsigned char)sym)) {
        /* terminal (includes $ for epsilon) */
        addSymbol(result, sym);
        return;
    }

    if (visiting[(unsigned char)sym]) {
        /* avoid infinite recursion on a left recursive / cyclic grammar */
        return;
    }
    visiting[(unsigned char)sym] = 1;

    {
        int i;
        for (i = 0; i < numProd; i++) {
            if (lhs[i] != sym) continue;

            if (rhs[i][0] == '$') {
                addSymbol(result, '$');
            } else {
                int j = 0;
                int nullable = 1;
                while (rhs[i][j] != '\0') {
                    char sub[MAX_LEN];
                    int hasEpsilon = 0, k;

                    FIRST(rhs[i][j], sub);
                    for (k = 0; sub[k] != '\0'; k++) {
                        if (sub[k] == '$') hasEpsilon = 1;
                        else addSymbol(result, sub[k]);
                    }
                    if (!hasEpsilon) { nullable = 0; break; }
                    j++;
                }
                if (nullable) addSymbol(result, '$');
            }
        }
    }

    visiting[(unsigned char)sym] = 0;
}

int main(void)
{
    int i;
    char query, choice;
    char result[MAX_LEN];

    printf("Enter number of productions: ");
    if (scanf("%d", &numProd) != 1 || numProd <= 0 || numProd > MAX_PROD) {
        printf("Invalid number of productions.\n");
        return 0;
    }

    printf("Enter productions in the form LHS=RHS (e.g. S=AaAb), $ for epsilon:\n");
    for (i = 0; i < numProd; i++) {
        char buf[30];
        printf("Production %d: ", i + 1);
        scanf("%29s", buf);
        lhs[i] = buf[0];
        strncpy(rhs[i], buf + 2, MAX_LEN - 1); /* skip "X=" */
        rhs[i][MAX_LEN - 1] = '\0';
    }

    do {
        printf("\nFind FIRST of (enter a single symbol): ");
        scanf(" %c", &query);

        FIRST(query, result);

        printf("FIRST(%c) = { ", query);
        for (i = 0; result[i] != '\0'; i++) printf("%c ", result[i]);
        printf("}\n");

        printf("Press y to continue, any other key to stop: ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}

/*
Sample Input:
4
S=AaAb
S=BbBa
A=$
B=$
S
y
A
y
B
n

Sample Output:
FIRST(S) = { a b }
FIRST(A) = { $ }
FIRST(B) = { $ }
*/
