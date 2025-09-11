#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char** match_lines(const char* file_path, int* count) {
    FILE* file = fopen(file_path, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", file_path);
        *count = 0;
        return NULL;
    }

    char line[256];
    char** matching_lines = NULL;
    *count = 0;
    regex_t regex;
    int reti = regcomp(&regex, "^[0-9]+.*\\.$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        fclose(file);
        return NULL;
    }

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove trailing newline
        regmatch_t match;
        reti = regexec(&regex, line, 1, &match, 0);
        if (!reti) {
            (*count)++;
            matching_lines = realloc(matching_lines, (*count) * sizeof(char*));
            matching_lines[*count - 1] = strdup(line);
        } 
    }
    regfree(&regex);
    fclose(file);
    return matching_lines;
}

int main() {
    for (int i = 1; i <= 5; i++) {
        char filename[20];
        sprintf(filename, "test%d.txt", i);
        int count;
        char** lines = match_lines(filename, &count);
        if (lines) {
            for (int j = 0; j < count; j++) {
                printf("%s\n", lines[j]);
                free(lines[j]);
            }
            free(lines);
        }
        printf("\n");
    }
    return 0;
}