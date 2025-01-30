/**
 * @link https://en.wikipedia.org/wiki/List_of_file_signatures
 */
#include <stdlib.h>
#include <stdio.h>

#define MAX_SIG_SIZE 20

// a way to store mime types data and iterate over them
typedef struct {
    unsigned char sig[MAX_SIG_SIZE];
    int sig_length;
    char *mime;
} mime_type;

int main(int argc, char *argv[]) {
    mime_type data_set[] = {
        {
            // rbxl
            {0x3C, 0x72, 0x6F, 0x62, 0x6C, 0x6F, 0x78, 0x21},
            8,
            "application/octet-stream"
        },
        {
            {0x1B, 0x4C, 0x75, 0x61},
            4,
            "application/x-lua-bytecode"
        },
        {
            // iso-mp4
            {0x66, 0x74, 0x79, 0x70, 0x69, 0x73, 0x6F, 0x6D},
            8,
            "ftypiso2",
        },
        {
            // MPEG-4
            {0x66, 0x74, 0x79, 0x70, 0x4D, 0x53, 0x4E, 0x56},
            8,
            "ftypMSNV",
        },
        {
            {0x47, 0x49, 0x46, 0x38, 0x39, 0x61},
            6,
            "image/gif"
        },
        {
            {0xFF, 0xD8, 0xFF, 0xE0},
            4,
            "image/jpeg"
        },
        
        {
            {0xCF, 0xFA, 0xED, 0xFE, 0x0C, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00},
            20,
            "application/octet-stream"
        },
        {
            {37, 80, 68, 70},
            4,
            "application/pdf"
        },
        {
            // https://en.wikipedia.org/wiki/Portable_Network_Graphics
            {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A},
            8,
            "image/png"
        },
        {
            // https://en.wikipedia.org/wiki/ZIP_(file_format)
            {0x50, 0x4B, 0x03, 0x04},
            4,
            "application/zip"
        }
    };

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    unsigned char buffer[MAX_SIG_SIZE];
    size_t readed = fread(buffer, 1, MAX_SIG_SIZE, file);
    fclose(file);


    printf("Signature: ");
    for (int i = 0; i < readed; i++) {
        printf("%02X ", buffer[i]);
    }
    printf("\n");

    for (int i = 0; i < sizeof(data_set) / sizeof(mime_type); i++) {
        int j;
        for (j = 0; j < data_set[i].sig_length; j++) {
            if (data_set[i].sig[j] != buffer[j]) break;
        }

        if (j == data_set[i].sig_length) {
            printf("MIME type: %s\n", data_set[i].mime);
            return EXIT_SUCCESS;
        }
    }

    printf("MIME type not found\n");
    printf("Signature: ");
    for (int i = 0; i < MAX_SIG_SIZE; i++) {
        printf("%02X ", buffer[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
