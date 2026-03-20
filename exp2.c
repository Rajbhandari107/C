#include <stdio.h>
#include <string.h>

#define MAX 20

int n, m;
char states[MAX][10], alphabet[MAX];
int trans[MAX][MAX]; // state x symbol → state index
int accept[MAX];

int find_state(char *s) {
    for (int i = 0; i < n; i++)
        if (strcmp(states[i], s) == 0)
            return i;
    return -1;
}

int main() {
    printf("Number of states: ");
    scanf("%d", &n);

    printf("States:\n");
    for (int i = 0; i < n; i++)
        scanf("%s", states[i]);

    printf("Alphabet size: ");
    scanf("%d", &m);

    printf("Alphabet:\n");
    for (int i = 0; i < m; i++)
        scanf(" %c", &alphabet[i]);

    printf("Enter transitions (state symbol next_state):\n");
    for (int i = 0; i < n * m; i++) {
        char s1[10], s2[10], sym;
        scanf("%s %c %s", s1, &sym, s2);
        int a = find_state(s1);
        int b = find_state(s2);

        for (int j = 0; j < m; j++) {
            if (alphabet[j] == sym) {
                trans[a][j] = b;
                break;
            }
        }
    }

    printf("Enter accept states (1 for accept, 0 for not):\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &accept[i]);

    // Initial partition: 0 = non-final, 1 = final
    int group[MAX];
    for (int i = 0; i < n; i++)
        group[i] = accept[i];

    int changed;
    do {
        changed = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (group[i] == group[j]) {
                    int same = 1;
                    for (int k = 0; k < m; k++) {
                        if (group[trans[i][k]] != group[trans[j][k]]) {
                            same = 0;
                            break;
                        }
                    }
                    if (!same) {
                        group[j] = group[i] + 1;
                        changed = 1;
                    }
                }
            }
        }
    } while (changed);

    printf("\nMinimized DFA Groups:\n");
    for (int i = 0; i < n; i++)
        printf("%s -> Group %d\n", states[i], group[i]);

    printf("\nTransitions:\n");
    for (int i = 0; i < n; i++) {
        printf("Group %d:\n", group[i]);
        for (int j = 0; j < m; j++) {
            printf("  %c -> Group %d\n", alphabet[j], group[trans[i][j]]);
        }
    }

    return 0;
}


Number of states: 4
States:
A B C D
Alphabet size: 2
Alphabet:
0 1

Enter transitions (state symbol next_state):
A 0 B
A 1 C
B 0 A
B 1 D
C 0 D
C 1 A
D 0 C
D 1 B

Enter accept states (1 for accept, 0 for not):
1 0 0 0
