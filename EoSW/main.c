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
    char title[MAX_TITLE_LENGTH]; // suppose to be unique
    int year;
    char director[MAX_DIRECTOR_LENGTH];
    enum Genre genre;
    int duration;
} Movie;

typedef struct index {
    char title[MAX_TITLE_LENGTH];
    size_t offset; // position in the file
} Index;

void remove_newline(char *s) {
    char *p=s;
    while (*p && *p!='\n') p++;
    *p='\0';
}

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

void initializate_indexes(FILE *dbPtr, Index *ini_indexes[], size_t *indexes_size) {
    Movie movie;
    Index *index;
    *indexes_size = 0;

    fseek(dbPtr, 0, SEEK_SET);
    while (fread(&movie, sizeof(Movie), 1, dbPtr) == 1) {
        index = (Index *)malloc(sizeof(Index));
        strcpy(index->title, movie.title);
        index->offset = *indexes_size * sizeof(Movie);
        ini_indexes[*indexes_size] = index;
        (*indexes_size)++; 
    }

}

void release_indexes(Index *index[]) {
    for (int i = 0; index[i] != NULL; i++) {
        free(index[i]);
    }
}

void movie_form(bool modify, Movie *movie) {
    char * title = modify ? "Update movie" : "Add movie";
    printf("%s\n", title);
    printf("Enter movie title: ");
    fgets(movie->title, sizeof(movie->title), stdin);
    remove_newline(movie->title);

    printf("Enter release year: ");
    scanf("%d", &movie->year);
    getchar(); // Consume leftover newline

    printf("Enter director's name: ");
    fgets(movie->director, sizeof(movie->director), stdin);
    remove_newline(movie->director);

    printf("Select genre:\n");
    printf("0: Action\n1: Comedy\n2: Drama\n3: Horror\n4: Romance\n5: Thriller\n");
    printf("Enter genre number: ");
    scanf("%d", (int *)&movie->genre);
    getchar(); // Consume leftover newline

    printf("Enter duration (in minutes): ");
    scanf("%d", &movie->duration);
    getchar(); // Consume leftover newline
}

size_t search_by_title(const char *title, Index *indexes[]) {
    for (size_t i = 0; indexes[i] != NULL; i++) {
        if (strcmp(indexes[i]->title, title) == 0) {
            return indexes[i]->offset;
        }
    }

    return -1;
}

void add_movie(FILE *dbPtr, Index *indexes[], size_t *indexes_size) {
    Movie newMovie;
    Index *newIndex;

    movie_form(false, &newMovie);

    size_t offset_is_present = search_by_title(newMovie.title, indexes);
    
    if (offset_is_present != -1) {
        printf("Movie already exists in the database.\n");
        printf("Press enter to return to the main menu\n");
        getchar();
        return;
    }

    fseek(dbPtr, 0, SEEK_END);
    fwrite(&newMovie, sizeof(Movie), 1, dbPtr);

    (*indexes_size)++;
    newIndex = (Index *)malloc(sizeof(Index));
    strcpy(newIndex->title, newMovie.title);
    newIndex->offset = *indexes_size;
    indexes[*indexes_size] = newIndex;

    printf("Movie added successfully!\n");
    printf("Press enter to return to the main menu\n");
    getchar();
}

void list_movies(FILE *dbPtr) {
    Movie movie;
    bool hasMovies = false;
    fseek(dbPtr, 0, SEEK_SET);
    int page_size = 5;
    int movie_count = 0;
    int page_number = 1;
    bool quit = false;

    fseek(dbPtr, 0, SEEK_SET);
    while (fread(&movie, sizeof(Movie), 1, dbPtr) == 1) {
        if (movie_count % page_size == 0) {
            if (movie_count > 0) {
                printf("-------------------- Page %d --------------------\n", page_number - 1);
                printf("Press Enter for next page, or 'q' to quit: ");
                int c = getchar();
                if (c == 'q') {
                    quit = true;
                    break;
                }
                page_number++;
            }
            clear_screen();
            printf("-------------------- Page %d --------------------\n", page_number);
        }

        printf("Title: %s\n", movie.title);
        printf("Year: %d\n", movie.year);
        printf("Director: %s\n", movie.director);
        printf("Genre: %d\n", movie.genre);
        printf("Duration: %d\n", movie.duration);
        if (movie_count % page_size != page_size - 1) printf("--------------------\n");
        hasMovies = true;
        movie_count++;
    }

    if (!hasMovies) printf("Nothing in db\n");
    if (quit) {
        printf("Listing interrupted.\n");
    } else if (hasMovies) {
        printf("--------------------Page %d--------------------\n", page_number);
    }

    printf("Press enter to return to the main menu\n");
    getchar();
    return;
}

void drop_database(FILE *dbPtr, Index *indexes[], size_t *indexes_size) {
    release_indexes(indexes);
    fclose(dbPtr);
    remove("movies.db");

    dbPtr = openFile("movies.db");
    initializate_indexes(dbPtr, indexes, indexes_size);

    printf("Database dropped successfully!\n");
    printf("Press enter to return to the main menu\n");
    getchar();
}

