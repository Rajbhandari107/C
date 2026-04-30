#include <stdio.h>
#include <string.h>

int tempCount = 1;

char temp[10][10];

// generate new temp
void newTemp(char *t) {
    sprintf(t, "t%d", tempCount++);
}

// Quadruple
void generateQuadruple(char exp[]) {
    char op, arg1, arg2;
    char t[10];

    printf("\n--- Quadruple ---\n");
    printf("Op\tArg1\tArg2\tResult\n");

    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == '+' || exp[i] == '*' || exp[i] == '-' || exp[i] == '/') {
            op = exp[i];
            arg1 = exp[i - 1];
            arg2 = exp[i + 1];

            newTemp(t);
            printf("%c\t%c\t%c\t%s\n", op, arg1, arg2, t);

            exp[i + 1] = t[0]; // replace
        }
    }
}

// Triple
void generateTriple(char exp[]) {
    char op, arg1, arg2;

    printf("\n--- Triple ---\n");
    printf("Index\tOp\tArg1\tArg2\n");

    int index = 0;

    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == '+' || exp[i] == '*' || exp[i] == '-' || exp[i] == '/') {
            op = exp[i];
            arg1 = exp[i - 1];
            arg2 = exp[i + 1];

            printf("%d\t%c\t%c\t%c\n", index++, op, arg1, arg2);

            exp[i + 1] = '0' + (index - 1); // reference
        }
    }
}

// Indirect Triple
void generateIndirectTriple(char exp[]) {
    char op, arg1, arg2;

    printf("\n--- Indirect Triple ---\n");
    printf("Pointer Table:\n");

    int index = 0;

    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == '+' || exp[i] == '*' || exp[i] == '-' || exp[i] == '/') {
            printf("Pointer[%d] -> %d\n", index, index);
            index++;
        }
    }
}

int main() {
    char exp1[20], exp2[20], exp3[20];

    printf("Enter expression: ");
    scanf("%s", exp1);

    strcpy(exp2, exp1);
    strcpy(exp3, exp1);

    generateQuadruple(exp1);
    generateTriple(exp2);
    generateIndirectTriple(exp3);

    return 0;
}

