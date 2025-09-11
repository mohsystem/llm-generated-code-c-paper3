#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>

wchar_t *getRandomString(int length) {
    srand(time(NULL));
    wchar_t *randomString = malloc((length + 1) * sizeof(wchar_t));
    for (int i = 0; i < length; ++i) {
        randomString[i] = (wchar_t)(32 + rand() % 95);
    }
    randomString[length] = L'\0';
    return randomString;
}

wchar_t *stringToUnicode(const wchar_t *input) {
    int length = wcslen(input);
    wchar_t *unicodeString = malloc((length * 6 + 1) * sizeof(wchar_t));
    wchar_t *temp = unicodeString;
    for (int i = 0; i < length; ++i) {
        swprintf(temp, 7, L"\\u%04x", (int)input[i]);
        temp += 6;
    }
    *temp = L'\0';
    return unicodeString;
}

char *createTemporaryFile() {
    setlocale(LC_ALL, "");
    wchar_t *randomString = getRandomString(10);
    wchar_t *unicodeString = stringToUnicode(randomString);
    char *utf8String = wcstombs(NULL, unicodeString, wcslen(unicodeString) * 6 + 1);
    if (utf8String == NULL) {
        fprintf(stderr, "Failed to convert unicode string to UTF-8\n");
        exit(1);
    }
    char tempFileName[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(tempFileName);
    if (fd == -1) {
        fprintf(stderr, "Failed to create temporary file\n");
        exit(1);
    }
    close(fd);
    FILE *outFile = fopen(tempFileName, "wb");
    fwrite(utf8String, sizeof(char), strlen(utf8String), outFile);
    fclose(outFile);
    free(randomString);
    free(unicodeString);
    free(utf8String);
    return strdup(tempFileName);
}

int main() {
    char *tempFileName = createTemporaryFile();
    printf("%s\n", tempFileName);
    free(tempFileName);
    return 0;
}