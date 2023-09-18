#include <stdio.h> // printf

void logNumber(int number, char *text) {
    printf("\033[0;32m%d\033[0m %s", number, text);
};

int main() {
    int array[] = {9, 5, 2, 7, 1};
    int sortedArray[sizeof(array) / sizeof(array[0])];


    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        int min = array[0];
        int minIndex = 0;
        for (int j = 0; j < sizeof(array) / sizeof(array[0]); j++) {
            if (array[j] < min) {
                min = array[j];
                minIndex = j;
            }
        }
        sortedArray[i] = min;
        array[minIndex] = 999;
    };

    for (int i = 0; i < sizeof(sortedArray) / sizeof(sortedArray[0]); i++) {
        logNumber(sortedArray[i], "- ");
    };
}
