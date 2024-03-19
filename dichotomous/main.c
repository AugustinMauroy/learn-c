#include <stdio.h>
#include <stdlib.h>

int main(void) { 
    char input; // + or - or =
    int max;
    int min = 0;
    printf("Enter the maximum number: ");
    scanf("%d", &max);
    
    while (input != '=') {
        if(min == max || min + 1 == max) {
            printf("You're cheating!\n");
            printf("Hurensohn!\n");
            return EXIT_FAILURE;
        }

        int guess = (max + min) / 2;
        printf("Is your number %d? (use + || - || =) ", guess);
        scanf("%c", &input);
        if (input == '+') {
            min = guess;
        } else if (input == '-') {
            max = guess;
        } else if (input != '=') {
            printf("Invalid input\n");
        }
    }
    printf("I won!\n");
}
