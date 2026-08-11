/*
 * Lab Program 8
 * Write a C program to find FOLLOW() - predictive parser - for a
 * given grammar.
 *
 * Grammar used for the sample run:
 *   S -> AaAb | BbBa
 *   A -> epsilon
 *   B -> epsilon
 *
 * Enter each production as LHS=RHS (no spaces), e.g. S=AaAb
 * Non-terminals must be UPPERCASE letters, terminals are any other
 * character. Use $ to represent an epsilon (empty) production.
 * The LHS of the FIRST production entered is treated as the start
 * symbol.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 20
#define MAX_LEN  20
#define MAX_SET  30

char lhs[MAX_PROD];
char rhs[MAX_PROD][MAX_LEN];
int numProd = 0;
char startSymbol;

char followSet[128][MAX_SET]; /* indexed by ASCII of the non-terminal */
int visitingFirst[128];

void addSymbol(char *result, char sym)
{
    int k;
    for (k = 0; result[k] != '\0'; k++) {
        if (result[k] == sym) return;
    }
    result[k] = sym;
    result[k + 1] = '\0';
}

/* FIRST of a single grammar symbol */
void FIRST(char sym, char *result)
{
    result[0] = '\0';

    if (!isupper((unsigned char)sym)) {
        addSymbol(result, sym);
        return;
    }

    if (visitingFirst[(unsigned char)sym]) return;
    visitingFirst[(unsigned char)sym] = 1;

    {
        int i;
        for (i = 0; i < numProd; i++) {
            if (lhs[i] != sym) continue;
            if (rhs[i][0] == '$') {
                addSymbol(result, '$');
            } else {
                int j = 0, nullable = 1;
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

    visitingFirst[(unsigned char)sym] = 0;
}

/* FIRST of a string of grammar symbols; sets *nullable if the whole
   string can derive epsilon */
void firstOfString(const char *s, char *result, int *nullable)
{
    int j = 0;
    result[0] = '\0';
    *nullable = 1;

    while (s[j] != '\0') {
        char sub[MAX_LEN];
        int hasEpsilon = 0, k;
        FIRST(s[j], sub);
        for (k = 0; sub[k] != '\0'; k++) {
            if (sub[k] == '$') hasEpsilon = 1;
            else addSymbol(result, sub[k]);
        }
        if (!hasEpsilon) { *nullable = 0; return; }
        j++;
    }
    /* all symbols were nullable (or string was empty) */
}

int addSet(char *setStr, const char *toAdd)
{
    int i, changed = 0;
    for (i = 0; toAdd[i] != '\0'; i++) {
        int k, found = 0;
        for (k = 0; setStr[k] != '\0'; k++) {
            if (setStr[k] == toAdd[i]) { found = 1; break; }
        }
        if (!found) {
            int len = (int)strlen(setStr);
            setStr[len] = toAdd[i];
            setStr[len + 1] = '\0';
            changed = 1;
        }
    }
    return changed;
}

int main(void)
{
    int i;
    char query, choice;

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
        strncpy(rhs[i], buf + 2, MAX_LEN - 1);
        rhs[i][MAX_LEN - 1] = '\0';
        if (i == 0) startSymbol = lhs[0];
    }

    for (i = 0; i < 128; i++) followSet[i][0] = '\0';
    addSymbol(followSet[(unsigned char)startSymbol], '$');

    {
        int changed = 1, pass;
        for (pass = 0; changed && pass < numProd + 5; pass++) {
            changed = 0;
            for (i = 0; i < numProd; i++) {
                char A = lhs[i];
                int len = (int)strlen(rhs[i]);
                int p;
                if (rhs[i][0] == '$') continue;
                for (p = 0; p < len; p++) {
                    char B = rhs[i][p];
                    if (!isupper((unsigned char)B)) continue;

                    {
                        char rest[MAX_LEN];
                        char firstRest[MAX_SET];
                        int nullableRest;
                        strcpy(rest, rhs[i] + p + 1);
                        firstOfString(rest, firstRest, &nullableRest);

                        {
                            char toAdd[MAX_SET];
                            int k, m = 0;
                            for (k = 0; firstRest[k] != '\0'; k++) {
                                if (firstRest[k] != '$') toAdd[m++] = firstRest[k];
                            }
                            toAdd[m] = '\0';
                            if (addSet(followSet[(unsigned char)B], toAdd)) changed = 1;
                        }

                        if (nullableRest) {
                            if (addSet(followSet[(unsigned char)B], followSet[(unsigned char)A])) changed = 1;
                        }
                    }
                }
            }
        }
    }

    do {
        printf("\nFind FOLLOW of (enter a single non-terminal): ");
        scanf(" %c", &query);

        printf("FOLLOW(%c) = { ", query);
        for (i = 0; followSet[(unsigned char)query][i] != '\0'; i++) {
            printf("%c ", followSet[(unsigned char)query][i]);
        }
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
FOLLOW(S) = { $ }
FOLLOW(A) = { a b }
FOLLOW(B) = { b a }
*/
