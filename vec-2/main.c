#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct vec2 {
    float x;
    float y;
};

typedef struct vec2 vec2;

vec2 add(vec2 a, vec2 b) {
    vec2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

vec2 mul(vec2 a, vec2 b) {
    vec2 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;

    return result;
}

void displayVec2(vec2 v, char* name) {
    printf("%s = {\n", name);
    printf("\tx = \033[0;32m%f\033[0m,\n", v.x);
    printf("\ty = \033[0;32m%f\033[0m,\n", v.y);
    printf("};\n");
}

float distance(vec2 a, vec2 b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

int main(void) {
    vec2 a = {1.0, 2.0};
    vec2 b = {3.0, 4.0};

    vec2 c = add(a, b);
    vec2 d = mul(a, b);

    displayVec2(a, "a");
    displayVec2(b, "b");
    displayVec2(c, "a+b");
    displayVec2(d, "a*b");

    printf("Distance between a and b: %d\n", distance(a, b));

    return EXIT_SUCCESS;
}
