/*
 * Lab Program 17
 * Write a C program implementing a Lexical Analyzer to scan and count
 * the number of characters, words, and lines in a file.
 *
 * The program reads from a file named "input.txt" in the same folder
 * as the executable. A sample input.txt is provided alongside this
 * program.
 */
#include <stdio.h>

int main(void)
{
    FILE *fp;
    int ch;
    long characters = 0, words = 0, lines = 0;
    int inWord = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Could not open input.txt. Make sure it is in the same folder as this program.\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        characters++;

        if (ch == '\n') {
            lines++;
        }

        if (ch == ' ' || ch == '\t' || ch == '\n') {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            words++;
        }
    }

    fclose(fp);

    printf("Total number of characters : %ld\n", characters);
    printf("Total number of words      : %ld\n", words);
    printf("Total number of lines      : %ld\n", lines);

    return 0;
}

/*
Sample Input (input.txt):
void main()
{
int a;
int b;
a = b + c;
c = d * e;
}

Sample Output:
Total number of characters : 52
Total number of words      : 18
Total number of lines      : 7
*/
