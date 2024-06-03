#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
        if(input[i] == NULL) break;
        if(input[i][0] >= '0' && input[i][0] <= '9') {
            printf("\033[0;32m%s\033[0m ", input[i]);
        } else {
            printf("%s ", input[i]);
        }
    }
    printf("\n");
}

int main(void) {
    char *input[MAX_INPUT_SIZE];
    int stack[STACK_SIZE];

    // Explain how to use the program
    printf("This program is a simple calculator that can perform addition, subtraction, multiplication, and division.\n");
    printf("The program will ask you to enter an expression in the form of a space-separated list of numbers and operators.\n");
    printf("For example, to calculate 2 + 3, you should enter: 2 + 3\n");
    printf("The program will then display the result of the expression.\n");
    printf("\nEnter an expression: ");
    char buffer[MAX_INPUT_SIZE];
    fgets(buffer, MAX_INPUT_SIZE, stdin);
    char *token = strtok(buffer, " ");
    int i = 0;
    while(token != NULL) {
        input[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    for (int j = i; j < MAX_INPUT_SIZE; j++) {
        input[j] = NULL;
    }


    displayStackChar(input);

    int result = 0;
    int top = 0;
    for (int i = 0; i < MAX_INPUT_SIZE; i++) {
        if(input[i] == NULL) break;
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

    if(top != 1) {
        printf("Invalid expression\n");
        return EXIT_FAILURE;
    }

    printf("Result: %d\n", stack[0]);
    return EXIT_SUCCESS;
};