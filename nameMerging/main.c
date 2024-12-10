#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define INPUT1 "input-1.txt"
#define INPUT2 "input-2.txt"
#define OUTPUT "output.txt"
#define MAX_LINE 200

/*
        1. Lire une ligne de l'entrée 1
        2. Lire une ligne de l'entrée 2
        3. Comparer les deux lignes
        4. Si ligne1 < ligne2, écrire ligne1 et garder la ligne2 en mémoire
        5. Si ligne1 > ligne2, écrire ligne2 et garder la ligne1 en mémoire
        6. Si ligne1 == ligne2, écrire ligne1 et garder la ligne2 en mémoire
        7. Répétez les étapes 3 à 6 jusqu'à ce que l'un des deux fichiers soit terminé et écrivez le reste du fichier non terminé
    */

int main(void){
    FILE *input1, *input2, *output;

    input1 = fopen(INPUT1, "r");
    input2 = fopen(INPUT2, "r");
    output = fopen(OUTPUT, "w");

    if(input1 == NULL){
        perror(INPUT1);
        return EXIT_FAILURE;
    }

    if(input2 == NULL){
        perror(INPUT2);
        return EXIT_FAILURE;
    }

    if(output == NULL){
        perror(OUTPUT);
        return EXIT_FAILURE;
    }

    char linefile1[MAX_LINE], linefile2[MAX_LINE];
    bool endOfFile1 = false, endOfFile2 = false;

    // Lire la première ligne de chaque fichier pour lancé le programme
    fgets(linefile1, MAX_LINE, input1);
    fgets(linefile2, MAX_LINE, input2);

    while(!endOfFile1 || !endOfFile2) {
        if(endOfFile1) {
            while(fgets(linefile2, MAX_LINE, input2) != NULL) {
                fputs(linefile2, output);
            }
            break;
        }
        if(endOfFile2) {
            while(fgets(linefile1, MAX_LINE, input1) != NULL) {
                fputs(linefile1, output);
            }
            break;
        }

        int cmp = strcmp(linefile1, linefile2);

        if(cmp < 0) {
            fputs(linefile1, output);
            if(fgets(linefile1, MAX_LINE, input1) == NULL) {
                endOfFile1 = true;
            }
        } else if(cmp > 0) {
            fputs(linefile2, output);
            if(fgets(linefile2, MAX_LINE, input2) == NULL) {
                endOfFile2 = true;
            }
        } else {
            fputs(linefile1, output);
            if(fgets(linefile1, MAX_LINE, input1) == NULL) {
                endOfFile1 = true;
            }
            if(fgets(linefile2, MAX_LINE, input2) == NULL) {
                endOfFile2 = true;
            }
        }
    }

    fclose(input1);
    fclose(input2);

    if(fclose(output) == EOF){
        perror("fclose");
        return EXIT_FAILURE;
    }

    printf("Files merged successfully\n");

    return EXIT_SUCCESS;
}
