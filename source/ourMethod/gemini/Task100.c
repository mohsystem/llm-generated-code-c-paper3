#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void searchFile(const char *regexPattern, const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", fileName);
        return;
    }

    regex_t regex;
    int reti = regcomp(&regex, regexPattern, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        fclose(file);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        regmatch_t match;
        int offset = 0;
        while (regexec(&regex, line + offset, 1, &match, 0) == 0) {
            char *match_str = (char *)malloc(match.rm_eo - match.rm_so + 1);
            strncpy(match_str, line + offset + match.rm_so, match.rm_eo - match.rm_so);
            match_str[match.rm_eo - match.rm_so] = '\0';
            printf("Match found: %s\n", match_str);
            free(match_str);
            offset += match.rm_eo;
        }
    }

    regfree(&regex);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <regex_pattern> <file_name>\n", argv[0]);
        return 1;
    }

    searchFile(argv[1], argv[2]);

        // Test cases
    searchFile("hello", "test1.txt");
    searchFile("\\d+", "test2.txt");
    searchFile("^[a-zA-Z]+$", "test3.txt");
    searchFile("[aeiou]", "test4.txt");
    searchFile(".*error.*", "test5.txt");
    return 0;
}