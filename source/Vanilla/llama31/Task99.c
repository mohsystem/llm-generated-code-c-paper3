#include <stdio.h>
#include <regex.h>

void processFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("File not found: %s\n", filename);
        return;
    }
    char line[1024];
    regex_t regex;
    int reti;
    const char* pattern = "^[0-9].*\\.$";
    reti = regcomp(&regex, pattern, 0);
    if (reti) {
        printf("Could not compile regex\n");
        return;
    }
    while (fgets(line, sizeof(line), file)) {
        reti = regexec(&regex, line, 0, NULL, 0);
        if (!reti) {
            printf("%s", line);
        }
    }
    fclose(file);
    regfree(&regex);
}

int main() {
    const char* filenames[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    for (int i = 0; i < 5; ++i) {
        processFile(filenames[i]);
    }
    return 0;
}