#include <stdlib.h>
#include <stdio.h>

struct fraction {
    int num;
    int den;
};

typedef struct fraction Fraction;

int GCD(int a, int b) {
    if (b == 0) return a;
    return GCD(b, a % b);
}

int LCM(int a, int b) {
    return (a*b)/GCD(a,b); 
}

Fraction fractionSimplification(Fraction f1, Fraction f2) {
    Fraction result;
    result.num = f1.num * f2.den + f2.num * f1.den;
    result.den = f1.den * f2.den;
    int gcd = GCD(result.num, result.den);
    result.num /= gcd;
    result.den /= gcd;
    return result;
}

int main(void) {
    Fraction f1, f2;

    printf("Enter the first fraction: ");
    scanf("%d/%d", &f1.num, &f1.den);
    printf("Enter the second fraction: ");
    scanf("%d/%d", &f2.num, &f2.den);

    Fraction result = fractionSimplification(f1, f2);

    printf("The sum of the two fractions is: %d/%d\n", result.num, result.den);

    return EXIT_SUCCESS;
}