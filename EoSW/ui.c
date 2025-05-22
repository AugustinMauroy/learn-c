#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "./colors.h"

typedef struct {
    int x;
    int y;
} point;

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

point get_cursor_position(void) {
    printf("\033[6n");
    int x, y;
    scanf("\033[%d;%dR", &y, &x);
    return (point){x, y};
}

void set_cursor_position(point pos) {
    printf("\033[%d;%dH", pos.y, pos.x);
}

char *style_text(char *text, int style) {
    char *buffer = malloc(1000);
    sprintf(buffer, "\033[%dm%s\033[0m", style, text);
    return buffer;
}

size_t multiple_choice(char *choices[], size_t num_choices, char *title) {
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
    point pos = get_cursor_position();
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

    clear_screen();
    toggle_canonical(true);
    toggle_echo(true);
    toggle_cursor(true);

    return selected;
}
