#include <stdio.h>
#include <regex.h>

void matchLinesInFile(const char* fileName) {
    regex_t regex;
    int ret;
    char buf[1024];
    const char* pattern = "^[0-9].*\\.$";

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    FILE* file = fopen(fileName, "r");
    if (file) {
        while (fgets(buf, sizeof(buf), file) != NULL) {
            ret = regexec(&regex, buf, 0, NULL, 0);
            if (!ret) {
                printf("%s", buf);
            }
        }
        fclose(file);
    } else {
        fprintf(stderr, "Could not open file\n");
    }

    regfree(&regex);
}

int main() {
    matchLinesInFile("input.txt");
    return 0;
}