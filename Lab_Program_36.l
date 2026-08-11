/* Experiment 36: Identify and count positive and negative numbers */
%{
#include <stdio.h>
int positive_no = 0, negative_no = 0;
%}

%%
"-"[0-9]+   { negative_no++; printf("negative number = %s\n", yytext); }
[0-9]+      { positive_no++; printf("positive number = %s\n", yytext); }
.|\n        { }
%%

int yywrap(void) { return 1; }

char *sample_text = "10 -20 35 -7 42\n";

int main(void)
{
    printf("Sample input: %s\n", sample_text);
    yy_scan_string(sample_text);
    yylex();
    printf("\nNumber of positive numbers = %d\n", positive_no);
    printf("Number of negative numbers = %d\n", negative_no);
    return 0;
}
