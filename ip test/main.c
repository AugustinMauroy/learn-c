#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int validateIP(char *ip) {
    int ipArr[4];
    char *token = strtok(ip, ".");
    int i = 0;

    while (token != NULL) {
        ipArr[i] = atoi(token);
        if (ipArr[i] < 0 || ipArr[i] > 255) {
            return 0; // Invalid IP
        }
        token = strtok(NULL, ".");
        i++;
    }

    return (i == 4) ? 1 : 0; // Valid IP should have 4 segments
}

int main() {
    printf("Your first IP: ");
    char ip[100];

    if (fgets(ip, sizeof(ip), stdin) == NULL) {
        printf("Failed to read input.");
        return 1;
    }

    if (!validateIP(ip)) {
        printf("Invalid IP\n");
        return 1;
    }

    printf("Your second IP: ");
    char ip2[100];
    if (fgets(ip2, sizeof(ip2), stdin) == NULL) {
        printf("Failed to read input.");
        return 1;
    }

    if (!validateIP(ip2)) {
        printf("Invalid IP\n");
        return 1;
    }

    printf("Your subnet mask: ");
    char mask[100];
    if (fgets(mask, sizeof(mask), stdin) == NULL) {
        printf("Failed to read input.");
        return 1;
    }

    if (!validateIP(mask) && strcmp(mask, "255.0.0.0\n") != 0) {
        printf("Invalid subnet mask\n");
        return 1;
    }

    // Convert IP strings to integers
    int ipArr[4], ipArr1[4], maskArr[4];
    sscanf(ip, "%d.%d.%d.%d", &ipArr[0], &ipArr[1], &ipArr[2], &ipArr[3]);
    sscanf(ip2, "%d.%d.%d.%d", &ipArr1[0], &ipArr1[1], &ipArr1[2], &ipArr1[3]);
    sscanf(mask, "%d.%d.%d.%d", &maskArr[0], &maskArr[1], &maskArr[2], &maskArr[3]);

    for (int i = 0; i < 4; i++) {
        if ((ipArr[i] & maskArr[i]) != (ipArr1[i] & maskArr[i])) {
            printf("Not in the same network\n");
            return 1;
        }
    }

    printf("In the same network\n");
    return 0;
}
