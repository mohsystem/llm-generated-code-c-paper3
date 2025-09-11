#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <libgen.h>
#include <limits.h>

int isValidFilePath(const char *filePath) {
    regex_t regex;
    int reti;
    reti = regcomp(&regex, "^[a-zA-Z0-9._/\\:-]+$", REG_EXTENDED);
    if (reti) {
        return 0;
    }
    reti = regexec(&regex, filePath, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

void readFile(const char *filePath) {
    if (!isValidFilePath(filePath)) {
        printf("Invalid file path.\n");
        return;
    }

    char realPath[PATH_MAX];
    if (!realpath(filePath, realPath)) {
        printf("An error occurred while resolving the file path.\n");
        return;
    }

    FILE *file = fopen(realPath, "r");
    if (!file) {
        printf("An error occurred while opening the file.\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
}

int main() {
    readFile("test.txt");
    readFile("nonexistent.txt");
    readFile("../test.txt");
    readFile("C:\\Windows\\System32\\test.txt");
    readFile("/etc/passwd");
    return 0;
}