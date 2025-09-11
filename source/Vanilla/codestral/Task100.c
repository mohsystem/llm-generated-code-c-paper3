#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

void search_file(const char* regex_pattern, const char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", file_name);
        return;
    }

    regex_t regex;
    int ret = regcomp(&regex, regex_pattern, REG_EXTENDED);
    if (ret != 0) {
        char error_message[MAX_LINE_LENGTH];
        regerror(ret, &regex, error_message, sizeof(error_message));
        printf("Invalid regex pattern: %s\n", error_message);
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        ret = regexec(&regex, line, 0, NULL, 0);
        if (ret == 0) {
            printf("Found match: %s", line);
        }
    }

    fclose(file);
    regfree(&regex);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: ./Task100 <regex_pattern> <file_name>\n");
        return 1;
    }

    const char* regex_pattern = argv[1];
    const char* file_name = argv[2];

    search_file(regex_pattern, file_name);

    return 0;
}