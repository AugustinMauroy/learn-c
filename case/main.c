#include <stdlib.h>
#include <stdio.h>

// other ways to convert to uppercase and lowercase
char to_upper(char c) {
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    return c;
}

char to_lower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    return c;
}

int main(void) {
    char sentence[80], temp;
    int modified[80];
    printf("Enter a sentence: ");
    fgets(sentence, 80, stdin);

    for (int i = 0; sentence[i] != '\0'; i++)
        modified[i] = 0;


    for (int i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] >= 'A' && sentence[i] <= 'Z') { 
            temp = sentence[i] - 'A' + 'a';
            if (temp != sentence[i]) {
                sentence[i] = temp;
                modified[i] = 1;
            }
        }
        sentence[i] = sentence[i];
    }

    printf("The modified sentence is: ");
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (modified[i] == 1)
            printf("\033[0;31m%c\033[0m", sentence[i]);
        else
            printf("%c", sentence[i]);
    }

    return EXIT_SUCCESS;
}