#include <stdio.h>
#include <ctype.h>

int tempCount = 1;

void generate(char op, char op1, char op2) {
    printf("t%d = %c %c %c\n", tempCount++, op1, op, op2);
}

int main() {
    char exp[20];
    char stack[20];
    int top = -1;

    printf("Enter expression (e.g., a+b*c): ");
    scanf("%s", exp);

    for (int i = 0; exp[i] != '\0'; i++) {

        // If operand → push
        if (isalnum(exp[i])) {
            stack[++top] = exp[i];
        }

        // If operator
        else {
            char op2 = stack[top--];
            char op1 = stack[top--];

            generate(exp[i], op1, op2);

            // Push temp result
            stack[++top] = 't';  // simplified temp
        }
    }

    return 0;
}
