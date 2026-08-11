/*
 * Lab Program 6
 * Develop a Lexical Analyzer to test whether a given identifier is
 * valid or not, using C.
 *
 * Rule: an identifier must start with a letter or underscore, and the
 * remaining characters must be letters, digits or underscores.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 50

int main(void)
{
    char id[MAX_LEN];
    int len, i, valid = 1;

    printf("Enter an identifier:\n");
    if (fgets(id, sizeof(id), stdin) == NULL) {
        printf("No input read.\n");
        return 0;
    }
    len = (int)strlen(id);
    if (len > 0 && id[len - 1] == '\n') {
        id[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        valid = 0;
    } else if (!(isalpha((unsigned char)id[0]) || id[0] == '_')) {
        valid = 0;
    } else {
        for (i = 1; i < len; i++) {
            if (!(isalnum((unsigned char)id[i]) || id[i] == '_')) {
                valid = 0;
                break;
            }
        }
    }

    if (valid) {
        printf("\"%s\" is a VALID identifier.\n", id);
    } else {
        printf("\"%s\" is NOT a valid identifier.\n", id);
    }

    return 0;
}

/*
Sample Input:
abc123

Sample Output:
"abc123" is a VALID identifier.

Sample Input:
123abc

Sample Output:
"123abc" is NOT a valid identifier.
*/
