#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void searchFile(const char* regexPattern, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "Error: File '%s' not found.\n", fileName);
        return;
    }

    regex_t regex;
    regcomp(&regex, regexPattern, REG_EXTENDED);

    char line[1024];
    int lineNumber = 1;
    while (fgets(line, sizeof(line), file)) {
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
            printf("Found match at line %d: %s", lineNumber, line);
        }
        lineNumber++;
    }

    regfree(&regex);
    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <regex_pattern> <file_name>\n", argv[0]);
        return 1;
    }

    const char* regexPattern = argv[1];
    const char* fileName = argv[2];

    searchFile(regexPattern, fileName);

    // Test cases
    const char* testCases[][2] = {
        {"hello", "test.txt"},
        {"world", "test.txt"},
        {"foo", "nonexistent.txt"},
        {"bar", "test.txt"},
        {"baz", "test.txt"}
    };

    for (int i = 0; i < 5; ++i) {
        searchFile(testCases[i][0], testCases[i][1]);
    }

    return 0;
}