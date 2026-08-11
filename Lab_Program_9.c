/*
 * Lab Program 9
 * Implement a C program to eliminate left recursion from a given CFG.
 *
 * Grammar used for the sample run:
 *   S -> (L) | a
 *   L -> L , S | S
 *
 * For a non-terminal A with productions:
 *   A -> A alpha1 | A alpha2 | ... | beta1 | beta2 | ...
 * (beta_i not starting with A), the standard transformation is:
 *   A  -> beta1 A' | beta2 A' | ...
 *   A' -> alpha1 A' | alpha2 A' | ... | epsilon
 *
 * Enter one non-terminal at a time with ALL of its alternatives
 * separated by '|', e.g.  L=L,S|S
 */
#include <stdio.h>
#include <string.h>

#define MAX_LEN 100
#define MAX_ALT 10

int main(void)
{
    int numNT, n;

    printf("Enter number of non-terminals to check: ");
    if (scanf("%d", &numNT) != 1 || numNT <= 0) {
        printf("Invalid input.\n");
        return 0;
    }

    for (n = 0; n < numNT; n++) {
        char line[MAX_LEN];
        char nonTerminal;
        char alts[MAX_ALT][MAX_LEN];
        int numAlts = 0;
        int i, hasLeftRecursion = 0;
        char alphaList[MAX_ALT][MAX_LEN];
        char betaList[MAX_ALT][MAX_LEN];
        int numAlpha = 0, numBeta = 0;

        printf("\nEnter production %d as A=alt1|alt2|... (e.g. L=L,S|S): ", n + 1);
        scanf(" %99s", line);

        nonTerminal = line[0];
        {
            /* split line+2 (after "A=") on '|' */
            char *token = strtok(line + 2, "|");
            while (token != NULL && numAlts < MAX_ALT) {
                strcpy(alts[numAlts], token);
                numAlts++;
                token = strtok(NULL, "|");
            }
        }

        for (i = 0; i < numAlts; i++) {
            if (alts[i][0] == nonTerminal) {
                hasLeftRecursion = 1;
                strcpy(alphaList[numAlpha], alts[i] + 1); /* part after A */
                numAlpha++;
            } else {
                strcpy(betaList[numBeta], alts[i]);
                numBeta++;
            }
        }

        printf("Production: %c -> ", nonTerminal);
        for (i = 0; i < numAlts; i++) printf("%s%s", alts[i], (i < numAlts - 1) ? " | " : "\n");

        if (!hasLeftRecursion) {
            printf("%c is NOT left recursive. No change needed.\n", nonTerminal);
            continue;
        }

        if (numBeta == 0) {
            printf("%c is left recursive in every alternative and cannot be reduced\n", nonTerminal);
            printf("(every alternative starts with %c, so there is no base case).\n", nonTerminal);
            continue;
        }

        printf("%c is left recursive. Eliminating left recursion:\n", nonTerminal);
        printf("%c  -> ", nonTerminal);
        for (i = 0; i < numBeta; i++) {
            printf("%s%c'%s", betaList[i], nonTerminal, (i < numBeta - 1) ? " | " : "\n");
        }
        printf("%c' -> ", nonTerminal);
        for (i = 0; i < numAlpha; i++) {
            printf("%s%c'%s", alphaList[i], nonTerminal, " | ");
        }
        printf("epsilon\n");
    }

    return 0;
}

/*
Sample Input:
2
S=(L)|a
L=L,S|S

Sample Output:
Production: S -> (L) | a
S is NOT left recursive. No change needed.

Production: L -> L,S | S
L is left recursive. Eliminating left recursion:
L  -> SL'
L' -> ,SL' | epsilon
*/
