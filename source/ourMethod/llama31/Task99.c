#include <stdio.h>
#include <regex.h>

void readAndMatchLines(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", fileName);
        return;
    }

    char line[1024];
    regex_t regex;
    regcomp(&regex, "^[0-9].*\\.$", REG_EXTENDED);

    while (fgets(line, sizeof(line), file)) {
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
            printf("%s", line);
        }
    }

    regfree(&regex);
    fclose(file);
}

int main() {
    const char* testFiles[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    for (int i = 0; i < 5; i++) {
        readAndMatchLines(testFiles[i]);
    }
    return 0;
}