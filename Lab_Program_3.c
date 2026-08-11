/*
 * Lab Program 3
 * Design a Lexical Analyzer for a given language which should ignore
 * redundant spaces, tabs and new lines, and should also ignore comments,
 * while classifying the remaining tokens as keywords, identifiers,
 * numbers or operators.
 *
 * Input is typed line by line at the terminal. Enter a line containing
 * only END to finish typing the source code.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SRC 2000
#define MAX_TOK 64

const char *keywords[] = {
    "auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if","int",
    "long","register","return","short","signed","sizeof","static",
    "struct","switch","typedef","union","unsigned","void","volatile",
    "while","main","printf","scanf"
};
#define NUM_KEYWORDS (int)(sizeof(keywords) / sizeof(keywords[0]))

int isKeyword(const char *buf)
{
    int i;
    for (i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(keywords[i], buf) == 0) return 1;
    }
    return 0;
}

int main(void)
{
    char src[MAX_SRC];
    char line[256];

    printf("Enter the source code line by line.\n");
    printf("Type a line containing only END when you are finished.\n");

    src[0] = '\0';
    while (fgets(line, sizeof(line), stdin) != NULL) {
        /* strip trailing newline for the END check */
        char trimmed[256];
        int n = (int)strlen(line);
        strcpy(trimmed, line);
        if (n > 0 && trimmed[n - 1] == '\n') trimmed[n - 1] = '\0';
        if (strcmp(trimmed, "END") == 0) break;

        if ((int)(strlen(src) + strlen(line) + 1) < MAX_SRC) {
            strcat(src, line);
        }
    }

    {
        int len = (int)strlen(src);
        int i = 0;

        printf("\n--- Tokens ---\n");
        while (i < len) {
            char c = src[i];

            /* skip whitespace, tabs, newlines */
            if (isspace((unsigned char)c)) {
                i++;
                continue;
            }

            /* skip single line comments */
            if (c == '/' && i + 1 < len && src[i + 1] == '/') {
                while (i < len && src[i] != '\n') i++;
                continue;
            }

            /* skip multi line comments */
            if (c == '/' && i + 1 < len && src[i + 1] == '*') {
                i += 2;
                while (i + 1 < len && !(src[i] == '*' && src[i + 1] == '/')) i++;
                i += 2;
                continue;
            }

            /* identifiers and keywords */
            if (isalpha((unsigned char)c) || c == '_') {
                char buf[MAX_TOK];
                int j = 0;
                while (i < len && (isalnum((unsigned char)src[i]) || src[i] == '_') && j < MAX_TOK - 1) {
                    buf[j++] = src[i++];
                }
                buf[j] = '\0';
                if (isKeyword(buf)) {
                    printf("%s\t\t-> keyword\n", buf);
                } else {
                    printf("%s\t\t-> identifier\n", buf);
                }
                continue;
            }

            /* numbers */
            if (isdigit((unsigned char)c)) {
                char buf[MAX_TOK];
                int j = 0;
                while (i < len && (isdigit((unsigned char)src[i]) || src[i] == '.') && j < MAX_TOK - 1) {
                    buf[j++] = src[i++];
                }
                buf[j] = '\0';
                printf("%s\t\t-> number\n", buf);
                continue;
            }

            /* operators */
            if (strchr("+-*/%=<>!&|", c) != NULL) {
                printf("%c\t\t-> operator\n", c);
                i++;
                continue;
            }

            /* punctuation such as ( ) { } ; , */
            if (strchr("(){};,", c) != NULL) {
                printf("%c\t\t-> punctuation\n", c);
                i++;
                continue;
            }

            /* anything else is skipped */
            i++;
        }
    }

    return 0;
}

/*
Sample Input:
int a, b;   // declare variables
a = a + b;
END

Sample Output:
--- Tokens ---
int             -> keyword
a               -> identifier
,               -> punctuation
b               -> identifier
;               -> punctuation
a               -> identifier
=               -> operator
a               -> identifier
+               -> operator
b               -> identifier
;               -> punctuation
*/
