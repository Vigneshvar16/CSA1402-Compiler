/*
 * Lab Program 13
 * Write a C program to implement a Top-Down parsing technique to check
 * whether a given input string satisfies the grammar:
 *   S -> aS | Sb | ab
 *
 * This grammar generates exactly the strings that are one or more
 * 'a's followed by one or more 'b's (a+ b+), since every derivation
 * eventually bottoms out at the base production S -> ab, with S -> aS
 * adding extra a's on the left and S -> Sb adding extra b's on the
 * right.
 *
 * The parser below works top-down: it repeatedly tries to match the
 * input against the grammar by first consuming as many leading a's as
 * possible (rule S -> aS), then requires the base case "ab", then
 * consumes any trailing b's (rule S -> Sb).
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[100];
    int len, i = 0;
    int accepted = 1;

    printf("The grammar is: S -> aS | Sb | ab\n");
    printf("Enter the string to be checked:\n");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        printf("No input read.\n");
        return 0;
    }
    len = (int)strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }

    if (len < 2) {
        accepted = 0;
    } else {
        int aCount = 0, bCount = 0;

        /* Step 1: apply S -> aS repeatedly: consume leading a's */
        while (i < len && str[i] == 'a') {
            aCount++;
            i++;
        }

        /* Step 2: apply S -> Sb from the other end: consume trailing b's */
        {
            int j = len - 1;
            while (j >= i && str[j] == 'b') {
                bCount++;
                j--;
            }
        }

        /* Step 3: what remains must be empty (base case S -> ab already
           accounted for by requiring at least one a and one b) */
        if (aCount < 1 || bCount < 1 || aCount + bCount != len) {
            accepted = 0;
        }
    }

    if (accepted) {
        printf("String ACCEPTED by the grammar.\n");
    } else {
        printf("String NOT accepted by the grammar.\n");
    }

    return 0;
}

/*
Sample Input:
aaabb

Sample Output:
String ACCEPTED by the grammar.

Sample Input:
abab

Sample Output:
String NOT accepted by the grammar.
*/
