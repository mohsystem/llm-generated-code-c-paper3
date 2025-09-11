
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_LINE_LENGTH 1024
#define MAX_MATCHES 100

char** findMatchingLines(const char* filename, int* matchCount) {
    char** matches = malloc(MAX_MATCHES * sizeof(char*));
    *matchCount = 0;
    
    if (!matches) {
        fprintf(stderr, "Memory allocation failed\\n");
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\\n", filename);
        free(matches);
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "^[0-9].*\\\\.$", REG_EXTENDED) != 0) {
        fprintf(stderr, "Regular expression compilation failed\\n");
        fclose(file);
        free(matches);
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\\n') {
            line[len-1] = '\\0';
        }

        if (regexec(&regex, line, 0, NULL, 0) == 0) {
            if (*matchCount < MAX_MATCHES) {
                matches[*matchCount] = strdup(line);
                if (!matches[*matchCount]) {
                    fprintf(stderr, "Memory allocation failed for match\\n");
                    break;
                }
                (*matchCount)++;
            }
        }
    }

    regfree(&regex);
    fclose(file);
    return matches;
}

int main() {
    const char* testFiles[] = {
        "test1.txt", // Contains: "123 hello world."
        "test2.txt", // Contains: "456 testing."
        "test3.txt", // Contains: "abc 123." (shouldn't match)
        "test4.txt", // Contains: "789 test case."
        "test5.txt"  // Contains: "012 final test."
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Testing file: %s\\n", testFiles[i]);
        int matchCount = 0;
        char** matches = findMatchingLines(testFiles[i], &matchCount);
        
        if (matches) {
            for (int j = 0; j < matchCount; j++) {
                printf("Matched line: %s\\n", matches[j]);
                free(matches[j]);
            }
            free(matches);
        }
        printf("\\n");
    }
    
    return 0;
}
