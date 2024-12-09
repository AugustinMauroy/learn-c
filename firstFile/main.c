#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fptr;
    char line[100];

    fptr = fopen("input.txt", "rt");

    if (fptr == NULL) {
        printf("Error opening file\n");
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), fptr) != NULL)
        printf("%s", line);

    fclose(fptr);

    return EXIT_SUCCESS;
}