void delete_movie(FILE *dbPtr, Index *indexes[]) {
    char title[MAX_TITLE_LENGTH];
    size_t indexToDelete = -1, i;
    Movie movie, lastMovie;
    long lastMovieOffset;

    printf("Enter the title of the movie to delete: ");
    fgets(title, sizeof(title), stdin);
    remove_newline(title);

    indexToDelete = search_by_title(title, indexes);

    if (indexToDelete == -1) {
        printf("Movie not found.\n");
        printf("Press enter to return to the main menu\n");
        getchar();
        return;
    }

    fseek(dbPtr, 0, SEEK_END);
    lastMovieOffset = ftell(dbPtr) - sizeof(Movie);

    if (lastMovieOffset == indexToDelete) {
        ftruncate(fileno(dbPtr), lastMovieOffset);

        // update the index
        for (i = 0; indexes[i] != NULL; i++) {
            if (strcmp(indexes[i]->title, title) == 0) {
                free(indexes[i]);
                indexes[i] = NULL;
                break;
            }
        }
    } else {
        fseek(dbPtr, lastMovieOffset, SEEK_SET);
        fread(&lastMovie, sizeof(Movie), 1, dbPtr);

        fseek(dbPtr, indexToDelete, SEEK_SET);
        fwrite(&lastMovie, sizeof(Movie), 1, dbPtr);

        // Truncate the file to remove the duplicate last movie
        ftruncate(fileno(dbPtr), lastMovieOffset);

        // Update the index
        for (i = 0; indexes[i] != NULL; i++) {
            if (strcmp(indexes[i]->title, title) == 0) {
                free(indexes[i]);
                indexes[i] = NULL;
                break;
            }
        }
    }

    printf("Movie deleted successfully!\n");
    printf("Press enter to return to the main menu\n");
    getchar();
}

void search_by_title_or_director(FILE *dbPtr, Index *indexes[]) {
    char search_term[MAX_TITLE_LENGTH];
    Movie movie;
    bool found = false;
    int search_option;

    printf("Enter the title to search: ");
    fgets(search_term, sizeof(search_term), stdin);
    remove_newline(search_term);

    size_t index = search_by_title(search_term, indexes);

    if (index != -1) {
        fseek(dbPtr, index, SEEK_SET);
        fread(&movie, sizeof(Movie), 1, dbPtr);

        printf("--------------------\n");
        printf("Title: %s\n", movie.title);
        printf("Year: %d\n", movie.year);
        printf("Director: %s\n", movie.director);
        printf("Genre: %d\n", movie.genre);
        printf("Duration: %d\n", movie.duration);
        printf("--------------------\n");
        found = true;
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
            remove_newline(search_term);

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

    printf("Press enter to return to the main menu\n");
    getchar();
}

void update_movie(FILE *dbPtr, Index *indexes[]) {
    char title[MAX_TITLE_LENGTH];
    unsigned int i;
    size_t indexToUpdate = -1;
    Movie movie;

    printf("Enter the title of the movie to update: ");
    fgets(title, sizeof(title), stdin);
    remove_newline(title);

    indexToUpdate = search_by_title(title, indexes);

    if (indexToUpdate == -1) {
        printf("Movie not found.\n");
        printf("Press enter to return to the main menu\n");
        getchar();
        return;
    }

    fseek(dbPtr, indexToUpdate, SEEK_SET);
    fread(&movie, sizeof(Movie), 1, dbPtr);

    printf("Current movie details:\n");
    printf("Title: %s\n", movie.title);
    printf("Year: %d\n", movie.year);
    printf("Director: %s\n", movie.director);
    printf("Genre: %d\n", movie.genre);
    printf("Duration: %d\n", movie.duration);
    printf("--------------------\n");

    movie_form(true, &movie);

    for (i = 0; indexes[i] != NULL; i++) {
        if (strcmp(indexes[i]->title, title) == 0) {
            strcpy(indexes[i]->title, movie.title);
            break;
        }
    }
    fseek(dbPtr, indexToUpdate, SEEK_SET);
    fwrite(&movie, sizeof(Movie), 1, dbPtr);


    printf("Movie updated successfully!\n");
    printf("Press enter to return to the main menu\n");
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
    size_t indexes_size;
    initializate_indexes(dbPtr, indexes, &indexes_size);

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

        char *title =
            "\nWelcome to the Movie Database 🎞️\n"
            "--------------------------------\n";

        int choice = multiple_choice(choices,7, false, title);

        switch (choice) {
            case 0:
                add_movie(dbPtr, indexes, &indexes_size);
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
                drop_database(dbPtr, indexes, &indexes_size);
                break;
            case 6:
            default:
                appRunning = false;
                break;
        }
    }

    fclose(dbPtr);
    release_indexes(indexes);

    printf("\nMade by Augustin Mauroy (%s on GitHub) for my End of Studies Work.\n\n", style_text("@AugustinMauroy", GREEN));

    return EXIT_SUCCESS;
}

