#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int matchLine(const char* line) {
    regex_t regex;
    int ret;
    ret = regcomp(&regex, "^\\d.*\\.$", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }
    ret = regexec(&regex, line, 0, NULL, 0);
    regfree(&regex);
    return !ret;
}

void readFileAndMatch(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        char line[1024];
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = 0; // Remove newline character
            if (matchLine(line)) {
                printf("Match: %s\n", line);
            }
        }
        fclose(file);
    } else {
        perror("Error reading the file");
    }
}

int main() {
    // Test cases
    readFileAndMatch("test1.txt");
    readFileAndMatch("test2.txt");
    readFileAndMatch("test3.txt");
    readFileAndMatch("test4.txt");
    readFileAndMatch("test5.txt");
    return 0;
}