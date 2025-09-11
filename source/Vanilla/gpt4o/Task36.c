#include <stdio.h>
#include <stdlib.h>

char* readFileContents(const char* filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        return "Error reading file: Unable to open file";
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *content = (char *)malloc(length + 1);
    if (content) {
        fread(content, 1, length, file);
        content[length] = '\0';
    }
    fclose(file);
    return content;
}

int main() {
    const char* testFiles[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    for (int i = 0; i < 5; i++) {
        printf("Contents of %s:\n", testFiles[i]);
        char *content = readFileContents(testFiles[i]);
        printf("%s\n", content);
        free(content);
    }
    return 0;
}