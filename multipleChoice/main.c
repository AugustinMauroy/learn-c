#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int multipleChoiceInteface(char *question, char *answers[], int correctAnswer) {
    system("clear");
    system("stty -icanon -echo"); // turn off canonical mode and echo
    int userAnswer = -1, userInput;

    while (userAnswer == -1) {
        printf("\033[2J\033[1;1H");
        printf("%s\n", question);
        for (int i = 0; i < 4; i++) {
            if (i == userInput) {
                printf("-> ");
            } else {
                printf("   ");
            }
            printf("%s\n", answers[i]);
        }
        int c = getchar();
        if (c == 27) {
            getchar();
            switch (getchar()) {
                case 'A':
                    userInput--;
                    break;
                case 'B':
                    userInput++;
                    break;
            }
        } else if (c == 10) {
            userAnswer = userInput;
        }
        userInput = (userInput + 4) % 4;
    }
    
    system("stty icanon echo"); // turn on canonical mode and echo

    return userAnswer;
}

void toggleCursor(int show) {
    if (show) {
        printf("\e[?25h");
    } else {
        printf("\e[?25l");
    }
}

int main(void) {
    char *answers[] = {
        "Brussels",
        "Paris",
        "Berlin",
        "Amsterdam"
    };

    toggleCursor(0);
    printf("What is the capital of Belgium?\n");
    int userAnswer = multipleChoiceInteface("What is the capital of Belgium?", answers, 1);

    if (userAnswer == 0) {
        printf("\033[0;32m✔︎\033[0m Correct!\n");
    } else {
        printf("\033[0;31m✘\033[0m Incorrect!\n");
        printf("The correct answer is: %s\n", answers[0]);
    }

    toggleCursor(1);
    return EXIT_SUCCESS;
}
