#include <stdio.h>
#include <stdlib.h> 

int main(void) {
    unsigned int i, j, n;

    printf("16 colors\n");
    for (i = 0; i < 11; i++) {
        for (j = 0; j < 10; j++) {
            n = 10 * i + j;
            if (n > 108) break;
            printf(" \033[%dm %3d \033[m", n, n);
        }
        printf("\n");
    }

    printf("\n");

    printf("256 colors\n");
    for (i = 0; i < 256; i++) {
        printf("\033[48;5;%dm %3d \033[m", i, i);
        if (i % 16 == 15) printf("\n");
    }
    printf("\n");

    return EXIT_SUCCESS;
}