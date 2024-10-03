#include "./colors.h"
#include "./ui.c"
#include "./utils.c"

#define MAX_TITLE_LENGTH 100

typedef struct {
    int id;
    char *name;
} Genre;

typedef struct {
    int id;
    char title[MAX_TITLE_LENGTH];
    int num_genres;
    int *genre_ids;
} Movie;

typedef struct {
    int num_genres;
    Genre *genres;
    int num_movies;
    Movie *movies;
} Database;

Database *database;
Genre *genres;
int num_genres;
int num_movies;

void insert_genre(Genre **genres, int *num_genres, char *name) {
    Genre genre = {(*num_genres)++, strdup(name)};
    *genres = realloc(*genres, *num_genres * sizeof(Genre));
    (*genres)[*num_genres - 1] = genre;
}

void insert_movie(Movie **movies, int *num_movies, char *title, int num_genres, int *genre_ids) {
    Movie movie = {(*num_movies)++, "", num_genres, genre_ids};
    strcpy(movie.title, title);
    *movies = realloc(*movies, *num_movies * sizeof(Movie));
    (*movies)[*num_movies - 1] = movie;
}

void free_genres(Genre *genres, int num_genres) {
    for (int i = 0; i < num_genres; i++) {
        free(genres[i].name);
    }
    free(genres);
}

void free_movies(Movie *movies, int num_movies) {
    for (int i = 0; i < num_movies; i++) {
        free(movies[i].genre_ids);
    }
    free(movies);
}

// use for testing/debugging
void initialize_database(Database *database) {
    database->num_genres = 0;
    database->genres = NULL;
    database->num_movies = 0;
    database->movies = NULL;

    // Add some genres
    insert_genre(&database->genres, &database->num_genres, "Action");
    insert_genre(&database->genres, &database->num_genres, "Comedy");
    insert_genre(&database->genres, &database->num_genres, "Drama");

    // Add some movies
    int *genre_ids = malloc(2 * sizeof(int));
    genre_ids[0] = 0; // Action
    genre_ids[1] = 1; // Comedy
    insert_movie(&database->movies, &database->num_movies, "The Hangover", 2, genre_ids);

    genre_ids = malloc(1 * sizeof(int));
    genre_ids[0] = 2; // Drama
    insert_movie(&database->movies, &database->num_movies, "The Shawshank Redemption", 1, genre_ids);
}

void display_genres(Database *database) {
    char *headers[] = {"ID", "Name"};

    char *rows[database->num_genres * 2];

    for (int i = 0; i < database->num_genres; i++) {
        rows[i * 2] = malloc(10 * sizeof(char));
        sprintf(rows[i * 2], "%d", database->genres[i].id);
        rows[i * 2 + 1] = strdup(database->genres[i].name);
    }

    print_table(headers, 2, rows, database->num_genres);

    for (int i = 0; i < database->num_genres; i++) {
        free(rows[i * 2]);
        free(rows[i * 2 + 1]);
    }

    free_genres(database->genres, database->num_genres);

    printf("Press any key to return to the main menu...\n");
    getchar();
}

void display_movies(Database *database) {
    char *headers[] = {"ID", "Title", "Genres"};

    char *rows[database->num_movies * 3];

    for (int i = 0; i < database->num_movies; i++) {
        rows[i * 3] = malloc(10 * sizeof(char));
        sprintf(rows[i * 3], "%d", database->movies[i].id);
        rows[i * 3 + 1] = strdup(database->movies[i].title);

        char *genres = malloc(MAX_TITLE_LENGTH * sizeof(char));
        genres[0] = '\0';

        for (int j = 0; j < database->movies[i].num_genres; j++) {
            strcat(genres, database->genres[database->movies[i].genre_ids[j]].name);
            if (j < database->movies[i].num_genres - 1) {
                strcat(genres, ", ");
            }
        }

        rows[i * 3 + 2] = genres;
    }

    print_table(headers, 3, rows, database->num_movies);

    for (int i = 0; i < database->num_movies; i++) {
        free(rows[i * 3]);
        free(rows[i * 3 + 1]);
        free(rows[i * 3 + 2]);
    }

    printf("Press any key to return to the main menu...\n");
    getchar();
}

void add_genre(Database *database) {
    char name[MAX_TITLE_LENGTH];
    printf("Enter genre name: ");
    scanf("%s", name);
    insert_genre(&database->genres, &database->num_genres, name);
}

void add_movie(Database *database) {
    char title[MAX_TITLE_LENGTH];
    printf("Enter movie title: ");
    scanf("%s", title);

    printf("Select genres for the movie (enter genre IDs separated by spaces, -1 to finish):\n");
    display_genres(database);

    int genre_id;
    int num_genres = 0;
    int *genre_ids = NULL;

    while (true) {
        scanf("%d", &genre_id);
        if (genre_id == -1) {
            break;
        }
        genre_ids = realloc(genre_ids, (num_genres + 1) * sizeof(int));
        genre_ids[num_genres++] = genre_id;
    }

    insert_movie(&database->movies, &database->num_movies, title, num_genres, genre_ids);
}

int main(void) {
    char *answers[] = {"Add Movie", "Remove Movie", "Display Movies", "Add Genre", "Remove Genre", "Display Genres", "Search Movies by Genre", "Exit"};
    char answers_size = sizeof(answers) / sizeof(answers[0]);

    display_title();
    display_description();

    database = malloc(sizeof(Database));
    initialize_database(database);

    int choice = -1;

    do {
        if (choice != -1) clear_screen();
        choice = multiple_choice(answers, 8, false);

        switch (choice) {
            case 0:
                printf("Add Movie\n");
                add_movie(database);
                break;
            case 1:
                printf("Remove Movie\n");
                break;
            case 2:
                printf("Display Movies\n");
                display_movies(database);
                break;
            case 3:
                printf("Add Genre\n");
                add_genre(database);
                break;
            case 4:
                printf("Remove Genre\n");
                break;
            case 5:
                printf("Display Genres\n");
                display_genres(database);
                break;
            case 6:
                printf("Search Movies by Genre\n");
                break;
            case 7:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 7);

    free_genres(database->genres, database->num_genres);
    free_movies(database->movies, database->num_movies);
    free(database);
    exit_program();
}
