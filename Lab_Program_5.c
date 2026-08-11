/*
 * Lab Program 5
 * Design a Lexical Analyzer to find the number of whitespaces and
 * newline characters in a given input, using C.
 *
 * Enter text line by line. Enter a line containing only END to finish.
 */
#include <stdio.h>
#include <string.h>

#define MAX_LINE 256

int main(void)
{
    char line[MAX_LINE];
    long whitespaces = 0, tabs = 0, newlines = 0, otherChars = 0;

    printf("Enter text line by line.\n");
    printf("Type a line containing only END when you are finished.\n");

    while (fgets(line, sizeof(line), stdin) != NULL) {
        int i;
        int len = (int)strlen(line);
        char trimmed[MAX_LINE];

        strcpy(trimmed, line);
        if (len > 0 && trimmed[len - 1] == '\n') trimmed[len - 1] = '\0';
        if (strcmp(trimmed, "END") == 0) break;

        for (i = 0; i < len; i++) {
            if (line[i] == '\n') {
                newlines++;
            } else if (line[i] == '\t') {
                tabs++;
            } else if (line[i] == ' ') {
                whitespaces++;
            } else {
                otherChars++;
            }
        }
        /* if fgets did not capture a trailing newline (last line of input),
           still count it as one logical line */
        if (len > 0 && line[len - 1] != '\n') newlines++;
    }

    printf("\nTotal number of whitespaces : %ld\n", whitespaces);
    printf("Total number of tabs        : %ld\n", tabs);
    printf("Total number of newlines    : %ld\n", newlines);
    printf("Total number of other characters : %ld\n", otherChars);

    return 0;
}

/*
Sample Input:
int a;
int b;
a = a + b;
END

Sample Output:
Total number of whitespaces : 6
Total number of tabs        : 0
Total number of newlines    : 3
Total number of other characters : 16
*/
