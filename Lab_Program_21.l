/* Experiment 21: Count characters, words, and lines in a C source program */
%{
#include <stdio.h>
int nchar = 0, nword = 0, nline = 0;
%}

%%
\n          { nline++; nchar++; }
[^ \t\n]+   { nword++; nchar += yyleng; }
.           { nchar++; }
%%

int yywrap(void) { return 1; }

char *sample_program =
"#include <stdio.h>\n"
"int main()\n"
"{\n"
"    int number1, number2, sum;\n"
"    printf(\"Enter two integers: \");\n"
"    scanf(\"%d %d\", &number1, &number2);\n"
"    sum = number1 + number2;\n"
"    printf(\"%d + %d = %d\", number1, number2, sum);\n"
"    return 0;\n"
"}\n";

int main(void)
{
    printf("Sample input C program:\n\n%s\n", sample_program);
    yy_scan_string(sample_program);
    yylex();
    printf("Number of characters = %d\n", nchar);
    printf("Number of words      = %d\n", nword);
    printf("Number of lines      = %d\n", nline);
    return 0;
}
