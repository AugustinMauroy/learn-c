#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include "./colors.h"

typedef struct {
    int x;
    int y;
} vec2;

void toggle_cursor(bool show) {
    printf("\033[?25%c", show ? 'h' : 'l');
}

void toggle_echo(bool show) {
    system(show ? "stty echo" : "stty -echo");
}

void toggle_canonical(bool show) {
    system(show ? "stty icanon" : "stty -icanon");
}

void clear_screen(void) {
    system("clear");
}

vec2 get_cursor_position(void) {
    printf("\033[6n");
    int x, y;
    scanf("\033[%d;%dR", &y, &x);
    return (vec2){x, y};
}

void set_cursor_position(vec2 pos) {
    printf("\033[%d;%dH", pos.y, pos.x);
}

char *style_text(char *text, int style) {
    char *buffer = malloc(1000);
    sprintf(buffer, "\033[%dm%s\033[0m", style, text);
    return buffer;
}

int multiple_choice(char *choices[], int num_choices, bool keep_after, char *title) {
    toggle_cursor(false);
    toggle_canonical(false);
    toggle_echo(false);
    clear_screen();
    int selected = 0;

    if (title != NULL) {
        printf("%s\n", title);
    }

    // Print all the options initially
    for (int i = 0; i < num_choices; i++) {
        printf("   %s\n", choices[i]);
    }
    vec2 pos = get_cursor_position();
    pos.y -= num_choices;
    set_cursor_position(pos);
    printf("%s", style_text("->", BOLD));

    while (true) {
        int c = getchar();
        if (c == 27) {
            getchar();
            switch (getchar()) {
                case 'A':
                    if (selected > 0) {
                        set_cursor_position(pos);
                        printf("  ");
                        pos.y--;
                        selected--;
                    }
                    break;
                case 'B':
                    if (selected < num_choices - 1) {
                        set_cursor_position(pos);
                        printf("  ");
                        pos.y++;
                        selected++;
                    }
                    break;
            }
            set_cursor_position(pos);
            printf("%s", style_text("->", BOLD));
        } else if (c == 10) {
            break;
        }
    }

    // Todo(@AugustinMauroy): add a way to remove the options and come back to initial position instead of clearing the screen
    keep_after ? printf("\n") : clear_screen();
    toggle_canonical(true);
    toggle_echo(true);
    toggle_cursor(true);

    return selected;
}
