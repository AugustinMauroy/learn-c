#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GREEN "\033[0;32m"
#define RESET "\033[0m"

int main(void) {
    int userInput;

    do {
        printf("Enter a number between 1 and 10: ");
        scanf("%d", &userInput);
    } while (userInput < 1 || userInput > 10);

    printf("\033[1;1H\033[2J"); // Clear the screen
    printf("╭──────────────────────╮\n");
    printf("│ %sMultiplication Table%s │\n", GREEN, RESET);
    printf("╞──────────────────────╡\n");
    for (int i = 1; i <= 10; i++) {
        char text[100];
        sprintf(text, "%2d * %2d = %3d", userInput, i, userInput * i);

        int padding = (22 - strlen(text)) / 2;
        printf("│");
        for (int j = 0; j < padding; j++) {
            printf(" ");
        }
        printf("%s", text);
        for (int j = 0; j < padding; j++) {
            printf(" ");
        }
        // add extra space if the text is odd
        if (strlen(text) % 2 != 0) {
            printf(" ");
        }
        printf("│\n");
    }

    printf("╰──────────────────────╯\n");

    return EXIT_SUCCESS;
}
