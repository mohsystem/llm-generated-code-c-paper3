#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

bool isValidFileName(const char* fileName) {
    regex_t regex;
    const char* pattern = "^.+\\.(java|py|c|cpp|cs|js|html|css)$";
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return false;
    }
    int status = regexec(&regex, fileName, 0, NULL, 0);
    regfree(&regex);
    return status == 0;
}

char* readFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        char* error = malloc(strlen(fileName) + 20);
        sprintf(error, "File not found: %s", fileName);
        return error;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* content = malloc(size + 1);
    fread(content, 1, size, file);
    content[size] = '\0';
    fclose(file);
    return content;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./Task65 <filename>\n");
        return 1;
    }

    const char* fileName = argv[1];
    if (!isValidFileName(fileName)) {
        printf("Invalid file name format: %s\n", fileName);
        return 1;
    }

    char* content = readFile(fileName);
    printf("%s\n", content);
    free(content);
    return 0;
}