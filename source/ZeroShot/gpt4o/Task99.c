#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void findLinesMatchingPattern(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "An error occurred while opening the file: %s\n", filePath);
        return;
    }

    regex_t regex;
    int reti = regcomp(&regex, "^\\d.*\\.$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        reti = regexec(&regex, line, 0, NULL, 0);
        if (!reti) {
            printf("%s", line);
        }
    }

    regfree(&regex);
    fclose(file);
}

int main() {
    // 5 test cases (provide your own file paths)
    findLinesMatchingPattern("testfile1.txt");
    findLinesMatchingPattern("testfile2.txt");
    findLinesMatchingPattern("testfile3.txt");
    findLinesMatchingPattern("testfile4.txt");
    findLinesMatchingPattern("testfile5.txt");

    return 0;
}