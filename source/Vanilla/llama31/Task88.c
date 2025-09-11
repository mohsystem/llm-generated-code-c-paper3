#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generateRandomString(int length) {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char* randomString = malloc(length + 1);
    if (!randomString) return NULL;

    srand(time(NULL));
    for (int i = 0; i < length; ++i) {
        randomString[i] = characters[rand() % (sizeof(characters) - 1)];
    }
    randomString[length] = '\0';
    return randomString;
}

char* createTempFileWithUtf8Encoding() {
    char tempFileName[] = "/tmp/temp_XXXXXX.txt";
    int fd = mkstemp(tempFileName);
    if (fd == -1) return NULL;

    FILE* file = fdopen(fd, "w");
    if (!file) {
        close(fd);
        return NULL;
    }

    char* randomString = generateRandomString(10);
    if (randomString) {
        fprintf(file, "%s", randomString);
        free(randomString);
    }

    fclose(file);
    return strdup(tempFileName);
}

int main() {
    for (int i = 0; i < 5; ++i) {
        char* filePath = createTempFileWithUtf8Encoding();
        if (filePath) {
            printf("Temporary File Path: %s\n", filePath);
            free(filePath);
        }
    }
    return 0;
}