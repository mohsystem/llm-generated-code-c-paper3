#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <regex> <filename>\n", argv[0]);
        return 1;
    }

    char* regex = argv[1];
    char* filename = argv[2];

    // Security check: Validate the filename to prevent path traversal attacks
    if (strstr(filename, "../") != NULL || strstr(filename, "..\\") != NULL || filename[0] == '/') {
        printf("Invalid filename. Potential path traversal attack.\n");
        return 1;
    }

    regex_t regex_compiled;
    int reti = regcomp(&regex_compiled, regex, REG_EXTENDED);
    if (reti) {
        char msgbuf[100];
        regerror(reti, &regex_compiled, msgbuf, sizeof(msgbuf));
        printf("Invalid regular expression: %s\n", msgbuf);
        return 1;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        regfree(&regex_compiled);
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        if (regexec(&regex_compiled, line, 0, NULL, 0) == 0) {
            printf("Found match: %s\n", line);
        }
    }

    fclose(file);
    regfree(&regex_compiled);

    return 0;
}