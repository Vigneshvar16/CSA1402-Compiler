/* Experiment 29: Convert every occurrence of substring "abc" to "ABC" in the input string */
%{
#include <stdio.h>
%}

%%
"abc"   { printf("ABC"); }
.|\n    { ECHO; }
%%

int yywrap(void) { return 1; }

char *sample_text = "abcdefghabcijkla\n";

int main(void)
{
    printf("Original string : %s", sample_text);
    printf("Converted string : ");
    yy_scan_string(sample_text);
    yylex();
    return 0;
}
