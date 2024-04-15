#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define PI 3.14159265
#define RADIUS 10
#define DELAY 10000

void drawFullCircle(int radius) {
    int x, y;

    for (y = -radius; y <= radius; y++) {
        for (x = -radius; x <= radius; x++) {
            if (sqrt(x*x + y*y) <= radius) {
                printf("██");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void drawCircle(int radius) {
    int x, y;

    for (y = -radius; y <= radius; y++) {
        for (x = -radius; x <= radius; x++) {
            if (sqrt(x*x + y*y) <= radius && sqrt(x*x + y*y) >= radius - 2) {
                printf("██");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void drawCircleWithAngle(int radius, int angle) {
    int x, y;

    for (y = -radius; y <= radius; y++) {
        for (x = -radius; x <= radius; x++) {
            if (sqrt(x*x + y*y) <= radius && sqrt(x*x + y*y) >= radius - 2) {
                // put green dot on the circle to indicate the angle
                // sumary of the condition: if x and y are within 1 unit of the angle
                if (x >= (int)(radius * cos(angle * PI / 180)) - 1 && x <= (int)(radius * cos(angle * PI / 180)) + 1 && y >= (int)(radius * sin(angle * PI / 180)) - 1 && y <= (int)(radius * sin(angle * PI / 180)) + 1) {
                    printf("\033[0;32m██\033[0m");
                } else {
                    printf("██");
                }
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }

}

int main(void) {
    char user_input;
    int i=0;

    system("stty -icanon -echo");
    do {
        system("clear");
        drawCircleWithAngle(RADIUS, i);
        if(i == 360) {
            i = 0;
        } else {
            i++;
        }
        usleep(DELAY);
    } while (1);

    return EXIT_SUCCESS;
}
