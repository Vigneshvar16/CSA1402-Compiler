/* Experiment 40: Implement basic mathematical operations (+, -, *, /) */
%{
#include <stdio.h>
#include <stdlib.h>
double op1 = 0, op2 = 0, result = 0;
int have_op1 = 0, have_operator = 0;
char oper;
void eval(void);
%}
DIGIT [0-9]
NUM   {DIGIT}+(\.{DIGIT}+)?

%%
{NUM}     {
              if (!have_op1) {
                  op1 = atof(yytext);
                  have_op1 = 1;
              } else if (have_operator) {
                  op2 = atof(yytext);
                  eval();
                  have_op1 = 0;
                  have_operator = 0;
              }
          }
[-+*/]    { oper = yytext[0]; have_operator = 1; }
[ \t]     { }
\n        { }
%%

int yywrap(void) { return 1; }

void eval(void)
{
    switch (oper) {
        case '+': result = op1 + op2; break;
        case '-': result = op1 - op2; break;
        case '*': result = op1 * op2; break;
        case '/':
            if (op2 == 0) { printf("Error: division by zero\n"); return; }
            result = op1 / op2;
            break;
    }
    printf("%.2f %c %.2f = %.2f\n", op1, oper, op2, result);
}

int main(void)
{
    char *expr1 = "20 + 30\n";
    char *expr2 = "25 * 5\n";
    char *expr3 = "100 / 4\n";

    printf("Evaluating: %s", expr1);
    yy_scan_string(expr1);
    yylex();
    yy_delete_buffer(YY_CURRENT_BUFFER);

    printf("Evaluating: %s", expr2);
    yy_scan_string(expr2);
    yylex();
    yy_delete_buffer(YY_CURRENT_BUFFER);

    printf("Evaluating: %s", expr3);
    yy_scan_string(expr3);
    yylex();
    yy_delete_buffer(YY_CURRENT_BUFFER);

    return 0;
}
