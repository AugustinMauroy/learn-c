#include <stdlib.h>
#include <stdio.h>

float imc(float weight, float height) {
    return weight / (height * height);
};

int main(void) {
    float weight, height;
    printf("Enter your weight: ");
    scanf("%f", &weight);
    printf("Enter your height: ");
    scanf("%f", &height);

    float imcValue = imc(weight, height > 3 ? height/100 : height);

    if(imcValue < 16.5) {
        printf("dénutrition");
    } else if (imcValue < 18.5) {
        printf("maigreur");
    } else if (imcValue < 25) {
        printf("poids normal");
    } else if (imcValue < 30) {
        printf("surpoids");
    } else if (imcValue < 35) {
        printf("obésité modérée");
    } else if (imcValue < 40) {
        printf("obésité sévère");
    } else {
        printf("obésité morbide");
    }
    return EXIT_SUCCESS;
};
