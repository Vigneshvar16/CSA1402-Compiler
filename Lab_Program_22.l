/* Experiment 22: Print all numeric constants in a C source program */
%{
#include <stdio.h>
int cons = 0;
%}
digit [0-9]

%%
{digit}+   { cons++; printf("%s is a constant\n", yytext); }
.|\n       { }
%%

int yywrap(void) { return 1; }

char *sample_program =
"#define P 314\n"
"#include<stdio.h>\n"
"void main()\n"
"{\n"
"   int a,b,c = 30;\n"
"   printf(\"hello\");\n"
"}\n";

int main(void)
{
    printf("Sample input C program:\n\n%s\n", sample_program);
    printf("Constants found:\n");
    yy_scan_string(sample_program);
    yylex();
    printf("Number of Constants : %d\n", cons);
    return 0;
}
