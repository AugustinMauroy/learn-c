#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

struct vec2 {
    int x;
    int y;
};
typedef struct vec2 vec2;
struct vec3 {
    int x;
    int y;
    int z;
};
typedef struct vec3 vec3;

void toggle_cursor(bool show) {
    printf("\033[?25%c", show ? 'h' : 'l');
}

void toggle_echo(bool show) {
    system(show ? "stty echo" : "stty -echo");
}

void toggle_canonical(bool show) {
    system(show ? "stty icanon" : "stty -icanon");
}

void clear_screen() {
    system("clear");
}

vec2 get_cursor_position() {
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


int main(void) {
    char *choices[] = {"Option 1", "Option 2", "Option 3"};
    
    clear_screen();
    int selected = multiple_choice(choices, 3, true);

    printf("Selected: %s\n", choices[selected]);

    return EXIT_SUCCESS;
}