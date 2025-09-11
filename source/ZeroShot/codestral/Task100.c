#include <stdio.h>
#include <regex.h>
#include <string.h>

void searchPattern(const char* regex, const char* fileName) {
    regex_t pattern;
    int ret = regcomp(&pattern, regex, REG_EXTENDED);
    if (ret) {
        char errorMessage[100];
        regerror(ret, &pattern, errorMessage, sizeof(errorMessage));
        printf("Invalid regular expression pattern: %s\n", errorMessage);
        return;
    }

    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("Error opening file: %s\n", fileName);
        regfree(&pattern);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        ret = regexec(&pattern, line, 0, NULL, 0);
        if (!ret) {
            printf("Match found: %s\n", line);
        }
    }

    fclose(file);
    regfree(&pattern);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <regex> <filename>\n", argv[0]);
        return 1;
    }
    searchPattern(argv[1], argv[2]);
    return 0;
}