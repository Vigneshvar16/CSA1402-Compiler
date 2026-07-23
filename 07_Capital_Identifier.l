%{
#include<stdio.h>
%}

%%
[A-Z]                         { printf("Capital Letter: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*        { printf("Identifier: %s\n", yytext); }
.|\n                          ;
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
