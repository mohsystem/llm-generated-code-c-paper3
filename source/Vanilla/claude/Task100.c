
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_LINE_LENGTH 1024
#define MAX_MATCHES 100

char* findPattern(const char* pattern, const char* filename) {
    regex_t regex;
    char* result = malloc(10000); // Allocate space for results
    result[0] = '\\0';
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        strcpy(result, "Error: Invalid regex pattern");
        return result;
    }
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        strcpy(result, "Error: Unable to open file");
        regfree(&regex);
        return result;
    }
    
    char line[MAX_LINE_LENGTH];
    regmatch_t matches[MAX_MATCHES];
    
    while (fgets(line, sizeof(line), file)) {
        int offset = 0;
        while (regexec(&regex, line + offset, 1, matches, 0) == 0) {
            int len = matches[0].rm_eo - matches[0].rm_so;
            strncat(result, line + offset + matches[0].rm_so, len);
            strcat(result, "\\n");
            offset += matches[0].rm_eo;
        }
    }
    
    fclose(file);
    regfree(&regex);
    return result;
}

int main() {
    // Test cases
    struct {
        const char* pattern;
        const char* filename;
    } testCases[] = {
        {"[[:alnum:]]+@[[:alnum:]]+\\\\.[[:alnum:]]+", "test.txt"},     // Find email addresses
        {"[0-9]{3}-[0-9]{3}-[0-9]{4}", "contacts.txt"},               // Find phone numbers
        {"[A-Z][a-z]*", "names.txt"},                                 // Find capitalized words
        {"[0-9]+\\\\.[0-9]{2}", "prices.txt"},                         // Find prices
        {"https?://[^ \\n]+", "urls.txt"}                             // Find URLs
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Pattern: %s\\n", testCases[i].pattern);
        printf("File: %s\\n", testCases[i].filename);
        printf("Results:\\n");
        char* result = findPattern(testCases[i].pattern, testCases[i].filename);
        printf("%s", result);
        free(result);
        printf("------------------------\\n");
    }
    
    return 0;
}
