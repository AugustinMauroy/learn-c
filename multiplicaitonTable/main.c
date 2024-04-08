#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int userInput;

    do {
        printf("Enter a number between 1 and 10: ");
        scanf("%d", &userInput);
    } while (userInput < 1 || userInput > 10);

    for (int i = 1; i <= 10; i++) {
        printf("%d * %d = %d\n", userInput, i, userInput * i);
    }

    return EXIT_SUCCESS;
}
