/* Experiment 37: Validate a URL */
%{
#include <stdio.h>
int valid;
%}

%%
("http"|"https"|"ftp")"://"[a-zA-Z0-9.-]+"."[a-zA-Z]{2,}([a-zA-Z0-9/_.-]*)?   { valid = 1; }
.|\n                                                                          { }
%%

int yywrap(void) { return 1; }

int main(void)
{
    char *urls[] = { "https://www.google.com", "http://sse.in/page", "ftp://files.example.org", "not a url" };
    int i, n = 4;

    for (i = 0; i < n; i++) {
        valid = 0;
        yy_scan_string(urls[i]);
        yylex();
        printf("%-28s -> %s\n", urls[i], valid ? "Valid URL" : "Invalid URL");
        yy_delete_buffer(YY_CURRENT_BUFFER);
    }
    return 0;
}
