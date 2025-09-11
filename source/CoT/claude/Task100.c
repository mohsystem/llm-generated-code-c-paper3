
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

#define MAX_LINE_LENGTH 1024
#define MAX_MATCHES 100
#define MAX_ERROR_MSG 1024

char* search_pattern(const char* regex_pattern, const char* file_name) {
    static char result[4096];
    result[0] = '\\0';
    
    // Validate inputs
    if (!regex_pattern || strlen(regex_pattern) == 0) {
        return "Invalid regex pattern";
    }
    
    if (!file_name || strlen(file_name) == 0) {
        return "Invalid file name";
    }
    
    // Compile regex pattern
    regex_t regex;
    int ret = regcomp(&regex, regex_pattern, REG_EXTENDED);
    if (ret) {
        char error_message[MAX_ERROR_MSG];
        regerror(ret, &regex, error_message, MAX_ERROR_MSG);
        snprintf(result, sizeof(result), "Invalid regex pattern syntax: %s", error_message);
        return result;
    }
    
    // Open and validate file
    FILE* file = fopen(file_name, "r");
    if (!file) {
        regfree(&regex);
        snprintf(result, sizeof(result), "Error opening file: %s", strerror(errno));
        return result;
    }
    
    // Process file
    char line[MAX_LINE_LENGTH];
    regmatch_t matches[MAX_MATCHES];
    int found = 0;
    size_t result_pos = 0;
    
    while (fgets(line, sizeof(line), file)) {
        size_t line_len = strlen(line);
        if (line_len > 0 && line[line_len-1] == '\\n') {
            line[line_len-1] = '\\0';
        }
        
        size_t offset = 0;
        while (offset < strlen(line)) {
            ret = regexec(&regex, line + offset, MAX_MATCHES, matches, 0);
            if (ret == REG_NOMATCH) {
                break;
            }
            
            found = 1;
            int match_len = matches[0].rm_eo - matches[0].rm_so;
            char match[MAX_LINE_LENGTH];
            strncpy(match, line + offset + matches[0].rm_so, match_len);
            match[match_len] = '\\0';
            
            result_pos += snprintf(result + result_pos, sizeof(result) - result_pos,
                                 "Match found: %s\\n", match);
            
            offset += matches[0].rm_eo;
        }
    }
    
    fclose(file);
    regfree(&regex);
    
    if (!found) {
        return "No matches found";
    }
    
    return result;
}

int main() {
    // Test cases
    printf("Test Case 1:\\n");
    printf("%s\\n\\n", search_pattern("[0-9]+", "test.txt"));
    
    printf("Test Case 2:\\n");
    printf("%s\\n\\n", search_pattern("[a-zA-Z]+", "sample.txt"));
    
    printf("Test Case 3:\\n");
    printf("%s\\n\\n", search_pattern(NULL, "test.txt"));
    
    printf("Test Case 4:\\n");
    printf("%s\\n\\n", search_pattern("[0-9]+", "nonexistent.txt"));
    
    printf("Test Case 5:\\n");
    printf("%s\\n", search_pattern("[", "test.txt"));
    
    return 0;
}
