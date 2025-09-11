#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void task100(const char *regex, const char *fileName) {
    regex_t pattern;
    if (regcomp(&pattern, regex, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    FILE *file = fopen(fileName, "r");
    if (!file) {
        perror("File not found");
        regfree(&pattern);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        if (!regexec(&pattern, line, 0, NULL, 0)) {
            printf("%s", line);
        }
    }

    free(line);
    fclose(file);
    regfree(&pattern);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./program <regex> <file>\n");
        return 1;
    }

    task100(argv[1], argv[2]);
    return 0;
}