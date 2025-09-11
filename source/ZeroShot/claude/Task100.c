
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

#define MAX_LINE_LENGTH 1024
#define MAX_MATCHES 100
#define MAX_ERROR_MSG 1024

char* search_pattern(const char* pattern, const char* filename) {
    regex_t regex;
    char* result = malloc(10000); // Allocate memory for result
    if (!result) return "Memory allocation failed";
    result[0] = '\\0';
    
    int reti = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (reti) {
        char error_message[MAX_ERROR_MSG];
        regerror(reti, &regex, error_message, MAX_ERROR_MSG);
        snprintf(result, 9999, "Invalid regex pattern: %s", error_message);
        return result;
    }
    
    FILE* file = fopen(filename, "r");
    if (!file) {
        snprintf(result, 9999, "Error reading file: %s", strerror(errno));
        regfree(&regex);
        return result;
    }
    
    char line[MAX_LINE_LENGTH];
    regmatch_t matches[MAX_MATCHES];
    int line_num = 1;
    int found = 0;
    char temp[MAX_LINE_LENGTH];
    
    while (fgets(line, sizeof(line), file)) {
        int offset = 0;
        while (regexec(&regex, line + offset, 1, matches, 0) == 0) {
            found = 1;
            int len = matches[0].rm_eo - matches[0].rm_so;
            strncpy(temp, line + offset + matches[0].rm_so, len);
            temp[len] = '\\0';
            
            char match_result[MAX_LINE_LENGTH];
            snprintf(match_result, sizeof(match_result), 
                    "Line %d: %s\\n", line_num, temp);
            strcat(result, match_result);
            
            offset += matches[0].rm_eo;
        }
        line_num++;
    }
    
    fclose(file);
    regfree(&regex);
    
    if (!found) {
        strcpy(result, "No matches found");
    }
    
    return result;
}

int main() {
    // Test cases
    const char* patterns[] = {
        "\\\\b[[:alnum:]]+@[[:alnum:]]+\\\\.[[:alnum:]]+\\\\b",  // email pattern
        "\\\\b[0-9]{3}-[0-9]{3}-[0-9]{4}\\\\b", // phone number pattern
        "https?://[^[:space:]]+", // URL pattern
        "\\\\b[A-Z][a-z]+\\\\b", // Capitalized word
        "[0-9]+" // Numbers
    };
    
    const char* files[] = {
        "sample1.txt",
        "sample2.txt",
        "sample3.txt",
        "sample4.txt",
        "sample5.txt"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("\\nTest Case %d:\\n", i+1);
        printf("Pattern: %s\\n", patterns[i]);
        printf("File: %s\\n", files[i]);
        printf("Result:\\n");
        char* result = search_pattern(patterns[i], files[i]);
        printf("%s\\n", result);
        free(result);
    }
    
    return 0;
}
