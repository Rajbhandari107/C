#include <stdio.h>
#include <string.h>

void removeLeftRecursion(char prod[]) {
    char alpha[10][10], beta[10][10];
    int a = 0, b = 0;

    char lhs = prod[0];
    char *rhs = strchr(prod, '>') + 1;

    char *token = strtok(rhs, "|");

    while (token != NULL) {
        if (token[0] == lhs) {
            strcpy(alpha[a++], token + 1); // remove A
        } else {
            strcpy(beta[b++], token);
        }
        token = strtok(NULL, "|");
    }

    if (a == 0) {
        printf("No Left Recursion\n");
        return;
    }

    printf("\nAfter Removing Left Recursion:\n");
    printf("%c -> ", lhs);
    for (int i = 0; i < b; i++) {
        printf("%s%c'", beta[i], lhs);
        if (i != b - 1) printf(" | ");
    }

    printf("\n%c' -> ", lhs);
    for (int i = 0; i < a; i++) {
        printf("%s%c' | ", alpha[i], lhs);
    }
    printf("ε\n");
}

void leftFactoring(char prod[]) {
    char lhs = prod[0];
    char *rhs = strchr(prod, '>') + 1;

    char first[10], rest1[10], rest2[10];

    char *p1 = strtok(rhs, "|");
    char *p2 = strtok(NULL, "|");

    if (!p1 || !p2) {
        printf("No Left Factoring needed\n");
        return;
    }

    int i = 0;
    while (p1[i] == p2[i] && p1[i] != '\0') {
        first[i] = p1[i];
        i++;
    }
    first[i] = '\0';

    strcpy(rest1, p1 + i);
    strcpy(rest2, p2 + i);

    if (strlen(first) == 0) {
        printf("No Left Factoring needed\n");
        return;
    }

    printf("\nAfter Left Factoring:\n");
    printf("%c -> %s%c'\n", lhs, first, lhs);
    printf("%c' -> %s | %s\n", lhs, rest1, rest2);
}

int main() {
    char prod1[50], prod2[50];

    printf("Enter production for Left Recursion (e.g. A->Aa|b): ");
    scanf("%s", prod1);

    removeLeftRecursion(prod1);

    printf("\nEnter production for Left Factoring (e.g. A->ab|ac): ");
    scanf("%s", prod2);

    leftFactoring(prod2);

    return 0;
}

A->Aa|b
A->ab|ac
    
