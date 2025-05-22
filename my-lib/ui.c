#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct vec2 {
    int x;
    int y;
};
typedef struct vec2 vec2;

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

char *style_text(char *text, int style) {
    char *buffer = malloc(1000);
    sprintf(buffer, "\033[%dm%s\033[0m", style, text);
    return buffer;
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

void set_cursor_position_relative(vec2 pos) {
    printf("\033[%d;%dH", pos.y, pos.x);
}

int screen_width(void) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void centered_text(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int width = screen_width();
    int len = vsnprintf(NULL, 0, format, args);
    int start = (width - len) / 2;
    printf("\033[%dG", start);
    vprintf(format, args);

    va_end(args);
}

int multiple_choice(char *choices[], int num_choices, bool keep_after) {
    toggle_cursor(false);
    toggle_canonical(false);
    toggle_echo(false);
    int selected = 0;

    // Print all the options initially
    for (int i = 0; i < num_choices; i++) {
        printf("   %s\n", choices[i]);
    }
    vec2 pos = get_cursor_position();
    pos.y -= num_choices;
    set_cursor_position(pos);
    printf("->");

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
            printf("->");
        } else if (c == 10) {
            break;
        }
    }

    keep_after ? printf("\n") : clear_screen();
    toggle_canonical(true);
    toggle_echo(true);
    toggle_cursor(true);

    return selected;
}

void print_table(char *headers[], int num_headers, char *rows[], int num_rows) {
    int *max_widths = (int *)malloc(num_headers * sizeof(int));
    for (int i = 0; i < num_headers; i++) {
        max_widths[i] = strlen(headers[i]);
    }

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_headers; j++) {
            int len = strlen(rows[i * num_headers + j]);
            if (len > max_widths[j]) {
                max_widths[j] = len;
            }
        }
    }

    // Print top border
    for (int i = 0; i < num_headers; i++) {
        printf("+");
        for (int j = 0; j < max_widths[i] + 2; j++) {
            printf("-");
        }
    }
    printf("+\n");

    for (int i = 0; i < num_headers; i++) {
        printf("| %-*s ", max_widths[i], headers[i]);
    }
    printf("|\n");

    // Print middle border
    for (int i = 0; i < num_headers; i++) {
        printf("+");
        for (int j = 0; j < max_widths[i] + 2; j++) {
            printf("-");
        }
    }
    printf("+\n");

    // Print rows
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_headers; j++) {
            printf("| %-*s ", max_widths[j], rows[i * num_headers + j]);
        }
        printf("|\n");
    }

    // Print bottom border
    for (int i = 0; i < num_headers; i++) {
        printf("+");
        for (int j = 0; j < max_widths[i] + 2; j++) {
            printf("-");
        }
    }
    printf("+\n");

    free(max_widths);
}
