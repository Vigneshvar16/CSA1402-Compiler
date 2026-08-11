/*
 * Lab Program 11
 * Implement a C program to perform symbol table operations:
 * insert, display, search and modify.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYM 50
#define MAX_LABEL 20

struct symtab {
    char label[MAX_LABEL];
    int addr;
};

struct symtab table[MAX_SYM];
int cnt = 0;

void readLabel(char *dest, int size)
{
    char buf[100];
    if (fgets(buf, sizeof(buf), stdin) != NULL) {
        int len = (int)strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') buf[len - 1] = '\0';
        strncpy(dest, buf, size - 1);
        dest[size - 1] = '\0';
    } else {
        dest[0] = '\0';
    }
}

int search(const char *s)
{
    int i;
    for (i = 0; i < cnt; i++) {
        if (strcmp(table[i].label, s) == 0) return i;
    }
    return -1;
}

void insertSymbol(void)
{
    char lab[MAX_LABEL];
    int addr;

    if (cnt >= MAX_SYM) {
        printf("Symbol table is full.\n");
        return;
    }

    printf("Enter the label: ");
    readLabel(lab, sizeof(lab));

    if (search(lab) != -1) {
        printf("Duplicate symbol. Not inserted.\n");
        return;
    }

    printf("Enter the address: ");
    if (scanf("%d", &addr) != 1) {
        printf("Invalid address.\n");
        while (getchar() != '\n'); /* clear bad input */
        return;
    }
    while (getchar() != '\n'); /* consume rest of line */

    strcpy(table[cnt].label, lab);
    table[cnt].addr = addr;
    cnt++;
    printf("Inserted successfully.\n");
}

void displaySymbols(void)
{
    int i;
    if (cnt == 0) {
        printf("Symbol table is empty.\n");
        return;
    }
    printf("Label\tAddress\n");
    for (i = 0; i < cnt; i++) {
        printf("%s\t%d\n", table[i].label, table[i].addr);
    }
}

void searchSymbol(void)
{
    char lab[MAX_LABEL];
    int idx;
    printf("Enter the label to search: ");
    readLabel(lab, sizeof(lab));
    idx = search(lab);
    if (idx != -1) {
        printf("Label found. Address = %d\n", table[idx].addr);
    } else {
        printf("Label not found.\n");
    }
}

void modifySymbol(void)
{
    char lab[MAX_LABEL];
    int idx, addr;
    printf("Enter the label to modify: ");
    readLabel(lab, sizeof(lab));
    idx = search(lab);
    if (idx == -1) {
        printf("No such symbol.\n");
        return;
    }
    printf("Label found. Enter new address: ");
    if (scanf("%d", &addr) != 1) {
        printf("Invalid address.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    table[idx].addr = addr;
    printf("Modified successfully.\n");
}

int main(void)
{
    int ch;

    do {
        printf("\n1. Insert\n2. Display\n3. Search\n4. Modify\n5. Exit\nEnter your choice: ");
        if (scanf("%d", &ch) != 1) {
            printf("Invalid choice.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n'); /* consume newline before reading label */

        switch (ch) {
            case 1: insertSymbol(); break;
            case 2: displaySymbols(); break;
            case 3: searchSymbol(); break;
            case 4: modifySymbol(); break;
            case 5: printf("Exiting.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (ch != 5);

    return 0;
}

/*
Sample Input:
1
a
100
2
3
a
5

Sample Output:
1. Insert
2. Display
3. Search
4. Modify
5. Exit
Enter your choice: Enter the label: Enter the address: Inserted successfully.

1. Insert
2. Display
3. Search
4. Modify
5. Exit
Enter your choice: Label   Address
a       100

1. Insert
2. Display
3. Search
4. Modify
5. Exit
Enter your choice: Enter the label to search: Label found. Address = 100

1. Insert
2. Display
3. Search
4. Modify
5. Exit
Enter your choice: Exiting.
*/
