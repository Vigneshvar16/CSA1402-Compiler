/* Experiment 38: Validate date of birth (DD/MM/YYYY) */
%{
#include <stdio.h>
int valid;
%}

%%
(0[1-9]|[12][0-9]|3[01])"/"(0[1-9]|1[0-2])"/"(19[0-9][0-9]|20[0-9][0-9])   { valid = 1; }
.|\n                                                                       { }
%%

int yywrap(void) { return 1; }

int main(void)
{
    char *dobs[] = { "26/07/1995", "31/12/2000", "32/13/1995", "1/2/95" };
    int i, n = 4;

    for (i = 0; i < n; i++) {
        valid = 0;
        yy_scan_string(dobs[i]);
        yylex();
        printf("%-12s -> %s\n", dobs[i], valid ? "Valid DoB" : "Invalid DoB");
        yy_delete_buffer(YY_CURRENT_BUFFER);
    }
    return 0;
}
