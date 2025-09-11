#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int searchFileWithRegex(const char* regex, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        return 0;
    }
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(fsize + 1);
    fread(content, 1, fsize, file);
    fclose(file);
    content[fsize] = '\0';

    regex_t reg;
    int ret = regcomp(&reg, regex, REG_EXTENDED);
    if (ret) {
        free(content);
        return 0;
    }
    ret = regexec(&reg, content, 0, NULL, 0);
    regfree(&reg);
    free(content);
    return ret == 0;
}

int main() {
    printf("%d\n", searchFileWithRegex("pattern1", "test1.txt"));
    printf("%d\n", searchFileWithRegex("pattern2", "test2.txt"));
    printf("%d\n", searchFileWithRegex("pattern3", "test3.txt"));
    printf("%d\n", searchFileWithRegex("pattern4", "test4.txt"));
    printf("%d\n", searchFileWithRegex("pattern5", "test5.txt"));
    return 0;
}