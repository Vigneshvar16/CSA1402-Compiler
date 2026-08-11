/* Experiment 31: Lexical analyzer - separate tokens of a C program with appropriate captions */
%{
#include <stdio.h>
int count_id = 0, count_key = 0;
%}
digit  [0-9]
letter [A-Za-z]

%%
"stdio.h"                              { printf("%s is a standard library\n", yytext); }
(include|void|main|printf|int|return)  { printf("%s is a keyword\n", yytext); count_key++; }
{letter}({letter}|{digit})*            { printf("%s is an identifier\n", yytext); count_id++; }
{digit}+                               { printf("%s is a number\n", yytext); }
\"(\\.|[^"\\])*\"                      { printf("%s is a string literal\n", yytext); }
.|\n                                   { }
%%

int yywrap(void) { return 1; }

char *sample_program =
"#include<stdio.h>\n"
"void main()\n"
"{\n"
"   int a,b,c = 30;\n"
"   printf(\"hello\");\n"
"}\n";

int main(void)
{
    printf("Sample input C program:\n\n%s\n", sample_program);
    printf("Tokens identified:\n");
    yy_scan_string(sample_program);
    yylex();
    printf("\nNumber of identifiers = %d\n", count_id);
    printf("Number of keywords    = %d\n", count_key);
    return 0;
}
