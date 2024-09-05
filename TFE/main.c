#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./textUtils.c"
#include "./gui.c"

struct movieTable{
    int id;
    char name[50];
    int genreId;
    // Duration is in minutes
    int duration;
};
typedef struct movieTable movieTable;

struct genreTable{
    int id;
    char name[50];
};
typedef struct genreTable genreTable;

genreTable loadGenreTable(void){
    // search for a binary file
    FILE *file = fopen("genreTable.bin", "rb");
    if (file == NULL){
        // if the file does not exist, create it
        file = fopen("genreTable.bin", "wb");
        genreTable newTable = {0, "none"};
        fwrite(&newTable, sizeof(genreTable), 1, file);
        fclose(file);
        file = fopen("genreTable.bin", "rb");
    }
    genreTable table;
    fread(&table, sizeof(genreTable), 1, file);
    fclose(file);
    return table;
}

movieTable loadMovieTable(void){
    // search for a binary file
    FILE *file = fopen("movieTable.bin", "rb");
    if (file == NULL){
        // if the file does not exist, create it
        file = fopen("movieTable.bin", "wb");
        movieTable newTable = {0, "Default Movie", 0, 0};
        fwrite(&newTable, sizeof(movieTable), 1, file);
        fclose(file);
        file = fopen("movieTable.bin", "rb");
    }
    movieTable table;
    fread(&table, sizeof(movieTable), 1, file);
    fclose(file);
    return table;
}

void saveMovieTable(movieTable table){
    FILE *file = fopen("movieTable.bin", "wb");
    fwrite(&table, sizeof(movieTable), 1, file);
    fclose(file);
}

void saveGenreTable(genreTable table){
    FILE *file = fopen("genreTable.bin", "wb");
    fwrite(&table, sizeof(genreTable), 1, file);
    fclose(file);
}

void addGenre(genreTable *table){
    // id is unique and auto-incremented
    // name is unique
    char name[50];
    printf("Enter the name of the genre: ");
    fgets(name, 50, stdin);
    // -> is the same as (*table).id
    table->id++;
    strcpy(table->name, name);
}

void displayGenres(genreTable table){
    printf("ID: %d\n", table.id);
    printf("Name: %s\n", table.name);
}

int main(void) {
    display_title();
    display_description();
    movieTable table = loadMovieTable();
    genreTable genreTable = loadGenreTable();

    char *answers[] = {"Add Movie", "Remove Movie", "Display Movies", "Add Genre", "Remove Genre", "Display Genres", "Search Movies by Genre", "Exit"};
    char answers_size = sizeof(answers) / sizeof(answers[0]);

    int choice = multiple_choice("What would you like to do?", answers, 8);
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
            addGenre(&genreTable);
            break;
        case 4:
            printf("Remove Genre\n");
            break;
        case 5:
            displayGenres(genreTable);
            break;
        case 6:
            printf("Search Movies by Genre\n");
            break;
        case 7:
            saveMovieTable(table);
            saveGenreTable(genreTable);
            exit_program();
            break;
    }

    return EXIT_SUCCESS;
};
