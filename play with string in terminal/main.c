#include <stdio.h> // printf, fgets, stdin
#include <string.h> // strlen, strcpy, strcat, strcspn
#include <stdlib.h> // malloc, free
#include <ctype.h> // toupper, tolower

void logInfo(const char *str) {
    printf("\033[34m[info]\033[0m %s\n", str);
}

void logError(const char *str) {
    printf("\033[31m[error]\033[0m %s\n", str);
}

void logWarning(const char *str) {
    printf("\033[33m[warning]\033[0m %s\n", str);
}

void removeAtIndex(char *str, int index) {
    int len = strlen(str);
    if (index < 0 || index >= len) {
        return;
    }

    for (int i = index; i < len - 1; i++) {
        str[i] = str[i + 1];
    }
    str[len - 1] = '\0';

}

int main() {
    char str[100];
    char *result;
    logInfo("Write your full name: ");
    
    if (fgets(str, sizeof(str), stdin) == NULL) {
        logError("Failed to read input.");
        return 1;
    }

    // Remove trailing newline character
    str[strcspn(str, "\n")] = '\0';

    if (strlen(str) > 100) {
        logError("Name is too long");
        return 1;
    }

    // Remove unnecessary spaces
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ' ' && (i == 0 || str[i + 1] == ' ')) {
            removeAtIndex(str, i);
            i--; // Reduce index to check the next character
        }
    }

    if (strlen(str) == 0) {
        logError("Name is empty");
        return 1;
    }

    for (int i = 0; i < strlen(str); i++) {
        if (i == 0 || str[i - 1] == ' ') {
            str[i] = toupper(str[i]);
        } else {
            str[i] = tolower(str[i]);
        }
    }

    result = (char *)malloc(strlen(str) + 8); // 8 = strlen("Hello, ") + strlen("!") + 1
    if (result == NULL) {
        logError("Memory allocation failed.");
        return 1;
    }

    strcpy(result, "Hello, ");
    strcat(result, str);
    strcat(result, "!");

    logInfo(result);

    free(result); // Free memory

    return 0;
}
