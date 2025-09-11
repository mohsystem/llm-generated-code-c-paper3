#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

// Structure to hold matching lines
typedef struct {
    char** lines;
    int count;
} MatchingLines;


MatchingLines match_lines(const char* file_path) {
    MatchingLines matching_lines = {NULL, 0};
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", file_path);
        return matching_lines; 
    }

    char line[256]; // Adjust buffer size as needed
    regex_t regex;
    int reti;
    reti = regcomp(&regex, "^[0-9]+.*\\.$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        fclose(file); // Close the file in case of regex compilation error
        return matching_lines;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0; // Remove trailing newline
        reti = regexec(&regex, line, 0, NULL, 0);
        if (!reti) {
            matching_lines.count++;
            matching_lines.lines = realloc(matching_lines.lines, matching_lines.count * sizeof(char*));
            matching_lines.lines[matching_lines.count - 1] = strdup(line); 
        } else if (reti != REG_NOMATCH) {
            fprintf(stderr, "Regex match failed\n");
            break; // Stop on regex error
        }
    }

    regfree(&regex);
    fclose(file);
    return matching_lines;
}

void free_matching_lines(MatchingLines matching_lines) {
    for (int i = 0; i < matching_lines.count; i++) {
        free(matching_lines.lines[i]);
    }
    free(matching_lines.lines);
}


int main() {
    MatchingLines test1 = match_lines("test1.txt");
    printf("Test 1: ");
    for (int i = 0; i < test1.count; i++) {
        printf("%s ", test1.lines[i]);
    }
    printf("\n");
    free_matching_lines(test1);


    MatchingLines test2 = match_lines("test2.txt");
    printf("Test 2: ");
    for (int i = 0; i < test2.count; i++) {
        printf("%s ", test2.lines[i]);
    }
    printf("\n");
    free_matching_lines(test2);


    MatchingLines test3 = match_lines("test3.txt");
    printf("Test 3: ");
    for (int i = 0; i < test3.count; i++) {
        printf("%s ", test3.lines[i]);
    }
    printf("\n");
    free_matching_lines(test3);



    MatchingLines test4 = match_lines("test4.txt");
    printf("Test 4: ");
    for (int i = 0; i < test4.count; i++) {
        printf("%s ", test4.lines[i]);
    }
    printf("\n");
    free_matching_lines(test4);

    MatchingLines test5 = match_lines("test5.txt");
    printf("Test 5: ");
    for (int i = 0; i < test5.count; i++) {
        printf("%s ", test5.lines[i]);
    }
    printf("\n");
    free_matching_lines(test5);




    return 0;
}