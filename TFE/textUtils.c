#include <stdio.h>
#include <stdlib.h>

enum {
    BOLD = 1,
    ITALIC = 2,
    UNDERLINE = 4,
    STRIKETHROUGH = 8,
    INVERTED = 16,
    HIDDEN = 32,
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37,
    BG_BLACK = 40,
    BG_RED = 41,
    BG_GREEN = 42,
    BG_YELLOW = 43,
    BG_BLUE = 44,
    BG_MAGENTA = 45,
    BG_CYAN = 46,
    BG_WHITE = 47
};

char *style_text(char *text, int style) {
    char *buffer = malloc(1000);
    sprintf(buffer, "\033[%dm%s\033[0m", style, text);
    return buffer;
}

void display_title(void){
    printf("$$\\      $$\\                     $$\\           $$$$$$$\\  $$$$$$$\\  \n");
    printf("$$$\\    $$$ |                    \\__|          $$  __$$\\ $$  __$$\\ \n");
    printf("$$$$\\  $$$$ | $$$$$$\\ $$\\    $$\\ $$\\  $$$$$$\\  $$ |  $$ |$$ |  $$ |\n");
    printf("$$\\$$\\$$ $$ |$$  __$$\\$$\\  $$  |$$ |$$  __$$\\ $$ |  $$ |$$$$$$$\\ |\n");
    printf("$$ \\$$$  $$ |$$ /  $$ |\\$$\\$$  / $$ |$$$$$$$$ |$$ |  $$ |$$  __$$\\ \n");
    printf("$$ |\\$  /$$ |$$ |  $$ | \\$$$  /  $$ |$$   ____|$$ |  $$ |$$ |  $$ |\n");
    printf("$$ | \\_/ $$ |\\$$$$$$  |  \\$  /   $$ |\\$$$$$$$\\ $$$$$$$  |$$$$$$$  |\n");
    printf("\\__|     \\__| \\______/    \\_/    \\__| \\_______|\\_______/ \\_______/ \n");
}

void display_description(void){
    printf("This program is a simple movie database that allows you to add, remove, and display movies.\n");
    printf("You can also add, remove, and display genres.\n");
    printf("The program will also allow you to search for movies by genre.\n");
}

void exit_program(void){
    system("clear");
    printf("Goodbye!\n");
    printf("Made by: %s\n", style_text("Augustin Mauroy", GREEN));
    exit(EXIT_SUCCESS);
}