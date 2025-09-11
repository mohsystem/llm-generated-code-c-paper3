#include <stdio.h>
#include <stdlib.h>

char* readFileC(const char* filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        return "Error reading file: Unable to open file";
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *content = (char*)malloc(fileSize + 1);
    if (content) {
        fread(content, 1, fileSize, file);
        content[fileSize] = '\0';
    }
    fclose(file);
    return content;
}

int main() {
    char filePath[256];
    printf("Enter file path: ");
    if (fgets(filePath, sizeof(filePath), stdin)) {
        filePath[strcspn(filePath, "\n")] = 0; // Remove newline character
        char *content = readFileC(filePath);
        printf("%s", content);
        free(content);
    }
    return 0;
}