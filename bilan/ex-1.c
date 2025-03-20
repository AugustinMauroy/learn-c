#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 20
#define MAX_NAMES 7

int main(void) {
  //char name[MAX_NAME_LENGTH];
  char c;
  FILE *fptr = fopen("exemple.bin", "rb");

  if (fptr == NULL) {
    printf("Error: File not found\n");
    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < MAX_NAMES; i++) {
    /*fread(name, sizeof(char), MAX_NAME_LENGTH, fptr);
    printf("Name: %s\n", name);*/
    while ((c = fgetc(fptr)) != EOF) {
      printf("%c", c);
    }
  }

  fclose(fptr);

  return EXIT_SUCCESS;
}
