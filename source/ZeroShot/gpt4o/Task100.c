#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int searchFileWithPattern(const char* patternStr, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        perror("File not found");
        return 0;
    }

    regex_t regex;
    if (regcomp(&regex, patternStr, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        fclose(file);
        return 0;
    }

    char line[1024];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
            found = 1;
            break;
        }
    }

    regfree(&regex);
    fclose(file);
    return found;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: ./a.out <pattern> <filename>\n");
        return 1;
    }
    printf("%s\n", searchFileWithPattern(argv[1], argv[2]) ? "true" : "false");
    // You can add more test cases below if needed
    return 0;
}