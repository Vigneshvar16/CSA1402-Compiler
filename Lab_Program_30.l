/* Experiment 30: Check whether given mobile numbers are valid or not */
%{
#include <stdio.h>
int valid;
%}

%%
[6-9][0-9]{9}   { valid = 1; }
.|\n            { }
%%

int yywrap(void) { return 1; }

int main(void)
{
    char *numbers[] = { "9876543210", "7856453489", "12345", "1234567890" };
    int i, n = 4;

    for (i = 0; i < n; i++) {
        valid = 0;
        yy_scan_string(numbers[i]);
        yylex();
        printf("%-15s -> %s\n", numbers[i], valid ? "Valid Mobile Number" : "Invalid Mobile Number");
        yy_delete_buffer(YY_CURRENT_BUFFER);
    }
    return 0;
}
