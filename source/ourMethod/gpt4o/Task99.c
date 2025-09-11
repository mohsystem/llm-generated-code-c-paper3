#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_LINE_LENGTH 1024

void find_matching_lines(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    regex_t regex;
    const char *pattern = "^\\d.*\\.$";
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        perror("Failed to compile regex");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline character
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
            printf("%s\n", line);
        }
    }

    regfree(&regex);
    fclose(file);
}

int main() {
    const char *test_file_path = "test.txt";
    // Assuming test.txt exists and is accessible.

    find_matching_lines(test_file_path);

    return 0;
}