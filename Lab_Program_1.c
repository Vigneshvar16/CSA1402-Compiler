/*
 * Lab Program 1
 * Develop a Lexical Analyzer to identify identifiers, constants and
 * operators in a given input string, using a C program.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE  200
#define MAX_TOKS  100
#define MAX_TOK_LEN 30

int main(void)
{
    char line[MAX_LINE];
    char identifiers[MAX_TOKS][MAX_TOK_LEN];
    char constants[MAX_TOKS][MAX_TOK_LEN];
    char operators[MAX_TOKS][MAX_TOK_LEN];
    int ic = 0, cc = 0, oc = 0;
    int i, len;

    printf("Enter an expression (e.g. a = b + c * e + 100):\n");
    if (fgets(line, sizeof(line), stdin) == NULL) {
        printf("No input read.\n");
        return 0;
    }
    len = (int)strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
        len--;
    }

    i = 0;
    while (i < len) {
        if (isspace((unsigned char)line[i])) {
            i++;
        } else if (isalpha((unsigned char)line[i]) || line[i] == '_') {
            /* identifier: letter/underscore followed by letters/digits/underscore */
            char buf[MAX_TOK_LEN];
            int j = 0;
            while (i < len && (isalnum((unsigned char)line[i]) || line[i] == '_') && j < MAX_TOK_LEN - 1) {
                buf[j++] = line[i++];
            }
            buf[j] = '\0';
            if (ic < MAX_TOKS) {
                strcpy(identifiers[ic], buf);
                ic++;
            }
        } else if (isdigit((unsigned char)line[i])) {
            /* constant: sequence of digits (optionally with one decimal point) */
            char buf[MAX_TOK_LEN];
            int j = 0;
            while (i < len && (isdigit((unsigned char)line[i]) || line[i] == '.') && j < MAX_TOK_LEN - 1) {
                buf[j++] = line[i++];
            }
            buf[j] = '\0';
            if (cc < MAX_TOKS) {
                strcpy(constants[cc], buf);
                cc++;
            }
        } else if (strchr("+-*/=<>!%&|^~", line[i]) != NULL) {
            /* operator: single character, or two characters for things like ==, <=, >=, != */
            char buf[3];
            buf[0] = line[i];
            buf[1] = '\0';
            i++;
            if (i < len && line[i] == '=') {
                buf[1] = '=';
                buf[2] = '\0';
                i++;
            }
            if (oc < MAX_TOKS) {
                strcpy(operators[oc], buf);
                oc++;
            }
        } else {
            /* any other punctuation such as (), ; , is skipped */
            i++;
        }
    }

    printf("\nIdentifiers : ");
    for (i = 0; i < ic; i++) printf("%s ", identifiers[i]);

    printf("\nConstants   : ");
    for (i = 0; i < cc; i++) printf("%s ", constants[i]);

    printf("\nOperators   : ");
    for (i = 0; i < oc; i++) printf("%s ", operators[i]);

    printf("\n");
    return 0;
}

/*
Sample Input:
a = b + c * e + 100

Sample Output:
Identifiers : a b c e
Constants   : 100
Operators   : = + *  +
*/
