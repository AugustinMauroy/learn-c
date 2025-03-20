/**
 * remaining workarounds:
 * - create an index (in memory)
 *   - de-block search
 *   - de-block delete
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ui.c"

enum Genre {
    ACTION,
    COMEDY,
    DRAMA,
    HORROR,
    ROMANCE,
    THRILLER
};

typedef struct movie {
    char title[100];
    int year;
    char director[100];
    enum Genre genre;
    int duration;
} Movie;

void mock_db(FILE *dbPtr) {
    Movie movies[] = {
        {"The Shawshank Redemption", 1994, "Frank Darabont", DRAMA, 142},
        {"The Godfather", 1972, "Francis Ford Coppola", DRAMA, 175},
        {"The Dark Knight", 2008, "Christopher Nolan", ACTION, 152},
        {"The Godfather: Part II", 1974, "Francis Ford Coppola", DRAMA, 202},
        {"The Lord of the Rings: The Return of the King", 2003, "Peter Jackson", ACTION, 201},
        {"Pulp Fiction", 1994, "Quentin Tarantino", THRILLER, 154},
        {"Schindler's List", 1993, "Steven Spielberg", DRAMA, 195},
    };

    for (int i = 0; i < sizeof(movies) / sizeof(Movie); i++) {
        //@DEBUG
        //printf("Adding movie: %s\n", movies[i].title);
        fwrite(&movies[i], sizeof(Movie), 1, dbPtr);
    }
}

void not_impl(char *msg) {
    printf("Not implemented: %s\n", msg);
    printf("Press any key to return to the main menu\n");
    getchar();
}

FILE *openFile(const char *filename) {
    FILE *file = fopen(filename, "r+b");

    if (file == NULL) {
        file = fopen(filename, "w+b");
        //@DEBUG
        mock_db(file);
    }

    return file;
}

void add_movie(FILE *dbPtr) {
    Movie newMovie;

    printf("Enter movie title: ");
    fgets(newMovie.title, sizeof(newMovie.title), stdin);
    newMovie.title[strcspn(newMovie.title, "\n")] = '\0'; // Remove trailing newline

    printf("Enter release year: ");
    scanf("%d", &newMovie.year);
    getchar(); // Consume leftover newline

    printf("Enter director's name: ");
    fgets(newMovie.director, sizeof(newMovie.director), stdin);
    newMovie.director[strcspn(newMovie.director, "\n")] = '\0'; // Remove trailing newline

    printf("Select genre:\n");
    printf("0: Action\n1: Comedy\n2: Drama\n3: Horror\n4: Romance\n5: Thriller\n");
    printf("Enter genre number: ");
    scanf("%d", (int *)&newMovie.genre);
    getchar(); // Consume leftover newline

    printf("Enter duration (in minutes): ");
    scanf("%d", &newMovie.duration);
    getchar(); // Consume leftover newline

    fseek(dbPtr, 0, SEEK_END);
    fwrite(&newMovie, sizeof(Movie), 1, dbPtr);

    printf("Movie added successfully!\n");
    printf("Press any key to return to the main menu\n");
    getchar();
}

void list_movies(FILE *dbPtr) {
    Movie movie;
    bool hasMovies = false;

    fseek(dbPtr, 0, SEEK_SET);
    // @todo(@AugustinMauroy): add a way/function to display movies in a "table" format
    while (fread(&movie, sizeof(Movie), 1, dbPtr) == 1) {
        // hacky way to know when it's the first movie
        if (!hasMovies) printf("--------------------\n");
        printf("Title: %s\n", movie.title);
        printf("Year: %d\n", movie.year);
        printf("Director: %s\n", movie.director);
        printf("Genre: %d\n", movie.genre);
        printf("Duration: %d\n", movie.duration);
        printf("--------------------\n");
        hasMovies = true;
    }

    if (!hasMovies) printf("Nothing in db\n");

    printf("Press any key to return to the main menu\n");
    getchar();
}

void drop_database(FILE *dbPtr) {
    fclose(dbPtr);
    remove("movies.db");
    // re-initialize the db
    dbPtr = openFile("movies.db");
    printf("Database dropped successfully!\n");
    printf("Press any key to return to the main menu\n");
    getchar();
}

int main(void) {
    // I assume that `db` file will have correct structure
    FILE *dbPtr = openFile("movies.db");
    bool appRunning = true;

    if (dbPtr == NULL) {
        printf("Error: Unable to open file\n");
        return EXIT_FAILURE;
    }

    while (appRunning) {
        char *choices[] = {
            "Add movie",
            "List movies",
            "Search movie",
            "Delete movie",
            "Drop database",
            "Exit"
        };

        int choice = multiple_choice(choices, 6, false);

        switch (choice) {
            case 0:
                add_movie(dbPtr);
                break;
            case 1:
                list_movies(dbPtr);
                break;
            case 2:
                /**
                 * @todo Implement search movie
                 * - Need minmum 2 search criteria
                 * - Search by title, director, genre, year, duration
                 * - Display all movies that match the search criteria
                 */
                not_impl("Search movie");
                break;
            case 3: 
                not_impl("Delete movie");
                break;
            case 4:
                drop_database(dbPtr);
                break;
            case 5:
            default:
                appRunning = false;
                break;
        }
    }

    fclose(dbPtr);

    return EXIT_SUCCESS;
}

