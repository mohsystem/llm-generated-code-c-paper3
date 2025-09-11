#include <stdio.h>
#include <regex.h>

void findMatchingLines(const char* filename) {
    FILE* file = fopen(filename, "r");
    char line[256];
    regex_t regex;
    regcomp(&regex, "^[0-9].*\\.$", REG_EXTENDED);
    while (fgets(line, sizeof(line), file)) {
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
            printf("%s", line);
        }
    }
    fclose(file);
    regfree(&regex);
}

int main() {
    findMatchingLines("file.txt");
    return 0;
}