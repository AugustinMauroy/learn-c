#include "./colors.h"
#include "./ui.c"
#include "./utils.c"

int main(void) {
    char *answers[] = {"Add Movie", "Remove Movie", "Display Movies", "Add Genre", "Remove Genre", "Display Genres", "Search Movies by Genre", "Exit"};
    char answers_size = sizeof(answers) / sizeof(answers[0]);

    display_title();
    display_description();

    int choice = multiple_choice(answers, 8, false);
    
    switch (choice) {
        case 0:
            printf("Add Movie\n");
            break;
        case 1:
            printf("Remove Movie\n");
            break;
        case 2:
            printf("Display Movies\n");
            break;
        case 3:
            printf("Add Genre\n");
            break;
        case 4:
            printf("Remove Genre\n");
            break;
        case 5:
            printf("Display Genres\n");
            break;
        case 6:
            printf("Search Movies by Genre\n");
            break;
        case 7:
            exit_program();
            break;
        default:
            exit_program();
            break;
    }
}