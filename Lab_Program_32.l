/* Experiment 32: Count the number of vowels and consonants in the given sentence */
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

char *sample_text = "Vowel sounds allow the air to flow freely\n";

int main(void)
{
    printf("Sample input text:\n%s\n", sample_text);
    yy_scan_string(sample_text);
    yylex();
    printf("Number of vowels      = %d\n", vow_count);
    printf("Number of consonants  = %d\n", const_count);
    return 0;
}
