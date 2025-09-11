#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void searchFile(const char* regexPattern, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "File not found: %s\n", fileName);
        return;
    }

    regex_t regex;
    int reti = regcomp(&regex, regexPattern, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        fclose(file);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        regmatch_t pmatch[1];
        reti = regexec(&regex, line, 1, pmatch, 0);
        if (!reti) {
            printf("Found match: %.*s\n", pmatch[0].rm_eo - pmatch[0].rm_so, line + pmatch[0].rm_so);
        }
    }

    regfree(&regex);
    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <regex_pattern> <file_name>\n", argv[0]);
        return 1;
    }

    const char* regexPattern = argv[1];
    const char* fileName = argv[2];

    searchFile(regexPattern, fileName);

    // Test cases
    const char* testCases[][2] = {
        {"\\d+", "test.txt"},
        {"[a-zA-Z]+", "test.txt"},
        {"\\w+", "test.txt"},
        {"\\d{4}-\\d{2}-\\d{2}", "test.txt"},
        {"[^a-zA-Z0-9]", "test.txt"}
    };

    for (int i = 0; i < 5; ++i) {
        searchFile(testCases[i][0], testCases[i][1]);
    }

    return 0;
}