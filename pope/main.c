#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(void) {
    char name[100];
    printf("Enter a string: ");
    fgets(name, 100, stdin);

    FILE *file = fopen("popes.txt", "rt");

    if (file == NULL) {
        printf("Error opening file: popes.txt\n");
        exit(EXIT_FAILURE);
    }

    FILE *rest = fopen("rest.txt", "wt");

    if (rest == NULL) {
        printf("Error opening file: rest.txt\n");
        exit(EXIT_FAILURE);
    }

    char line[100];
    bool found = false;

    while (fgets(line, 100, file) != NULL) {
        printf("line: %s", line);
        printf("name: %s\n\n", name);
        if (strcasecmp(line, name) == 0) {
            found = true;
        } else {
            fputs(line, rest);
        }
    }

    fclose(file);
    fclose(rest);

    name[strlen(name) - 1] = '\0';

    if (found) {
        printf("Pope %s has been removed\n", name);
    } else {
        printf("Pope %s not found\n", name);
    }

    return EXIT_SUCCESS;
};
