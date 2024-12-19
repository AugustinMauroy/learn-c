#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_IP_LIST 1024
#define MAX_IP_LENGTH 16
#define MAX_LINE 4096

bool isInArray(const char *ipaddr, const char ipList[][MAX_IP_LENGTH], size_t count) {
    for (size_t i = 0; i < count; i++) {
        if (strcmp(ipaddr, ipList[i]) == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    FILE *fprt = fopen("access.log", "rt");

    if (fprt == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    char ipaddr[MAX_IP_LIST][MAX_IP_LENGTH], line[MAX_LINE];
    size_t count = 0, i;
    
    // first space means the end of the IP address
    while (fgets(line, MAX_LINE, fprt) != NULL) {
        for (i = 0;  line[i] != ' ' && i < MAX_IP_LENGTH - 1; i++) {
            ipaddr[count][i] = line[i];
        }
        
        ipaddr[count][i] = '\0';

        if (!isInArray(ipaddr[count], ipaddr, count)) count++;
        if (count >= MAX_IP_LIST) break;
    }

    fclose(fprt);

    fprt = fopen("ipaddr.txt", "wt");

    if (fprt == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    // Print all IP addresses
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", ipaddr[i]);
        fprintf(fprt, "%s\n", ipaddr[i]);
    }

    fclose(fprt);

    printf("Total IP addresses: %zu\n", count);

    return EXIT_SUCCESS;
}