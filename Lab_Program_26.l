/* Experiment 26: Count comment lines in a C program, remove them, and show the result */
%{
#include <stdio.h>
int com = 0;
%}
%x COMMENT

%%
"/*"            { BEGIN(COMMENT); }
<COMMENT>"*/"   { BEGIN(INITIAL); com++; }
<COMMENT>\n     { }
<COMMENT>.      { }
"//".*          { com++; }
.|\n            { fputc(yytext[0], yyout); }
%%

int yywrap(void) { return 1; }

char *sample_program =
"#include<stdio.h>\n"
"int main()\n"
"{\n"
"   int a,b,c; /* variable declaration */\n"
"   a = 10; b = 20; // adding two numbers\n"
"   c = a + b;\n"
"   printf(\"sum is %d\", c);\n"
"   return 0;\n"
"}\n";

int main(void)
{
    printf("Sample input C program:\n\n%s\n", sample_program);
    yyout = stdout;
    printf("Program after removing comments:\n\n");
    yy_scan_string(sample_program);
    yylex();
    printf("\n\nNumber of comments removed = %d\n", com);
    return 0;
}
