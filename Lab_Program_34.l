/* Experiment 34: Separate the keywords and identifiers from a C program
   (Same objective as Experiment 31, demonstrated with a different sample program) */
%{
#include <stdio.h>
int count_id = 0, count_key = 0;
%}
digit  [0-9]
letter [A-Za-z]

%%
(if|else|return|int|float|void|main)   { printf("%s is a keyword\n", yytext); count_key++; }
{letter}({letter}|{digit})*            { printf("%s is an identifier\n", yytext); count_id++; }
{digit}+                                { }
.|\n                                    { }
%%

int yywrap(void) { return 1; }

char *sample_program =
"int total, count;\n"
"void main()\n"
"{\n"
"   if (count > 0)\n"
"      total = count;\n"
"   else\n"
"      total = 0;\n"
"   return;\n"
"}\n";

int main(void)
{
    printf("Sample input C program:\n\n%s\n", sample_program);
    printf("Keywords and identifiers found:\n");
    yy_scan_string(sample_program);
    yylex();
    printf("\nNumber of keywords    = %d\n", count_key);
    printf("Number of identifiers = %d\n", count_id);
    return 0;
}
