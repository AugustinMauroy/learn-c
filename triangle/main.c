#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool isRectangle(unsigned int side[3]) {
    if ((side[0])*(side[0]) + (side[1]*side[1]) == (side[2]*side[2])) {
        return true;
    } else {
        return false;
    }
};

int main(void) {
    unsigned int side[3];
    printf("Enter first side: ");
    scanf("%d", &side[0]);
    printf("Enter second side: ");
    scanf("%d", &side[1]);
    printf("Enter third side: ");
    scanf("%d", &side[2]);

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(side[i] < side[j]) {
                unsigned int temp = side[i];
                side[i] = side[j];
                side[j] = temp;
            };
        };
    };

    bool quel = true;

    if(isRectangle(side)) {
        printf("it's renctangle\n");
        quel = false;
    };
    if(side[0] == side[1] || side[1] == side[2]) {
        printf("isocèle\n");
        quel = false;
    };
    if(side[0] == side[1] && side[1] == side[2]) {
        printf("équilatéral\n");
        quel = false;
    };

    if(quel) {
        printf("quelconque\n");
    };

    return EXIT_SUCCESS;
};
