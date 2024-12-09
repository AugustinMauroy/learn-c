#include <stdlib.h>
#include <stdio.h>

void displayEratosthenesSieve(int arr[], int max) {
    printf("{");
    for (int i = 0; i < max; i++)
        arr[i] == 1 && printf("\033[0;32m%d\033[0m, ", i);
    printf("}\n");
};


int main(void) {
    int max;

    printf("Enter the maximum number: ");
    scanf("%d", &max);

    int *arr = (int *) malloc(max * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    arr[0] = 0;
    arr[1] = 0;
    for (int i = 2; i < max; i++) {
        arr[i] = 1;
    }

    for (int i = 2; i < max; i++)
        if (arr[i] == 1) 
            for (int j = i + i; j < max; j += i) 
                arr[j] = 0;

    displayEratosthenesSieve(arr, max);
    free(arr);
    
    return EXIT_SUCCESS;
}
