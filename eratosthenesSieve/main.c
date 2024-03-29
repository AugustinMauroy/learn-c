#include <stdlib.h>
#include <stdio.h>

#define MAX 1000

void displayEratosthenesSieve(int arr[], int max) {
    printf("{");
    for (int i = 0; i < max; i++){ 
        if (arr[i] == 1) {
            printf("\033[0;32m%d\033[0m%s", i, (i == max -1) ? "" : ", ");
        } else {
            printf("\033[0;31m\033[9m%d\033[0m%s", i, (i == max -1) ? "" : ", ");
        }
    }
    printf("}\n");
};


int main(void) {
    int arr[MAX];

    arr[0] = 0;
    arr[1] = 0;
    for (int i = 2; i < MAX; i++) {
        arr[i] = 1;
    }

    for (int i = 2; i < MAX; i++) {
        if (arr[i] == 1) {
            for (int j = i + i; j < MAX; j += i) {
                arr[j] = 0;
            }
        }
    }

    displayEratosthenesSieve(arr, MAX);

    return EXIT_SUCCESS;
}
