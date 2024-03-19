#include <stdio.h>
#include <string.h>

int estPalindrome(char *mot) {
    int stringLenght = strlen(mot);
    for (short unsigned int i = 0; i < stringLenght; i++) {
        if(mot[i] != mot[stringLenght - i]) return 0;
    }
    return 1;
}

int main(void) {
    char mot[100];

    printf("Entrez une chaîne de caractères : ");
    scanf("%s", mot);

    if (estPalindrome(mot)) {
        printf("%s est un palindrome.\n", mot);
    } else {
        printf("%s n'est pas un palindrome.\n", mot);
    }

    return 0;
}
