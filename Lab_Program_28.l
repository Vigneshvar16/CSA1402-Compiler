/* Experiment 28: Check whether given email addresses are valid or not */
%{
#include <stdio.h>
int valid;
%}

%%
[a-zA-Z0-9._]+"@"[a-zA-Z]+"."("com"|"in"|"org")   { valid = 1; }
.|\n                                              { }
%%

int yywrap(void) { return 1; }

int main(void)
{
    char *emails[] = { "student123@gmail.com", "test.user@college.in", "invalid-email" };
    int i, n = 3;

    for (i = 0; i < n; i++) {
        valid = 0;
        yy_scan_string(emails[i]);
        yylex();
        printf("%-25s -> %s\n", emails[i], valid ? "Accepted (Valid Email)" : "Not Accepted (Invalid Email)");
        yy_delete_buffer(YY_CURRENT_BUFFER);
    }
    return 0;
}
