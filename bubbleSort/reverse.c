#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX 10

bool inArray(int arr[], int n) {
    for(int i = 0; i < MAX; i++) {
        if(arr[i] == n) {
            return true;
        }
    }
    return false;
}

void displayArray(int arr[]) {
    printf("{");
    for (int i = 0; i < MAX; i++){ 
        printf("\033[0;32m%d\033[0m%s", arr[i], (i == MAX -1) ? "" : ", ");
    }
    printf("}\n");
}

int main(void) {
    int arr[MAX], permutations;
    char user_input;

    srand(time(NULL));

    do {
        printf("Do you want to input your number? (y/n): ");
        scanf(" %c", &user_input);
    } while (user_input != 'y' && user_input != 'n');

    if(user_input == 'y') {
        for(int i = 0; i < MAX; i++) {
            printf("Enter number %d: ", i+1);
            scanf("%d", &arr[i]);
        }
    } else {
        for(int i = 0; i < MAX; i++) {
            int n;
            do {
                n = i%2 == 0 ? rand() % 30 : rand() % 29;
            } while(inArray(arr, n));
            arr[i] = n;
        }
    }


    printf("Not sorted array = ");
    displayArray(arr);

    // bubble Sorting in reverse order
    for (int i = 0; i < MAX - 1; i++) {
        for (int j = 0; j < MAX - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("Sorted array = ");
    displayArray(arr);
    
    return EXIT_SUCCESS;
}
