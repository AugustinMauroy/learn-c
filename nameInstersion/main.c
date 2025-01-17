#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(void) {
    FILE *source = fopen("source.txt", "rt");
    FILE *destination = fopen("destination.txt", "wt");
    bool isSourceExist = source != NULL;
    
    if (!destination) {
        fclose(source);
        return EXIT_FAILURE;
    }

    char name[100];
    printf("Enter a name: ");
    fgets(name, 100, stdin);

    if(isSourceExist) {
        char line[100];
        bool isNameInserted = false;

        while (fgets(line, 100, source)) {
            if (!isNameInserted && strcasecmp(name, line) < 0) {
                fputs(name, destination);
                isNameInserted = true;
            }
            fputs(line, destination);
        }

        if (!isNameInserted) {
            fputs(name, destination);
        }
        
    } else {
        fprintf(destination, "%s", name);
    }

    if (!isSourceExist) {
        fclose(source);
    }
    fclose(destination);

    return EXIT_SUCCESS;
}