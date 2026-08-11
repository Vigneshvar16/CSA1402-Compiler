/* Experiment 24: Print all HTML tags present in an HTML input */
%{
#include <stdio.h>
int tags = 0;
%}

%%
"<"[^>]*">"   { tags++; printf("%s\n", yytext); }
.|\n          { }
%%

int yywrap(void) { return 1; }

char *sample_html =
"<html>\n"
"<body>\n"
"<h1>My First Heading</h1>\n"
"<p>My first paragraph.</p>\n"
"</body>\n"
"</html>\n";

int main(void)
{
    printf("Sample input HTML:\n\n%s\n", sample_html);
    printf("HTML tags found:\n");
    yy_scan_string(sample_html);
    yylex();
    printf("\nNumber of HTML tags: %d\n", tags);
    return 0;
}
