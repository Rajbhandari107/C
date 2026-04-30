#include <stdio.h>
#include <string.h>

char stack[20];
char input[20];
int top = -1;

void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';
}

void pop(int n) {
    top -= n;
    stack[top + 1] = '\0';
}

void check() {
    // Reduce E->E+E
    if (strcmp(stack + top - 2, "E+E") == 0) {
        pop(3);
        push('E');
        printf("Reduce: E->E+E\n");
    }
    // Reduce E->E*E
    else if (strcmp(stack + top - 2, "E*E") == 0) {
        pop(3);
        push('E');
        printf("Reduce: E->E*E\n");
    }
    // Reduce E->id
    else if (stack[top] == 'i' && stack[top-1] == 'd') {
        pop(2);
        push('E');
        printf("Reduce: E->id\n");
    }
}

int main() {
    strcpy(input, "id+id*id$");
    int i = 0;

    printf("Stack\tInput\tAction\n");

    while (input[i] != '$') {
        push(input[i]);
        printf("%s\t%s\tShift\n", stack, input + i + 1);
        i++;

        check();
    }

    if (strcmp(stack, "E") == 0)
        printf("Accepted\n");
    else
        printf("Rejected\n");

    return 0;
}
