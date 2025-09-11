#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generateRandomString(char* str, size_t length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    size_t charsetSize = strlen(charset);
    for (size_t i = 0; i < length; ++i) {
        int key = rand() % charsetSize;
        str[i] = charset[key];
    }
    str[length] = '\0';
}

void convertToUnicode(const char* str, char* unicodeStr) {
    while (*str) {
        sprintf(unicodeStr, "\\u%04X", *str++);
        unicodeStr += strlen(unicodeStr);
    }
}

char* createTempFileWithUnicodeString() {
    char* tempPath = tmpnam(NULL);
    if (!tempPath) {
        perror("Failed to generate temporary file name");
        exit(EXIT_FAILURE);
    }

    FILE* tempFile = fopen(tempPath, "w");
    if (!tempFile) {
        perror("Could not open temporary file");
        exit(EXIT_FAILURE);
    }

    char randomString[11];
    generateRandomString(randomString, 10);

    char unicodeString[100] = {0};
    convertToUnicode(randomString, unicodeString);

    fprintf(tempFile, "%s", unicodeString);
    fclose(tempFile);

    return tempPath;
}

int main() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 5; ++i) {
        char* path = createTempFileWithUnicodeString();
        printf("%s\n", path);
    }
    return 0;
}