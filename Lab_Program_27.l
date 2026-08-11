/* Experiment 27: Identify all capital (all-uppercase) words from the input */
%{
#include <stdio.h>
%}

%%
[A-Z]+   { printf("%s is a capital word\n", yytext); }
.|\n     { }
%%

int yywrap(void) { return 1; }

char *sample_text = "CAPITAL of INDIA is DELHI\n";

int main(void)
{
    printf("Sample input text:\n%s\n", sample_text);
    printf("Capital words found:\n");
    yy_scan_string(sample_text);
    yylex();
    return 0;
}
