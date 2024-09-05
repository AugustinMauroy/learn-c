#include <stdlib.h>
#include <stdio.h>

void clear_screen(void){
    system("clear");
}

int multiple_choice(char *question, char *answers[], int numAnswers) {
    clear_screen();
    system("stty -icanon -echo"); // turn off canonical mode and echo
    int userAnswer = -1, userInput = 0;

    while (userAnswer == -1) {
        printf("\033[2J\033[1;1H");
        printf("%s\n", question);
        for (int i = 0; i < numAnswers; i++) {
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
        userInput = (userInput + numAnswers) % numAnswers;
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
