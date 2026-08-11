/* Experiment 25: Add line numbers to a given C program and display on screen */
%{
#include <stdio.h>
int line_no = 0;
%}

%%
^.*\n   { line_no++; printf("%4d\t%s", line_no, yytext); }
%%

int yywrap(void) { return 1; }

char *sample_program =
"#define PI 3.14\n"
"#include<stdio.h>\n"
"#include<math.h>\n"
"void main()\n"
"{\n"
"   int a,b,c = 30;\n"
"   printf(\"hello\");\n"
"}\n";

int main(void)
{
    printf("Program with line numbers added:\n\n");
    yy_scan_string(sample_program);
    yylex();
    return 0;
}
