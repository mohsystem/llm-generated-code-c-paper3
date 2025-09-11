#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

// Structure to hold matched lines
typedef struct {
    char** lines;
    int count;
} MatchedLines;


// Function to match lines in a file
MatchedLines match_lines(const char* file_path) {
    MatchedLines matched = {NULL, 0};
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        return matched; // Return empty structure on file open error
    }

    regex_t regex;
    int reti = regcomp(&regex, "^[0-9]+.*\\.$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        fclose(file);
        return matched;
    }


    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) {
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
            matched.count++;
            matched.lines = realloc(matched.lines, matched.count * sizeof(char*));
            matched.lines[matched.count - 1] = strdup(line); // Allocate memory and copy
        }
    }
    
    free(line);
    fclose(file);
    regfree(&regex);
    return matched;
}

int main() {
    // Test Cases
    MatchedLines result1 = match_lines("test1.txt");
    MatchedLines result2 = match_lines("test2.txt");
    MatchedLines result3 = match_lines("test3.txt");
    MatchedLines result4 = match_lines("test4.txt");
    MatchedLines result5 = match_lines("test5.txt");


    for (int i = 0; i < result1.count; i++) {
      printf("%s", result1.lines[i]);
      free(result1.lines[i]); 
    }
    free(result1.lines);
    printf("\n");

    for (int i = 0; i < result2.count; i++) {
        printf("%s", result2.lines[i]);
        free(result2.lines[i]);
    }
    free(result2.lines);
    printf("\n");

    // ... (similarly for result3, result4, result5) ...
        for (int i = 0; i < result3.count; i++) {
        printf("%s", result3.lines[i]);
        free(result3.lines[i]);
    }
    free(result3.lines);
    printf("\n");

    for (int i = 0; i < result4.count; i++) {
        printf("%s", result4.lines[i]);
        free(result4.lines[i]);
    }
    free(result4.lines);
    printf("\n");

    for (int i = 0; i < result5.count; i++) {
        printf("%s", result5.lines[i]);
        free(result5.lines[i]);
    }
    free(result5.lines);
    printf("\n");

    return 0;
}