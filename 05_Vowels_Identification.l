%{
#include<stdio.h>
%}

%%
[aAeEiIoOuU]    { printf("Vowel: %s\n", yytext); }
.|\n            ;
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
