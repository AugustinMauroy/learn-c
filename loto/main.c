#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

void fillArray(int arr[], int input, int limit) {
    for (int i = 0; i < limit; i++) arr[i] = input;
}

bool inArray(int num, int arr[], int index) {
    for (int i = 0; i < index; i++) {
        if (arr[i] == num) return true;
    }
    return false;
}

bool sameArray(int arr1[], int arr2[]) {
    for (int i = 0; i < 6; i++) {
        if (arr1[i] != arr2[i]) return false;
    }
    return true;
}

int main(void) {
    int num[6], input[6], i, temp;
    srand(time(NULL));

    fillArray(input, 0, 6);
    for (i = 0; i < 6; i++) {
        int temp = (rand() % 50)+1;
        if (inArray(temp, num, i)) {
            i--;
        } else {
            num[i] = temp;
        };
    }

    printf("Enter 6 numbers: \n");
    for (i = 0; i < 6; i++) {
        printf("%d: ", i+1);
        do {
            scanf("%d", &temp);
            if (inArray(temp, input, i)) printf("Number already entered, try again: ");
        } while (inArray(temp, input, i));
        input[i] = temp;
    };

    if (!sameArray(num, input)) {
        printf("You lose!\n");
        printf("Correct numbers: ");
        for (i = 0; i < 6; i++) printf("%d ", num[i]);
        return 0;
    };

    printf("You win!\n");
    return 0;
}