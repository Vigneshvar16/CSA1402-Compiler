/* Experiment 33: Count the number of vowels and consonants in the given sentence
   (Same objective as Experiment 32, demonstrated with a different sample sentence) */
%{
#include <stdio.h>
int vow_count = 0, const_count = 0;
%}

%%
[aeiouAEIOU]   { vow_count++; }
[a-zA-Z]       { const_count++; }
.|\n           { }
%%

int yywrap(void) { return 1; }

char *sample_text = "Compiler design lab experiment using flex and lex tool\n";

int main(void)
{
    printf("Sample input text:\n%s\n", sample_text);
    yy_scan_string(sample_text);
    yylex();
    printf("Number of vowels      = %d\n", vow_count);
    printf("Number of consonants  = %d\n", const_count);
    return 0;
}
