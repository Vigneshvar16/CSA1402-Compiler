%{
#include <stdio.h>
%}

%%
https:\/\/.*    { printf("Valid URL\n"); }
http:\/\/.*     { printf("Valid URL\n"); }
.*              { printf("Invalid URL\n"); }
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
