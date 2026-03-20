#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char prod[MAX][20];
char first[MAX][MAX], follow[MAX][MAX];
char table[MAX][MAX][20];

char nonTerminals[MAX], terminals[MAX];
int ntCount = 0, tCount = 0;

// find index
int findIndex(char arr[], int size, char c) {
    for (int i = 0; i < size; i++)
        if (arr[i] == c) return i;
    return -1;
}

int main() {
    int n;
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (A->aB):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
        nonTerminals[ntCount++] = prod[i][0];
    }

    // extract terminals
    for (int i = 0; i < n; i++) {
        for (int j = 3; prod[i][j]; j++) {
            if (!isupper(prod[i][j]) && prod[i][j] != 'e') {
                if (findIndex(terminals, tCount, prod[i][j]) == -1)
                    terminals[tCount++] = prod[i][j];
            }
        }
    }

    terminals[tCount++] = '$';

    // input FIRST
    printf("\nEnter FIRST sets:\n");
    for (int i = 0; i < ntCount; i++) {
        printf("FIRST(%c): ", nonTerminals[i]);
        scanf("%s", first[i]);
    }

    // input FOLLOW
    printf("\nEnter FOLLOW sets:\n");
    for (int i = 0; i < ntCount; i++) {
        printf("FOLLOW(%c): ", nonTerminals[i]);
        scanf("%s", follow[i]);
    }

    // build table
    for (int i = 0; i < n; i++) {
        char A = prod[i][0];
        int row = findIndex(nonTerminals, ntCount, A);

        char *rhs = &prod[i][3];

        // if first symbol is terminal
        if (!isupper(rhs[0])) {
            int col = findIndex(terminals, tCount, rhs[0]);
            strcpy(table[row][col], prod[i]);
        }
        else {
            int idx = findIndex(nonTerminals, ntCount, rhs[0]);

            for (int k = 0; first[idx][k]; k++) {
                if (first[idx][k] != 'e') {
                    int col = findIndex(terminals, tCount, first[idx][k]);
                    strcpy(table[row][col], prod[i]);
                }
            }

            // epsilon case
            if (strchr(first[idx], 'e')) {
                for (int k = 0; follow[row][k]; k++) {
                    int col = findIndex(terminals, tCount, follow[row][k]);
                    strcpy(table[row][col], prod[i]);
                }
            }
        }
    }

    // print table
    printf("\nPredictive Parsing Table:\n\n");

    printf("      ");
    for (int i = 0; i < tCount; i++)
        printf("%5c", terminals[i]);
    printf("\n");

    for (int i = 0; i < ntCount; i++) {
        printf("%5c", nonTerminals[i]);
        for (int j = 0; j < tCount; j++) {
            if (strlen(table[i][j]) > 0)
                printf("%5s", table[i][j]);
            else
                printf("%5s", "-");
        }
        printf("\n");
    }

    return 0;
}


Enter number of productions: 3
E->TR
R->+TR
R->e

FIRST(E): t
FIRST(R): +e

FOLLOW(E): $
FOLLOW(R): $
