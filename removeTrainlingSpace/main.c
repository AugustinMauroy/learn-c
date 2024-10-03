#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char sentence[100];
    char clean_sentence[100];

    printf("Enter a sentence: ");
    fgets(sentence, 100, stdin);

    int clean_index = 0;

    for (int i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] != ' ') {
            clean_sentence[clean_index] = sentence[i];
            clean_index++;
        } else if (clean_index > 0 && clean_sentence[clean_index - 1] != ' ') {
            clean_sentence[clean_index] = ' ';
            clean_index++;
        }
    }

    for (int i = clean_index; i < 100; i++) {
        clean_sentence[i] = 0;
    }

    printf("Clean sentence: %s", clean_sentence);

    return EXIT_SUCCESS;
}