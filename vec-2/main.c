#include <stdio.h>
#include <stdlib.h>

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


int main(void) {
    vec2 a = {1.0f, 2.0f};
    vec2 b = {3.0f, 4.0f};

    vec2 c = add(a, b);
    vec2 d = mul(a, b);

    displayVec2(a, "a");
    displayVec2(b, "b");
    displayVec2(c, "a+b");
    displayVec2(d, "a*b");

    return EXIT_SUCCESS;
}
