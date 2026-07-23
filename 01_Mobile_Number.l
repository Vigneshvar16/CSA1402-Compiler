%{
#include<stdio.h>
%}

%%
[0-9]{2}      { printf("Valid 2-digit number\n"); }
.*            { printf("Invalid\n"); }
%%

int yywrap()
{
    return 1;
}

int main()
{
    yylex();
    return 0;
}