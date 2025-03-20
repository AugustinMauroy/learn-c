#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 20
#define MAX_NAMES 5

int main(void) {
  char name[MAX_NAME_LENGTH];
  FILE *fptr = fopen("names.bin", "wb+");

  if (fptr == NULL) {
    printf("Error: File not found\n");
    return EXIT_FAILURE;
  }

  for(size_t i = 0; i < MAX_NAMES; i++) {
    printf("Enter a name: ");
    scanf("%s", name);
    fwrite(name, sizeof(char), MAX_NAME_LENGTH, fptr);
  }

  name[0] = '\0';
  
  fseek(fptr, 0, SEEK_SET);
  for (size_t i = 0; i < MAX_NAMES; i++) {
    fread(name, sizeof(char), MAX_NAME_LENGTH, fptr);
    printf("Name: %s\n", name)
  }

  fclose(fptr);

  return EXIT_SUCCESS;
}
