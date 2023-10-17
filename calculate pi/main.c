#include <stdio.h>

int main(void) {
    int state = 0; // 0= + 1= -
    float pi = 0;
    for(int i = 1; i <= 1000000000; i++) {
        if(state == 0) {
            pi += 4.0 / (i*2-1); // Utilisez 4.0 pour forcer la division en virgule flottante
            state = 1;
        } else {
            pi -= 4.0 / (i*2-1); // Utilisez 4.0 pour forcer la division en virgule flottante
            state = 0;
        }
    }
    printf("pi = %f\n", pi);

    return 0;
}
