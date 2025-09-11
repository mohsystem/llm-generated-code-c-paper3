#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <regex_pattern> <file_name>\n", argv[0]);
        return 1;
    }

    char* regexPattern = argv[1];
    char* fileName = argv[2];
    regex_t regex;
    int reti;

    reti = regcomp(&regex, regexPattern, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    FILE* file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "File not found: %s\n", fileName);
        regfree(&regex);
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        reti = regexec(&regex, line, 0, NULL, 0);
        if (!reti) {
            printf("%s", line);
        }
    }

    fclose(file);
    regfree(&regex);
    return 0;
}