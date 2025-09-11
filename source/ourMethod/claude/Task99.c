
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_LINE_LENGTH 1024

char* findNumberDotLines(const char* filename) {
    char* result = malloc(MAX_LINE_LENGTH * 100); // Allocate space for result
    if (result == NULL) {
        return "Memory allocation error";
    }
    result[0] = '\\0';
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        free(result);
        return "Error opening file";
    }
    
    regex_t regex;
    int ret = regcomp(&regex, "^[0-9].*\\\\.$", REG_EXTENDED);
    if (ret) {
        free(result);
        fclose(file);
        return "Could not compile regex";
    }
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline if present
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\\n') {
            line[len-1] = '\\0';
        }
        
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
            strcat(result, line);
            strcat(result, "\\n");
        }
    }
    
    regfree(&regex);
    fclose(file);
    return result;
}

int main() {
    // Test cases
    const char* testFiles[] = {
        "test1.txt",
        "test2.txt",
        "test3.txt",
        "test4.txt",
        "test5.txt"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Testing file: %s\\n", testFiles[i]);
        char* result = findNumberDotLines(testFiles[i]);
        printf("%s", result);
        printf("-------------------\\n");
        if (result != NULL && strcmp(result, "Memory allocation error") != 0 && 
            strcmp(result, "Error opening file") != 0 && 
            strcmp(result, "Could not compile regex") != 0) {
            free(result);
        }
    }
    
    return 0;
}
