#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX 10
#define DELAY 200000 // 200ms delay

bool inArray(int arr[], int n) {
    for(int i = 0; i < MAX; i++) {
        if(arr[i] == n) {
            return true;
        }
    }
    return false;
};

void displayArray(int arr[]) {
  printf("{");
  for (int i = 0; i < MAX; i++){ 
    printf("\033[0;32m%d\033[0m%s", arr[i], (i == MAX -1) ? "" : ", ");
  }
  printf("}\n");
};

void displayBars(int arr[], int selected) {
    for(int i = 0; i < MAX; i++) {
        if(i == selected) {
            printf("\033[0;31m");
        } else {
            printf("\033[0;32m");
        }
        for(int j = 0; j < arr[i]; j++) {
            printf("#");
        }
        printf("\033[0m %d\n", arr[i]);
    }
}

int main(void) {
  int arr[MAX], arrCopy[MAX];
  char user_input;

  srand(time(NULL));

    do {
        printf("Do you want to input your number? (y/n): ");
        scanf("%c", &user_input);
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



    // Selection sort
    for(int i = 0; i<MAX-1; i++) {
        //now search minmun
        int posmin = i;
        for(int j = i; j<MAX; j++){
            if(arr[j] < arr[posmin]){
                posmin = j;
            }
        }
        // swap
        int temp = arr[posmin];
        arr[posmin] = arr[i];
        arr[i] = temp;
        system("clear");
        displayBars(arr, i);
        usleep(DELAY);
    }

    system("clear");
    printf("Not sorted array = ");
    displayArray(arrCopy);
    displayBars(arr, -1);
    printf("Sorted array = ");
    displayArray(arr);

    return EXIT_SUCCESS;
}

