#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX 20
#define DELAY 100000 // 0.1s 

bool inArray(int arr[], int n) {
    for(int i = 0; i < MAX; i++) {
        if(arr[i] == n) return true;
    }
    return false;
};

void toggleCursor(int show) {
    if (show) {
        printf("\e[?25h");
    } else {
        printf("\e[?25l");
    }
}

void displayArray(int arr[]) {
    printf("{");
    for (int i = 0; i < MAX; i++){
        printf("\033[0;32m%d\033[0m%s", arr[i], (i == MAX -1) ? "" : ", ");
    }
    printf("}\n");
};

void displayBars(int arr[], int selected) {
    system("clear");
    toggleCursor(0);
    for(int i = 0; i < MAX; i++) {
        if(i == selected) {
            printf("\033[0;31m");
        } else {
            printf("\033[0;32m");
        }
        for(int j = 0; j < arr[i]; j++) {
            printf("█");
        }
        printf("\033[0m %d\n", arr[i]);
    }
    toggleCursor(1);
}

int main(void) {
    int arr[MAX], arrCopy[MAX];
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
			arrCopy[i] = n;
        }
    }

    // insertion sort
    for(int i = 1; i < MAX; i++){
        int j = i;
        while (j > 0 && arr[j] < arr[j - 1]) {
            int temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
            j--;
            displayBars(arr, j);
            usleep(DELAY);
        }
    }

    printf("Not sorted array = ");
    displayArray(arrCopy);
    displayBars(arr, -1);
    printf("Sorted array = ");
    displayArray(arr);

    return EXIT_SUCCESS;
};
