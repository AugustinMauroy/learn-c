#include <stdlib.h>
#include <stdio.h>
#include "./textUtils.c"

struct movieTable{
    int id;
    char name[50];
    int genreId;
    // Duration is in minutes
    int duration;
};

struct genreTable{
    int id;
    char name[50];
};


int main(void) {
    displayTitle();
};
