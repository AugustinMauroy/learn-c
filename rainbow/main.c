// command to build the program
// clang ./main.c -o rainbow -Wall -Wextra -Werror -Wpedantic -std=c99 -lncurses
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

struct termios orig_termios;

void reset_terminal_mode(void){
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode(void){
    struct termios new_termios;
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit(char *pressedKey){
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    if (select(1, &fds, NULL, NULL, &tv) > 0) {
        *pressedKey = getchar();
        return 1;
    }
    return 0;
}

int main(void) {
    int state = 0;
    char *colors[] = {"\033[31m", "\033[33m", "\033[32m", "\033[36m", "\033[34m", "\033[35m", "\033[31m"};
    char *new_colors[7];
    char pressedKey;

    while (!kbhit(&pressedKey)) {
        for (int i = 0; i < 7; i++) {
            new_colors[i] = colors[(i + state) % 7];
            printf("%s%c", new_colors[i], "RAINBOW"[i]);
        }
        printf("\n");
        usleep(50000);
        state = (state + 1) % 7;
    }
    
    printf("\033[0m Bey!\n Software by: \033[32m@augustinmauroy\033[0m on github\n");

    return EXIT_SUCCESS;
}
