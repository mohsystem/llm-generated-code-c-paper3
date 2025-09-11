#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int searchPatternInFile(const char* pattern, const char* fileName) {
    regex_t compiledPattern;
    int reti;
    char msgbuf[100];
    
    reti = regcomp(&compiledPattern, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }
    
    FILE* file = fopen(fileName, "r");
    if (!file) {
        perror("Error opening file");
        regfree(&compiledPattern);
        return 0;
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        reti = regexec(&compiledPattern, line, 0, NULL, 0);
        if (!reti) {
            printf("Pattern found: %s", line);
            fclose(file);
            regfree(&compiledPattern);
            return 1;
        }
    }
    
    printf("Pattern not found.\n");
    fclose(file);
    regfree(&compiledPattern);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <regex-pattern> <file-name>\n", argv[0]);
        return 1;
    }

    const char* pattern = argv[1];
    const char* fileName = argv[2];

    // Execute test cases
    searchPatternInFile(pattern, fileName);

    return 0;
}