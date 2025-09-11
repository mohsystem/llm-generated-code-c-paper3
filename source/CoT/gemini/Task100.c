#include <stdio.h>
#include <string.h>
#include <regex.h>

void search_file(const char *regex, const char *filename) {
    regex_t compiled_regex;
    regmatch_t match;
    char line[1024];
    FILE *file;

    int reti = regcomp(&compiled_regex, regex, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        regfree(&compiled_regex);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        int offset = 0;
        while (regexec(&compiled_regex, line + offset, 1, &match, 0) == 0) {
            printf("Match found: %.*s\n", (int)(match.rm_eo - match.rm_so), line + offset + match.rm_so);
            offset += match.rm_eo;
        }
    }

    fclose(file);
    regfree(&compiled_regex);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <regex> <filename>\n", argv[0]);
        return 1;
    }

    search_file(argv[1], argv[2]);


    // Test cases (assuming test.txt exists with appropriate content)
    search_file("hello", "test.txt");
    search_file("\\d+", "test.txt");
    search_file("[a-zA-Z]+", "test.txt");
    search_file("^\\s*$", "test.txt"); // Matches empty lines. May need adjustments for newline handling
    search_file(".*", "test.txt"); // Matches any line.


    return 0;
}