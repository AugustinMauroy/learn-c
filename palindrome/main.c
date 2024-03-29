#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isPalindrome(char* mot) {
    unsigned int stringLength = strlen(mot);

    for (int i = 0; i < stringLength / 2; i++) {
        if (mot[i] != mot[stringLength - i - 1]) return false;
    }

    return true;
}

int main(void) {
    char mot[100];

    printf("Entrez une chaîne de caractères : ");
    scanf("%s", mot);

    if (isPalindrome(mot)) {
        printf("%s est un palindrome.\n", mot);
    } else {
        printf("%s n'est pas un palindrome.\n", mot);
    }

    return EXIT_SUCCESS;
}
