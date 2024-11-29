/**
 * Afficher une string à partir d'un pointeur
 * mais seulement au à partir du 3ème caractère
 * chaine de caractère provenant de l'utilisateur
 */
#include <stdio.h>
#include <stdlib.h>

void displayFromFirstSpace(char *str) {
    int i = 0;
    while (str[i] != ' ') i++;
    i++;
    while (str[i] != '\0') {
        printf("%c", str[i]);
        i++;
    }
}

int main(void) {
    char str[100];
    printf("Entrez une chaine de caractère: ");
    fgets(str, 100, stdin);
    displayFromFirstSpace(str);
    
    return EXIT_SUCCESS;
}
