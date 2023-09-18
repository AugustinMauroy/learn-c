#include <stdio.h>
#include <string.h>

int logInfo(char *str) {
    printf("\033[34m[info]\033[0m %s\n", str);
    return 0;
};

int logError(char *str) {
    printf("\033[31m[error]\033[0m %s\n", str);
    return 1;
};

int main() {
    char str[100];
    char result[114];
    logInfo("write your name: ");
    scanf("%[^\n]%*c", str);

    if (strlen(str) > 100) {
        logError("name is too long");
        return 1;
    };

    strcpy(result, "Hello, ");
    strcat(result, str);
    strcat(result, "!");
    
    logInfo(result);

    return 0;
};
