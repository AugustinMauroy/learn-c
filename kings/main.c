#include <stdio.h>
#include <stdlib.h> 

typedef struct {
    char name[20];
    int next; // is the number that represent the position of the next king in the file
} King;

int main(void) {
		FILE *file;

		file = fopen("kings.dat", "rb");

		if (file == NULL) {
			printf("Error: File not found\n");
			return EXIT_FAILURE;
		};

		// take first king
		// then take next king by using the offset
		King king;
		int offset = 0;
		fread(&king, sizeof(King), 1, file);

		while (king.next != -1) {
			printf("King: %s\n", king.name);
			offset = king.next * sizeof(King);
			fseek(file, offset, SEEK_SET);
			fread(&king, sizeof(King), 1, file);
		};
		
		fclose(file);	

    return EXIT_SUCCESS;
}

