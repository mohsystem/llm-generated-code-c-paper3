#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

char* createTempFile() {
    setlocale(LC_ALL, "");

    char randomString[50];
    snprintf(randomString, sizeof(randomString), "RandomString%d", rand());

    wchar_t unicodeString[100];
    mbstowcs(unicodeString, randomString, strlen(randomString) + 1);

    char tempFileName[] = "/tmp/tempfile_XXXXXX.txt";
    int fd = mkstemps(tempFileName, 4);
    if (fd == -1) {
        return NULL;
    }

    FILE *tempFile = fdopen(fd, "w");
    if (tempFile == NULL) {
        return NULL;
    }
    fwprintf(tempFile, L"%ls", unicodeString);
    fclose(tempFile);

    char* result = (char*)malloc(strlen(tempFileName) + 1);
    strcpy(result, tempFileName);
    return result;
}

int main() {
    for (int i = 0; i < 5; i++) {
        char* tempFilePath = createTempFile();
        if (tempFilePath != NULL) {
            printf("%s\n", tempFilePath);
            free(tempFilePath);
        }
    }
    return 0;
}