#include <stdio.h>
#include <regex.h>

int main() {
    char *file_name = "file.txt";
    FILE *file = fopen(file_name, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }
    char line[256];
    regex_t pattern;
    if (regcomp(&pattern, "^[0-9].*\\.$", REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }
    while (fgets(line, sizeof(line), file)) {
        if (!regexec(&pattern, line, 0, NULL, 0)) {
            printf("%s", line);
        }
    }
    fclose(file);
    regfree(&pattern);
    return 0;
}