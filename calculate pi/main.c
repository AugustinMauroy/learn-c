#include <stdio.h>
#include <stdlib.h>

int main(void) {
    double pi = 0;
    for(size_t i = 1; i <= 1000000000000000000; i++) {
        if(i % 2 == 0) {
            pi -= 4.0 / (i*2-1); // Utilisez 4.0 pour forcer la division en virgule flottante
        } else {
            pi += 4.0 / (i*2-1); // Utilisez 4.0 pour forcer la division en virgule flottante
        }    
        printf("actuel = %f\n", pi);
    }
    printf("pi = %f\n", pi);
    return EXIT_SUCCESS;
}
