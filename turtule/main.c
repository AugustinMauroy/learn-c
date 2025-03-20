#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct point {
    int x;
    int y;
} point;

int main(void) {
    FILE *fptr = fopen("move.txt", "rt");

    if (fptr == NULL) {
        fprintf(stderr, "Error opening file\n");
        return EXIT_FAILURE;
    }

    point p = {0, 0};

    char line[100];

    while (fgets(line, 100, fptr) != NULL) {
        switch (line[0]) {
            case 'H':
                p.y++;
                break;
            case 'B':
                p.y--;
                break;
            case 'G':
                p.x--;
                break;
            case 'D':
                p.x++;
                break;
            default:
								printf("Invalid move: %c\n", line[0]);
                break;
        }
    }

    printf("Position finale: (%d, %d)\n", p.x, p.y);
    assert(p.x == 2);
    assert(p.y == 1);
    

    return EXIT_SUCCESS;
}

