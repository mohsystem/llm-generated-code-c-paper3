#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void searchFile(const char* regexPattern, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", fileName);
        return;
    }

    regex_t regex;
    if (regcomp(&regex, regexPattern, 0) != 0) {
        fprintf(stderr, "Error compiling regex: %s\n", regexPattern);
        fclose(file);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
            printf("%s", line);
        }
    }

    regfree(&regex);
    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <regex_pattern> <file_name>\n", argv[0]);
        return 1;
    }

    const char* regexPattern = argv[1];
    const char* fileName = argv[2];

    searchFile(regexPattern, fileName);

    return 0;
}