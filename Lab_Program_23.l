/* Experiment 23: Count number of macros defined and header files included */
%{
#include <stdio.h>
int nmacro = 0, nheader = 0;
%}

%%
^"#define"    { nmacro++; }
^"#include"   { nheader++; }
.|\n          { }
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
    printf("Sample input C program:\n\n%s\n", sample_program);
    yy_scan_string(sample_program);
    yylex();
    printf("Number of macros defined       = %d\n", nmacro);
    printf("Number of header files included = %d\n", nheader);
    return 0;
}
