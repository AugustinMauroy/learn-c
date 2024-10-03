#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./textUtils.c"
#include "./gui.c"

#define MAX_TABLE_SIZE 1000

struct movie{
    int id;
    char name[50];
    int genreId;
    // Duration is in minutes
    int duration;
};
typedef struct movie movie;

struct movieTable{
    movie movies[MAX_TABLE_SIZE];
};
typedef struct movieTable movieTable;

struct genre{
    int id;
    char name[50];
};
typedef struct genre genre;

struct genreTable{
    genre genres[MAX_TABLE_SIZE];
};
typedef struct genreTable genreTable;

movieTable loadMovieTable(void){
    movieTable table;
    FILE *file = fopen("movieTable.bin", "rb");
    if (file) {
        fread(&table, sizeof(movieTable), 1, file);
        fclose(file);
    } else {
        // create an empty movie table
        table.movies[0].id = 0;
        strcpy(table.movies[0].name, "none");
        table.movies[0].genreId = 0;
        table.movies[0].duration = 0;
    }
    return table;
}

genreTable loadGenreTable(void){
    genreTable table;
    FILE *file = fopen("genreTable.bin", "rb");
    if (file) {
        fread(&table, sizeof(genreTable), 1, file);
        fclose(file);
    } else {
        // create an empty genre table
        table.genres[0].id = 0;
        strcpy(table.genres[0].name, "none");
    }
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

int main(void) {
    display_title();
    display_description();
    movieTable movieTable = loadMovieTable();
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
            saveMovieTable(movieTable);
            saveGenreTable(genreTable);
            exit_program();
            break;
    }

    return EXIT_SUCCESS;
};
