#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void processFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("File not found: %s\n", fileName);
        return;
    }

    char line[1024];
    regex_t regex;
    regcomp(&regex, "^\\d+.*\\.$", REG_EXTENDED);

    while (fgets(line, sizeof(line), file)) {
        if (!regexec(&regex, line, 0, NULL, 0)) {
            printf("%s", line);
        }
    }

    regfree(&regex);
    fclose(file);
}

int main() {
    const char* testFiles[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    for (int i = 0; i < 5; ++i) {
        printf("Processing file: %s\n", testFiles[i]);
        processFile(testFiles[i]);
    }
    return 0;
}