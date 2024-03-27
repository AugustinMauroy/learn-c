#include <stdio.h>
#include <stdlib.h>

struct vec2{
    float x;
    float y;
};

struct vec2 add(struct vec2 a, struct vec2 b) {
    struct vec2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

struct vec2 mul(struct vec2 a, struct vec2 b) {
    struct vec2 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;

    return result;
}

void displayVec2(struct vec2 v, char* name) {
    printf("%s = {\n", name);
    printf("\tx = \033[0;32m%f\033[0m,\n", v.x);
    printf("\ty = \033[0;32m%f\033[0m,\n", v.y);
    printf("};\n");
}


int main(void) {
    struct vec2 a = {1.0f, 2.0f};
    struct vec2 b = {3.0f, 4.0f};

    struct vec2 c = add(a, b);
    struct vec2 d = mul(a, b);

    displayVec2(a, "a");
    displayVec2(b, "b");
    displayVec2(c, "a+b");
    displayVec2(d, "a*b");

    return EXIT_SUCCESS;
}
