// clang main.c && ./a.out --source "source.txt" --destination "test"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *src, *dest;

    /**
     * --source or -s is source of the copy file
     * --destination or -d is destination of the copy file
     */
    if (argc != 5 || strcmp(argv[1], "--source") != 0 || strcmp(argv[3], "--destination") != 0) {
        fprintf(stderr, "Usage: %s --source <source_file> --destination <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    src = fopen(argv[2], "r");

    if (src == NULL) {
        perror(argv[2]);
        return EXIT_FAILURE;
    }

    dest = fopen(argv[4], "w");

    if (dest == NULL) {
        perror(argv[4]);
        return EXIT_FAILURE;
    }

    char line[200];

    while (fgets(line, 200, src) != NULL)
        fputs(line, dest);

    fclose(src);

    if (fclose(dest) == EOF) {
        perror("fclose");
        return EXIT_FAILURE;
    }

    printf("File copied successfully\n");

    fclose(dest);
    
    return EXIT_SUCCESS;
}
