#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char** match_lines(const char* file_path, int* count) {
    char** matching_lines = NULL;
    *count = 0;
    regex_t regex;
    int reti = regcomp(&regex, "^[0-9]+.*\\.$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return NULL;
    }

    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        regfree(&regex);
        return NULL;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0; // Remove trailing newline
        regmatch_t match;
        reti = regexec(&regex, line, 1, &match, 0);
        if (!reti) {
            (*count)++;
            matching_lines = realloc(matching_lines, (*count) * sizeof(char*));
            matching_lines[*count - 1] = strdup(line);

        } else if (reti != REG_NOMATCH) {
            char msgbuf[100];
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            regfree(&regex);
            fclose(file);
            return NULL; // Or handle the error as needed.
        }
    }

    fclose(file);
    regfree(&regex);
    return matching_lines;
}

int main() {
    int count;
    char** lines;

    for(int i = 1; i <= 5; i++){
        char filename[20];
        sprintf(filename, "test%d.txt", i);
        lines = match_lines(filename, &count);

        if(lines != NULL){
            for(int j = 0; j < count; j++){
                printf("%s\n", lines[j]);
                free(lines[j]);
            }
            free(lines);
        }

        printf("\n"); // Add an extra newline for separation
    }



    return 0;
}