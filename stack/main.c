#include <stdlib.h>
#include <stdio.h>

#define MAX_INPUT_SIZE 100
#define STACK_SIZE 10


int s2i(char *s) {
    int result = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if(s[i] < '0' || s[i] > '9') continue;
        result = result * 10 + s[i] - '0';
    }
    return result;
}

void displayStackChar(char *input[STACK_SIZE]) {
    for (int i = 0; i < STACK_SIZE; i++) {
        if(input[i][0] >= '0' && input[i][0] <= '9') {
            printf("\033[0;32m%s\033[0m ", input[i]);
        } else {
            printf("%s ", input[i]);
        }
    }
    printf("\n");
}

int main(void) {
    char *input[STACK_SIZE] = {"42","2","+"};
    int stack[STACK_SIZE];

    //printf("Enter a postfix expression: ");
    // TODO: read user input

    displayStackChar(input);

    int result = 0;
    int top = 0;
    for (int i = 0; i < STACK_SIZE; i++) {
        // if not operator, push to stack
        if(input[i][0] >= '0' && input[i][0] <= '9') {
            stack[top] = s2i(input[i]);
            top++;
        } else {
            if(top < 2) {
                printf("Invalid expression\n");
                return EXIT_FAILURE;
            }
            int operand1 = stack[top - 2];
            int operand2 = stack[top - 1];
            top -= 2;
            switch(input[i][0]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
            }
            stack[top] = result;
            top++;
        }
    }

    printf("Result: %d\n", result);
    
    return EXIT_SUCCESS;
};