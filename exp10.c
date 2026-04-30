#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char prod[MAX][10];   // productions
char items[MAX][20];  // LR(0) items
int n;                // number of productions
int itemCount = 0;

// Add dot at beginning
void addInitialItems() {
    for (int i = 0; i < n; i++) {
        sprintf(items[itemCount++], "%c->.%s", prod[i][0], prod[i] + 3);
    }
}

// Closure function
void closure() {
    int added;
    do {
        added = 0;
        for (int i = 0; i < itemCount; i++) {
            char *dot = strchr(items[i], '.');
            if (dot && isupper(*(dot + 1))) {
                char nonTerm = *(dot + 1);

                for (int j = 0; j < n; j++) {
                    if (prod[j][0] == nonTerm) {
                        char temp[20];
                        sprintf(temp, "%c->.%s", prod[j][0], prod[j] + 3);

                        int exists = 0;
                        for (int k = 0; k < itemCount; k++) {
                            if (strcmp(items[k], temp) == 0) {
                                exists = 1;
                                break;
                            }
                        }

                        if (!exists) {
                            strcpy(items[itemCount++], temp);
                            added = 1;
                        }
                    }
                }
            }
        }
    } while (added);
}

// Move dot (GOTO-like)
void moveDot() {
    for (int i = 0; i < itemCount; i++) {
        char temp[20];
        strcpy(temp, items[i]);

        char *dot = strchr(temp, '.');
        if (dot && *(dot + 1) != '\0') {
            char t = *(dot + 1);
            *dot = t;
            *(dot + 1) = '.';

            printf("GOTO: %s\n", temp);
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (E->E+T format):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
    }

    addInitialItems();
    closure();

    printf("\nLR(0) Items (Closure):\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%s\n", items[i]);
    }

    printf("\nTransitions (GOTO):\n");
    moveDot();

    return 0;
}
