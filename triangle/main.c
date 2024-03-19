#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int isRectangle(unsigned int side[3]) {
    if ((side[0])*(side[0]) + (side[1]*side[1]) == (side[2]*side[2])) {
        return 1;
    } else {
        return 0;
    }
};

int main(void) {
    unsigned int side[3];
    unsigned int orderedSide[3];
    printf("Enter first side: ");
    scanf("%d", &side[0]);
    printf("Enter second side: ");
    scanf("%d", &side[1]);
    printf("Enter third side: ");
    scanf("%d", &side[2]);

    for (int i = 0; i < 3; i++) {
        int min = side[0];
        int minIndex = 0;
        for (int j = 0; j < 3; j++) {
            if (side[j] < min) {
                min = side[j];
                minIndex = j;
            }
        }
        orderedSide[i] = min;
        side[minIndex] = 999;
    };

    int quel = 1;

    if(isRectangle(orderedSide)) {
        printf("it's renctangle\n");
        quel = 0;
    };
    if(orderedSide[0] == orderedSide[1] || orderedSide[1] == orderedSide[2]) {
        printf("isocèle\n");
        quel = 0;
    };
    if(orderedSide[0] == orderedSide[1] && orderedSide[1] == orderedSide[2]) {
        printf("équilatéral\n");
        quel = 0;
    };

    if(quel) {
        printf("quelconque");
    };

    return EXIT_SUCCESS;
};