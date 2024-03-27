#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define MAX 10 

bool inArray(int arr[], int n) {
    for(int i = 0; i < MAX; i++) {
        if(arr[i] == n) return true;
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
                n = rand() % 15;
            } while(inArray(arr, n));
            arr[i] = n;
        }
    }

    printf("Not sorted array = ");
    displayArray(arr);

    // Insertion sort in reverse order
    for(int i = 0; i < MAX; i++){
        // find the max value
        int possMax = i;
        for(int j = i; j < MAX; j++){
            if(arr[j] > arr[possMax]){ // Changed condition here
                possMax = j;
            }
        }
        int temp = arr[possMax];
        // offset the array
        for(int j = possMax; j > i; j--){
            arr[j] = arr[j-1];
        }
        // insert the max value
        arr[i] = temp;
    }

    printf("Sorted array in reverse = ");
    displayArray(arr);

    return EXIT_SUCCESS;
}
