/*
 * Lab Program 16
 * Write a C program to generate the Three Address Code (TAC)
 * representation for a given input statement of the form:
 *   result = operand1 op operand2 op operand3 ...
 * where op is one of + - * /  (all operators are left associative and
 * are handled one at a time, e.g. out = in1 + in2 + in3 - in4).
 */
#include <stdio.h>
#include <string.h>

#define MAX_TOKENS 30
#define MAX_TOK_LEN 20

int main(void)
{
    char line[200];
    char tokens[MAX_TOKENS][MAX_TOK_LEN];
    int numTokens = 0;

    printf("Enter a statement (e.g. out = in1 + in2 + in3 - in4):\n");
    if (fgets(line, sizeof(line), stdin) == NULL) {
        printf("No input read.\n");
        return 0;
    }

    /* tokenize on whitespace */
    {
        char *tok = strtok(line, " \t\n");
        while (tok != NULL && numTokens < MAX_TOKENS) {
            strncpy(tokens[numTokens], tok, MAX_TOK_LEN - 1);
            tokens[numTokens][MAX_TOK_LEN - 1] = '\0';
            numTokens++;
            tok = strtok(NULL, " \t\n");
        }
    }

    /* expected form: result = operand1 (op operand)* */
    if (numTokens < 3 || strcmp(tokens[1], "=") != 0) {
        printf("Input must look like:  result = operand1 op operand2 ...\n");
        return 0;
    }

    printf("\nThree Address Code:\n");

    if (numTokens == 3) {
        /* simple copy: result = operand1 */
        printf("%s = %s\n", tokens[0], tokens[2]);
        return 0;
    }

    {
        char temp[MAX_TOK_LEN];
        int tempCount = 1;
        int idx = 2; /* points at first operand after '=' */

        sprintf(temp, "t%d", tempCount);
        printf("%s = %s %s %s\n", temp, tokens[idx], tokens[idx + 1], tokens[idx + 2]);
        idx += 3;
        tempCount++;

        while (idx + 1 < numTokens) {
            char prevTemp[MAX_TOK_LEN];
            strcpy(prevTemp, temp);
            sprintf(temp, "t%d", tempCount);
            printf("%s = %s %s %s\n", temp, prevTemp, tokens[idx], tokens[idx + 1]);
            idx += 2;
            tempCount++;
        }

        printf("%s = %s\n", tokens[0], temp);
    }

    return 0;
}

/*
Sample Input:
out = in1 + in2 + in3 - in4

Sample Output:
Three Address Code:
t1 = in1 + in2
t2 = t1 + in3
t3 = t2 - in4
out = t3
*/
