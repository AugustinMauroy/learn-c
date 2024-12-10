#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT1 "input-1.txt"
#define INPUT2 "input-2.txt"
#define OUTPUT "output.txt"
#define MAX_LINE 200
#define VPL_MOODLE 1

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

    // Lire la première ligne de chaque fichier pour lancé le programme
    fgets(linefile1, MAX_LINE, input1);
    fgets(linefile2, MAX_LINE, input2);

    while(!feof(input1) && !feof(input2)){
        int cmp = strcmp(linefile1, linefile2);

        if(cmp < 0) {
            fputs(linefile1, output);
            fgets(linefile1, MAX_LINE, input1);
        } else if(cmp > 0) {
            fputs(linefile2, output);
            fgets(linefile2, MAX_LINE, input2);
        } else {
            fputs(linefile1, output);
            fgets(linefile1, MAX_LINE, input1);
        }
    }

    if(feof(input1)){
        while(fgets(linefile2, MAX_LINE, input2) != NULL){
            fputs(linefile2, output);
        }
    } else {
        while(fgets(linefile1, MAX_LINE, input1) != NULL){
            fputs(linefile1, output);
        }
    }

    fclose(input1);
    fclose(input2);

    if(fclose(output) == EOF){
        perror("fclose");
        return EXIT_FAILURE;
    }

    printf("\nFiles merged successfully\n");

    output = fopen(OUTPUT, "r");

    if(output == NULL){
        perror(OUTPUT);
        return EXIT_FAILURE;
    }

    #if VPL_MOODLE
    printf("%s:", OUTPUT);
    printf("\n------------------------------------------------\n");
    while(fgets(linefile1, MAX_LINE, output) != NULL){
        printf("%s", linefile1);
    }
    printf("\n------------------------------------------------\n");
    #endif

    return EXIT_SUCCESS;
}
