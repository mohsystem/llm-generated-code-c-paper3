#include <stdio.h>
#include <stdlib.h>

char* readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return "Error: Unable to open file";
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* content = (char*)malloc(length + 1);
    if (content) {
        fread(content, 1, length, file);
        content[length] = '\0';
    }
    fclose(file);
    return content;
}

int main() {
    // Test cases
    printf("%s\n", readFile("test1.txt"));
    printf("%s\n", readFile("test2.txt"));
    printf("%s\n", readFile("test3.txt"));
    printf("%s\n", readFile("test4.txt"));
    printf("%s\n", readFile("test5.txt"));
    return 0;
}