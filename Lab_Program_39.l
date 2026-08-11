/* Experiment 39: Check whether the given input consists only of digits */
%{
#include <stdio.h>
int valid;
%}

%%
[0-9]+     { }
[^0-9\n]   { valid = 0; }
\n         { }
%%

int yywrap(void) { return 1; }

int main(void)
{
    char *inputs[] = { "23456", "h56", "789", "12a34" };
    int i, n = 4;

    for (i = 0; i < n; i++) {
        valid = 1;
        yy_scan_string(inputs[i]);
        yylex();
        printf("%-8s -> %s\n", inputs[i], valid ? "Valid digit(s) only" : "Invalid (contains non-digit characters)");
        yy_delete_buffer(YY_CURRENT_BUFFER);
    }
    return 0;
}
