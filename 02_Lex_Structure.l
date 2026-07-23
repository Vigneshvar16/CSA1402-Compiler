%{
#include<stdio.h>
%}

%%
hello   { printf("Hello Found\n"); }
.|\n    ;
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
