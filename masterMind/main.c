#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_TRIES 10
#define IS_CHEAT_MODE 1

void flushInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void fillArray(int arr[], int input, int length) {
    for (int i = 0; i < length; i++) arr[i] = input;
}

void copyArray(int arr1[], int arr2[], int length) {
    for (int i = 0; i < length; i++) arr1[i] = arr2[i];
}

bool sameArray(int arr1[], int arr2[], int length) {
    for (int i = 0; i < length; i++) {
        if (arr1[i] != arr2[i]) return false;
    }
    return true;
}

int askColor(void) {
    char input, result;

    // loop until the user enters a valid color
    do {
        input = getchar();
        flushInputBuffer();
        result = tolower(input);
        if (result != 'r' && result != 'g' && result != 'y' && result != 'b') {
            printf("Invalid color, please use (r, g, y, b), try again : ");
        }
    } while (result != 'r' && result != 'g' && result != 'y' && result != 'b');

    // return the index of the color
    switch (result) {
    case 'r':
        return 0;
    case 'g':
        return 1;
    case 'y':
        return 2;
    case 'b':
        return 3;
    };

    // should never happen
    return -1;
}

int main(void) {
    char *colors[4] = {"\033[0;31m", "\033[0;32m", "\033[0;33m", "\033[0;34m"}; // red, green, yellow, blue
    char *resetColors = "\033[0m";
    int balls[4];
    unsigned int tries;
    int rightPlace = 0, rightColor = 0;

    srand(time(NULL));
    fillArray(balls, -1, 4);

    // assign random colors to balls
    for (int i = 0; i < 4; i++) balls[i] = (rand() % 4);


    printf("Welcome to the \e[1mMastermind\e[m game!\n");
    printf("To play the game, simply enter R for red, G for green, Y for yellow and B for blue.\n");
    printf("Have Fun !!!\n");

    // cheat mode
    if (IS_CHEAT_MODE) {
        printf("Cheat mode: ");
        for (int i = 0; i < 4; i++) {
            printf("%s*%s ", colors[balls[i]], resetColors);
        };
        printf("\n");
    }

    // game loop
    for (tries = 0; tries < MAX_TRIES; tries++) {
        int input[4];
        fillArray(input, -1, 4);
        for (int i = 0; i < 4; i++) {
            i == 0 && tries == 0 ? printf("Enter a color (R, G, Y, B) : ") : printf("Enter a color : ");
            input[i] = askColor();
        };

        if (sameArray(input, balls, 4)) {
            printf("You found the solution in %d tries!\n", tries + 1);
            break;
        };

        // Test the input and display the result
        rightPlace = 0;
        rightColor = 0;
        int inputCopy[4], ballsCopy[4];
        copyArray(inputCopy, input, 4);
        copyArray(ballsCopy, balls, 4);
        for (int i = 0; i < 4; i++) {
            if (input[i] == balls[i]) {
                rightPlace++;
                inputCopy[i] = -1;
                ballsCopy[i] = -2;
            };
        };

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (inputCopy[i] == ballsCopy[j]) {
                    rightColor++;
                    inputCopy[i] = -1;
                    ballsCopy[j] = -2;
                };
            };
        };
        
        printf("Right place: %d, Right color: %d\n", rightPlace, rightColor);

        // display which balls are in the right place
        if(rightPlace > 0) {
            printf("Right place: ");
            for (int i = 0; i < 4; i++) {
                if (input[i] == balls[i]) {
                    printf("%s*%s ", colors[balls[i]], resetColors);
                } else {
                    printf("x ");
                };
            };
            printf("\n");
        }
    };

    if (tries == MAX_TRIES) {
        printf("You lost, the solution was: ");
    };

    // display the solution
    printf("Solution: ");
    for (int i = 0; i < 4; i++) {
        printf("%s*%s ", colors[balls[i]], resetColors);
    };

    return EXIT_SUCCESS;
}