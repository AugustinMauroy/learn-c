#include <stdlib.h>
#include <stdio.h>

int possibleCurrency[7]= {500, 100, 50, 10, 5, 2, 1};
#define ARRAY_LENGTH 7

int main(void){
    int inputValue;

    do {
        printf("Enter a number: \033[0;32m");
        scanf("%d", &inputValue);
        printf("\033[0;37m");
        if(inputValue < 0 ) {
            printf("You cannot input negative value");
        }
    } while(inputValue < 0);
    
    for(int i =0 ; i < ARRAY_LENGTH; i++){        
        printf("You got \033[0;32m%d\033[0;37m currency of \033[0;32m%d\033[0;37m €\n", inputValue / possibleCurrency[i], possibleCurrency[i]);
        inputValue = inputValue % possibleCurrency[i];
    };

    return EXIT_SUCCESS;
};
