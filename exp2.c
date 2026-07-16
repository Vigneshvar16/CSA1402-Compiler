#include <stdio.h>
#include <string.h>

int main() {
    char str[200];

    printf("Enter a line: ");
    fgets(str, sizeof(str), stdin);

    // Check for single-line comment
    if (strncmp(str, "//", 2) == 0) {
        printf("It is a Single Line Comment.\n");
    }
    // Check for multi-line comment
    else if (strncmp(str, "/*", 2) == 0 && strstr(str, "*/") != NULL) {
        printf("It is a Multi Line Comment.\n");
    }
    // Check if only the beginning of a multi-line comment is entered
    else if (strncmp(str, "/*", 2) == 0) {
        printf("It is the Beginning of a Multi Line Comment.\n");
    }
    // Not a comment
    else {
        printf("It is Not a Comment.\n");
    }

    return 0;
}