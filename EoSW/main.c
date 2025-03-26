// TODO: add modify entry
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ui.c"

#define MAX_TITLE_LENGTH 100
#define MAX_DIRECTOR_LENGTH 50

enum Genre {
    ACTION,
    COMEDY,
    DRAMA,
    HORROR,
    ROMANCE,
    THRILLER
};

typedef struct movie {
    char title[MAX_TITLE_LENGTH];
    int year;
    char director[MAX_DIRECTOR_LENGTH];
    enum Genre genre;
    int duration;
} Movie;

typedef struct index {
    char title[MAX_TITLE_LENGTH];
    int offset;
} Index;

void mock_db(FILE *dbPtr) {
    Movie movies[] = {
        {"The Shawshank Redemption", 1994, "Frank Darabont", DRAMA, 142},
        {"The Godfather", 1972, "Francis Ford Coppola", DRAMA, 175},
        {"The Dark Knight", 2008, "Christopher Nolan", ACTION, 152},
        {"The Godfather: Part II", 1974, "Francis Ford Coppola", DRAMA, 202},
        {"The Lord of the Rings: The Return of the King", 2003, "Peter Jackson", ACTION, 201},
        {"Pulp Fiction", 1994, "Quentin Tarantino", THRILLER, 154},
        {"Schindler's List", 1993, "Steven Spielberg", DRAMA, 195},
        {"Star Wars: Episode I - The Phantom Menace", 1999, "George Lucas", ACTION, 136},
        {"Star Wars: Episode II - Attack of the Clones", 2002, "George Lucas", ACTION, 142},
        {"Star Wars: Episode III - Revenge of the Sith", 2005, "George Lucas", ACTION, 140},
        {"Star Wars: Episode IV - A New Hope", 1977, "George Lucas", ACTION, 121},
        {"Star Wars: Episode V - The Empire Strikes Back", 1980, "Irvin Kershner", ACTION, 124},
        {"Star Wars: Episode VI - Return of the Jedi", 1983, "Richard Marquand", ACTION, 131},
        {"Star Wars: Episode VII - The Force Awakens", 2015, "J.J. Abrams", ACTION, 138},
        {"Star Wars: Episode VIII - The Last Jedi", 2017, "Rian Johnson", ACTION, 152},
        {"Star Wars: Episode IX - The Rise of Skywalker", 2019, "J.J. Abrams", ACTION, 142},
        {"Rogue One: A Star Wars Story", 2016, "Gareth Edwards", ACTION, 133},
        {"Solo: A Star Wars Story", 2018, "Ron Howard", ACTION, 135},
        {"Harry Potter and the Philosopher's Stone", 2001, "Chris Columbus", ACTION, 152},
        {"Harry Potter and the Chamber of Secrets", 2002, "Chris Columbus", ACTION, 161},
        {"Harry Potter and the Prisoner of Azkaban", 2004, "Alfonso Cuarón", ACTION, 142},
        {"Harry Potter and the Goblet of Fire", 2005, "Mike Newell", ACTION, 157},
        {"Harry Potter and the Order of the Phoenix", 2007, "David Yates", ACTION, 138},
        {"Harry Potter and the Half-Blood Prince", 2009, "David Yates", ACTION, 153},
        {"Harry Potter and the Deathly Hallows – Part 1", 2010, "David Yates", ACTION, 146},
        {"Harry Potter and the Deathly Hallows – Part 2", 2011, "David Yates", ACTION, 130},
    };

    for (int i = 0; i < sizeof(movies) / sizeof(Movie); i++) {
        //@DEBUG
        //printf("Adding movie: %s\n", movies[i].title);
        fwrite(&movies[i], sizeof(Movie), 1, dbPtr);
    }
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

void initializate_indexes(FILE *dbPtr, Index *ini_indexes[]) {
    Movie movie;
    Index *index;
    int i = 0;

    fseek(dbPtr, 0, SEEK_SET);
    while (fread(&movie, sizeof(Movie), 1, dbPtr) == 1) {
        index = (Index *)malloc(sizeof(Index));
        strcpy(index->title, movie.title);
        index->offset = i;
        ini_indexes[i] = index;
        i++;
    }
}

void display_indexes(Index *indexes[]) {
    Index *index;
    for (int i = 0; indexes[i] != NULL; i++) {
        index = indexes[i];
        printf("Title: %s\n", index->title);
        printf("Offset: %d\n", index->offset);
    }
}

void release_indexes(Index *index[]) {
    for (int i = 0; index[i] != NULL; i++) {
        free(index[i]);
    }
}

void add_movie(FILE *dbPtr, Index *indexes[]) {
    Movie newMovie;
    Index *newIndex;
    int i = 0;
    bool movieExist = false; 

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

    while (indexes[i] != NULL) {
        if (strcmp(indexes[i]->title, newMovie.title) == 0) {
            movieExist = true;
            break;
        }
        i++;
    }

    if (movieExist) {
        printf("Movie already exists in the database.\n");
        printf("Press any key to return to the main menu\n");
        getchar();
        return;
    }

    fseek(dbPtr, 0, SEEK_END);
    fwrite(&newMovie, sizeof(Movie), 1, dbPtr);

    while (indexes[i] != NULL) i++;
    newIndex = (Index *)malloc(sizeof(Index));
    strcpy(newIndex->title, newMovie.title);
    newIndex->offset = i;
    indexes[i] = newIndex;
    indexes[i + 1] = NULL;

    printf("Movie added successfully!\n");
    printf("Press any key to return to the main menu\n");
    getchar();
}

void list_movies(FILE *dbPtr) {
    Movie movie;
    bool hasMovies = false;

    fseek(dbPtr, 0, SEEK_SET);
    // @todo(@AugustinMauroy): add a way/function to display movies in a "table" format
    // also investigate for a pagination system to make it digestible
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

void drop_database(FILE *dbPtr, Index *indexes[]) {
    for (int i = 0; indexes[i] != NULL; i++) {
        free(indexes[i]);
    }
    fclose(dbPtr);
    remove("movies.db");
    // re-initialize the db
    dbPtr = openFile("movies.db");
    // re-initialize indexes
    initializate_indexes(dbPtr, indexes);
    printf("Database dropped successfully!\n");
    printf("Press any key to return to the main menu\n");
    getchar();
}

void delete_movie(FILE *dbPtr, Index *indexes[]) {
    char title[MAX_TITLE_LENGTH];
    unsigned int i;
    int indexToDelete = -1;
    Movie movie, lastMovie;
    long lastMovieOffset;

    printf("Enter the title of the movie to delete: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    for (i = 0; indexes[i] != NULL; i++) {
        if (strcmp(indexes[i]->title, title) == 0) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == -1) {
        printf("Movie not found.\n");
        printf("Press any key to return to the main menu\n");
        getchar();
        return;
    }

    fseek(dbPtr, 0, SEEK_END);
    lastMovieOffset = ftell(dbPtr) - sizeof(Movie);

    if (lastMovieOffset == indexToDelete * sizeof(Movie)) {
        ftruncate(fileno(dbPtr), lastMovieOffset);
    } else {
        fseek(dbPtr, lastMovieOffset, SEEK_SET);
        fread(&lastMovie, sizeof(Movie), 1, dbPtr);

        fseek(dbPtr, indexToDelete * sizeof(Movie), SEEK_SET);
        fwrite(&lastMovie, sizeof(Movie), 1, dbPtr);

        // Truncate the file to remove the duplicate last movie
        ftruncate(fileno(dbPtr), lastMovieOffset);

        // update index
        for (i = 0; indexes[i] != NULL; i++) {
            if (strcmp(indexes[i]->title, lastMovie.title) == 0) {
                indexes[i]->offset = indexToDelete;
                break;
            }
        }
    }

    // swap
    Index *temp = indexes[indexToDelete];
    indexes[indexToDelete] = indexes[i - 1];
    indexes[i - 1] = temp;
    indexes[i - 1] = NULL;

    printf("Movie deleted successfully!\n");
    printf("Press any key to return to the main menu\n");
    getchar();
}

void search_by_title_or_director(FILE *dbPtr, Index *indexes[]) {
    char search_term[MAX_TITLE_LENGTH];
    Movie movie;
    bool found = false;
    int search_option;

    printf("Enter the title to search: ");
    fgets(search_term, sizeof(search_term), stdin);
    search_term[strcspn(search_term, "\n")] = '\0';

    for (int i = 0; indexes[i] != NULL; i++) {
        if (strcasecmp(indexes[i]->title, search_term) == 0) {
            fseek(dbPtr, indexes[i]->offset * sizeof(Movie), SEEK_SET);
            fread(&movie, sizeof(Movie), 1, dbPtr);

            printf("--------------------\n");
            printf("Title: %s\n", movie.title);
            printf("Year: %d\n", movie.year);
            printf("Director: %s\n", movie.director);
            printf("Genre: %d\n", movie.genre);
            printf("Duration: %d\n", movie.duration);
            printf("--------------------\n");
            found = true;
            break;
        }
    }

    if (!found) {
        printf("No movie found with the title \"%s\".\n", search_term);
        printf("Do you want to search by director instead?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("Enter your choice: ");
        scanf("%d", &search_option);
        getchar(); 

        if (search_option == 1) {
            printf("Enter the director's name to search: ");
            fgets(search_term, sizeof(search_term), stdin);
            search_term[strcspn(search_term, "\n")] = '\0';

            found = false;
            fseek(dbPtr, 0, SEEK_SET);
            while (fread(&movie, sizeof(Movie), 1, dbPtr) == 1) {
                if (strcasecmp(movie.director, search_term) == 0) {
                    printf("--------------------\n");
                    printf("Title: %s\n", movie.title);
                    printf("Year: %d\n", movie.year);
                    printf("Director: %s\n", movie.director);
                    printf("Genre: %d\n", movie.genre);
                    printf("Duration: %d\n", movie.duration);
                    printf("--------------------\n");
                    found = true;
                }
            }

            if (!found) {
                printf("No movie found with the director \"%s\".\n", search_term);
            }
        }
    }

    printf("Press any key to return to the main menu\n");
    getchar();
}

void update_movie(FILE *dbPtr, Index *indexes[]) {
    char title[MAX_TITLE_LENGTH];
    unsigned int i;
    int indexToUpdate = -1;
    Movie movie;

    printf("Enter the title of the movie to update: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    for (i = 0; indexes[i] != NULL; i++) {
        if (strcmp(indexes[i]->title, title) == 0) {
            indexToUpdate = i;
            break;
        }
    }

    if (indexToUpdate == -1) {
        printf("Movie not found.\n");
        printf("Press any key to return to the main menu\n");
        getchar();
        return;
    }

    fseek(dbPtr, indexToUpdate * sizeof(Movie), SEEK_SET);
    fread(&movie, sizeof(Movie), 1, dbPtr);

    printf("Enter new title: ");
    fgets(movie.title, sizeof(movie.title), stdin);
    movie.title[strcspn(movie.title, "\n")] = '\0';

    printf("Enter new release year: ");
    scanf("%d", &movie.year);
    getchar(); // Consume leftover newline

    printf("Enter new director's name: ");
    fgets(movie.director, sizeof(movie.director), stdin);
    movie.director[strcspn(movie.director, "\n")] = '\0';

    printf("Select new genre:\n");
    printf("0: Action\n1: Comedy\n2: Drama\n3: Horror\n4: Romance\n5: Thriller\n");
    printf("Enter genre number: ");
    scanf("%d", (int *)&movie.genre);
    getchar(); // Consume leftover newline

    printf("Enter new duration (in minutes): ");
    scanf("%d", &movie.duration);
    getchar(); // Consume leftover newline

    fseek(dbPtr, indexToUpdate * sizeof(Movie), SEEK_SET);
    fwrite(&movie, sizeof(Movie), 1, dbPtr);

    printf("Movie updated successfully!\n");
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

    Index *indexes[100];
    initializate_indexes(dbPtr, indexes);
    //@DEBUG
    //display_indexes(indexes);

    while (appRunning) {
        char *choices[] = {
            "Add movie",
            "List movies",
            "Search movie",
            "Delete movie",
            "Update movie",
            "Drop database",
            "Exit"
        };

        int choice = multiple_choice(choices,7, false);

        switch (choice) {
            case 0:
                add_movie(dbPtr, indexes);
                break;
            case 1:
                list_movies(dbPtr);
                break;
            case 2:
                search_by_title_or_director(dbPtr, indexes);
                break;
            case 3:
                delete_movie(dbPtr, indexes);
                break;
            case 4:
                update_movie(dbPtr, indexes);
                break;
            case 5:
                drop_database(dbPtr, indexes);
                break;
            case 6:
            default:
                appRunning = false;
                break;
        }
    }

    fclose(dbPtr);
    release_indexes(indexes);

    return EXIT_SUCCESS;
}

