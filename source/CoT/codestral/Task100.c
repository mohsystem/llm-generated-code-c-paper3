#include <stdio.h>
#include <regex.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

void searchFile(regex_t* pattern, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Error reading file: %s\n", fileName);
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        if (regexec(pattern, line, 0, NULL, 0) == 0) {
            printf("Match found: %s", line);
        }
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: ./program <regex_pattern> <file_name>\n");
        return 1;
    }

    const char* regexPattern = argv[1];
    const char* fileName = argv[2];

    regex_t pattern;
    int ret = regcomp(&pattern, regexPattern, REG_EXTENDED);
    if (ret) {
        char errorMessage[MAX_LINE_LENGTH];
        regerror(ret, &pattern, errorMessage, sizeof(errorMessage));
        fprintf(stderr, "Invalid regular expression pattern: %s\n", errorMessage);
        return 1;
    }

    searchFile(&pattern, fileName);
    regfree(&pattern);

    return 0;
}