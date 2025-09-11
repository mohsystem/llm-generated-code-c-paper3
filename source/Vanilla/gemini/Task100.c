#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void findMatches(const char *regex, const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    regex_t re;
    int reti;

    reti = regcomp(&re, regex, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        fclose(file);
        return;
    }


    while ((read = getline(&line, &len, file)) != -1) {
        regmatch_t match;
        int offset = 0;

        while (regexec(&re, line + offset, 1, &match, 0) == 0) {
            for (int i = match.rm_so; i < match.rm_eo; i++) {
                putchar(line[offset + i]);
            }
            putchar('\n');
            offset += match.rm_eo;
        }
    }

    if (line)
        free(line);
    fclose(file);
    regfree(&re);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <regex> <filename>\n", argv[0]);
        return 1;
    }

    findMatches(argv[1], argv[2]);


    // Test cases (assuming a file "test.txt" exists with appropriate content):
    findMatches("hello", "test.txt");
    findMatches("\\d+", "test.txt");
    findMatches("[A-Z]+", "test.txt");
    findMatches("^[a-z]+", "test.txt");
    findMatches("\\b\\w+\\b", "test.txt");



    return 0;
}