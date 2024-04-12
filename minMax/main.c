#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int max4(int a, int b, int c, int d) {
    return max(max(max(a, b), c), d);
}

int maxsecond(int a, int b, int c, int d) {
    return max(
            min(
                max(a, b),
                max(c, d)
            ), 
            min(
                max(a, c),
                max(b, d)
            )
        );
}

int main(void) {
    int a, b, c, d;

    printf("Enter 4 integers: ");
    scanf("%d %d %d %d", &a, &b, &c, &d);
    
    printf("The second largest number is: %d\n", maxsecond(a, b, c, d));
    
    return EXIT_SUCCESS;
}