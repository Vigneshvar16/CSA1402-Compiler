/*
 * Lab Program 10
 * Implement a C program to eliminate left factoring from a given CFG.
 *
 * Grammar used for the sample run:
 *   S -> iEtS | iEtSeS | a
 *   E -> b
 *
 * For a non-terminal A with alternatives that share a common prefix,
 * the standard transformation factors out the longest common prefix:
 *   A  -> prefix A' | (other alternatives that do not share the prefix)
 *   A' -> (remainder of each alternative that shared the prefix) | epsilon
 *
 * Enter one non-terminal at a time with ALL of its alternatives
 * separated by '|', e.g.  S=iEtS|iEtSeS|a
 */
#include <stdio.h>
#include <string.h>

#define MAX_LEN 100
#define MAX_ALT 10

int commonPrefixLen(const char *a, const char *b)
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i]) i++;
    return i;
}

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
        int numAlts = 0, i;
        int prefixLen;

        printf("\nEnter production %d as A=alt1|alt2|... (e.g. S=iEtS|iEtSeS|a): ", n + 1);
        scanf(" %99s", line);

        nonTerminal = line[0];
        {
            char *token = strtok(line + 2, "|");
            while (token != NULL && numAlts < MAX_ALT) {
                strcpy(alts[numAlts], token);
                numAlts++;
                token = strtok(NULL, "|");
            }
        }

        printf("Production: %c -> ", nonTerminal);
        for (i = 0; i < numAlts; i++) printf("%s%s", alts[i], (i < numAlts - 1) ? " | " : "\n");

        /* find the longest prefix shared by two or more alternatives */
        prefixLen = 0;
        {
            int bestI = -1, bestJ = -1;
            int a, b;
            for (a = 0; a < numAlts; a++) {
                for (b = a + 1; b < numAlts; b++) {
                    int len = commonPrefixLen(alts[a], alts[b]);
                    if (len > prefixLen) {
                        prefixLen = len;
                        bestI = a;
                        bestJ = b;
                    }
                }
            }
            (void)bestI; (void)bestJ;
        }

        if (prefixLen == 0) {
            printf("%c has no common prefix among its alternatives. No left factoring needed.\n", nonTerminal);
            continue;
        }

        {
            char prefix[MAX_LEN];
            strncpy(prefix, alts[0], prefixLen);
            /* find the actual prefix from any alternative that has it - use the
               first alternative that matches the longest common prefix length
               against at least one other alternative */
            int found = 0;
            int a, b;
            for (a = 0; a < numAlts && !found; a++) {
                for (b = a + 1; b < numAlts && !found; b++) {
                    if (commonPrefixLen(alts[a], alts[b]) == prefixLen) {
                        strncpy(prefix, alts[a], prefixLen);
                        prefix[prefixLen] = '\0';
                        found = 1;
                    }
                }
            }

            printf("%c is left factored (common prefix \"%s\"). Result:\n", nonTerminal, prefix);
            printf("%c  -> %s%c'", nonTerminal, prefix, nonTerminal);
            for (i = 0; i < numAlts; i++) {
                if (strncmp(alts[i], prefix, (size_t)prefixLen) != 0) {
                    printf(" | %s", alts[i]);
                }
            }
            printf("\n%c' -> ", nonTerminal);
            {
                int first = 1;
                for (i = 0; i < numAlts; i++) {
                    if (strncmp(alts[i], prefix, (size_t)prefixLen) == 0) {
                        const char *rest = alts[i] + prefixLen;
                        if (!first) printf(" | ");
                        if (rest[0] == '\0') printf("epsilon");
                        else printf("%s", rest);
                        first = 0;
                    }
                }
            }
            printf("\n");
        }
    }

    return 0;
}

/*
Sample Input:
1
S=iEtS|iEtSeS|a

Sample Output:
Production: S -> iEtS | iEtSeS | a
S is left factored (common prefix "iEtS"). Result:
S  -> iEtSS' | a
S' -> epsilon | eS
*/
