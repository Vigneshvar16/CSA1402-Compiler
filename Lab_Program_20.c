/*
 * Lab Program 20
 * Write a C program to compute TRAILING() - used in operator
 * precedence parsing - for the given grammar:
 *   E -> E + T | T
 *   T -> T * F | F
 *   F -> ( E ) | id
 *
 * A terminal 'a' is in TRAILING(A) if A can derive a sentential form
 * that ends with 'a', or ends with a non-terminal whose TRAILING set
 * contains 'a' (standard for operator precedence grammars, which
 * never have two adjacent non-terminals in any production).
 *
 * Fixed point rule used for a production  A -> Y1 Y2 ... Yk :
 *   - if Yk is a terminal, add Yk to TRAILING(A)
 *   - if Yk is a non-terminal, add all of TRAILING(Yk) to TRAILING(A);
 *     additionally, if there is a Y(k-1) and it is a terminal, add it
 *     too
 *
 * Enter each production as LHS=RHS (no spaces), e.g. E=E+T
 * Non-terminals must be UPPERCASE letters, "i" is used for id.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 20
#define MAX_LEN 20
#define MAX_SET 30

char lhs[MAX_PROD];
char rhs[MAX_PROD][MAX_LEN];
int numProd = 0;

char trailingSet[128][MAX_SET];

int addSymbol(char *set, char sym)
{
    int k;
    for (k = 0; set[k] != '\0'; k++) {
        if (set[k] == sym) return 0;
    }
    set[k] = sym;
    set[k + 1] = '\0';
    return 1;
}

int addSet(char *dest, const char *src)
{
    int i, changed = 0;
    for (i = 0; src[i] != '\0'; i++) {
        if (addSymbol(dest, src[i])) changed = 1;
    }
    return changed;
}

int isNonTerminal(char c) { return isupper((unsigned char)c); }

int main(void)
{
    int i;

    printf("Enter number of productions: ");
    if (scanf("%d", &numProd) != 1 || numProd <= 0 || numProd > MAX_PROD) {
        printf("Invalid input.\n");
        return 0;
    }

    printf("Enter productions as LHS=RHS (e.g. E=E+T):\n");
    for (i = 0; i < numProd; i++) {
        char buf[30];
        printf("Production %d: ", i + 1);
        scanf("%29s", buf);
        lhs[i] = buf[0];
        strncpy(rhs[i], buf + 2, MAX_LEN - 1);
        rhs[i][MAX_LEN - 1] = '\0';
    }

    for (i = 0; i < 128; i++) trailingSet[i][0] = '\0';

    {
        int changed = 1, pass;
        for (pass = 0; changed && pass < numProd + 5; pass++) {
            changed = 0;
            for (i = 0; i < numProd; i++) {
                char A = lhs[i];
                int len = (int)strlen(rhs[i]);
                char yk, ykm1;
                if (len == 0) continue;
                yk = rhs[i][len - 1];
                ykm1 = (len >= 2) ? rhs[i][len - 2] : '\0';

                if (!isNonTerminal(yk)) {
                    char tmp[2] = { yk, '\0' };
                    if (addSet(trailingSet[(unsigned char)A], tmp)) changed = 1;
                } else {
                    if (addSet(trailingSet[(unsigned char)A], trailingSet[(unsigned char)yk])) changed = 1;
                    if (ykm1 != '\0' && !isNonTerminal(ykm1)) {
                        char tmp[2] = { ykm1, '\0' };
                        if (addSet(trailingSet[(unsigned char)A], tmp)) changed = 1;
                    }
                }
            }
        }
    }

    printf("\nTRAILING sets:\n");
    {
        int printed[128] = { 0 };
        for (i = 0; i < numProd; i++) {
            char A = lhs[i];
            if (printed[(unsigned char)A]) continue;
            printed[(unsigned char)A] = 1;
            printf("TRAILING(%c) = { ", A);
            {
                int k;
                for (k = 0; trailingSet[(unsigned char)A][k] != '\0'; k++) {
                    printf("%c ", trailingSet[(unsigned char)A][k]);
                }
            }
            printf("}\n");
        }
    }

    return 0;
}

/*
Sample Input:
6
E=E+T
E=T
T=T*F
T=F
F=(E)
F=i

Sample Output:
TRAILING sets:
TRAILING(E) = { + * ) i }
TRAILING(T) = { * ) i }
TRAILING(F) = { ) i }
*/
