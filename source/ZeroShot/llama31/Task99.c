#include <stdio.h>
#include <regex.h>
#include <stdlib.h>

void processFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("File not found: %s\n", filename);
        return;
    }

    regex_t regex;
    if (regcomp(&regex, "^[0-9].*\\.$", 0) != 0) {
        printf("Failed to compile regex\n");
        fclose(file);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
            printf("%s", line);
        }
    }

    regfree(&regex);
    fclose(file);
}

int main() {
    const char* filenames[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    for (int i = 0; i < 5; ++i) {
        processFile(filenames[i]);
    }
    return 0;
}