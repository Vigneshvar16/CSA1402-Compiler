/* Experiment 35: Recognize numbers and words in a statement */
%{
#include <stdio.h>
%}

%%
[ \t]+                    { }
[0-9]+(\.[0-9]+)?         { printf("%s is a NUMBER\n", yytext); }
"#".*                     { printf("%s is a COMMENT\n", yytext); }
[a-zA-Z]+                 { printf("%s is a WORD\n", yytext); }
\n                        { }
%%

int yywrap(void) { return 1; }

char *sample_text = "Variables A and B contain 10 and 20 respectively\n";

int main(void)
{
    printf("Sample input text:\n%s\n", sample_text);
    printf("Tokens identified:\n");
    yy_scan_string(sample_text);
    yylex();
    return 0;
}
