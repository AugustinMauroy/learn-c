#include <stdio.h>
#include <stdlib.h>

struct vec3{
    float x;
    float y;
    float z;
};

struct vec3 add(struct vec3 a, struct vec3 b) {
    struct vec3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

struct vec3 mul(struct vec3 a, struct vec3 b) {
    struct vec3 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;

    return result;
}

void displayVec3(struct vec3 v, char* name) {
    printf("%s = {\n", name);
    printf("\tx = \033[0;32m%f\033[0m,\n", v.x);
    printf("\ty = \033[0;32m%f\033[0m,\n", v.y);
    printf("\tz = \033[0;32m%f\033[0m\n", v.z);
    printf("};\n");
}

int main(void) {
    struct vec3 a = {1.0f, 2.0f, 3.0f};
    struct vec3 b = {4.0f, 5.0f, 6.0f};

    struct vec3 c = add(a, b);
    struct vec3 d = mul(a, b);
    
    displayVec3(a, "a");
    displayVec3(b, "b");
    displayVec3(c, "a+b");
    displayVec3(d, "a*b");

    return EXIT_SUCCESS;
}
