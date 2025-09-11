#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generateRandomString(char *dest, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    while (length-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}

void convertToUnicode(const char *input, char *output) {
    while (*input) {
        sprintf(output, "\\u%04x", *input++);
        output += 6;
    }
}

char* createTempFileWithRandomUnicode() {
    char tempFileName[] = "/tmp/tempfileXXXXXX.txt";
    FILE *tempFile = fopen(mktemp(tempFileName), "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        exit(EXIT_FAILURE);
    }

    char randomString[11];
    char unicodeString[61] = "";
    generateRandomString(randomString, 10);
    convertToUnicode(randomString, unicodeString);
    
    fprintf(tempFile, "%s", unicodeString);
    fclose(tempFile);

    char *filePath = (char *)malloc(strlen(tempFileName) + 1);
    strcpy(filePath, tempFileName);
    return filePath;
}

int main() {
    srand((unsigned int) time(NULL));
    for (int i = 0; i < 5; ++i) {
        char *filePath = createTempFileWithRandomUnicode();
        printf("Temporary file created at: %s\n", filePath);
        free(filePath);
    }
    return 0;
}